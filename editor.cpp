#include "editor.h"
#include <math.h>
#include <iostream>

void EditorView::draw()
{
    // if(!level.layer[0].texture){
    //     level.layer[0].texture = new Texture();
    //     level.layer[0].texture->LoadFromFile("texture/tileset_1616.png");
    // }
    if (!valid())
    {
        render.UpdateViewPort(w(), h());
        render.Prepare2D();
    }
    render.ClearScreen();
    render.DrawLevel(level);
}

// Override the handle() function to capture events
int EditorView::handle(int event)
{
    int deltaX = Fl::event_x() - oldX;
    int deltaY = Fl::event_y() - oldY;
    oldX = Fl::event_x();
    oldY = Fl::event_y();
    switch (event)
    {
    case FL_MOUSEWHEEL:
    {
        int dy = Fl::event_dy();
        if (dy < 0)
        {
            render.ScaleDown();
            this->redraw();
            // Scrolling up
            printf("Mouse wheel scrolled up.\n");
        }
        else if (dy > 0)
        {
            render.ScaleUp();
            this->redraw();

            // Scrolling down
            printf("Mouse wheel scrolled down.\n");
        }

        return 1;
    }
    case FL_PUSH: // Mouse button press
        std::cout << "Mouse button pressed at ("
                  << Fl::event_x() << ", " << Fl::event_y() << ")"
                  << std::endl;
        return 1; // Event was handled
    case FL_DRAG: // Mouse dragging
        if (Fl::event_button() == FL_MIDDLE_MOUSE)
        {
            render.Translate(deltaX, deltaY);
            this->redraw();
        }
        std::cout << "Mouse drag at ("
                  << Fl::event_x() << ", " << Fl::event_y() << ")"
                  << std::endl;
        return 1;
    case FL_RELEASE: // Mouse button release
        std::cout << "Mouse button released" << std::endl;
        return 1;
    case FL_KEYDOWN: // Key press
        std::cout << "Key pressed: " << Fl::event_key() << std::endl;
        return 1;
    case FL_KEYUP: // Key release
        std::cout << "Key released: " << Fl::event_key() << std::endl;
        return 1;
    case FL_FOCUS:   // Window focus
        return 1;    // Accept the focus
    case FL_UNFOCUS: // Window loses focus
        return 1;    // Accept the unfocus
    default:
        // Pass other events to the default handler
        return Fl_Gl_Window::handle(event);
    }
}