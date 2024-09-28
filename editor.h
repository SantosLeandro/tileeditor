#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Window.H>
#include <FL/gl.h>
#include "gl_render.h"
#include "global.h"

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

    void insertTile(int x, int y, int id);
    Level *level = nullptr;
    int oldX = 0;
    int oldY = 0;
    int mouseX = 0;
    int mouseY = 0;
    int tileId = 3;
    int layerId = 0;
};
