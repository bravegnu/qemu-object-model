#ifndef QWT_THEME
#define QWT_THEME

#include <SDL.h>
#include <SDL_ttf.h>
#include "emitter.h"

#define TYPE_THEME "theme"

typedef struct Theme
{
        Object parent;

        /* public */
        TTF_Font *font;
        SDL_Color border_color;
        SDL_Color fill_color;
        SDL_Color text_color;
        SDL_Color select_color;
        SDL_Color activate_color;
} Theme;

typedef struct ThemeClass {
        ObjectClass parent_class;
} ThemeClass;

#define THEME_GET_CLASS(obj) \
        OBJECT_GET_CLASS(ThemeClass, obj, TYPE_THEME)

#define THEME_CLASS(klass) \
        OBJECT_CLASS_CHECK(ThemeClass, klass, TYPE_THEME)

#define THEME(obj) \
        OBJECT_CHECK(Theme, obj, TYPE_THEME)

Theme *theme_new(void);
void theme_type_register(void);
bool theme_read(Theme *theme, const char *filename);

#endif
