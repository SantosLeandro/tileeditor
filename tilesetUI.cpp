#include "tilesetUI.h"
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl.H>


TilesetUI::TilesetUI(int X, int Y, int W, int H, const char *L)
    : Fl_Box(X, Y, W, H, L), clicked(false) {}


void TilesetUI::draw() {

    Fl_Box::draw();
    if(img){
        img->draw(x(),y(),w(),h());
        // cpImg = img->copy(512,512);
        // cpImg->draw(x(),y(),w(),h());
        // w(512);
        // h(512);
    }
    
    //fl_draw_image(img,0,0,512,512);

    fl_color(FL_RED);
    fl_rect(mouseX+10, mouseY+10, tileSize, tileSize);
    if (clicked) {
        
    } else {
        //fl_circle(x() + w() / 2, y() + h() / 2, 50);
    }
}

int TilesetUI::handle(int event) {
    switch (event) {
        case FL_PUSH:  
            if (Fl::event_button() == FL_LEFT_MOUSE) {  
                std::cout << "Mouse clicked at (" << Fl::event_x() << ", " << Fl::event_y() << ")\n";
                clicked = !clicked;  
                redraw();  
            }
            return 1;
        case FL_MOVE:
            std::cout <<" mouse move\n";
           
            mouseX = Fl::event_x()/ tileSize * tileSize;
            mouseY = Fl::event_y()/ tileSize * tileSize;
            std::cout <<" x "<<Fl::event_x()<<" y "<<Fl::event_y()<<"\n";
            redraw();
            return 1;
        default:
            return Fl_Box::handle(event);  
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
            this->redraw();                 
        } else {
            delete img;                   
            fl_alert("Invalid Image file!");
        }
    }
}
