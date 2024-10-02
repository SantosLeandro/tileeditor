#pragma once

#include "level.h"
#include "global.h"

Level* LoadLevel(const char* filename);

bool SaveLevel(Level *level, const char* filename);

Level* LoadLevelFile(const char* filename);

void LoadGameObjects();

void DebugVal(const char *n, int v);
void DebugVal(const char *n, float v);
void DebugVal(const char *n, const char *v);