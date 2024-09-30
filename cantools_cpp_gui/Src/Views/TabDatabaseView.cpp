#include "TabDatabaseView.hpp"

enum {
    ID_LoadDBC = 1001  // Event ID for the Load DBC button
};

// Event table to handle the button click event
wxBEGIN_EVENT_TABLE(TabDatabaseView, wxPanel)
EVT_BUTTON(ID_LoadDBC, TabDatabaseView::OnLoadDBC)
wxEND_EVENT_TABLE()

TabDatabaseView::TabDatabaseView(wxNotebook* parent)
    : wxPanel(parent, wxID_ANY)
{
    SetupLayout();
}

void TabDatabaseView::SetupLayout()
{
    // Horizontal box sizer to align the load button and file path field
    wxBoxSizer* hBoxTop = new wxBoxSizer(wxHORIZONTAL);
    filePathCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(600, -1));
    loadDBCButton = new wxButton(this, ID_LoadDBC, "Load DBC");

    hBoxTop->Add(filePathCtrl, 1, wxEXPAND | wxALL, 5);
    hBoxTop->Add(loadDBCButton, 0, wxEXPAND | wxALL, 5);

    // Grid for CAN messages
    messagesGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(600, 150));
    messagesGrid->CreateGrid(5, 5); // Placeholder grid with 5 rows and 5 columns
    messagesGrid->SetColLabelValue(0, "ID");
    messagesGrid->SetColLabelValue(1, "Name");
    messagesGrid->SetColLabelValue(2, "DLC");
    messagesGrid->SetColLabelValue(3, "Transmitter");
    messagesGrid->SetColLabelValue(4, "CycleTime");

    // Grid for CAN signals
    signalsGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(600, 300));
    signalsGrid->CreateGrid(10, 10); // Placeholder grid with 10 rows and 10 columns
    signalsGrid->SetColLabelValue(0, "ID");
    signalsGrid->SetColLabelValue(1, "Name");
    signalsGrid->SetColLabelValue(2, "StartBit");
    signalsGrid->SetColLabelValue(3, "Length");
    signalsGrid->SetColLabelValue(4, "ByteOrder");
    signalsGrid->SetColLabelValue(5, "IsSigned");
    signalsGrid->SetColLabelValue(6, "InitialValue");
    signalsGrid->SetColLabelValue(7, "Factor");
    signalsGrid->SetColLabelValue(8, "Offset");
    signalsGrid->SetColLabelValue(9, "Minimum");

    // List control for CAN nodes
    nodesList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(600, 100), wxLC_REPORT);
    nodesList->InsertColumn(0, "Node Name", wxLIST_FORMAT_LEFT, 200);
    nodesList->InsertColumn(1, "Details", wxLIST_FORMAT_LEFT, 400);

    // Vertical box sizer for overall layout
    wxBoxSizer* vBox = new wxBoxSizer(wxVERTICAL);
    vBox->Add(hBoxTop, 0, wxEXPAND | wxALL, 5);
    vBox->Add(nodesList, 0, wxEXPAND | wxALL, 5);
    vBox->Add(messagesGrid, 0, wxEXPAND | wxALL, 5);
    vBox->Add(signalsGrid, 1, wxEXPAND | wxALL, 5);

    // Set the sizer for this panel
    this->SetSizerAndFit(vBox);
}

void TabDatabaseView::OnLoadDBC(wxCommandEvent& event)
{
    // Handle DBC file loading with a file dialog
    wxFileDialog openFileDialog(this, _("Open DBC file"), "", "",
        "DBC files (*.dbc)|*.dbc|All files (*.*)|*.*",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user canceled the operation

    wxString filePath = openFileDialog.GetPath();
    filePathCtrl->SetValue(filePath);

    // You can now load and parse the DBC file here...
    PopulateData();
}

void TabDatabaseView::PopulateData()
{
    // Placeholder for populating CAN data after DBC file load
    // This can be updated later to load real CAN messages, signals, and nodes
    nodesList->InsertItem(0, "NEO");
    nodesList->SetItem(0, 1, "Transmitting");

    messagesGrid->SetCellValue(0, 0, "0x488");
    messagesGrid->SetCellValue(0, 1, "DAS_steeringCmd");
    messagesGrid->SetCellValue(0, 2, "8");
    messagesGrid->SetCellValue(0, 3, "NEO");
    messagesGrid->SetCellValue(0, 4, "0");

    signalsGrid->SetCellValue(0, 0, "0x488");
    signalsGrid->SetCellValue(0, 1, "DAS_steeringAngle");
    signalsGrid->SetCellValue(0, 2, "31");
    signalsGrid->SetCellValue(0, 3, "12");
    signalsGrid->SetCellValue(0, 4, "0");
}
