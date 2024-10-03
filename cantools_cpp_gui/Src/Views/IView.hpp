/**
 * @file IView.hpp
 *
 * @author Long Pham
 * @date 10/03/2024
 */

#pragma once

#include <wx/notebook.h>
#include "IViewObserver.hpp"

class IView : public wxPanel, IViewObserver
{
public:
    IView::IView(wxNotebook* parent)
        : wxPanel(parent, wxID_ANY) // Initialize parser with bus manager
    {
    }

};