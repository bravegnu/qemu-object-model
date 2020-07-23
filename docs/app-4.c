#include <stdio.h>
#include <qwt.h>

void on_app_close(SignalSet signals, void *data)
{
        App *app = APP(data);

        printf("App close called!\n");
        app_quit(app);
}

int main()
{
        App *app;
        Button *button;

        qwt_init();

        app = app_new();
        app_set_title(app, "My App!");

        emitter_set_callback(EMITTER(app), on_app_close, app);
        emitter_set_when(EMITTER(app), SIGNAL_CLOSE);

        button = button_new();
        button_set_text(button, "Hello!");

        app_add(app, WIDGET(button));
        app_run(app);

        return 0;
}
