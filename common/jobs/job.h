/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2022 Mark Roszko <mark.roszko@gmail.com>
 * Copyright (C) 1992-2022 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JOB_H
#define JOB_H

/**
 * An simple container class that lets us dispatch output jobs to kifaces
 */
class JOB
{
public:
    JOB( const std::string& aType, bool aIsCli ) : m_type( aType ), m_isCli( aIsCli ) {}

    virtual ~JOB() {}

    const std::string& GetType() const { return m_type; };
    bool IsCli() const { return m_isCli; };

private:
    std::string m_type;
    bool m_isCli;
};

#endif