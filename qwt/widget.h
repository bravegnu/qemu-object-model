#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SDL.h>
#include "app.h"
#include "emitter.h"

#define TYPE_WIDGET "widget"

struct App;
typedef struct App App;

typedef struct Widget
{
        /* private */
        Emitter parent;
        SDL_Rect rect;
        App *app;
} Widget;

typedef struct WidgetClass {
        EmitterClass parent_class;

        void (*draw)(Widget *this, SDL_Renderer *renderer);
        void (*handle_event)(Widget *this, SDL_Event *event);
        void (*get_min_size)(Widget *this, int *width, int *height);
        void (*set_size)(Widget *this, int width, int height);
        void (*set_pos)(Widget *this, int x, int y);
        void (*set_app)(Widget *this, App *app);
} WidgetClass;

#define WIDGET_GET_CLASS(obj) \
        OBJECT_GET_CLASS(WidgetClass, obj, TYPE_WIDGET)

#define WIDGET_CLASS(klass) \
        OBJECT_CLASS_CHECK(WidgetClass, klass, TYPE_WIDGET)

#define WIDGET(obj) \
        OBJECT_CHECK(Widget, obj, TYPE_WIDGET)

Widget *widget_new(void);
void widget_type_register(void);
void widget_draw(Widget *this, SDL_Renderer *renderer);
void widget_handle_event(Widget *this, SDL_Event *event);
void widget_get_min_size(Widget *this, int *width, int *height);
void widget_set_size(Widget *this, int width, int height);
void widget_set_pos(Widget *this, int x, int y);
void widget_set_app(Widget *this, App *app);
App *widget_get_app(Widget *this);

#endif
