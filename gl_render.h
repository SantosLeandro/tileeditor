#pragma once
#include "level.h"

class GLRender
{
protected:
    int w, h;
    int scale = 1;
    int x = 0;
    int y = 0;
public:
    void UpdateViewPort(int w, int h);
    void Prepare2D();
    void DrawTest();
    void DrawLayer(const Layer *layer, int t);
    void DrawLevel(const Level *level);
    void DrawGrid(int w, int h, int t);
    void DrawBackground(int w, int h, int t);
    void ClearScreen();
    void ScaleUp();
    void ScaleDown();
    void Translate(int x, int y);
};