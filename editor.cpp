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
    render.DrawCursor(mouseX,mouseY,level);
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

        if (Fl::event_button() == FL_LEFT_MOUSE)
        {
            this->insertTile(mouseX,mouseY,TileSelector::tileId,true);
            this->redraw();
        }
        return 1; // Event was handled
    case FL_DRAG: // Mouse dragging
        if (Fl::event_button() == FL_MIDDLE_MOUSE)
        {
            render.Translate(deltaX, deltaY);
            this->redraw();
        }
        if (Fl::event_button() == FL_RIGHT_MOUSE)
        {
            std::cout << "Selection tool\n";
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
        if ((Fl::event_state() & FL_CTRL) && Fl::event_key() == 'z' && rollback.size() > 0) {
            insertTile(rollback.back().x,rollback.back().y,rollback.back().id,false);
            rollback.pop_back();
            //std::cout<<rollback[last].x<<" y "<<rollback[last].y<<rollback[last].id<<"\n";
             std::cout << "rollback\n";
            this->redraw();
        }
        
        std::cout << "Key pressed: " << Fl::event_key() << std::endl;
        return 1;
    case FL_KEYUP: // Key release
        std::cout << "Key released: " << Fl::event_key() << std::endl;
        return 1;
    case FL_FOCUS:   // Window focus
        return 1;    // Accept the focus
    case FL_UNFOCUS: // Window loses focus
        return 1;    // Accept the unfocus
    case FL_MOVE:
       this->handleMouseMovement(Fl::event_x(),Fl::event_y());
        return 1;
    default:
        // Pass other events to the default handler
        
        return Fl_Gl_Window::handle(event);
    }
}

void EditorView::handleMouseMovement(int x, int y)
{
    mouseX = (x - render.GetX()) / render.GetScale();
    mouseY = (y - render.GetY()) / render.GetScale();
    this->redraw();
}

void EditorView::insertTile(int x, int y, int id, bool tilememo)
{
    if(!level) {
        return;
    }

    int h = y / level->tileSize;
    int w = x / level->tileSize;
    // std::cout << "size" << level->layer[0].data.size()<<"\n";
    // std::cout << "size" << level->layer[0].data[0].size()<<"\n";
    // std::cout << "posX: " << w << std::endl;
    // std::cout << "posY: " << h << std::endl;
    // std::cout << this->level->layer[0].data[h][w] <<"\n";
    if(tilememo) {
        rollback.push_back(TileMemo(x,y,this->level->layer[0].data[h][w]));
        if(rollback.size() > 100 ){
            rollback.pop_front();
        }
    }
    
    this->level->layer[0].data[h][w] = id;

    
    //level->layer[0].data[h][w] = tileId;
}
