#include "Frame.h"
#include "TextEditorField.h"

Frame::Frame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title) {
    // Устанавливаем размер окна
    SetSize(800, 600);
    Centre();

    // Создаем панель
    wxPanel* mainPanel = new wxPanel(this, wxID_ANY);

    // Создаем экземпляр TextEditorField
    TextEditorField* textEditor = new TextEditorField(mainPanel, wxID_ANY, "",
        wxDefaultPosition, wxDefaultSize);

    // Настраиваем layout
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(textEditor, 1, wxEXPAND | wxALL, 5);
    mainPanel->SetSizer(sizer);
}