/**
 * @file TabDatabaseView.cpp
 *
 * @author Long Pham
 * @date 10/03/2024
 */

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
#include "CANNode.hpp"
#include "CANMessage.hpp"
#include "IView.hpp"

class CANViewModel;

class TabDatabaseView : public IView
{
public:
    TabDatabaseView(wxNotebook* parent);

    void OnLoadDBC(wxCommandEvent& event);  // Event handler for loading a DBC file
    void PopulateData(std::vector<std::shared_ptr<cantools_cpp::CANNode>> nodes, std::vector<std::shared_ptr<cantools_cpp::CANMessage>> messages, std::string busName);                    // Placeholder for populating CAN data
    void OnGridLabelLeftClick(wxGridEvent& event);
    void OnMessageGridCellChange(wxGridEvent& event);
    void OnSignalGridCellChange(wxGridEvent& event);

    virtual void UpdateMessageGrid(std::string busName, uint32_t messageId) override;
    virtual void UpdateSignalGrid(std::string busName, uint32_t messageId, std::string signalName) override;

    void setViewModel(std::shared_ptr<CANViewModel> _canViewModel);

    virtual void Update(std::vector<std::shared_ptr<cantools_cpp::CANNode>> nodes, std::vector<std::shared_ptr<cantools_cpp::CANMessage>> messages, std::string busName) override;

private:
    wxTextCtrl* _filePathCtrl;               // Text control to show the loaded file path
    wxButton* _loadDBCButton;                // Button to load the DBC file
    wxGrid* _messagesGrid;                   // Grid for displaying CAN messages
    wxGrid* _signalsGrid;                    // Grid for displaying CAN signals
    wxListCtrl* _nodesList;                  // List control for nodes

    std::shared_ptr<CANViewModel> _canViewModel;

    std::string _currentBusName;

    void SetupLayout();                     // Method to set up the layout

    wxDECLARE_EVENT_TABLE();
};
