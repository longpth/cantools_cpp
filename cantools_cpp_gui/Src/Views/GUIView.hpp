#pragma once

#include <wx/wx.h>
#include <wx/notebook.h>
#include <memory>
#include "CANViewModel.hpp"

class GUIView : public wxFrame
{
public:
    GUIView();
    wxNotebook* notebook;
    std::shared_ptr<CANViewModel> _canViewModel;

private:
    void SetupLayout();
};