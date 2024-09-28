#pragma once

#include "level.h"


Level* LoadLevel(const char* filename);

bool SaveLevel(Level *level, const char* filename);