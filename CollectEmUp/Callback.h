#pragma once

#include <functional>
#include "Event.h"

typedef std::function<void( Event e )> Callback;
typedef std::vector<Callback> CallbackVector;