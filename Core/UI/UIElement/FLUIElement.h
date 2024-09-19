#pragma once
#include "../FLUI.h"

namespace FLUI
{
    class FLUIElement
    {
    public:
        virtual void pushDrawCommands() = 0;
    };
}
