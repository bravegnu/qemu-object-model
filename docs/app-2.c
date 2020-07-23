#include <stdio.h>
#include <qwt.h>

App *app;

void on_app_close(SignalSet signals, void *data)
{
        printf("App close called!\n");
        app_quit(app);
}

int main()
{
        qwt_init();

        app = app_new();
        app_set_title(app, "My App!");

        emitter_set_callback(EMITTER(app), on_app_close, NULL);
        emitter_set_when(EMITTER(app), SIGNAL_CLOSE);

        app_run(app);

        return 0;
}
