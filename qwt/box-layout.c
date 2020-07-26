#include <SDL.h>
#include "widget.h"
#include "app.h"

#include "box-layout.h"

static void resize(BoxLayout *this)
{
        int i;
        int min_width;
        int min_height;
        Layout *layout = LAYOUT(this);
        Widget *widget = WIDGET(this);

        if (layout->nchild == 0)
                return;

        if (this->orientation == BOX_LAYOUT_HORIZONTAL) {
                int total_min_width = 0;
                int offset = 0;

                for (i = 0; i < layout->nchild; i++) {
                        widget_get_min_size(layout->children[i],
                                            &min_width, &min_height);

                        total_min_width += min_width;
                }

                int fill_width = (widget->rect.w - total_min_width) / layout->nchild;

                for (i = 0; i < layout->nchild; i++) {
                        widget_set_pos(layout->children[i],
                                       widget->rect.x + offset, widget->rect.y);
                        widget_get_min_size(layout->children[i],
                                            &min_width, &min_height);
                        widget_set_size(layout->children[i],
                                        min_width + fill_width,
                                        widget->rect.h);
                                offset += min_width + fill_width;
                }
        } else {
                int total_min_height = 0;
                int offset = 0;

                for (i = 0; i < layout->nchild; i++) {
                        widget_get_min_size(layout->children[i],
                                            &min_width, &min_height);

                        total_min_height += min_height;
                }

                int fill_height = (widget->rect.h - total_min_height) / layout->nchild;

                for (i = 0; i < layout->nchild; i++) {
                        widget_set_pos(layout->children[i],
                                       widget->rect.x, widget->rect.y + offset);
                        widget_get_min_size(layout->children[i],
                                            &min_width, &min_height);
                        widget_set_size(layout->children[i],
                                        widget->rect.w,
                                        min_height + fill_height);
                        offset += min_height + fill_height;
                }
        }
}

static void add_widget(Layout *layout, Widget *widget)
{
        BOX_LAYOUT_GET_CLASS(layout)->parent_add_widget(layout, widget);
        resize(BOX_LAYOUT(layout));
}

static void set_size(Widget *widget, int width, int height)
{
        BOX_LAYOUT_GET_CLASS(widget)->parent_set_size(widget, width, height);
        resize(BOX_LAYOUT(widget));
}

static void set_pos(Widget *widget, int x, int y)
{
        BOX_LAYOUT_GET_CLASS(widget)->parent_set_pos(widget, x, y);
        resize(BOX_LAYOUT(widget));
}

static void get_min_size(Widget *widget, int *width, int *height)
{
        int i;
        int min_width;
        int min_height;
        BoxLayout *this = BOX_LAYOUT(widget);
        Layout *layout = LAYOUT(widget);

        *width = 0;
        *height = 0;

        if (this->orientation == BOX_LAYOUT_HORIZONTAL) {
                for (i = 0; i < layout->nchild; i++) {
                        widget_get_min_size(layout->children[i], &min_width, &min_height);

                        *width += min_width;

                        if (min_height > *height) {
                                *height = min_height;
                        }
                }
        } else {
                for (i = 0; i < layout->nchild; i++) {
                        widget_get_min_size(layout->children[i], &min_width, &min_height);

                        *height += min_height;

                        if (min_width > *width) {
                                *width = min_width;
                        }
                }
        }
}

static void set_app(Widget *widget, App *app)
{
        BOX_LAYOUT_GET_CLASS(widget)->parent_set_app(widget, app);
        resize(BOX_LAYOUT(widget));
}

void box_layout_set_orientation(BoxLayout *this, int orientation)
{
        this->orientation = orientation;
}

static void instance_init(Object *obj)
{
        BoxLayout *this = BOX_LAYOUT(obj);
        this->orientation = BOX_LAYOUT_HORIZONTAL;
}

static void class_init(ObjectClass *oc, void *data)
{
        BoxLayoutClass *klass = BOX_LAYOUT_CLASS(oc);
        WidgetClass *wc = WIDGET_CLASS(oc);
        LayoutClass *lc = LAYOUT_CLASS(oc);

        klass->parent_set_size = wc->set_size;
        klass->parent_set_pos = wc->set_pos;
        klass->parent_set_app = wc->set_app;
        klass->parent_add_widget = lc->add_widget;

        wc->set_size = set_size;
        wc->set_pos = set_pos;
        wc->set_app = set_app;
        wc->get_min_size = get_min_size;
        lc->add_widget = add_widget;
}

BoxLayout *box_layout_new(void)
{
        BoxLayout *p = (BoxLayout *)object_new(TYPE_BOX_LAYOUT);
        printf("%p\n", p);
        return p;
}

static const TypeInfo type_info = {
        .name = TYPE_BOX_LAYOUT,
        .parent = TYPE_LAYOUT,
        .instance_size = sizeof(BoxLayout),
        .abstract = false,
        .class_size = sizeof(BoxLayoutClass),
        .instance_init = instance_init,
        .class_init = class_init,
};

void box_layout_type_register(void)
{
        type_register_static(&type_info);
}
