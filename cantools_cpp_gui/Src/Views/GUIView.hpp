/**
 * @file GUIView.hpp
 *
 * @author Long Pham
 * @date 10/03/2024
 */

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