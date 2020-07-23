#include "layout.h"
#include "widget.h"
#include "app.h"

#define TYPE_BOX_LAYOUT "box-layout"

static const int BOX_LAYOUT_HORIZONTAL = 0;
static const int BOX_LAYOUT_VERTICAL = 1;

typedef struct BoxLayout
{
        /* private */
        Layout parent;
        int orientation;
} BoxLayout;

typedef struct BoxLayoutClass {
        LayoutClass parent_class;

        void (*parent_set_size)(Widget *widget, int w, int h);
        void (*parent_set_pos)(Widget *widget, int x, int y);
        void (*parent_set_app)(Widget *widget, App *app);
        void (*parent_add_widget)(Layout *layout, Widget *widget);
} BoxLayoutClass;

#define BOX_LAYOUT_GET_CLASS(obj) \
        OBJECT_GET_CLASS(BoxLayoutClass, obj, TYPE_BOX_LAYOUT)

#define BOX_LAYOUT_CLASS(klass) \
        OBJECT_CLASS_CHECK(BoxLayoutClass, klass, TYPE_BOX_LAYOUT)

#define BOX_LAYOUT(obj) \
        OBJECT_CHECK(BoxLayout, obj, TYPE_BOX_LAYOUT)

BoxLayout *box_layout_new(void);
void box_layout_type_register(void);
void box_layout_set_orientation(BoxLayout *this, int orientation);
