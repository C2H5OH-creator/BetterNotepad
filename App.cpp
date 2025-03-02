#include "App.h"
#include "Frame.h"

// Реализация метода OnInit
bool App::OnInit() {
    auto frame = new Frame("Hello wxWidgets");
    frame->Show(true);
    return true;
}

// Макрос для создания экземпляра приложения
wxIMPLEMENT_APP(App);