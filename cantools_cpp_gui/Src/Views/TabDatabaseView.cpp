/**
 * @file TabDatabaseView.cpp
 *
 * @author Long Pham
 * @date 10/03/2024
 */

#include "TabDatabaseView.hpp"
#include <wx/filename.h>
#include "Logger.hpp"
#include "CANMessage.hpp"
#include "Util.hpp"
#include "CANViewModel.hpp"


enum {
    ID_LoadDBC = 1001,  // Event ID for the Load DBC button
    ID_MessageGrid = 1002 // Event ID for the Message Grid
};

enum {
    COLUMN_SIGNAL_GRID_MSG_ID = 0,            // "ID"
    COLUMN_SIGNAL_GRID_NAME,              // "Name"
    COLUMN_SIGNAL_GRID_STARTBIT,          // "StartBit"
    COLUMN_SIGNAL_GRID_LENGTH,            // "Length"
    COLUMN_SIGNAL_GRID_BYTEORDER,         // "ByteOrder"
    COLUMN_SIGNAL_GRID_ISSIGNED,          // "IsSigned"
    COLUMN_SIGNAL_GRID_INITIALVAL,        // "InitialValue"
    COLUMN_SIGNAL_GRID_RAWVAL,            // "Raw Value"
    COLUMN_SIGNAL_GRID_PHYSICALVAL,       // "Physical value"
    COLUMN_SIGNAL_GRID_FACTOR,            // "Factor"
    COLUMN_SIGNAL_GRID_OFFSET,            // "Offset"
    COLUMN_SIGNAL_GRID_MINIMUM,           // "Minimum"
    COLUMN_SIGNAL_GRID_MAXIMUM,           // "Maximum"
    COLUMN_SIGNAL_GRID_UNIT,              // "Unit"
    COLUMN_SIGNAL_GRID_RECEIVER           // "Receiver"
};

enum {
    COLUMN_MESSAGE_GRID_ID = 0,
    COLUMN_MESSAGE_GRID_NAME,
    COLUMN_MESSAGE_GRID_DLC,
    COLUMN_MESSAGE_GRID_TRANSMITTER,
    COLUMN_MESSAGE_GRID_CYCLE,
    COLUMN_MESSAGE_GRID_BUS,
    COLUMN_MESSAGE_GRID_DATA,
};

// Event table to handle the button click and grid cell click events
wxBEGIN_EVENT_TABLE(TabDatabaseView, wxPanel)
    EVT_BUTTON(ID_LoadDBC, TabDatabaseView::OnLoadDBC) // Handle load dbc
    EVT_GRID_LABEL_LEFT_CLICK(TabDatabaseView::OnGridLabelLeftClick) // Handle grid cell click
wxEND_EVENT_TABLE()

TabDatabaseView::TabDatabaseView(wxNotebook* parent)
    : IView(parent) // Initialize parser with bus manager
{
    SetupLayout();
    //_canViewModel = std::make_shared<CANViewModel>();
    //_canViewModel->addObserver(this);
}

void TabDatabaseView::setViewModel(std::shared_ptr<CANViewModel> canViewModel)
{
    _canViewModel = canViewModel;
    _canViewModel->addObserver(this);
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
    _messagesGrid->CreateGrid(5, 7); // Placeholder grid with 5 rows and 6 columns
    _messagesGrid->SetColLabelValue(0, "ID");
    _messagesGrid->SetColLabelValue(1, "Name");
    _messagesGrid->SetColLabelValue(2, "DLC");
    _messagesGrid->SetColLabelValue(3, "Transmitter");
    _messagesGrid->SetColLabelValue(4, "CycleTime");
    _messagesGrid->SetColLabelValue(5, "Bus");
    _messagesGrid->SetColLabelValue(6, "Data");

    // Grid for CAN signals
    _signalsGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(600, 300));
    _signalsGrid->CreateGrid(10, 15); // Placeholder grid with 10 rows and 15 columns
    _signalsGrid->SetColLabelValue(0, "ID");
    _signalsGrid->SetColLabelValue(1, "Name");
    _signalsGrid->SetColLabelValue(2, "StartBit");
    _signalsGrid->SetColLabelValue(3, "Length");
    _signalsGrid->SetColLabelValue(4, "ByteOrder");
    _signalsGrid->SetColLabelValue(5, "IsSigned");
    _signalsGrid->SetColLabelValue(6, "InitialValue");
    _signalsGrid->SetColLabelValue(7, "Raw Value");
    _signalsGrid->SetColLabelValue(8, "Physical value");
    _signalsGrid->SetColLabelValue(9, "Factor");
    _signalsGrid->SetColLabelValue(10, "Offset");
    _signalsGrid->SetColLabelValue(11, "Minimum");
    _signalsGrid->SetColLabelValue(12, "Maximum");
    _signalsGrid->SetColLabelValue(13, "Unit");
    _signalsGrid->SetColLabelValue(14, "Receiver");

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

    // Enable grid editing
    _messagesGrid->EnableEditing(true);

    // Bind the message cell change event
    _messagesGrid->Bind(wxEVT_GRID_CELL_CHANGED, &TabDatabaseView::OnMessageGridCellChange, this);

    // Bind the signal cell change event
    _signalsGrid->Bind(wxEVT_GRID_CELL_CHANGED, &TabDatabaseView::OnSignalGridCellChange, this);
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
        _canViewModel->loadCANData(filePath.ToStdString()); // Convert wxString to std::string
    }
    else {
        // If the file path control is not empty, get the current path and populate data
        _canViewModel->loadCANData(_filePathCtrl->GetValue().ToStdString()); // Convert wxString to std::string
    }
}

