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
        Button *button1;
        Button *button2;
        BoxLayout *layout;

        qwt_init();

        app = app_new();
        app_set_title(app, "My App!");

        emitter_set_callback(EMITTER(app), on_app_close, app);
        emitter_set_when(EMITTER(app), SIGNAL_CLOSE);

        button1 = button_new();
        button_set_text(button1, "Hello!");

        button2 = button_new();
        button_set_text(button2, "Goodbye!");

        layout = box_layout_new();
        layout_add_widget(LAYOUT(layout), WIDGET(button1));
        layout_add_widget(LAYOUT(layout), WIDGET(button2));

        app_add(app, WIDGET(layout));
        app_run(app);

        return 0;
}
