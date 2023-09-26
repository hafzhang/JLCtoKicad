/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2017 Jon Evans <jon@craftyjon.com>
 * Copyright (C) 2017-2019 KiCad Developers, see AUTHORS.txt for contributors.
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

#include "tool/tool_action.h"
#include <bitmaps.h>

#include <cvpcb_mainframe.h>
#include <listboxes.h>
#include <tools/cvpcb_actions.h>

// Actions, being statically-defined, require specialized I18N handling.  We continue to
// use the _() macro so that string harvesting by the I18N framework doesn't have to be
// specialized, but we don't translate on initialization and instead do it in the getters.

#undef _
#define _(s) s


// Selection tool action for the footprint viewer window
// No description, it is not supposed to be shown anywhere
TOOL_ACTION CVPCB_ACTIONS::selectionActivate( TOOL_ACTION_ARGS()
        .Name( "cvpcb.FootprintViewerInteractiveSelection" )
        .Scope( AS_GLOBAL )
        .Flags( AF_ACTIVATE ) );

// No description, it is not supposed to be shown anywhere
TOOL_ACTION CVPCB_ACTIONS::controlActivate( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Control" )
        .Scope( AS_GLOBAL )
        .Flags( AF_ACTIVATE ) );


// Action to show the footprint viewer window
TOOL_ACTION CVPCB_ACTIONS::showFootprintViewer( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Control.ShowFootprintViewer" )
        .Scope( AS_GLOBAL )
        .MenuText( _( "View selected footprint" ) )
        .Tooltip( _( "View the selected footprint in the footprint viewer" ) )
        .Icon( BITMAPS::show_footprint ) );


// Actions to handle management tasks
TOOL_ACTION CVPCB_ACTIONS::showEquFileTable( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Control.ShowEquFileTable" )
        .Scope( AS_GLOBAL )
        .MenuText( _( "Manage Footprint Association Files" ) )
        .Tooltip( _( "Configure footprint association file (.equ) list.  These files are "
           "used to automatically assign footprint names from symbol values." ) ) );

TOOL_ACTION CVPCB_ACTIONS::saveAssociationsToSchematic( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Control.SaveAssociationsToSchematic" )
        .Scope( AS_GLOBAL )
        .DefaultHotkey( MD_CTRL + 'S' )
        .LegacyHotkeyName( "Save" )
        .MenuText( _( "Save to Schematic" ) )
        .Tooltip( _( "Save footprint associations in schematic symbol footprint fields" ) )
        .Icon( BITMAPS::save ) );

TOOL_ACTION CVPCB_ACTIONS::saveAssociationsToFile( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Control.SaveAssociationsToFile" )
        .Scope( AS_GLOBAL )
        .DefaultHotkey( MD_CTRL + 'S' )
        .LegacyHotkeyName( "Save" )
        .MenuText( _( "Save to Schematic and File" ) )
        .Tooltip( _( "Save footprint associations in schematic symbol footprint fields and schematic files" ) )
        .Icon( BITMAPS::save ) );

// Actions to navigate the display
TOOL_ACTION CVPCB_ACTIONS::changeFocusRight( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Control.changeFocusRight" )
        .Scope( AS_GLOBAL )
        .DefaultHotkey( WXK_TAB )
        .Flags( AF_NONE )
        .Parameter( CVPCB_MAINFRAME::CHANGE_FOCUS_RIGHT ) );

TOOL_ACTION CVPCB_ACTIONS::changeFocusLeft( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Control.changeFocusLeft" )
        .Scope( AS_GLOBAL )
        .DefaultHotkey( MD_SHIFT + WXK_TAB )
        .Flags( AF_NONE )
        .Parameter( CVPCB_MAINFRAME::CHANGE_FOCUS_LEFT ) );

