#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Window.H>
#include <FL/gl.h>
#include "gl_render.h"
#include "global.h"
#include <list>

class TileMemo {
public:
    int x,y,id;
    TileMemo(){}
    TileMemo(int x, int y, int id){
        this->x = x;
        this->y = y;
        this->id = id;
    }
};

class TileCopy {
    public:
    std::vector<int> tiles;
    int w,h;
    int layerId;
};

// Custom OpenGL window inheriting from Fl_Gl_Window
class EditorView : public Fl_Gl_Window
{
protected:
    GLRender render;
public:
    EditorView(int x, int y, int w, int h, const char *l = 0)
        : Fl_Gl_Window(x, y, w, h, l) {}

    void draw() override;
    int handle(int event);
    void handleMouseMovement(int x, int y);
    void handleSelectionTool(int startX, int startY, int endX, int endY);
    void insertTile(int x, int y, int id, bool tilememo);
    void copyTilesData();
    void pasteTilesData();
    void deleteTilesData();
    void undo();
    Level *level = nullptr;
    int oldX = 0;
    int oldY = 0;
    int mouseX = 0;
    int mouseY = 0;
    int tileId = 3;
    int layerId = 0;
    bool selectionTool = false;
    int startX = 0;
    int startY = 0;
    int selectX = 0;
    int selectY = 0;
    std::list<TileMemo> rollback;
    std::list<TileMemo> copyTiles;
};
