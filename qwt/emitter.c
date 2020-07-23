#include "emitter.h"

void emitter_set_callback(Emitter *this, Callback cb, void *data)
{
        this->cb = cb;
        this->data = data;
}

void emitter_set_when(Emitter *this, SignalSet when)
{
        this->when = when;
}

SignalSet emitter_get_when(Emitter *this)
{
        return this->when;
}

void emitter_emit(Emitter *this, SignalSet signals)
{
        if (this->when & signals) {
                if (this->cb) {
                        (this->cb)(signals, this->data);
                }
        }
}

static void instance_init(Object *obj)
{
        Emitter *this = EMITTER(obj);
        this->cb = NULL;
        this->when = 0;
}

Emitter * emitter_new(void)
{
        return (Emitter *)object_new(TYPE_EMITTER);
}

static void class_init(ObjectClass *oc, void *data)
{

}

static const TypeInfo type_info = {
        .name = TYPE_EMITTER,
        .parent = TYPE_OBJECT,
        .instance_size = sizeof(Emitter),
        .abstract = false,
        .class_size = sizeof(EmitterClass),
        .instance_init = instance_init,
        .class_init = class_init,
};

void emitter_type_register(void)
{
        type_register_static(&type_info);
}

