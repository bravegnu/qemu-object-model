#ifndef LAYOUT_H
#define LAYOUT_H

#include "widget.h"

#define TYPE_LAYOUT "layout"

#define LAYOUT_MAX_CHILDREN 32

typedef struct Layout
{
        /* private */
        Widget parent;
        Widget *children[LAYOUT_MAX_CHILDREN];
        int nchild;
} Layout;

typedef struct LayoutClass {
        WidgetClass parent_class;

        void (*add_widget)(Layout *this, Widget *widget);
} LayoutClass;

#define LAYOUT_GET_CLASS(obj) \
        OBJECT_GET_CLASS(LayoutClass, obj, TYPE_LAYOUT)

#define LAYOUT_CLASS(klass) \
        OBJECT_CLASS_CHECK(LayoutClass, klass, TYPE_LAYOUT)

#define LAYOUT(obj) \
        OBJECT_CHECK(Layout, obj, TYPE_LAYOUT)

Layout *layout_new(void);
void layout_type_register(void);
void layout_add_widget(Layout *this, Widget *widget);

#endif
