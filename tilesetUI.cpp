#include "tilesetUI.h"
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl.H>

// Constructor
TilesetUI::TilesetUI(int X, int Y, int W, int H, const char *L)
    : Fl_Box(X, Y, W, H, L), clicked(false) {}

// Override the draw() method for custom drawing
void TilesetUI::draw() {
    // Call the base class draw() to ensure the image is drawn
    Fl_Box::draw();
    if(img){
        cpImg = img->copy(512,512);
        cpImg->draw(x(),y(),w(),h());
    }
    
    //fl_draw_image(img,0,0,512,512);
   
    // Custom drawing logic (for example, a red rectangle)
    fl_color(FL_RED);  // Set drawing color to red

    if (clicked) {
        // Draw a rectangle when the mouse is clicked
        fl_rect(x() + 20, y() + 20, 100, 100);
    } else {
        // Draw a circle when not clicked
        fl_circle(x() + w() / 2, y() + h() / 2, 50);
    }
}

// Override the handle() method to capture mouse click events
int TilesetUI::handle(int event) {
    switch (event) {
        case FL_PUSH:  // Mouse click detected
            if (Fl::event_button() == FL_LEFT_MOUSE) {  // Check if it's a left mouse click
                std::cout << "Mouse clicked at (" << Fl::event_x() << ", " << Fl::event_y() << ")\n";
                clicked = !clicked;  // Toggle clicked state
                redraw();  // Redraw the box to reflect the new state
            }
            return 1;  // Indicate event was handled
        default:
            return Fl_Box::handle(event);  // Call the base class for other events
    }
}

// Function to load and display the selected image
void TilesetUI::load_image(const char *file) {
    // Open the file chooser dialog with BMP, PNG, and JPEG filters
    //const char *file = fl_file_chooser("Choose an Image (BMP, PNG, or JPEG)", "*.bmp *.png *.jpg *.jpeg", NULL);

    // Check if a file was selected
    if (file != NULL) {
        img = nullptr;

        // Determine the file extension and load the image accordingly
        std::string filename = file;
        if (filename.find(".bmp") != std::string::npos) {
            img = new Fl_BMP_Image(file);  // Load BMP image
        } else if (filename.find(".png") != std::string::npos) {
            img = new Fl_PNG_Image(file);  // Load PNG image
        } else if (filename.find(".jpg") != std::string::npos || filename.find(".jpeg") != std::string::npos) {
            img = new Fl_JPEG_Image(file); // Load JPEG image
        }

        // Check if the image is valid and set it to the box
        if (img && img->w() > 0 && img->h() > 0) {
            
            //this->image(img);               // Set the image in the box
            this->redraw();                 // Redraw the box to show the image
        } else {
            delete img;                    // Clean up if the image was invalid
            fl_alert("Invalid Image file!");
        }
    }
}
