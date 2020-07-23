#include <assert.h>

#include <SDL.h>

#include "widget.h"
#include "app.h"

#include "layout.h"

static void add_widget(Layout *this, Widget *widget)
{
        assert(this->nchild != LAYOUT_MAX_CHILDREN);

        this->children[this->nchild++] = widget;
        widget_set_app(widget, WIDGET(this)->app);
}

static void handle_event(Widget *widget, SDL_Event *event)
{
        int i;
        Layout *this = LAYOUT(widget);

        for (i = 0; i < this->nchild; i++)
                widget_handle_event(this->children[i], event);
}

static void draw(Widget *widget, SDL_Renderer *renderer)
{
        int i;
        Layout *this = LAYOUT(widget);

        for (i = 0; i < this->nchild; i++)
                widget_draw(this->children[i], renderer);
}

static void set_app(Widget *widget, App *app)
{
        int i;
        Layout *this = LAYOUT(widget);

        widget->app = app;
        for (i = 0; i < this->nchild; i++) {
                widget_set_app(this->children[i], app);
        }
}

void layout_add_widget(Layout *this, Widget *widget)
{
        LAYOUT_GET_CLASS(this)->add_widget(this, widget);
}

static void instance_init(Object *obj)
{
        Layout *this = LAYOUT(obj);
        this->nchild = 0;
}

static void class_init(ObjectClass *oc, void *data)
{
        LayoutClass *klass = LAYOUT_CLASS(oc);
        WidgetClass *wc = WIDGET_CLASS(oc);

        klass->add_widget = add_widget;
        wc->draw = draw;
        wc->handle_event = handle_event;
        wc->set_app = set_app;
}

Layout *layout_new(void)
{
        return (Layout *)object_new(TYPE_LAYOUT);
}

static const TypeInfo type_info = {
        .name = TYPE_LAYOUT,
        .parent = TYPE_WIDGET,
        .instance_size = sizeof(Layout),
        .abstract = true,
        .class_size = sizeof(LayoutClass),
        .instance_init = instance_init,
        .class_init = class_init,
};

void layout_type_register(void)
{
        type_register_static(&type_info);
}
