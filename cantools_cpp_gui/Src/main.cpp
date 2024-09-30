#include "GUIModel.hpp"
#include "GUIView.hpp"
#include "GUIController.hpp"
#include "Logger.hpp"

class MyApp : public wxApp
{
private:
    // Use unique_ptr for automatic memory management
    GUIModel* model;
    GUIView* view;
    GUIController* controller;

public:
    virtual bool OnInit() {
        // Enable memory leak detection in debug mode
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        // Use unique_ptr for automatic memory management
        model = new GUIModel();
        view = new GUIView();
        controller = new GUIController(*model, *view);

        view->Show(true);
        // The smart pointers will automatically clean up the memory when they go out of scope.
        return true;
    }

    virtual int OnExit()
    {
        delete model;
        delete controller;
        cantools_cpp::Logger::getInstance().log("Application is closing. Cleanup done.", cantools_cpp::Logger::LOG_INFO);
        return 0;
    }
};

wxIMPLEMENT_APP(MyApp);