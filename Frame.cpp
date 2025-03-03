#include "Frame.h"

Frame::Frame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title) {
    // Устанавливаем размер окна
    SetSize(800, 600);
    Centre();

    // Создаем панель
    wxPanel* mainPanel = new wxPanel(this, wxID_ANY);

    // Создаем экземпляр TextEditorField
    textEditor = new TextEditorField(mainPanel, wxID_ANY, "",
        wxDefaultPosition, wxDefaultSize);

    // Настраиваем layout
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(textEditor, 1, wxEXPAND | wxALL, 5);
    mainPanel->SetSizer(sizer);

    // Создаем меню
    wxMenuBar* menuBar = new wxMenuBar();

    // Создаем меню "Файл"
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(wxID_OPEN, wxString::FromUTF8("Файл"));

    // Добавляем меню "Файл" в менюбар
    menuBar->Append(fileMenu, wxString::FromUTF8("Открыть"));

    // Устанавливаем менюбар для окна
    SetMenuBar(menuBar);

    // Привязываем обработчик события для "Открыть"
    Bind(wxEVT_MENU, &Frame::OnOpenFile, this, wxID_OPEN);
}

// Обработчик для пункта "Открыть"
void Frame::OnOpenFile(wxCommandEvent& event) {
    // Создаем диалоговое окно для выбора файла
    wxFileDialog openFileDialog(this, wxString::FromUTF8("Открыть файл"), wxString::FromUTF8(""), wxString::FromUTF8(""),
        wxString::FromUTF8("Текстовые файлы (*.txt)|*.txt | Все файлы (*.*)|*.*"),
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    // Показываем диалоговое окно
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return; // Пользователь отменил выбор
    }

    // Получаем путь к выбранному файлу
    wxString filePath = openFileDialog.GetPath();

    // Открываем файл и загружаем его содержимое в TextEditorField
    wxTextFile file;
    if (file.Open(filePath)) {
        wxString content;
        for (size_t i = 0; i < file.GetLineCount(); i++) {
            content += file.GetLine(i) + "\n";
        }
        file.Close();

        // Загружаем содержимое в TextEditorField
        if (textEditor) {
            textEditor->SetValue(content);
        }
    }
    else {
        wxMessageBox(wxString::FromUTF8("Не удалось открыть файл."), wxString::FromUTF8("Ошибка"), wxOK | wxICON_ERROR);
    }
}