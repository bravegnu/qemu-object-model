#ifndef APP_HPP
#define APP_HPP

#include <SDL.h>

#include "theme.h"
#include "emitter.h"
#include "widget.h"

#define TYPE_APP "app"

struct Widget;
typedef struct Widget Widget;

typedef struct App
{
        /* private */
        Emitter parent;
        SDL_Window *window;
        SDL_Renderer *renderer;
        Widget *child;
        bool quit_flag;

        /* public */
        Theme *theme;
} App;

typedef struct AppClass {
        EmitterClass parent_class;
} AppClass;

#define APP_GET_CLASS(obj) \
        OBJECT_GET_CLASS(AppClass, obj, TYPE_APP)

#define APP_CLASS(klass) \
        OBJECT_CLASS_CHECK(AppClass, klass, TYPE_APP)

#define APP(obj) \
        OBJECT_CHECK(App, obj, TYPE_APP)

App *app_new(void);
void app_type_register(void);

void app_add(App *this, Widget *widget);
void app_run(App *this);
void app_quit(App *this);
void app_set_title(App *this, const char *title);
Theme *app_get_theme(App *this);

#endif
