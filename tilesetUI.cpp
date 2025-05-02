#include "tilesetUI.h"
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl.H>



TilesetUI::TilesetUI(int X, int Y, int W, int H, const char *L)
    : Fl_Double_Window(X, Y, W, H, L), clicked(false) {}


void TilesetUI::draw() {
    Fl_Double_Window::draw();
    if(img){
        std::cout <<" x() "<<x()<<" y() "<<y()<<"\n";
        //img->draw(0,0,w(),h());
        cpImg = img->copy(img->w()*scale,img->h()*scale);
        cpImg->draw(offsetX,offsetY,img->w(),img->h());
        // w(512);
        // h(512);
    }
    
    //fl_draw_image(img,0,0,512,512);
    // cursor vermelho
    fl_color(FL_RED);
    fl_line_style(1,2,0);
    fl_rect(mouseX, mouseY, tileSize*scale, tileSize*scale);
    fl_line_style(0,1,0);
    if (clicked) {
        
    } else {
        //fl_circle(x() + w() / 2, y() + h() / 2, 50);
    }
}

int TilesetUI::handle(int event) {
    tileSize = TileSelector::tileSize;
    switch (event) {
        case FL_MOUSEWHEEL:
        {
            int dy = Fl::event_dy();
            if (dy < 0)
            {
                scale += 1;
                this->redraw();
                // Scrolling up
                printf("Mouse wheel scrolled up.\n");
            }
            else if (dy > 0)
            {
                if(scale > 1) {
                    scale -= 1;
                    this->redraw();
                }
                

                // Scrolling down
                printf("Mouse wheel scrolled down.\n");
            }

            return 1;
        }
        case FL_PUSH:  
            if (Fl::event_button() == FL_LEFT_MOUSE) {  
                if(img){
                    int col = img->w() / tileSize;
                    tileId =  ((Fl::event_y()-offsetY) / (tileSize*scale)  * col) + ((Fl::event_x()-offsetX) / (tileSize*scale));
                    TileSelector::tileId = tileId;
                }
                redraw();  
            } if (Fl::event_button() == FL_MIDDLE_MOUSE) {
                moveTileset = true;
                imgPosX = Fl::event_x()  / (tileSize*scale) * (tileSize*scale);
                imgPosY = Fl::event_y() / (tileSize*scale) * (tileSize*scale);
                
                redraw();
            }
            return 1;
        case FL_RELEASE:
            if (Fl::event_button() == FL_MIDDLE_MOUSE) {
                moveTileset = false;
            }
            return 1;
        case FL_DRAG:
            if (moveTileset) {
                int dx = Fl::event_x() - imgPosX;
                int dy = Fl::event_y() - imgPosY;
                offsetX += dx;
                offsetY += dy;
                imgPosX = Fl::event_x();
                imgPosY = Fl::event_y();
                redraw();
            }
            return 1;
        case FL_MOVE:
            //std::cout <<" mouse move\n";
           
            mouseX = ((Fl::event_x() - offsetX) / (tileSize * scale)) * (tileSize * scale) + offsetX;
            mouseY = ((Fl::event_y() - offsetY) / (tileSize * scale)) * (tileSize * scale) + offsetY;
            //std::cout <<" x "<<Fl::event_x()<<" y "<<Fl::event_y()<<"\n";
            redraw();
            return 1;
        default:
            return Fl_Double_Window::handle(event);  
    }
}

void TilesetUI::load_image(const char *file) {

    if (file != NULL) {
        img = nullptr;

        std::string filename = file;
        if (filename.find(".bmp") != std::string::npos) {
            img = new Fl_BMP_Image(file); 
        } else if (filename.find(".png") != std::string::npos) {
            img = new Fl_PNG_Image(file);  
        } else if (filename.find(".jpg") != std::string::npos || filename.find(".jpeg") != std::string::npos) {
            img = new Fl_JPEG_Image(file); 
        }

        
        if (img && img->w() > 0 && img->h() > 0) {
            tileset[filename] = img;               
            this->redraw();                 
        } else {
            delete img;                   
            fl_alert("Invalid Image file!");
        }
    }
}

void TilesetUI::clearTileset()
{
    tileset.clear();
}
