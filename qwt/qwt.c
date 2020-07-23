#include <qwt.h>

void qwt_init()
{
        object_type_register();
        emitter_type_register();
        theme_type_register();
        app_type_register();
        widget_type_register();
        button_type_register();
        layout_type_register();
        box_layout_type_register();
        toggle_button_type_register();
}
