#include "AllegroBase.h"
#include <iostream>
#include "windows.h"



using namespace std;


AllegroBase::AllegroBase() :
    alDisplay_(0),
    alEventQueue_(0),
    alTimer_(0),
    exit_(false)
{
    memset(pressedKeys_, 0, sizeof(pressedKeys_));
}

AllegroBase::~AllegroBase()
{
    Destroy();
}

bool AllegroBase::Init(int screenWidth, int screenHeight, int fps)
{
    if (!al_init())
    {
        cout << "failed to initialize allegro!" << endl;
        return false;
    }

    alTimer_ = al_create_timer(1.0 / fps);
    if (!alTimer_)
    {
        cout << "failed to create timer!" << endl;
        return false;
    }

    alDisplay_ = al_create_display(screenWidth, screenHeight);
    if (!alDisplay_)
    {
        cout << "failed to create display!" << endl;
        return false;
    }

    if (!al_init_primitives_addon())
    {
        cout << "failed to init addons!" << endl;
        return false;
    }

    alEventQueue_ = al_create_event_queue();
    if (!alEventQueue_)
    {
        cout << "failed to create event queue!" << endl;
        return false;
    }

    if (!al_install_keyboard())
    {
        cout << "failed to install keyboard" << endl;
        return false;
    }

    al_register_event_source(alEventQueue_, al_get_display_event_source(alDisplay_));
    al_register_event_source(alEventQueue_, al_get_timer_event_source(alTimer_));
    al_register_event_source(alEventQueue_, al_get_keyboard_event_source());

    exit_ = false;

    return true;

}

void AllegroBase::Destroy()
{
    if (alTimer_)
    {
        al_destroy_timer(alTimer_);
        alTimer_ = 0;
    }

    if (alDisplay_)
    {
        al_destroy_display(alDisplay_);
        alDisplay_ = 0;
    }

    if (alEventQueue_)
    {
        al_destroy_event_queue(alEventQueue_);
        alEventQueue_ = 0;
    }

}

void AllegroBase::Run()
{
    // clear screen
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    al_start_timer(alTimer_);

    bool redraw = false;
    while (true)
    {
        al_wait_for_event(alEventQueue_, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            Fps();
            redraw = true;
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            OnKeyDown(ev.keyboard);
            pressedKeys_[ev.keyboard.keycode] = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            OnKeyUp(ev.keyboard);
            pressedKeys_[ev.keyboard.keycode] = false;
        }

        if (redraw && al_is_event_queue_empty(alEventQueue_))
        {
            redraw = false;
            Draw();
            al_flip_display();
        }


        if (ev.type == ASYNC_DIALOG_EVENT1) {
            al_unregister_event_source(alEventQueue_, &cur_dialog->event_source);

            if (al_get_native_file_dialog_count(cur_dialog->file_dialog) > 0) {
                std::string tmp = al_get_native_file_dialog_path(cur_dialog->file_dialog, 0);
                stop_async_dialog(cur_dialog);
                //std::cout << tmp << std::endl;
                FileOpenEvent(tmp);
            }
            else {
                stop_async_dialog(cur_dialog);
            }
            cur_dialog = NULL;
        }

        if (exit_)
        {
            break;
        }
    }
}

void AllegroBase::Exit()
{
    exit_ = true;
}

bool AllegroBase::IsPressed(int keycode)
{
    return pressedKeys_[keycode];
}



std::string AllegroBase::CreateFileDialog()
{

    cur_dialog = spawn_async_file_dialog(alDisplay_, "");
    al_register_event_source(alEventQueue_, &cur_dialog->event_source);

    return "";
}


