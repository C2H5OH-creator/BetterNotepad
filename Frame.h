#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include "TextEditorField.h"
#include <wx/filedlg.h> // Для wxFileDialog
#include <wx/file.h>
#include <wx/textfile.h>

// Класс основного окна
class Frame : public wxFrame {
public:

    Frame(const wxString& title);
private:

    void OnOpenFile(wxCommandEvent& event);
    TextEditorField* textEditor;
    
};

#endif // MAINFRAME_H