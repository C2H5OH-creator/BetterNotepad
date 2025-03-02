#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>

// Класс основного окна
class Frame : public wxFrame {
public:
    Frame(const wxString& title);
};

#endif // MAINFRAME_H