/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2019-2020 Thomas Pointhuber <thomas.pointhuber@gmx.at>
 * Copyright (C) 2020-2023 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef ALTIUM_PARSER_H
#define ALTIUM_PARSER_H

#include <map>
#include <memory>
#include <numeric>

#include <wx/gdicmn.h>
#include <math/vector2d.h>
#include <vector>


namespace CFB
{
class CompoundFileReader;
struct COMPOUND_FILE_ENTRY;
} // namespace CFB

/**
 * Helper for debug logging (vector -> string)
 * @param aVectorPath path
 * @return path formatted as string
 */
std::string FormatPath( const std::vector<std::string>& aVectorPath );


class ALTIUM_COMPOUND_FILE
{
public:
    /**
     * Open a CFB file. Constructor might throw an IO_ERROR.
     *
     * @param aFilePath path to file to open
     */
    ALTIUM_COMPOUND_FILE( const wxString& aFilePath );
    ALTIUM_COMPOUND_FILE( const ALTIUM_COMPOUND_FILE& temp_obj ) = delete;
    ALTIUM_COMPOUND_FILE& operator=( const ALTIUM_COMPOUND_FILE& temp_obj ) = delete;
    ~ALTIUM_COMPOUND_FILE() = default;

    const CFB::CompoundFileReader& GetCompoundFileReader() const { return *m_reader; }

    std::map<wxString, wxString> ListLibFootprints() const;

    wxString FindLibFootprintDirName( const wxString& aFpUnicodeName ) const;

    const CFB::COMPOUND_FILE_ENTRY* FindStream( const std::vector<std::string>& aStreamPath ) const;

    const CFB::COMPOUND_FILE_ENTRY* FindStreamSingleLevel( const CFB::COMPOUND_FILE_ENTRY* aEntry,
                                                           const std::string               aName,
                                                           const bool aIsStream ) const;

private:
    std::unique_ptr<CFB::CompoundFileReader> m_reader;
    std::vector<char>                        m_buffer;
};


class ALTIUM_PARSER
{
public:
    ALTIUM_PARSER( const ALTIUM_COMPOUND_FILE& aFile, const CFB::COMPOUND_FILE_ENTRY* aEntry );
    ALTIUM_PARSER( std::unique_ptr<char[]>& aContent, size_t aSize );
    ~ALTIUM_PARSER() = default;

    template <typename Type>
    Type Read()
    {
        const size_t remainingBytes = GetRemainingBytes();
        if( remainingBytes >= sizeof( Type ) )
        {
            Type val = *(Type*) ( m_pos );
            m_pos += sizeof( Type );
            return val;
        }
        else
        {
            m_pos += remainingBytes; // Ensure remaining bytes are zero
            m_error = true;
            return 0;
        }
    }

    template <typename Type>
    Type Peek()
    {
        char* const oldPos = m_pos;
        const bool  oldError = m_error;
        Type        result = Read<Type>();
        m_pos = oldPos;
        m_error = oldError;
        return result;
    }

    wxScopedCharBuffer ReadCharBuffer()
    {
        uint8_t len = Read<uint8_t>();
        if( GetRemainingBytes() >= len )
        {
            char* buf = new char[len];
            memcpy( buf, m_pos, len );
            m_pos += len;

            return wxScopedCharBuffer::CreateOwned( buf, len );
        }
        else
        {
            m_error = true;
            return wxScopedCharBuffer();
        }
    }

    wxString ReadWxString()
    {
        // TODO: Identify where the actual code page is stored. For now, this default code page
        //       has limited impact, because recent Altium files come with a UTF16 string table
        return wxString( ReadCharBuffer(), wxConvISO8859_1 );
    }

