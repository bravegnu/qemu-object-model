#include <stdio.h>
#include <qwt.h>

int main()
{
        App *app;

        qwt_init();

        app = app_new();
        app_set_title(app, "My App!");

        app_run(app);

        return 0;
}

