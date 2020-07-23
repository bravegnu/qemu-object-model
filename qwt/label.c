#include "label.h"

static void label_draw(Widget *widget, SDL_Renderer *renderer)
{
        Label *this = LABEL(widget);
        Theme *theme = app_get_theme(widget->app);

        SDL_Color *fill = &theme->fill_color;
        SDL_Color *activate = &theme->activate_color;
        SDL_Color *text_color = &theme->text_color;

        SDL_SetRenderDrawColor(renderer, fill->r, fill->g, fill->b, 0xFF);
        SDL_RenderFillRect(renderer, &widget->rect);

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

static void label_handle_event(Widget *widget, SDL_Event *event)
{

}

static void label_get_min_size(Widget *widget, int *width, int *height)
{
        Label *this = LABEL(widget);

        if (!widget->app)
                return;

        Theme *theme = app_get_theme(widget->app);

        SDL_Color *text_color = &theme->text_color;
        SDL_Surface *surface = TTF_RenderUTF8_Blended(theme->font, this->text,
                                                      *text_color);

        *width = surface->w + 10;
        *height = surface->h + 10;

        SDL_FreeSurface(surface);
}

void label_set_text(Label *this, const char *text)
{
        snprintf(this->text, sizeof(this->text), "%s", text);
}

static void instance_init(Object *obj)
{
        Label *this = LABEL(obj);
        snprintf(this->text, sizeof(this->text), "Untitled");
}

static void class_init(ObjectClass *oc, void *data)
{
        WidgetClass *wc = WIDGET_CLASS(oc);

        wc->draw = label_draw;
        wc->get_min_size = label_get_min_size;
        wc->handle_event = label_handle_event;
}

Label *label_new(void)
{
        return (Label *)object_new(TYPE_LABEL);
}

static const TypeInfo type_info = {
        .name = TYPE_LABEL,
        .parent = TYPE_WIDGET,
        .instance_size = sizeof(Label),
        .abstract = false,
        .class_size = sizeof(LabelClass),
        .instance_init = instance_init,
        .class_init = class_init,
};

void label_type_register(void)
{
        type_register_static(&type_info);
}
