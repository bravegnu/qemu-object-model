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
        Label *label1;
        Label *label2;
        Label *label3;
        BoxLayout *layout1;
        BoxLayout *layout2;
        BoxLayout *top_layout;

        qwt_init();

        app = app_new();
        app_set_title(app, "My App!");

        emitter_set_callback(EMITTER(app), on_app_close, app);
        emitter_set_when(EMITTER(app), SIGNAL_CLOSE);

        button1 = button_new();
        button_set_text(button1, "Hello!");

        button2 = button_new();
        button_set_text(button2, "Goodbye!");

        layout1 = box_layout_new();
        box_layout_set_orientation(layout1, BOX_LAYOUT_HORIZONTAL);
        layout_add_widget(LAYOUT(layout1), WIDGET(button1));
        layout_add_widget(LAYOUT(layout1), WIDGET(button2));

        label1 = label_new();
        label_set_text(label1, "One");

        label2 = label_new();
        label_set_text(label2, "Two");

        label3 = label_new();
        label_set_text(label3, "Three");

        layout2 = box_layout_new();
        box_layout_set_orientation(layout2, BOX_LAYOUT_HORIZONTAL);
        layout_add_widget(LAYOUT(layout2), WIDGET(label1));
        layout_add_widget(LAYOUT(layout2), WIDGET(label2));
        layout_add_widget(LAYOUT(layout2), WIDGET(label3));

        top_layout = box_layout_new();
        box_layout_set_orientation(top_layout, BOX_LAYOUT_VERTICAL);
        layout_add_widget(LAYOUT(top_layout), WIDGET(layout1));
        layout_add_widget(LAYOUT(top_layout), WIDGET(layout2));

        app_add(app, WIDGET(top_layout));
        app_run(app);

        return 0;
}
