#include "GUIModel.hpp"
#include "GUIView.hpp"
#include "GUIController.hpp"

class MyApp : public wxApp
{
public:
    virtual bool OnInit() {
        GUIModel* model = new GUIModel();
        GUIView* view = new GUIView();
        GUIController* controller = new GUIController(model, view);

        view->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);