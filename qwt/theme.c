#include <errno.h>
#include "theme.h"

static bool read_color(char *value, SDL_Color *color)
{
        int matched;

        matched = sscanf(value, "%d,%d,%d",
                         &color->r, &color->g, &color->b);
        if (matched != 3) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "incorrect color format");
                return false;
        }

        return true;
}

bool theme_read(Theme *this, const char *filename)
{
        FILE *fp;
        char *retp;
        int i;
        bool status = false;

        char line[64];
        char key[64];
        char value[64];
        char font_name[64];
        int size;
        int matched;

        fp = fopen(filename, "r");
        if (fp == NULL) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error opening file: %s",
                             strerror(errno));
                status = false;
                goto exit;
        }

        for (i = 0; i < 6; i++) {
                retp = fgets(line, sizeof(line), fp);
                if (retp == NULL) {
                        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "premature end of file");
                        status = false;
                        goto exit;
                }

                matched = sscanf(line, "%[^:]:%[^:]", key, value);
                if (matched != 2) {
                        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "incorrect format");
                        status = false;
                        goto exit;
                }

                // printf("%s = %s\n", key, value);

                if (strcmp(key, "border-color") == 0) {
                        status = read_color(value, &this->border_color);
                        if (!status)
                                goto exit;
                } else if (strcmp(key, "fill-color") == 0) {
                        status = read_color(value, &this->fill_color);
                        if (!status)
                                goto exit;
                } else if (strcmp(key, "select-color") == 0) {
                        status = read_color(value, &this->select_color);
                        if (!status)
                                goto exit;
                } else if (strcmp(key, "text-color") == 0) {
                        status = read_color(value, &this->text_color);
                        if (!status)
                                goto exit;
                } else if (strcmp(key, "activate-color") == 0) {
                        status = read_color(value, &this->activate_color);
                        if (!status)
                                goto exit;
                } else if (strcmp(key, "font") == 0) {
                        sscanf(value, "%[^,],%d", font_name, &size);
                        this->font = TTF_OpenFont(font_name, size);
                        if (!this->font) {
                                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                                             "error opening font: %s", TTF_GetError());
                                status = false;
                                goto exit;
                        }
                }
        }

        status = true;

 exit:
        if (fp != NULL)
                fclose(fp);

        return status;
}

static void instance_init(Object *obj)
{

}

static void class_init(ObjectClass *oc, void *data)
{

}

Theme *theme_new(void)
{
        return (Theme *)object_new(TYPE_THEME);
}

static const TypeInfo type_info = {
        .name = TYPE_THEME,
        .parent = TYPE_OBJECT,
        .instance_size = sizeof(Theme),
        .abstract = false,
        .class_size = sizeof(ThemeClass),
        .instance_init = instance_init,
        .class_init = class_init,
};

void theme_type_register(void)
{
        type_register_static(&type_info);
}

