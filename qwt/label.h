#ifndef LABEL_HPP
#define LABEL_HPP

#include "widget.h"

#define TYPE_LABEL "label"

typedef struct Label
{
        /* private */
        Widget parent;
        char text[64];
} Label;

typedef struct LabelClass {
        WidgetClass parent_class;
} LabelClass;

#define LABEL_GET_CLASS(obj) \
        OBJECT_GET_CLASS(LabelClass, obj, TYPE_LABEL)

#define LABEL_CLASS(klass) \
        OBJECT_CLASS_CHECK(LabelClass, klass, TYPE_LABEL)

#define LABEL(obj) \
        OBJECT_CHECK(Label, obj, TYPE_LABEL)

Label *label_new(void);
void label_type_register(void);
void label_set_text(Label *this, const char *text);

#endif