void TabDatabaseView::Update(std::vector<std::shared_ptr<cantools_cpp::CANNode>> nodes, std::vector<std::shared_ptr<cantools_cpp::CANMessage>> messages, std::string busName)
{
    PopulateData(nodes, messages, busName);
}

void TabDatabaseView::PopulateData(std::vector<std::shared_ptr<cantools_cpp::CANNode>> nodes, std::vector<std::shared_ptr<cantools_cpp::CANMessage>> messages, std::string busName)
{
    // Clear the previous data in the grid
    _messagesGrid->ClearGrid(); // Clear existing data
    _messagesGrid->DeleteRows(0, _messagesGrid->GetNumberRows()); // Remove all rows

    // Resize the grid to fit the number of messages
    _messagesGrid->AppendRows(messages.size());

    // Populate the grid with CAN message data
    for (size_t i = 0; i < messages.size(); ++i) {
        const auto& message = messages[i];
        _messagesGrid->SetCellValue(i, COLUMN_MESSAGE_GRID_ID, wxString::Format("0x%X", message->getId())); _messagesGrid->SetReadOnly(i, COLUMN_MESSAGE_GRID_ID); // ID
        _messagesGrid->SetCellValue(i, COLUMN_MESSAGE_GRID_NAME, message->getName()); // Name
        _messagesGrid->AutoSizeColumn(COLUMN_MESSAGE_GRID_NAME);  // Resize the specific column (index 1)
        _messagesGrid->SetCellValue(i, COLUMN_MESSAGE_GRID_DLC, wxString::Format("%d", message->getDlc())); // DLC
        _messagesGrid->SetCellValue(i, COLUMN_MESSAGE_GRID_TRANSMITTER, message->getTransmitter()); // Transmitter
        _messagesGrid->SetCellValue(i, COLUMN_MESSAGE_GRID_CYCLE, wxString::Format("%d", static_cast<int>(message->getCycle()))); // CycleTime
        _messagesGrid->SetCellValue(i, COLUMN_MESSAGE_GRID_BUS, busName); _messagesGrid->SetReadOnly(i, COLUMN_MESSAGE_GRID_BUS); // Bus 

        std::shared_ptr<uint8_t[]> data = message->getData();

        std::string dataStr = cantools_cpp::Util::getInstance().convertToHexString(data, message->getLength());
        _messagesGrid->SetCellValue(i, COLUMN_MESSAGE_GRID_DATA, dataStr); // Data
        // Automatically resize the column to fit the data
        _messagesGrid->AutoSizeColumn(COLUMN_MESSAGE_GRID_DATA);  // Resize the specific column (index 6)
    }

    // Clear the previous data in the nodes list
    _nodesList->DeleteAllItems();

    // Populate the node list with CAN node data
    for (size_t i = 0; i < nodes.size(); ++i) {
        const auto& node = nodes[i];

        // Insert node name and details into the list control
        long index = _nodesList->InsertItem(i, node->getName()); // Node Name
        _nodesList->SetItem(index, 1, ""); // You can add more detailed information about the node here if needed
    }

}

