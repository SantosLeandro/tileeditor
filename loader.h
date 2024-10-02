#pragma once

#include "level.h"


Level* LoadLevel(const char* filename);

bool SaveLevel(Level *level, const char* filename);

Level* LoadLevelFile(const char* filename);

void DebugVal(const char *n, int v);
void DebugVal(const char *n, float v);
void DebugVal(const char *n, const char *v);