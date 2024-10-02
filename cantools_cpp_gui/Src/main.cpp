#include "GUIView.hpp"
#include "Logger.hpp"

class MyApp : public wxApp
{
private:
    GUIView* view;

public:
    virtual bool OnInit() {
        // Enable memory leak detection in debug mode
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        view = new GUIView();

        view->Show(true);
        // The smart pointers will automatically clean up the memory when they go out of scope.
        return true;
    }

    virtual int OnExit()
    {
        cantools_cpp::Logger::getInstance().log("Application is closing. Cleanup done.", cantools_cpp::Logger::LOG_INFO);
        return 0;
    }
};

wxIMPLEMENT_APP(MyApp);