void TabDatabaseView::OnSignalGridCellChange(wxGridEvent& event) {
    int row = event.GetRow();
    int col = event.GetCol();

    // Access the bus using the extracted bus name
    auto bus = _canViewModel->getBusMan()->getBus(_currentBusName);
    
    // Get the value from the grid at row 'row' and column COLUMN_MESSAGE_GRID_ID
    wxString wxMsgId = _signalsGrid->GetCellValue(row, COLUMN_SIGNAL_GRID_MSG_ID);
    wxString wxSignalName = _signalsGrid->GetCellValue(row, COLUMN_SIGNAL_GRID_NAME);

    std::string msgId = wxMsgId.ToStdString();

    auto signal = bus->getMessageById(std::stoul(msgId, nullptr, 16))->getSignal(wxSignalName.ToStdString());

    wxString newValue = _signalsGrid->GetCellValue(row, col);

    switch (col) {
    case COLUMN_SIGNAL_GRID_RAWVAL: // Signal raw value
        signal.lock()->setRawValue(std::stoull(newValue.ToStdString()));
        break;
    case COLUMN_SIGNAL_GRID_PHYSICALVAL: // Signal physical value
        signal.lock()->setPhysicalValue(std::stod(newValue.ToStdString()));
        break;
    default:
        break;
    }
}

void TabDatabaseView::OnMessageGridCellChange(wxGridEvent& event) {
    int row = event.GetRow();
    int col = event.GetCol();

    // Get the value from the grid at row 'row' and column COLUMN_MESSAGE_GRID_BUS
    wxString valueAtColumn5 = _messagesGrid->GetCellValue(row, COLUMN_MESSAGE_GRID_BUS);

    std::string busName = valueAtColumn5.ToStdString();

    auto message = _canViewModel->getBusMan()->getBus(busName)->getMessageById(std::stoul(_messagesGrid->GetCellValue(row, COLUMN_MESSAGE_GRID_ID).ToStdString(), nullptr, 16));

    wxString newValue = _messagesGrid->GetCellValue(row, col);
    std::vector<uint8_t> data;

    switch (col) {
        case COLUMN_MESSAGE_GRID_NAME: // Message Name
            message->setName(newValue.ToStdString());
            break;
        case COLUMN_MESSAGE_GRID_DLC: // DLC (Data Length Code)
            message->setDlc(std::stoi(newValue.ToStdString()));
            break;
        case COLUMN_MESSAGE_GRID_TRANSMITTER: // Transmitter
            message->setTransmitter(newValue.ToStdString());
            break;
        case COLUMN_MESSAGE_GRID_CYCLE: // Cycle Time
            message->setCycle(std::stoi(newValue.ToStdString()));
            break;
        case COLUMN_MESSAGE_GRID_DATA: // Data (Hex string)
            data = cantools_cpp::Util::getInstance().convertFromHexString(newValue.ToStdString());
            message->setData(data.data(), data.size());
            break;
        default:
            break;
    }

    event.Skip(); // Allow the event to propagate further if needed
}

void TabDatabaseView::OnGridLabelLeftClick(wxGridEvent& event) {
    int row = event.GetRow(); // Get the clicked row index
    if (row >= 0) {
        // Retrieve the message ID from the clicked row
        std::string messageId = _messagesGrid->GetCellValue(row, COLUMN_MESSAGE_GRID_ID).ToStdString();
        std::string busName   = _messagesGrid->GetCellValue(row, COLUMN_MESSAGE_GRID_BUS).ToStdString();

        // Log the selected message ID or handle it as needed
        cantools_cpp::Logger::getInstance().log("Selected message ID: " + messageId);

        // Access the bus using the extracted bus name
        auto bus = _canViewModel->getBusMan()->getBus(busName);

        _currentBusName = busName;

        // Retrieve all messages
        auto messages = bus->getAllMessages();

        try {
            int msgId = std::stoi(messageId, nullptr, 16);  // Convert string to int

            auto it = std::find_if(messages.begin(), messages.end(), [&msgId](const std::shared_ptr<cantools_cpp::CANMessage>& msg) {
                return msgId == msg->getId();
                }
            );

            if (it != messages.end())
            {
                // Clear the previous data in the grid
                _signalsGrid->ClearGrid(); // Clear existing data
                _signalsGrid->DeleteRows(0, _signalsGrid->GetNumberRows()); // Remove all rows

                // Resize the grid to fit the number of messages
                _signalsGrid->AppendRows((*it)->getSignals().size());

                int i = 0;
                for (auto signal : (*it)->getSignals())
                {
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_MSG_ID, wxString::Format("0x%X", signal->getParent().lock()->getId())); // ID
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_NAME, signal->getName()); // Name
                    _signalsGrid->AutoSizeColumn(COLUMN_SIGNAL_GRID_NAME);  // Resize the specific column (index 1)
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_STARTBIT, wxString::Format("%d", signal->getStartBit())); // StartBit
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_LENGTH, wxString::Format("%d", signal->getLength())); // Length
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_BYTEORDER, wxString::Format("%d", signal->getByteOrder())); // ByteOrder
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_ISSIGNED, wxString::Format("%d", signal->getValueType())); // IsSigned
                    //_signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_INITIALVAL, wxString::Format("%f", signal->getInitialValue())); // InitialValue
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_RAWVAL, wxString::Format("%llu", static_cast<unsigned long long>(signal->getRawValue()))); // Raw Value
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_PHYSICALVAL, wxString::Format("%f", signal->getPhysicalValue())); // Physical Value
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_FACTOR, wxString::Format("%f", signal->getFactor())); // Factor
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_OFFSET, wxString::Format("%f", signal->getOffset())); // Offset
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_MINIMUM, wxString::Format("%f", signal->getMinVal())); // Minimum
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_MAXIMUM, wxString::Format("%f", signal->getMaxVal())); // Maximum
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_UNIT, signal->getUnit()); // Unit
                    _signalsGrid->SetCellValue(i, COLUMN_SIGNAL_GRID_RECEIVER, signal->getReceiver()); // Receiver

                    for (int j = 0; j < _signalsGrid->GetNumberCols(); j++)
                    {
                        if (j != COLUMN_SIGNAL_GRID_RAWVAL && j != COLUMN_SIGNAL_GRID_PHYSICALVAL)
                        {
                            _signalsGrid->SetReadOnly(i,j);
                        }
                    }

                    i++;
                }
            }
        }
        catch (const std::invalid_argument& e) {
        }
        catch (const std::out_of_range& e) {
        }
    }
}

