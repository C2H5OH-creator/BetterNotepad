#pragma once
#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include <md4c.h> // Подключаем MD4C



class TextEditorField : public wxRichTextCtrl {
public:
    using wxRichTextCtrl::wxRichTextCtrl;

private:
    void OnContextMenu(wxContextMenuEvent& event);
    void OnMakeItalic(wxCommandEvent& event);
    void OnMakeBold(wxCommandEvent& event);
    void OnUpdateMenuItem(wxUpdateUIEvent& event);
    //void OnChangeFontSize(wxCommandEvent& event);

    // Функция для вставки Markdown
    //void InsertMarkdown(const wxString& markdown);

    // Коллбэки для MD4C
    //static int MDCallback(MD_SPANTYPE tag, MD_TAGTYPE type, void* userdata);
    //static void MDTextCallback(MD_TEXTTYPE type, const MD_CHAR* text, MD_SIZE size, void* userdata);

    wxDECLARE_EVENT_TABLE();
};