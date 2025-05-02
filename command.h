#pragma once

#include "layer.h"

class Command
{
protected:
    Layer m_layer;
public:
    virtual void execute(){}
};