// Actions to navigate the component list
TOOL_ACTION CVPCB_ACTIONS::gotoNextNA( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Control.GotoNextNA" )
        .Scope( AS_GLOBAL )
        .MenuText( _( "Select next unassigned symbol" ) )
        .Tooltip( _( "Select next symbol with no footprint assignment" ) )
        .Icon( BITMAPS::right )
        .Flags( AF_NONE )
        .Parameter( CVPCB_MAINFRAME::ITEM_NEXT ) );

TOOL_ACTION CVPCB_ACTIONS::gotoPreviousNA( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Control.GotoPreviousNA" )
        .Scope( AS_GLOBAL )
        .MenuText( _( "Select previous unassigned symbol" ) )
        .Tooltip( _( "Select previous symbol with no footprint assignment" ) )
        .Icon( BITMAPS::left )
        .Flags( AF_NONE )
        .Parameter( CVPCB_MAINFRAME::ITEM_PREV ) );


// Actions to modify component associations
TOOL_ACTION CVPCB_ACTIONS::associate( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Association.Associate" )
        .Scope( AS_GLOBAL )
        .DefaultHotkey( WXK_RETURN )
        .MenuText( _( "Assign footprint" ) )
        .Tooltip( _( "Assign footprint to selected symbols" ) )
        .Icon( BITMAPS::auto_associate ) );

TOOL_ACTION CVPCB_ACTIONS::autoAssociate( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Association.AutoAssociate" )
        .Scope( AS_GLOBAL )
        .MenuText( _( "Automatically assign footprints" ) )
        .Tooltip( _( "Perform automatic footprint assignment" ) )
        .Icon( BITMAPS::auto_associate ) );

TOOL_ACTION CVPCB_ACTIONS::deleteAssoc( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Association.Delete" )
        .Scope( AS_GLOBAL )
        .DefaultHotkey( WXK_DELETE )
        .MenuText( _( "Delete association" ) )
        .Tooltip( _( "Delete selected footprint associations" ) )
        .Icon( BITMAPS::delete_association ) );

TOOL_ACTION CVPCB_ACTIONS::deleteAll( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Association.DeleteAll" )
        .Scope( AS_GLOBAL )
        .MenuText( _( "Delete all footprint associations" ) )
        .Tooltip( _( "Delete all footprint associations" ) )
        .Icon( BITMAPS::delete_association ) );


// Actions to filter the footprint list
TOOL_ACTION CVPCB_ACTIONS::FilterFPbyFPFilters( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Control.FilterFPbyFPFilters" )
        .Scope( AS_GLOBAL )
        .MenuText( _( "Use symbol footprint filters" ) )
        .Tooltip( _( "Filter footprint list by footprint filters defined in the symbol" ) )
        .Icon( BITMAPS::module_filtered_list )
        .Flags( AF_NONE )
        .Parameter( FOOTPRINTS_LISTBOX::FILTERING_BY_COMPONENT_FP_FILTERS ) );

TOOL_ACTION CVPCB_ACTIONS::filterFPbyPin( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Control.FilterFPByPin" )
        .Scope( AS_GLOBAL )
        .MenuText( _( "Filter by pin count" ) )
        .Tooltip( _( "Filter footprint list by pin count" ) )
        .Icon( BITMAPS::module_pin_filtered_list )
        .Flags( AF_NONE )
        .Parameter( FOOTPRINTS_LISTBOX::FILTERING_BY_PIN_COUNT ) );

TOOL_ACTION CVPCB_ACTIONS::FilterFPbyLibrary( TOOL_ACTION_ARGS()
        .Name( "cvpcb.Control.FilterFPbyLibrary" )
        .Scope( AS_GLOBAL )
        .MenuText( _( "Filter by library" ) )
        .Tooltip( _( "Filter footprint list by library" ) )
        .Icon( BITMAPS::module_library_list )
        .Flags( AF_NONE )
        .Parameter( FOOTPRINTS_LISTBOX::FILTERING_BY_LIBRARY ) );
