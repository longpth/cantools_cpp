#pragma once

#include <wx/wx.h>
#include <wx/notebook.h>

class GUIView : public wxFrame
{
public:
    GUIView();
    wxNotebook* notebook;

private:
    void SetupLayout();
};