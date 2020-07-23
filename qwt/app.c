#include <stdio.h>
#include <error.h>
#include <signal.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "app.h"
#include "widget.h"
#include "theme.h"

static void handle_window_event(App *this, SDL_Event *event)
{
        if (event->window.event == SDL_WINDOWEVENT_RESIZED) {
                int w, h;
                if (this->child) {
                        widget_set_size(this->child,
                                        event->window.data1,
                                        event->window.data2);

                        widget_get_min_size(this->child, &w, &h);
                        SDL_SetWindowMinimumSize(this->window, w, h);
                }
        } else if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
                emitter_emit(EMITTER(this), SIGNAL_CLOSE);
        }
}

void app_run(App *this)
{
        while (!this->quit_flag) {
                SDL_Event event;
                SDL_Surface *sp;
                SDL_Rect rect;

                while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_WINDOWEVENT)
                                handle_window_event(this, &event);

                        if (this->child)
                                widget_handle_event(this->child, &event);

                }

                sp = SDL_GetWindowSurface(this->window);
                rect.x = 0;
                rect.y = 0;
                rect.w = sp->w;
                rect.h = sp->h;

                SDL_RenderClear(this->renderer);
                SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0xFF);
                SDL_RenderFillRect(this->renderer, &rect);

                if (this->child)
                        widget_draw(this->child, this->renderer);

                SDL_RenderPresent(this->renderer);
        }
}

void app_add(App *this, Widget *widget)
{
        int w, h;

        this->child = widget;
        widget_set_app(this->child, this);
        widget_set_pos(this->child, 0, 0);

        SDL_GetWindowSize(this->window, &w, &h);
        widget_set_size(this->child, w, h);

        widget_get_min_size(this->child, &w, &h);
        SDL_SetWindowMinimumSize(this->window, w, h);
}

void app_quit(App *this)
{
        this->quit_flag = true;
}

void app_set_title(App *this, const char *title)
{
        SDL_SetWindowTitle(this->window, title);
}

Theme *app_get_theme(App *this)
{
        return this->theme;
}

static void instance_init(Object *obj)
{
        App *this = APP(this);
        int ret;

        this->quit_flag = false;
        this->child = NULL;

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
                error(1, 0, "SDL_Init: %s", SDL_GetError());

        /* Disable blocking of Ctrl-C */
        signal(SIGINT, SIG_DFL);

        if (TTF_Init() == -1)
                error(1, 0, "TTF_Init: %s", TTF_GetError());

        this->theme = theme_new();
        if (!theme_read(this->theme, "qwt/black.theme"))
                error(1, 0, "error reading theme");

        this->window = SDL_CreateWindow("Untitled",          // window title
                                  SDL_WINDOWPOS_UNDEFINED,   // initial x position
                                  SDL_WINDOWPOS_UNDEFINED,   // initial y position
                                  640,                       // width, in pixels
                                  480,                       // height, in pixels
                                  SDL_WINDOW_RESIZABLE);
        if (this->window == NULL)
                error(1, 0, "Could not create window: %s\n", SDL_GetError());

        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
}

static void instance_finalize(Object *obj)
{
        App *this = APP(obj);

        SDL_DestroyRenderer(this->renderer);

        // Close and destroy the window
        SDL_DestroyWindow(this->window);

        // Clean up
        SDL_Quit();
}

static void class_init(ObjectClass *oc, void *data)
{

}

App *app_new(void)
{
        return (App *)object_new(TYPE_APP);
}

static const TypeInfo type_info = {
        .name = TYPE_APP,
        .parent = TYPE_EMITTER,
        .instance_size = sizeof(App),
        .abstract = false,
        .class_size = sizeof(AppClass),
        .instance_init = instance_init,
        .instance_finalize = instance_finalize,
        .class_init = class_init,
};

void app_type_register(void)
{
        type_register_static(&type_info);
}

