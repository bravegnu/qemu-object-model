#include <SDL.h>

#include "emitter.h"
#include "button.h"
#include "toggle-button.h"

static void handle_event(Widget *widget, SDL_Event *event)
{
        ToggleButton *this = TOGGLE_BUTTON(widget);
        Button *button = BUTTON(widget);
        Emitter *emitter = EMITTER(widget);

        if (event->type == SDL_MOUSEBUTTONUP) {
                SDL_MouseButtonEvent *me = (SDL_MouseButtonEvent *)event;
                SDL_Point p = { me->x, me->y };
                if (SDL_PointInRect(&p, &widget->rect)) {
                        button->pressed = !button->pressed;
                        emitter_emit(emitter, SIGNAL_CLICKED);
                }
        }
}

static void class_init(ObjectClass *oc, void *data)
{
        WidgetClass *wc = WIDGET_CLASS(oc);

        wc->handle_event = handle_event;
}

ToggleButton *toggle_button_new(void)
{
        return (ToggleButton *)object_new(TYPE_TOGGLE_BUTTON);
}

static const TypeInfo type_info = {
        .name = TYPE_TOGGLE_BUTTON,
        .parent = TYPE_BUTTON,
        .instance_size = sizeof(ToggleButton),
        .abstract = false,
        .class_size = sizeof(ToggleButtonClass),
        .class_init = class_init,
};

void toggle_button_type_register(void)
{
        type_register_static(&type_info);
}
