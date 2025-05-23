#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <string>
#include <unordered_map>
#include "global.h"

// Custom class for Fl_Box to handle mouse clicks and custom drawing
class TilesetUI : public Fl_Double_Window {
public:
    // Constructor
    TilesetUI(int X, int Y, int W, int H, const char *L = 0);

    // Override the draw() method for custom drawing
    void draw() override;

    // Override the handle() method to capture mouse click events
    int handle(int event) override;

    // Load and display the selected image
    void load_image(const char *file);
    int tileSize = 8;
    int mouseX = 0;
    int mouseY = 0;
    int tileId = 0;
    int scale = 1;
    int imgPosX = 0;
    int imgPosY = 0;
    bool moveTileset = false;
    int offsetX;
    int offsetY;
    std::unordered_map<std::string, Fl_Image*> tileset;
    void clearTileset();
    void SetTileSet(const std::string &tileset);
private:
    
    Fl_Image *img;
    Fl_Image *cpImg;
    bool clicked;  // Track whether the box has been clicked
};
