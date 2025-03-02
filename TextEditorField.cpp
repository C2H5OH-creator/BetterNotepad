#include "TextEditorField.h"

// Идентификаторы для новых пунктов меню
enum {
    ID_MAKE_ITALIC = 1,
    ID_MAKE_BOLD = 2,
    ID_CHANGE_FONT_SIZE = 3
};

wxBEGIN_EVENT_TABLE(TextEditorField, wxRichTextCtrl)
EVT_CONTEXT_MENU(TextEditorField::OnContextMenu)
EVT_MENU(ID_MAKE_ITALIC, TextEditorField::OnMakeItalic)
EVT_MENU(ID_MAKE_BOLD, TextEditorField::OnMakeBold)
EVT_MENU(ID_CHANGE_FONT_SIZE, TextEditorField::OnChangeFontSize)
wxEND_EVENT_TABLE()

// Коллбэк для обработки элементов Markdown
int TextEditorField::MDCallback(MD_SPANTYPE tag, MD_TAGTYPE type, void* userdata) {
    TextEditorField* textCtrl = static_cast<TextEditorField*>(userdata);

    switch (tag) {
    case MD_SPAN_EM: // Курсив
        if (type == MD_TAGTYPE_OPEN) {
            wxRichTextAttr attr;
            attr.SetFontStyle(wxFONTSTYLE_ITALIC);
            textCtrl->BeginTextAttr(attr);
        }
        else {
            textCtrl->EndTextAttr();
        }
        break;
    case MD_SPAN_STRONG: // Жирный
        if (type == MD_TAGTYPE_OPEN) {
            wxRichTextAttr attr;
            attr.SetFontWeight(wxFONTWEIGHT_BOLD);
            textCtrl->BeginTextAttr(attr);
        }
        else {
            textCtrl->EndTextAttr();
        }
        break;
        // Обработка других тегов...
    }
    return 0;
}

// Коллбэк для обработки текста
void TextEditorField::MDTextCallback(MD_TEXTTYPE type, const MD_CHAR* text, MD_SIZE size, void* userdata) {
    TextEditorField* textCtrl = static_cast<TextEditorField*>(userdata);
    textCtrl->WriteText(wxString(text, size));
}

// Функция для вставки Markdown
void TextEditorField::InsertMarkdown(const wxString& markdown) {
    MD_PARSER parser;
    parser.enter_block = nullptr; // Указываем nullptr, если не используем
    parser.leave_block = nullptr;
    parser.enter_span = MDCallback;
    parser.leave_span = MDCallback;
    parser.text = MDTextCallback;
    parser.userdata = this;

    md_parse(markdown.c_str(), markdown.size(), &parser, this);
}

// Обработчик события контекстного меню
void TextEditorField::OnContextMenu(wxContextMenuEvent& event) {
    // Создаем контекстное меню
    wxMenu menu;

    // Добавляем стандартные действия
    menu.Append(wxID_COPY, "Копировать");
    menu.Append(wxID_PASTE, "Вставить");
    menu.Append(wxID_CUT, "Вырезать");
    menu.AppendSeparator();

    // Добавляем новый пункт меню
    menu.AppendCheckItem(ID_MAKE_ITALIC, "Курсив");
    menu.AppendCheckItem(ID_MAKE_BOLD, "Жирный");
    menu.AppendSeparator();

    // Добавляем пункт для вставки Markdown
    menu.Append(ID_CHANGE_FONT_SIZE, "Вставить Markdown");

    // Привязываем обработчики событий
    Bind(wxEVT_MENU, &TextEditorField::OnMakeItalic, this, ID_MAKE_ITALIC);
    Bind(wxEVT_MENU, &TextEditorField::OnMakeBold, this, ID_MAKE_BOLD);
    Bind(wxEVT_MENU, [this](wxCommandEvent&) {
        InsertMarkdown("**Жирный текст** и *курсив*"); // Пример Markdown
        }, ID_CHANGE_FONT_SIZE);

    // Показываем меню
    PopupMenu(&menu);
}

// Обработчик для пункта "Сделать курсивным"
void TextEditorField::OnMakeItalic(wxCommandEvent& event) {
    // Получаем текущий диапазон выделенного текста
    wxRichTextRange range = GetSelectionRange();

    if (range.GetLength() > 0) { // Проверяем, есть ли выделенный текст
        // Получаем текущий стиль выделенного текста
        wxRichTextAttr attr;
        GetStyle(range.GetStart(), attr);

        // Проверяем, является ли текст уже курсивным
        bool isItalic = (attr.GetFontStyle() == wxFONTSTYLE_ITALIC);

        // Устанавливаем новый стиль
        wxRichTextAttr newAttr;
        newAttr.SetFlags(wxTEXT_ATTR_FONT_ITALIC); // Указываем, что меняем только курсив
        newAttr.SetFontStyle(isItalic ? wxFONTSTYLE_NORMAL : wxFONTSTYLE_ITALIC); // Переключаем стиль

        // Применяем стиль к выделенному тексту
        SetStyle(range, newAttr);
    }
}

// Обработчик для пункта "Сделать жирным"
void TextEditorField::OnMakeBold(wxCommandEvent& event) {
    wxRichTextRange range = GetSelectionRange();

    if (range.GetLength() > 0) { // Проверяем, есть ли выделенный текст
        wxRichTextAttr attr;
        GetStyle(range.GetStart(), attr);

        // Переключаем жирный стиль
        bool isBold = (attr.GetFontWeight() == wxFONTWEIGHT_BOLD);
        wxRichTextAttr newAttr;
        newAttr.SetFlags(wxTEXT_ATTR_FONT_WEIGHT);
        newAttr.SetFontWeight(isBold ? wxFONTWEIGHT_NORMAL : wxFONTWEIGHT_BOLD);

        SetStyle(range, newAttr);
    }
}

// Обработчик для изменения размера шрифта
void TextEditorField::OnChangeFontSize(wxCommandEvent& event) {
    wxRichTextRange range = GetSelectionRange();

    if (range.GetLength() > 0) {
        // Получаем текущий размер шрифта
        wxRichTextAttr attr;
        GetStyle(range.GetStart(), attr);
        int currentSize = attr.GetFontSize();

        // Создаем диалог с SpinCtrl
        FontSizeDialog dialog(this, currentSize);
        if (dialog.ShowModal() == wxID_OK) {
            int newSize = dialog.GetFontSize();

            // Применяем новый размер шрифта
            wxRichTextAttr newAttr;
            newAttr.SetFlags(wxTEXT_ATTR_FONT_SIZE);
            newAttr.SetFontSize(newSize);
            SetStyle(range, newAttr);
        }
    }
}