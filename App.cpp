#include "App.h"
#include "Frame.h"

// Реализация метода OnInit
bool App::OnInit() {
    wxLocale locale;
    locale.Init(wxLANGUAGE_RUSSIAN, wxLOCALE_LOAD_DEFAULT);


    auto frame = new Frame("BetterNotepad");
    frame->Show(true);
    return true;
}
// Макрос для создания экземпляра приложения
wxIMPLEMENT_APP(App);