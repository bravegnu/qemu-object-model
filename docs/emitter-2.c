#include <stdio.h>
#include <qwt.h>

void func(SignalSet signals, void *data)
{
        printf("Hello World!\n");
}

int main()
{
        Emitter *emitter;

        qwt_init();

        emitter = emitter_new();
        emitter_set_callback(emitter, func, NULL);
        emitter_set_when(emitter, SIGNAL_CLICKED);

        emitter_emit(emitter, SIGNAL_CLICKED);
        emitter_emit(emitter, SIGNAL_CLICKED);
        emitter_emit(emitter, SIGNAL_CLOSE);

        return 0;
}

/*
 * Output:
 * Hello World!
 * Hello World!
 */
