#pragma once
#include "level.h"
#include "sprite.h"

class GLRender
{
protected:
    int w, h;
    int scale = 1;
    int x = 0;
    int y = 0;
    float alpha = 1.0f;
public:
    void UpdateViewPort(int w, int h);
    void Prepare2D();
    void DrawTest();
    void DrawCursor(int x, int y, Level *level);
    void DrawLayer(const Layer *layer, int t);
    void DrawLevel(const Level *level);
    void DrawSelectionTool(const Level *level, int x1, int y1, int x2, int y2);
    void DrawGrid(int w, int h, int t);
    void DrawBackground(int w, int h, int t);
    void DrawLayerLines(int w, int h, int t);
    void DrawGameObject(Sprite sprite, int x, int y, Texture* texture);
    void ClearScreen();
    void ScaleUp();
    void ScaleDown();
    const int GetScale();
    const int GetX();
    const int GetY();
    void Translate(int x, int y);
};