#include "TabDatabaseView.hpp"
#include <wx/filename.h>

enum {
    ID_LoadDBC = 1001  // Event ID for the Load DBC button
};

// Event table to handle the button click event
wxBEGIN_EVENT_TABLE(TabDatabaseView, wxPanel)
EVT_BUTTON(ID_LoadDBC, TabDatabaseView::OnLoadDBC)
wxEND_EVENT_TABLE()

TabDatabaseView::TabDatabaseView(wxNotebook* parent)
    : wxPanel(parent, wxID_ANY), _busManager(std::make_shared<cantools_cpp::CANBusManager>()),
    _parser(std::make_unique<cantools_cpp::Parser>(_busManager)) // Initialize parser with bus manager
{
    SetupLayout();
}

void TabDatabaseView::SetupLayout()
{
    // Horizontal box sizer to align the load button and file path field
    wxBoxSizer* hBoxTop = new wxBoxSizer(wxHORIZONTAL);
    _filePathCtrl = new wxTextCtrl(this, wxID_ANY, "..//..//..//..//cantools_cpp//DbcFiles//tesla_can.dbc", wxDefaultPosition, wxSize(600, -1));
    _loadDBCButton = new wxButton(this, ID_LoadDBC, "Load DBC");

    hBoxTop->Add(_filePathCtrl, 1, wxEXPAND | wxALL, 5);
    hBoxTop->Add(_loadDBCButton, 0, wxEXPAND | wxALL, 5);

    // Grid for CAN messages
    _messagesGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(600, 150));
    _messagesGrid->CreateGrid(5, 5); // Placeholder grid with 5 rows and 5 columns
    _messagesGrid->SetColLabelValue(0, "ID");
    _messagesGrid->SetColLabelValue(1, "Name");
    _messagesGrid->SetColLabelValue(2, "DLC");
    _messagesGrid->SetColLabelValue(3, "Transmitter");
    _messagesGrid->SetColLabelValue(4, "CycleTime");

    // Grid for CAN signals
    _signalsGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(600, 300));
    _signalsGrid->CreateGrid(10, 10); // Placeholder grid with 10 rows and 10 columns
    _signalsGrid->SetColLabelValue(0, "ID");
    _signalsGrid->SetColLabelValue(1, "Name");
    _signalsGrid->SetColLabelValue(2, "StartBit");
    _signalsGrid->SetColLabelValue(3, "Length");
    _signalsGrid->SetColLabelValue(4, "ByteOrder");
    _signalsGrid->SetColLabelValue(5, "IsSigned");
    _signalsGrid->SetColLabelValue(6, "InitialValue");
    _signalsGrid->SetColLabelValue(7, "Factor");
    _signalsGrid->SetColLabelValue(8, "Offset");
    _signalsGrid->SetColLabelValue(9, "Minimum");

    // List control for CAN nodes
    _nodesList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(600, 100), wxLC_REPORT);
    _nodesList->InsertColumn(0, "Node Name", wxLIST_FORMAT_LEFT, 200);
    _nodesList->InsertColumn(1, "Details", wxLIST_FORMAT_LEFT, 400);

    // Vertical box sizer for overall layout
    wxBoxSizer* vBox = new wxBoxSizer(wxVERTICAL);
    vBox->Add(hBoxTop, 0, wxEXPAND | wxALL, 5);
    vBox->Add(_nodesList, 0, wxEXPAND | wxALL, 5);
    vBox->Add(_messagesGrid, 0, wxEXPAND | wxALL, 5);
    vBox->Add(_signalsGrid, 1, wxEXPAND | wxALL, 5);

    // Set the sizer for this panel
    this->SetSizerAndFit(vBox);
}

void TabDatabaseView::OnLoadDBC(wxCommandEvent& event)
{
    // Check if the file path control is empty
    if (_filePathCtrl->GetValue().IsEmpty()) {
        // Handle DBC file loading with a file dialog
        wxFileDialog openFileDialog(this, _("Open DBC file"), "", "",
            "DBC files (*.dbc)|*.dbc|All files (*.*)|*.*",
            wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        if (openFileDialog.ShowModal() == wxID_CANCEL)
            return; // the user canceled the operation

        wxString filePath = openFileDialog.GetPath();
        _filePathCtrl->SetValue(filePath);

        // Call PopulateData with the file path
        PopulateData(filePath.ToStdString()); // Convert wxString to std::string
    }
    else {
        // If the file path control is not empty, get the current path and populate data
        PopulateData(_filePathCtrl->GetValue().ToStdString()); // Convert wxString to std::string
    }
}

void TabDatabaseView::PopulateData(const std::string filePath)
{
    // Load database from file
    _parser->loadDBC(filePath);

    // Extract the bus name from the file name (without the extension)
    wxFileName fileName(filePath);
    std::string busName = fileName.GetName().ToStdString(); // Get the file name without extension

    // Access the bus using the extracted bus name
    auto bus = _busManager->getBus(busName);

    // Retrieve all messages
    auto messages = bus->getAllMessages();

    // Clear the previous data in the grid
    _messagesGrid->ClearGrid(); // Clear existing data
    _messagesGrid->DeleteRows(0, _messagesGrid->GetNumberRows()); // Remove all rows

    // Resize the grid to fit the number of messages
    _messagesGrid->AppendRows(messages.size());

    // Populate the grid with CAN message data
    for (size_t i = 0; i < messages.size(); ++i) {
        const auto& message = messages[i];
        _messagesGrid->SetCellValue(i, 0, wxString::Format("0x%X", message->getId())); // ID
        _messagesGrid->SetCellValue(i, 1, message->getName()); // Name
        _messagesGrid->SetCellValue(i, 2, wxString::Format("%d", message->getDlc())); // DLC
        _messagesGrid->SetCellValue(i, 3, message->getTransmitter()); // Transmitter
        _messagesGrid->SetCellValue(i, 4, wxString::Format("%d", static_cast<int>(message->getCycle()))); // CycleTime
    }
}

