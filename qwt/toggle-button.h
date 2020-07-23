#ifndef TOGGLE_BUTTON_HPP
#define TOGGLE_BUTTON_HPP

#include "button.h"

#define TYPE_TOGGLE_BUTTON "toggle-button"

typedef struct ToggleButton
{
        Button parent;
        /* private */
} ToggleButton;

typedef struct ToggleButtonClass {
        ButtonClass parent_class;
} ToggleButtonClass;

#define TOGGLE_BUTTON_GET_CLASS(obj) \
        OBJECT_GET_CLASS(ToggleButtonClass, obj, TYPE_TOGGLE_BUTTON)

#define TOGGLE_BUTTON_CLASS(klass) \
        OBJECT_CLASS_CHECK(ToggleButtonClass, klass, TYPE_TOGGLE_BUTTON)

#define TOGGLE_BUTTON(obj) \
        OBJECT_CHECK(ToggleButton, obj, TYPE_TOGGLE_BUTTON)

ToggleButton *toggle_button_new(void);
void toggle_button_type_register(void);
ToggleButton *togggle_button_get_state(void);

#endif
