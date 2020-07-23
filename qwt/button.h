#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.h"

#define TYPE_BUTTON "button"

typedef struct Button
{
        /* private */
        Widget parent;
        char text[64];
        bool pressed;
} Button;

typedef struct ButtonClass {
        WidgetClass parent_class;
} ButtonClass;

#define BUTTON_GET_CLASS(obj) \
        OBJECT_GET_CLASS(ButtonClass, obj, TYPE_BUTTON)

#define BUTTON_CLASS(klass) \
        OBJECT_CLASS_CHECK(ButtonClass, klass, TYPE_BUTTON)

#define BUTTON(obj) \
        OBJECT_CHECK(Button, obj, TYPE_BUTTON)

Button *button_new(void);
void button_type_register(void);
void button_set_text(Button *this, const char *text);

#endif