    std::map<uint32_t, wxString> ReadWideStringTable()
    {
        std::map<uint32_t, wxString> table;
        size_t                       remaining = GetRemainingBytes();

        while( remaining >= 8 )
        {
            uint32_t index = Read<uint32_t>();
            uint32_t length = Read<uint32_t>();
            wxString str;
            remaining -= 8;

            if( length <= 2 )
                length = 0; // for empty strings, not even the null bytes are present
            else
            {
                if( length > remaining )
                    break;

                str = wxString( m_pos, wxMBConvUTF16LE(), length - 2 );
            }

            table.emplace( index, str );
            m_pos += length;
            remaining -= length;
        }

        return table;
    }

    std::vector<char> ReadVector( size_t aSize )
    {
        if( aSize > GetRemainingBytes() )
        {
            m_error = true;
            return {};
        }
        else
        {
            std::vector<char> data( m_pos, m_pos + aSize );
            m_pos += aSize;
            return data;
        }
    }

    int ReadBytes( char* aOut, size_t aSize )
    {
        if( aSize > GetRemainingBytes() )
        {
            m_error = true;
            return 0;
        }
        else
        {
            memcpy( aOut, m_pos, aSize );
            m_pos += aSize;
            return aSize;
        }
    }

    int32_t ReadKicadUnit()
    {
        return ConvertToKicadUnit( Read<int32_t>() );
    }

    int32_t ReadKicadUnitX()
    {
        return ReadKicadUnit();
    }

    int32_t ReadKicadUnitY()
    {
        return -ReadKicadUnit();
    }

    VECTOR2I ReadVector2IPos()
    {
        int32_t x = ReadKicadUnitX();
        int32_t y = ReadKicadUnitY();
        return { x, y };
    }

    VECTOR2I ReadVector2ISize()
    {
        int32_t x = ReadKicadUnit();
        int32_t y = ReadKicadUnit();
        return { x, y };
    }

    size_t ReadAndSetSubrecordLength()
    {
        uint32_t length = Read<uint32_t>();
        m_subrecord_end = m_pos + length;
        return length;
    }

    std::map<wxString, wxString> ReadProperties();

    static int32_t ConvertToKicadUnit( const double aValue );

    static int ReadInt( const std::map<wxString, wxString>& aProps,
                        const wxString& aKey, int aDefault );

    static double ReadDouble( const std::map<wxString, wxString>& aProps,
                              const wxString& aKey, double aDefault );

    static bool ReadBool( const std::map<wxString, wxString>& aProps,
                          const wxString& aKey, bool aDefault );

    static int32_t ReadKicadUnit( const std::map<wxString, wxString>& aProps,
                                  const wxString& aKey, const wxString& aDefault );

    static wxString ReadString( const std::map<wxString, wxString>& aProps,
                                const wxString& aKey, const wxString& aDefault );

    static wxString ReadUnicodeString( const std::map<wxString, wxString>& aProps,
                                       const wxString& aKey, const wxString& aDefault );

    void Skip( size_t aLength )
    {
        if( GetRemainingBytes() >= aLength )
        {
            m_pos += aLength;
        }
        else
        {
            m_error = true;
        }
    }

    void SkipSubrecord()
    {
        if( m_subrecord_end == nullptr || m_subrecord_end < m_pos )
        {
            m_error = true;
        }
        else
        {
            m_pos = m_subrecord_end;
        }
    };

    size_t GetRemainingBytes() const
    {
        return m_pos == nullptr ? 0 : m_size - ( m_pos - m_content.get() );
    }

    size_t GetRemainingSubrecordBytes() const
    {
        return m_pos == nullptr || m_subrecord_end == nullptr || m_subrecord_end <= m_pos ?
                       0 :
                       m_subrecord_end - m_pos;
    };

    bool HasParsingError()
    {
        return m_error;
    }

private:
    std::unique_ptr<char[]> m_content;
    size_t                  m_size;

    char* m_pos;           // current read pointer
    char* m_subrecord_end; // pointer which points to next subrecord start
    bool  m_error;
};


#endif //ALTIUM_PARSER_H
