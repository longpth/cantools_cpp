/**
 * @file GUIView.cpp
 *
 * @author Long Pham
 * @date 10/03/2024
 */

#include "GUIView.hpp"
#include "TabDatabaseView.hpp"

GUIView::GUIView() : wxFrame(nullptr, wxID_ANY, "cantools_cpp gui application", wxDefaultPosition, wxSize(1280, 720)) {
    // Call setup function to initialize the layout
    _canViewModel = std::make_shared<CANViewModel>();
    SetupLayout();
}

void GUIView::SetupLayout() {
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Create a notebook (tab control)
    notebook = new wxNotebook(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    // Create three tabs
    TabDatabaseView* tab1 = new TabDatabaseView(notebook);
    tab1->setViewModel(_canViewModel);
    wxPanel* tab2 = new wxPanel(notebook, wxID_ANY);
    wxPanel* tab3 = new wxPanel(notebook, wxID_ANY);

    // Add tabs to notebook
    notebook->AddPage(tab1, "CAN Database");
    notebook->AddPage(tab2, "Tab 2");
    notebook->AddPage(tab3, "Tab 3");

    // Add layout to the second tab (Tab 2)
    wxBoxSizer* tab2Sizer = new wxBoxSizer(wxVERTICAL);
    wxTextCtrl* text2 = new wxTextCtrl(tab2, wxID_ANY, "Tab 2 Content", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    tab2Sizer->Add(text2, 1, wxALL | wxEXPAND, 10);
    tab2->SetSizer(tab2Sizer);

    // Add layout to the third tab (Tab 3)
    wxBoxSizer* tab3Sizer = new wxBoxSizer(wxVERTICAL);
    wxTextCtrl* text3 = new wxTextCtrl(tab3, wxID_ANY, "Tab 3 Content", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    tab3Sizer->Add(text3, 1, wxALL | wxEXPAND, 10);
    tab3->SetSizer(tab3Sizer);

    // Add notebook to the main sizer
    mainSizer->Add(notebook, 1, wxALL | wxEXPAND, 5);
    panel->SetSizer(mainSizer);
}
