#include "editorUI.h"

int main(int argc, char **argv)
{
    EditorUI* editorUI = new EditorUI();
    editorUI->show(argc,argv);
    return Fl::run();
    // Fl_Window *window = new Fl_Window(800, 600, "FLTK + OpenGL Example");
    // MyGLWindow *glWindow = new MyGLWindow(10, 10, 780, 580);
    // window->end();
    // window->show(argc, argv);
    // return Fl::run();
}
