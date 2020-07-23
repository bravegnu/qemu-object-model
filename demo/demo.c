#include <stdio.h>
#include <error.h>

#include "emitter.h"
#include "theme.h"
#include "app.h"
#include "button.h"
#include "layout.h"
#include "box-layout.h"
#include "toggle-button.h"

void on_app_close(SignalSet signals, void *data)
{
        App *app = APP(data);

        app_quit(app);
}

void on_button_clicked(SignalSet signals, void *data)
{
        printf("%s\n", (char *)data);
}

int main()
{
        qwt_init();

        printf("App\n");
        App *app = app_new();
        app_set_title(app, "Demo");
        emitter_set_callback(EMITTER(app), on_app_close, app);
        emitter_set_when(EMITTER(app), SIGNAL_CLOSE);

        printf("Button1\n");
        Button *button1 = button_new();
        button_set_text(button1, "Button 1");
        emitter_set_callback(EMITTER(button1), on_button_clicked, "Hello World!");
        emitter_set_when(EMITTER(button1), SIGNAL_CLICKED);

        printf("Button2\n");
        ToggleButton *button2 = toggle_button_new();
        button_set_text(BUTTON(button2), "Button 2");
        emitter_set_callback(EMITTER(button2), on_button_clicked, "Goodbye World!");
        emitter_set_when(EMITTER(button2), SIGNAL_CLICKED);

        printf("BoxLayout\n");
        BoxLayout *top_layout = box_layout_new();
        box_layout_set_orientation(top_layout, BOX_LAYOUT_HORIZONTAL);
        layout_add_widget(LAYOUT(top_layout), WIDGET(button1));
        layout_add_widget(LAYOUT(top_layout), WIDGET(button2));

        printf("App Add\n");
        app_add(app, WIDGET(top_layout));
        app_run(app);

        return 0;
}