void TabDatabaseView::UpdateMessageGrid(std::string busName, uint32_t messageId)
{
    auto message = _canViewModel->getBusMan()->getBus(busName)->getMessageById(messageId);
    for (int row = 0; row < _messagesGrid->GetNumberRows(); row++)
    {
        if (std::stoul(_messagesGrid->GetCellValue(row, COLUMN_MESSAGE_GRID_ID).ToStdString(), nullptr, 16) == messageId)
        {
            std::shared_ptr<uint8_t[]> data = message->getData();

            std::string dataStr = cantools_cpp::Util::getInstance().convertToHexString(data, message->getLength());
            _messagesGrid->SetCellValue(row, COLUMN_MESSAGE_GRID_DATA, dataStr); // Data
            message->setData(data.get(), message->getLength()); // this trick to update signal physical, raw
        }
    }
}

void TabDatabaseView::UpdateSignalGrid(std::string busName, uint32_t messageId, std::string signalName)
{
    if (_signalsGrid->GetNumberRows() > 0)
    {
        std::string cellValueStr = _signalsGrid->GetCellValue(0, 0); // Get the cell value as a string
        uint32_t cellValue;

        try {
            cellValue = static_cast<uint32_t>(std::stoul(cellValueStr, nullptr, 0)); // Convert string to uint32_t
        }
        catch (const std::invalid_argument& e) {
            // Handle the case where the conversion is invalid (e.g., non-numeric string)
            //wxLogError("Invalid number in grid cell: %s", cellValueStr);
            cellValue = 0; // Set a default value or handle the error appropriately
        }
        catch (const std::out_of_range& e) {
            // Handle the case where the value is out of range for uint32_t
            //wxLogError("Value out of range for uint32_t in grid cell: %s", cellValueStr);
            cellValue = 0; // Set a default value or handle the error appropriately
        }

        if (cellValue == messageId)
        {
            int numRows = _signalsGrid->GetNumberRows();
            for (int row = 0; row < numRows; ++row) {
                std::string cellValueStr = _signalsGrid->GetCellValue(row, 1); // Get the value in column 1 for each row

                // Check if the cell value matches the signalName
                if (cellValueStr == signalName) {
                    if (_currentBusName != "")
                    {
                        auto signal = _canViewModel->getBusMan()->getBus(_currentBusName)->getMessageById(messageId)->getSignal(signalName);
                        _signalsGrid->SetCellValue(row, COLUMN_SIGNAL_GRID_RAWVAL, wxString::Format("%llu", signal.lock()->getRawValue())); // Raw Value
                        _signalsGrid->SetCellValue(row, COLUMN_SIGNAL_GRID_PHYSICALVAL, wxString::Format("%f", signal.lock()->getPhysicalValue())); // Physical Value
                    }
                }
            }
        }

    }
}