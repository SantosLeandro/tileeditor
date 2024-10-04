#include "editor.h"
#include <math.h>
#include <iostream>

void EditorView::draw()
{
    // if(!level.layer[TileSelector::layerId].texture){
    //     level.layer[TileSelector::layerId].texture = new Texture();
    //     level.layer[TileSelector::layerId].texture->LoadFromFile("texture/tileset_1616.png");
    // }
    if (!valid())
    {
        render.UpdateViewPort(w(), h());
        render.Prepare2D();
    }
    render.ClearScreen();
    render.DrawLevel(level);
    if(level) {
        render.DrawLayerLines(level->layer[TileSelector::layerId].data[0].size(), level->layer[TileSelector::layerId].data.size(),level->tileSize);
    }
    render.DrawCursor(mouseX, mouseY, level);
    if (selectionTool)
    {
        render.DrawSelectionTool(level, startX, startY, selectX, selectY);
    }
}


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
        }
        else if (dy > 0)
        {
            render.ScaleUp();
            this->redraw();
        }

        return 1;
    }
    case FL_PUSH: // Mouse button press

        if (Fl::event_button() == FL_LEFT_MOUSE)
        {
            if(insertMode = 0) {
                this->insertTile(mouseX, mouseY, TileSelector::tileId, true);
                
            } else {
                insertGameObject(mouseX, mouseY, gameObjectId);
            }
            this->redraw();
        }
        if (Fl::event_button() == FL_RIGHT_MOUSE)
        {
            this->startX = (Fl::event_x() - render.GetX()) / render.GetScale();
            this->startY = (Fl::event_y() - render.GetY()) / render.GetScale();
            this->startX = startX / level->tileSize * level->tileSize;
            this->startY = startY / level->tileSize * level->tileSize;
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
            selectionTool = true;
            selectX = (Fl::event_x() - render.GetX()) / render.GetScale();
            selectY = (Fl::event_y() - render.GetY()) / render.GetScale();

            this->redraw();
        }
        else
        {
            std::cout << " stop drag\n";
            selectX = 0;
            selectY = 0;
        }

        return 1;
    case FL_RELEASE: // Mouse button release

        return 1;
    case FL_KEYDOWN: // Key press
        if ((Fl::event_state() & FL_CTRL) && Fl::event_key() == 'z')
        {
            this->undo();
        }

        if ((Fl::event_state() & FL_CTRL) && Fl::event_key() == 'c')
        {
           this->copyTilesData();
        }

        if ((Fl::event_state() & FL_CTRL) && Fl::event_key() == 'v')
        {
            this->pasteTilesData();
        }

        if(Fl::event_key() == FL_Delete)
        {
            std::cout << "todo: Delete \n";
            this->deleteTilesData();
            this->redraw();
        }

        return 1;
    case FL_KEYUP: // Key release

        return 1;
    case FL_FOCUS:   // Window focus
        return 1;    // Accept the focus
    case FL_UNFOCUS: // Window loses focus
        return 1;    // Accept the unfocus
    case FL_MOVE:
        this->handleMouseMovement(Fl::event_x(), Fl::event_y());
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

void EditorView::handleSelectionTool(int startX, int startY, int endX, int endY)
{
}

void EditorView::insertTile(int x, int y, int id, bool tilememo)
{
    if (!level)
    {
        return;
    }

    int h = y / level->tileSize;
    int w = x / level->tileSize;

    if (h > this->level->layer[TileSelector::layerId].data.size() || w > this->level->layer[TileSelector::layerId].data[0].size()) {
        std::cout<<"Out of bounds";
        return;
    }
    // std::cout << "size" << level->layer[TileSelector::layerId].data.size()<<"\n";
    // std::cout << "size" << level->layer[TileSelector::layerId].data[0].size()<<"\n";
    // std::cout << "posX: " << w << std::endl;
    // std::cout << "posY: " << h << std::endl;
    // std::cout << this->level->layer[TileSelector::layerId].data[h][w] <<"\n";
    if (tilememo)
    {
        rollback.push_back(TileMemo(x, y, this->level->layer[TileSelector::layerId].data[h][w]));
        if (rollback.size() > 100)
        {
            rollback.pop_front();
        }
    }

    this->level->layer[TileSelector::layerId].data[h][w] = id;
}

void EditorView::insertGameObject(int x, int y, int id)
{
    if (!level)
    {
        return;
    }

    if (id < 0) {
        this->level->layer[TileSelector::layerId].removeGameObject(x,y);
    } else {
        int h = y / level->tileSize * level->tileSize;
        int w = x / level->tileSize * level->tileSize;
        this->level->layer[TileSelector::layerId].gameObjects.push_back(GameObject(TileSelector::gameObjects[id].name,w,h));
    }
    
}

void EditorView::copyTilesData()
{
    selectionTool = false;
    copyTiles.clear();
    int endW = selectX / level->tileSize;
    int endH = selectY / level->tileSize;
    int startW = startX / level->tileSize;
    int startH = startY / level->tileSize;

    int yv = 0;
    for (int i = startH; i <= endH; i++)
    {
        int xv = 0;
        for (int j = startW; j <= endW; j++)
        {
            if(i >= this->level->layer[TileSelector::layerId].data.size() || j >= this->level->layer[TileSelector::layerId].data[0].size()){
                continue;
            }
            copyTiles.push_back(TileMemo(xv * level->tileSize, yv * level->tileSize, this->level->layer[TileSelector::layerId].data[i][j]));
            xv += 1;
        }
        yv += 1;
    }
    this->redraw();
}

void EditorView::pasteTilesData()
{
    if (copyTiles.size() > 0)
    {
        std::list<TileMemo>::iterator it;
        for (it = copyTiles.begin(); it != copyTiles.end(); ++it)
        {
            this->insertTile(mouseX + it->x, mouseY + it->y, it->id, true);
        }
    }
    this->redraw();
}

void EditorView::deleteTilesData()
{
    selectionTool = false;
    int endW = selectX / level->tileSize;
    int endH = selectY / level->tileSize;
    int startW = startX / level->tileSize;
    int startH = startY / level->tileSize;
    int yv = 0;
    for (int i = startH; i <= endH; i++)
    {
        int xv = 0;
        for (int j = startW; j <= endW; j++)
        {
            if(i >= this->level->layer[TileSelector::layerId].data.size() || j >= this->level->layer[TileSelector::layerId].data[0].size()){
                continue;
            }
            this->insertTile(j*level->tileSize, i*level->tileSize, -1, true);
            xv += 1;
        }
        yv += 1;
    }
}

void EditorView::undo()
{
    if(rollback.size() > 0 ) {
        insertTile(rollback.back().x, rollback.back().y, rollback.back().id, false);
        rollback.pop_back();
        this->redraw();
    }
}

void EditorView::applyLayer(int w, int h, const char* name, const char* texture)
{
   this->level->layer[TileSelector::layerId].update(w,h,name,texture); 
}
