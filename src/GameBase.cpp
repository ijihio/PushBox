#include "GameBase.h"
// funny thing that you have to omit `static` here. Learn about global scope
// type qualifiers to understand why.
GameBase* GameBase::event_handling_instance;