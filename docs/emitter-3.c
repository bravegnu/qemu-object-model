#include <stdio.h>
#include <qwt.h>

void func1(SignalSet signals, void *data)
{
        printf("Hello World!\n");
}

void func2(SignalSet signals, void *data)
{
        printf("Goodbye World!\n");
}

int main()
{
        Emitter *emitter1;
        Emitter *emitter2;

        qwt_init();

        emitter1 = emitter_new();
        emitter2 = emitter_new();

        emitter_set_callback(emitter1, func1, NULL);
        emitter_set_when(emitter1, SIGNAL_CLICKED);

        emitter_set_callback(emitter2, func2, NULL);
        emitter_set_when(emitter2, SIGNAL_CLOSE);

        emitter_emit(emitter1, SIGNAL_CLICKED);
        emitter_emit(emitter2, SIGNAL_CLOSE);

        return 0;
}

/*
 * Output:
 * Hello World!
 * Goodbye World!
 */
