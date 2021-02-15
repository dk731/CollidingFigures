#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_windows.h>
#include <string>
#include "Al_native_filechooser.cpp"

class AllegroBase
{
public:
    AllegroBase();
    virtual ~AllegroBase();

    AsyncDialog* cur_dialog = NULL;

    bool Init(int screenWidth, int screenHeight, int fps);
    void Destroy();
    void Run();
    void Exit();

    // See help for ALLEGRO_KEYBOARD_STATE
    bool IsPressed(int keycode);

    virtual void Fps() = 0;
    virtual void Draw() = 0;
    virtual void OnKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard) {};
    virtual void OnKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard) {};

    virtual void FileOpenEvent(std::string a) = 0;

    std::string CreateFileDialog();

protected:
    ALLEGRO_DISPLAY* alDisplay_;
    ALLEGRO_EVENT_QUEUE* alEventQueue_;
    ALLEGRO_TIMER* alTimer_;
    ALLEGRO_EVENT ev;
    bool pressedKeys_[ALLEGRO_KEY_MAX];

private:
    bool exit_;

};
