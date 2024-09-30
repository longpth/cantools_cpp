#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <wx/button.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>

class TabDatabaseView : public wxPanel
{
public:
    TabDatabaseView(wxNotebook* parent);

    void OnLoadDBC(wxCommandEvent& event);  // Event handler for loading a DBC file
    void PopulateData();                    // Placeholder for populating CAN data

private:
    wxTextCtrl* filePathCtrl;               // Text control to show the loaded file path
    wxButton* loadDBCButton;                // Button to load the DBC file
    wxGrid* messagesGrid;                   // Grid for displaying CAN messages
    wxGrid* signalsGrid;                    // Grid for displaying CAN signals
    wxListCtrl* nodesList;                  // List control for nodes

    void SetupLayout();                     // Method to set up the layout

    wxDECLARE_EVENT_TABLE();
};
