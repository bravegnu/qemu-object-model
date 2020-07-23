#include "base.h"
#include <stdio.h>

int main()
{
   object_type_register();
   Base_register();

   Base *obj = Base_new();
   BASE_GET_CLASS(obj)->say(obj);

   return 0;
}
