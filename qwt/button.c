#include "app.h"
#include "emitter.h"
#include "widget.h"

#include "button.h"

static void button_draw(Widget *widget, SDL_Renderer *renderer)
{
        Button *this = BUTTON(widget);
        Theme *theme = app_get_theme(widget_get_app(widget));

        SDL_Color *border = &theme->border_color;
        SDL_Color *fill = &theme->fill_color;
        SDL_Color *activate = &theme->activate_color;
        SDL_Color *text_color = &theme->text_color;

        if (this->pressed) {
                SDL_SetRenderDrawColor(renderer, activate->r, activate->g, activate->b, 0xFF);
                SDL_RenderFillRect(renderer, &widget->rect);
                SDL_SetRenderDrawColor(renderer, border->r, border->g, border->b, 0xFF);
                SDL_RenderDrawRect(renderer, &widget->rect);
        } else {
                SDL_SetRenderDrawColor(renderer, fill->r, fill->g, fill->b, 0xFF);
                SDL_RenderFillRect(renderer, &widget->rect);
                SDL_SetRenderDrawColor(renderer, border->r, border->g, border->b, 0xFF);
                SDL_RenderDrawRect(renderer, &widget->rect);
        }

        SDL_Surface *surface = TTF_RenderUTF8_Blended(theme->font, this->text,
                                                      *text_color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect rect = { widget->rect.x + widget->rect.w / 2 - surface->w / 2,
                          widget->rect.y + widget->rect.h / 2 - surface->h / 2,
                          surface->w, surface->h };
        SDL_RenderCopy(renderer, texture, NULL, &rect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
}

static void handle_event(Widget *widget, SDL_Event *event)
{
        Button *this = BUTTON(widget);

        if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
                SDL_MouseButtonEvent *me = (SDL_MouseButtonEvent *)event;
                SDL_Point p = { me->x, me->y };
                if (SDL_PointInRect(&p, &widget->rect)) {
                        int new_state = (event->type == SDL_MOUSEBUTTONDOWN);
                        int old_state = this->pressed;

                        if (new_state != old_state && new_state == 0) {
                                emitter_emit(EMITTER(this), SIGNAL_CLICKED);
                        }

                        this->pressed = new_state;
                }
        }
}

static void get_min_size(Widget *widget, int *width, int *height)
{
        Button *this = BUTTON(widget);

        if (!widget->app)
                return;

        Theme *theme = app_get_theme(widget->app);
        SDL_Surface *surface = TTF_RenderUTF8_Blended(theme->font,
                                                      this->text,
                                                      theme->text_color);

        *width = surface->w + 10;
        *height = surface->h + 10;

        SDL_FreeSurface(surface);
}

void button_set_text(Button *this, const char *text)
{
        snprintf(this->text, sizeof(this->text), "%s", text);
}

static void instance_init(Object *obj)
{
        Button *this = BUTTON(obj);
        snprintf(this->text, sizeof(this->text), "Untitled");
        this->pressed = false;
}

static void class_init(ObjectClass *oc, void *data)
{
        WidgetClass *wc = WIDGET_CLASS(oc);

        wc->draw = button_draw;
        wc->get_min_size = get_min_size;
        wc->handle_event = handle_event;
}

Button *button_new(void)
{
        return (Button *)object_new(TYPE_BUTTON);
}

static const TypeInfo type_info = {
        .name = TYPE_BUTTON,
        .parent = TYPE_WIDGET,
        .instance_size = sizeof(Button),
        .abstract = false,
        .class_size = sizeof(ButtonClass),
        .instance_init = instance_init,
        .class_init = class_init,
};

void button_type_register(void)
{
        type_register_static(&type_info);
}
