#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <wx/button.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include "CANBusManager.hpp"
#include "CANBus.hpp"
#include "Parser.hpp"

class TabDatabaseView : public wxPanel
{
public:
    TabDatabaseView(wxNotebook* parent);

    void OnLoadDBC(wxCommandEvent& event);  // Event handler for loading a DBC file
    void PopulateData(const std::string filePath);                    // Placeholder for populating CAN data

private:
    wxTextCtrl* _filePathCtrl;               // Text control to show the loaded file path
    wxButton* _loadDBCButton;                // Button to load the DBC file
    wxGrid* _messagesGrid;                   // Grid for displaying CAN messages
    wxGrid* _signalsGrid;                    // Grid for displaying CAN signals
    wxListCtrl* _nodesList;                  // List control for nodes
    std::shared_ptr<cantools_cpp::CANBusManager> _busManager;  // Shared pointer to CANBusManager
    std::unique_ptr<cantools_cpp::Parser> _parser;              // Unique pointer to Parser

    void SetupLayout();                     // Method to set up the layout

    wxDECLARE_EVENT_TABLE();
};
