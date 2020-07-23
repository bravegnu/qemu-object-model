#ifndef EMITTER_HPP
#define EMITTER_HPP

#include "object.h"
#include <stdint.h>

#define TYPE_EMITTER "emitter"

typedef uint32_t SignalSet;
typedef void (*Callback)(SignalSet signals, void *data);

enum {
        SIGNAL_CLICKED = 1 << 0,
        SIGNAL_CLOSE = 1 << 1,
        SIGNAL_MAX = SIGNAL_CLOSE
};

typedef struct Emitter
{
        Object parent;

        /* private */
        Callback cb;
        void *data;
        SignalSet when;
} Emitter;

typedef struct EmitterClass {
        ObjectClass parent_class;
} EmitterClass;

#define EMITTER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(EmitterClass, obj, TYPE_EMITTER)

#define EMITTER_CLASS(klass) \
        OBJECT_CLASS_CHECK(EmitterClass, klass, TYPE_EMITTER)

#define EMITTER(obj) \
        OBJECT_CHECK(Emitter, obj, TYPE_EMITTER)

Emitter* emitter_new(void);
void emitter_set_callback(Emitter *this, Callback cb, void *data);
void emitter_set_when(Emitter *this, SignalSet when);
SignalSet emitter_get_when(Emitter *this);
void emitter_emit(Emitter *this, SignalSet signals);
void emitter_type_register(void);

#endif
