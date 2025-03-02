#ifndef APP_H
#define APP_H

#include <wx/wx.h>

// Класс приложения
class App : public wxApp {
public:
    virtual bool OnInit() override;
};

#endif // APP_H