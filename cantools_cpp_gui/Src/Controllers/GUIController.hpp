#pragma once

#include "GUIModel.hpp"
#include "GUIView.hpp"

class GUIController
{
public:
    GUIController(GUIModel& model, GUIView& view);

private:
    GUIModel& _model;
    GUIView& _view;
};
