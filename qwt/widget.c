#include <SDL.h>
#include "app.h"
#include "emitter.h"

#include "widget.h"

static void set_size(Widget *this, int width, int height)
{
        this->rect.w = width;
        this->rect.h = height;
}

static void set_pos(Widget *this, int x, int y)
{
        this->rect.x = x;
        this->rect.y = y;
}

static void set_app(Widget *this, App *app)
{
        this->app = app;
}

static void instance_init(Object *obj)
{
        Widget *this = WIDGET(this);
        this->app = NULL;
        this->rect.x = 0;
        this->rect.y = 0;
        this->rect.w = 0;
        this->rect.h = 0;
}

static void class_init(ObjectClass *oc, void *data)
{
        WidgetClass *klass = WIDGET_CLASS(oc);

        klass->set_size = set_size;
        klass->set_pos = set_pos;
        klass->set_app = set_app;
}

void widget_draw(Widget *this, SDL_Renderer *renderer)
{
        WIDGET_GET_CLASS(this)->draw(this, renderer);
}

void widget_handle_event(Widget *this, SDL_Event *event)
{
        WIDGET_GET_CLASS(this)->handle_event(this, event);
}

void widget_get_min_size(Widget *this, int *width, int *height)
{
        WIDGET_GET_CLASS(this)->get_min_size(this, width, height);
}

void widget_set_size(Widget *this, int width, int height)
{
        WIDGET_GET_CLASS(this)->set_size(this, width, height);
}

void widget_set_pos(Widget *this, int x, int y)
{
        WIDGET_GET_CLASS(this)->set_pos(this, x, y);
}

void widget_set_app(Widget *this, App *app)
{
        WIDGET_GET_CLASS(this)->set_app(this, app);
}

App *widget_get_app(Widget *this)
{
        return this->app;
}

Widget *widget_new(void)
{
        return (Widget *)object_new(TYPE_WIDGET);
}

static const TypeInfo type_info = {
        .name = TYPE_WIDGET,
        .parent = TYPE_EMITTER,
        .instance_size = sizeof(Widget),
        .abstract = true,
        .class_size = sizeof(WidgetClass),
        .instance_init = instance_init,
        .class_init = class_init,
};

void widget_type_register(void)
{
        type_register_static(&type_info);
}
