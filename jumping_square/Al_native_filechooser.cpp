#pragma once
#include <allegro5/allegro_native_dialog.h>


 /* To communicate from a separate thread, we need a user event. */
#define ASYNC_DIALOG_EVENT1   ALLEGRO_GET_EVENT_TYPE('e', 'N', 'F', '1')
#define ASYNC_DIALOG_EVENT2   ALLEGRO_GET_EVENT_TYPE('e', 'N', 'F', '2')


typedef struct
{
    ALLEGRO_DISPLAY* display;
    ALLEGRO_FILECHOOSER* file_dialog;
    ALLEGRO_EVENT_SOURCE event_source;
    ALLEGRO_THREAD* thread;


} AsyncDialog;



/* Our thread to show the native file dialog. */
static void* async_file_dialog_thread_func(ALLEGRO_THREAD* thread, void* arg)
{
    AsyncDialog* data = (AsyncDialog*)arg;
    ALLEGRO_EVENT event;
    (void)thread;

    /* The next line is the heart of this example - we display the
     * native file dialog.
     */
    al_show_native_file_dialog(data->display, data->file_dialog);

    /* We emit an event to let the main program know that the thread has
     * finished.
     */
    event.user.type = ASYNC_DIALOG_EVENT1;
    al_emit_user_event(&data->event_source, &event, NULL);

    return NULL;
}


/* Function to start the new thread. */
static AsyncDialog* spawn_async_file_dialog(ALLEGRO_DISPLAY* display,
    const char* initial_path)
{
    AsyncDialog* data = new AsyncDialog();

    data->file_dialog = al_create_native_file_dialog(
        initial_path, "Choose file", NULL, 0);
    al_init_user_event_source(&data->event_source);
    data->display = display;
    data->thread = al_create_thread(async_file_dialog_thread_func, data);

    al_start_thread(data->thread);

    return data;
}


static void stop_async_dialog(AsyncDialog* data)
{
    if (data) {
        al_destroy_thread(data->thread);
        al_destroy_user_event_source(&data->event_source);
        if (data->file_dialog)
            al_destroy_native_file_dialog(data->file_dialog);
        free(data);
    }
    //delete data;
    //data = nullptr;
}
