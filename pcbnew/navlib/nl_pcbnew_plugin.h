/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2021 3Dconnexion
 * Copyright (C) 2021 KiCad Developers, see AUTHORS.txt for contributors.
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

/**
 * @file  nl_pcbnew_plugin.h
 * @brief Declaration of the NL_PCBNEW_PLUGIN class
 */

#ifndef NL_PCBNEW_PLUGIN_H_
#define NL_PCBNEW_PLUGIN_H_

// Forward declarations.
class PCB_DRAW_PANEL_GAL;
class NL_PCBNEW_PLUGIN_IMPL;

/**
 * The class that implements the public interface to the SpaceMouse plug-in.
 */
class NL_PCBNEW_PLUGIN
{
public:
    /**
     * Initializes a new instance of the NL_3DVIEWER_PLUGIN.
     *
     *  @param aViewport is the viewport to be navigated.
     */
    NL_PCBNEW_PLUGIN( PCB_DRAW_PANEL_GAL* aViewport );

    virtual ~NL_PCBNEW_PLUGIN();

    /**
     * Set the connection to the 3Dconnexion driver to the focus state so that
     * 3DMouse data is routed to this connexion.
     *
     * @param aFocus is true to set the connexion active.
     */
    void SetFocus( bool aFocus );

private:
    NL_PCBNEW_PLUGIN_IMPL* m_impl;
};

#endif // NL_PCBNEW_PLUGIN_H_
