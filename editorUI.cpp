// generated by Fast Light User Interface Designer (fluid) version 1.0311

#include "editorUI.h"

void EditorUI::cb_menuOpen_i(Fl_Menu_*, void*) {
  //open file
  char *newfile = fl_file_chooser("Open File?", "*.json", filename);
  if(newfile == nullptr){
    return;
  }
  if(editorView->level){
    delete editorView->level;
  }
  editorView->level = LoadLevel(newfile);
  editorView->redraw();
  TileSelector::tileSize = editorView->level->tileSize;
  if(editorView->level->layer.size() != 0) {
    for(auto layer: editorView->level->layer) {
      tilesetUI->load_image(layer.texture->filename.c_str());
    }
  } else {
    tilesetUI->load_image("tileset_1616.png");
  }
  BrowserLayer->clear();
  for(int i=0; i < editorView->level->layer.size();i++) {
    BrowserLayer->add(editorView->level->layer[i].name.c_str());
  }
  if(BrowserGameObject->size() == 0 ) {
    LoadGameObjects();
    for(int i=0;i<TileSelector::gameObjects.size();i++){
      BrowserGameObject->add(TileSelector::gameObjects[i].name.c_str());
    }
  }
  currentFilename = newfile;
}
void EditorUI::cb_menuOpen(Fl_Menu_* o, void* v) {
  ((EditorUI*)(o->parent()->user_data()))->cb_menuOpen_i(o,v);
}

void EditorUI::cb_menuSave_i(Fl_Menu_*, void*) {
  SaveLevel(editorView->level,currentFilename.c_str());
}
void EditorUI::cb_menuSave(Fl_Menu_* o, void* v) {
  ((EditorUI*)(o->parent()->user_data()))->cb_menuSave_i(o,v);
}

void EditorUI::cb_menuSaveAs_i(Fl_Menu_*, void*) {
  //save as
 char *newfile = fl_file_chooser("Save as?", "*.json", filename);
 if(newfile){
   SaveLevel(editorView->level,newfile);
 }
 currentFilename = newfile;
}
void EditorUI::cb_menuSaveAs(Fl_Menu_* o, void* v) {
  ((EditorUI*)(o->parent()->user_data()))->cb_menuSaveAs_i(o,v);
}

void EditorUI::cb_Undo_i(Fl_Menu_*, void*) {
  editorView->undo();
}
void EditorUI::cb_Undo(Fl_Menu_* o, void* v) {
  ((EditorUI*)(o->parent()->user_data()))->cb_Undo_i(o,v);
}

void EditorUI::cb_Delete_i(Fl_Menu_*, void*) {
  editorView->deleteTilesData();
}
void EditorUI::cb_Delete(Fl_Menu_* o, void* v) {
  ((EditorUI*)(o->parent()->user_data()))->cb_Delete_i(o,v);
}

Fl_Menu_Item EditorUI::menu_[] = {
 {"File", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"New", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Open", 0,  (Fl_Callback*)EditorUI::cb_menuOpen, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Save", 0,  (Fl_Callback*)EditorUI::cb_menuSave, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Save As", 0x40073,  (Fl_Callback*)EditorUI::cb_menuSaveAs, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Edit", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Undo", 0x4007a,  (Fl_Callback*)EditorUI::cb_Undo, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Redo", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Delete", 0xffff,  (Fl_Callback*)EditorUI::cb_Delete, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Select", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};
Fl_Menu_Item* EditorUI::menuNew = EditorUI::menu_ + 1;
Fl_Menu_Item* EditorUI::menuOpen = EditorUI::menu_ + 2;
Fl_Menu_Item* EditorUI::menuSave = EditorUI::menu_ + 3;
Fl_Menu_Item* EditorUI::menuSaveAs = EditorUI::menu_ + 4;

void EditorUI::cb_BrowserGameObject_i(Fl_Browser*, void*) {
  editorView->gameObjectId = BrowserGameObject->value() - 1;
}
void EditorUI::cb_BrowserGameObject(Fl_Browser* o, void* v) {
  ((EditorUI*)(o->parent()->parent()->parent()->parent()->user_data()))->cb_BrowserGameObject_i(o,v);
}

void EditorUI::cb_applyLayer_i(Fl_Button*, void*) {
  editorView->applyLayer(layerW->value(),layerH->value(),layerName->value(),layerTexture->value());
BrowserLayer->text( BrowserLayer->value(), layerName->value());;
}
void EditorUI::cb_applyLayer(Fl_Button* o, void* v) {
  ((EditorUI*)(o->parent()->parent()->parent()->parent()->user_data()))->cb_applyLayer_i(o,v);
}

void EditorUI::cb_BrowserLayer_i(Fl_Browser*, void*) {
  TileSelector::layerId = BrowserLayer->value() - 1;
layerName->value(editorView->level->layer[TileSelector::layerId].name.c_str());
layerTexture->value(editorView->level->layer[TileSelector::layerId].texture->filename.c_str());
layerW->value(editorView->level->layer[TileSelector::layerId].Width());
layerH->value(editorView->level->layer[TileSelector::layerId].Height());
tilesetUI->SetTileSet(editorView->level->layer[TileSelector::layerId].texture->filename);
}
void EditorUI::cb_BrowserLayer(Fl_Browser* o, void* v) {
  ((EditorUI*)(o->parent()->parent()->user_data()))->cb_BrowserLayer_i(o,v);
}

#include <FL/Fl_Image.H>
static const unsigned char idata_pencil[] =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
152,113,24,255,176,129,17,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,137,101,18,255,152,113,
24,255,152,113,24,255,176,129,17,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,124,92,20,255,137,101,18,255,
137,101,18,255,152,113,24,255,152,113,24,255,176,129,17,255,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,124,92,20,255,124,
92,20,255,137,101,18,255,137,101,18,255,152,113,24,255,152,113,24,255,176,129,
17,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,124,92,20,255,124,92,20,255,137,101,18,255,137,101,18,255,152,113,24,
255,152,113,24,255,176,129,17,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,124,92,20,255,124,92,20,255,137,101,18,255,
137,101,18,255,152,113,24,255,152,113,24,255,176,129,17,255,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,124,92,20,255,124,
92,20,255,137,101,18,255,137,101,18,255,152,113,24,255,152,113,24,255,176,129,
17,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,124,92,20,255,124,92,20,255,137,101,18,255,137,101,18,255,152,113,24,
255,152,113,24,255,176,129,17,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,124,92,20,255,124,92,20,255,137,101,18,255,
137,101,18,255,152,113,24,255,152,113,24,255,176,129,17,255,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,124,92,20,255,124,
92,20,255,137,101,18,255,137,101,18,255,152,113,24,255,152,113,24,255,24,24,24,
255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,124,92,20,255,124,92,20,255,137,101,18,255,137,101,18,255,24,24,24,255,24,
24,24,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,124,92,20,255,124,92,20,255,24,24,24,255,24,24,24,255,24,
24,24,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,24,24,255,24,24,24,255,24,24,24,255,24,24,24,
255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static Fl_Image *image_pencil() {
  static Fl_Image *image = new Fl_RGB_Image(idata_pencil, 16, 16, 4, 0);
  return image;
}

void EditorUI::cb_btnEraser_i(Fl_Button*, void*) {
  TileSelector::tileId = 0;
editorView->gameObjectId = -1;
}
void EditorUI::cb_btnEraser(Fl_Button* o, void* v) {
  ((EditorUI*)(o->parent()->parent()->parent()->user_data()))->cb_btnEraser_i(o,v);
}

static const unsigned char idata_eraser[] =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,167,41,41,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,127,35,35,255,146,52,52,255,167,41,41,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,35,35,255,
146,52,52,255,146,52,52,255,146,52,52,255,167,41,41,255,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,35,35,255,146,52,
52,255,146,52,52,255,146,52,52,255,146,52,52,255,146,52,52,255,167,41,41,255,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,35,35,255,
146,52,52,255,146,52,52,255,146,52,52,255,146,52,52,255,146,52,52,255,146,52,52,
255,146,52,52,255,167,41,41,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
97,20,20,255,126,30,30,255,127,35,35,255,146,52,52,255,146,52,52,255,146,52,52,
255,146,52,52,255,146,52,52,255,127,35,35,255,97,20,20,255,209,209,209,255,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,97,20,20,255,97,20,20,255,97,20,20,255,126,30,30,
255,127,35,35,255,146,52,52,255,146,52,52,255,146,52,52,255,127,35,35,255,97,20,
20,255,233,233,233,255,233,233,233,255,209,209,209,255,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,97,20,20,255,97,20,20,255,97,20,20,255,126,30,30,255,127,35,35,255,
146,52,52,255,127,35,35,255,97,20,20,255,233,233,233,255,233,233,233,255,233,
233,233,255,233,233,233,255,209,209,209,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,97,
20,20,255,97,20,20,255,97,20,20,255,126,30,30,255,127,35,35,255,97,20,20,255,
233,233,233,255,233,233,233,255,233,233,233,255,233,233,233,255,209,209,209,255,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,97,20,20,255,97,20,20,255,97,
20,20,255,126,30,30,255,209,209,209,255,233,233,233,255,233,233,233,255,233,
233,233,255,209,209,209,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,97,20,20,255,97,20,20,255,183,183,183,255,209,209,209,255,209,209,
209,255,233,233,233,255,209,209,209,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,158,158,158,255,183,183,183,255,183,
183,183,255,209,209,209,255,209,209,209,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,158,158,158,255,
183,183,183,255,183,183,183,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,158,158,158,
255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static Fl_Image *image_eraser() {
  static Fl_Image *image = new Fl_RGB_Image(idata_eraser, 16, 16, 4, 0);
  return image;
}

void EditorUI::cb_btnCopy_i(Fl_Button*, void*) {
  editorView->copyTilesData();
}
void EditorUI::cb_btnCopy(Fl_Button* o, void* v) {
  ((EditorUI*)(o->parent()->parent()->parent()->user_data()))->cb_btnCopy_i(o,v);
}

static const unsigned char idata_copy[] =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,
255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,
255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,112,112,112,255,
112,112,112,255,112,112,112,255,112,112,112,255,112,112,112,255,112,112,112,255,
112,112,112,255,112,112,112,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,255,112,112,112,255,112,112,112,255,112,112,112,255,112,112,
112,255,112,112,112,255,112,112,112,255,112,112,112,255,112,112,112,255,0,0,0,
255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,112,112,112,255,
112,112,112,255,112,112,112,255,112,112,112,255,112,112,112,255,112,112,112,255,
112,112,112,255,112,112,112,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,255,112,112,112,255,112,112,112,255,112,112,112,255,0,0,0,255,
0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,
255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,112,112,112,255,112,112,112,255,112,112,
112,255,0,0,0,255,186,181,181,255,186,181,181,255,186,181,181,255,186,181,181,
255,186,181,181,255,186,181,181,255,186,181,181,255,186,181,181,255,0,0,0,255,0,
0,0,0,0,0,0,0,0,0,0,255,112,112,112,255,112,112,112,255,112,112,112,255,0,0,0,
255,186,181,181,255,87,134,21,255,85,145,0,255,87,134,21,255,85,145,0,255,87,
134,21,255,85,145,0,255,186,181,181,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,112,
112,112,255,112,112,112,255,112,112,112,255,0,0,0,255,186,181,181,255,85,145,0,
255,87,134,21,255,85,145,0,255,87,134,21,255,85,145,0,255,87,134,21,255,186,181,
181,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,112,112,112,255,112,112,112,255,112,
112,112,255,0,0,0,255,186,181,181,255,89,64,15,255,87,134,21,255,89,64,15,255,
89,64,15,255,87,134,21,255,89,64,15,255,186,181,181,255,0,0,0,255,0,0,0,0,0,0,
0,0,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,186,181,181,255,95,69,
17,255,89,64,15,255,95,69,17,255,95,69,17,255,89,64,15,255,95,69,17,255,186,
181,181,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,
186,181,181,255,95,69,17,255,89,64,15,255,95,69,17,255,95,69,17,255,89,64,15,
255,95,69,17,255,186,181,181,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,255,186,181,181,255,95,69,17,255,95,69,17,255,95,69,17,255,
95,69,17,255,95,69,17,255,95,69,17,255,186,181,181,255,0,0,0,255,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,186,181,181,255,186,181,181,255,
186,181,181,255,186,181,181,255,186,181,181,255,186,181,181,255,186,181,181,255,
186,181,181,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,
255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static Fl_Image *image_copy() {
  static Fl_Image *image = new Fl_RGB_Image(idata_copy, 16, 16, 4, 0);
  return image;
}

void EditorUI::cb_btnPaste_i(Fl_Button*, void*) {
  editorView->pasteTilesData();
}
void EditorUI::cb_btnPaste(Fl_Button* o, void* v) {
  ((EditorUI*)(o->parent()->parent()->parent()->user_data()))->cb_btnPaste_i(o,v);
}

static const unsigned char idata_paste[] =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,
255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,
255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,112,112,112,255,
112,112,112,255,112,112,112,255,112,112,112,255,112,112,112,255,112,112,112,255,
112,112,112,255,112,112,112,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,255,112,112,112,255,87,134,21,255,85,145,0,255,87,134,21,255,
85,145,0,255,87,134,21,255,85,145,0,255,112,112,112,255,0,0,0,255,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,112,112,112,255,85,145,0,255,87,
134,21,255,85,145,0,255,87,134,21,255,85,145,0,255,87,134,21,255,112,112,112,
255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,112,112,
112,255,89,64,15,255,87,134,21,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,
0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,
255,112,112,112,255,95,69,17,255,89,64,15,255,0,0,0,255,186,181,181,255,186,181,
181,255,186,181,181,255,186,181,181,255,186,181,181,255,186,181,181,255,186,181,
181,255,186,181,181,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,112,112,112,255,95,
69,17,255,89,64,15,255,0,0,0,255,186,181,181,255,87,134,21,255,85,145,0,255,87,
134,21,255,85,145,0,255,87,134,21,255,85,145,0,255,186,181,181,255,0,0,0,255,0,
0,0,0,0,0,0,0,0,0,0,255,112,112,112,255,95,69,17,255,95,69,17,255,0,0,0,255,
186,181,181,255,85,145,0,255,87,134,21,255,85,145,0,255,87,134,21,255,85,145,0,
255,87,134,21,255,186,181,181,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,112,112,
112,255,112,112,112,255,112,112,112,255,0,0,0,255,186,181,181,255,89,64,15,255,
87,134,21,255,89,64,15,255,89,64,15,255,87,134,21,255,89,64,15,255,186,181,181,
255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,
186,181,181,255,95,69,17,255,89,64,15,255,95,69,17,255,95,69,17,255,89,64,15,
255,95,69,17,255,186,181,181,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,255,186,181,181,255,95,69,17,255,89,64,15,255,95,69,17,255,
95,69,17,255,89,64,15,255,95,69,17,255,186,181,181,255,0,0,0,255,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,186,181,181,255,95,69,17,255,95,
69,17,255,95,69,17,255,95,69,17,255,95,69,17,255,95,69,17,255,186,181,181,255,
0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,186,181,
181,255,186,181,181,255,186,181,181,255,186,181,181,255,186,181,181,255,186,181,
181,255,186,181,181,255,186,181,181,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,
0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0};
static Fl_Image *image_paste() {
  static Fl_Image *image = new Fl_RGB_Image(idata_paste, 16, 16, 4, 0);
  return image;
}

static const unsigned char idata_selection[] =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,
255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,0,0,
0,0,0,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,72,72,72,255,72,
72,72,255,72,72,72,255,0,0,0,0,0,0,0,0,72,72,72,255,72,72,72,255,72,72,72,255,
0,0,0,0,0,0,0,0,72,72,72,255,72,72,72,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,
72,72,72,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,72,72,72,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,72,72,72,255,0,
0,0,0,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,
72,255,72,72,72,255,72,72,72,255,0,0,0,0,72,72,72,255,0,0,0,255,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,
72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,255,72,72,72,255,0,0,0,0,72,72,72,255,72,72,72,255,72,72,
72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,0,0,0,
0,72,72,72,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,72,72,72,255,0,0,0,0,72,72,
72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,
72,255,72,72,72,255,0,0,0,0,72,72,72,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,
72,72,72,255,0,0,0,0,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,
72,255,72,72,72,255,72,72,72,255,72,72,72,255,0,0,0,0,72,72,72,255,0,0,0,255,0,
0,0,0,0,0,0,0,0,0,0,255,72,72,72,255,0,0,0,0,72,72,72,255,72,72,72,255,72,72,
72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,0,0,0,
0,72,72,72,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,72,72,72,255,
72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,
72,72,72,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,72,72,72,255,0,
0,0,0,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,72,255,72,72,
72,255,72,72,72,255,72,72,72,255,0,0,0,0,72,72,72,255,0,0,0,255,0,0,0,0,0,0,0,
0,0,0,0,255,72,72,72,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,72,72,72,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,
72,72,72,255,72,72,72,255,72,72,72,255,0,0,0,0,0,0,0,0,72,72,72,255,72,72,72,
255,72,72,72,255,0,0,0,0,0,0,0,0,72,72,72,255,72,72,72,255,0,0,0,255,0,0,0,0,0,
0,0,0,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,
255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static Fl_Image *image_selection() {
  static Fl_Image *image = new Fl_RGB_Image(idata_selection, 16, 16, 4, 0);
  return image;
}

void EditorUI::cb__i(Fl_Group*, void*) {
  editorView->insertMode = 1;
}
void EditorUI::cb_(Fl_Group* o, void* v) {
  ((EditorUI*)(o->parent()->parent()->user_data()))->cb__i(o,v);
}

void EditorUI::cb_radioTiles_i(Fl_Round_Button*, void*) {
  //calbackradio
editorView->insertMode = 0;
}
void EditorUI::cb_radioTiles(Fl_Round_Button* o, void* v) {
  ((EditorUI*)(o->parent()->parent()->parent()->user_data()))->cb_radioTiles_i(o,v);
}

void EditorUI::cb_radioObjects_i(Fl_Round_Button*, void*) {
  //calbackradio
editorView->insertMode = 1;
}
void EditorUI::cb_radioObjects(Fl_Round_Button* o, void* v) {
  ((EditorUI*)(o->parent()->parent()->parent()->user_data()))->cb_radioObjects_i(o,v);
}

EditorUI::EditorUI() {
  { mainWindow = new Fl_Window(1280, 720, "LevelEditor");
    mainWindow->user_data((void*)(this));
    { editorView = new EditorView(320, 25, 960, 695, "EditorView");
      editorView->box(FL_UP_BOX);
      editorView->color(FL_BACKGROUND_COLOR);
      editorView->selection_color(FL_BACKGROUND_COLOR);
      editorView->labeltype(FL_NORMAL_LABEL);
      editorView->labelfont(0);
      editorView->labelsize(14);
      editorView->labelcolor(FL_FOREGROUND_COLOR);
      editorView->align(Fl_Align(FL_ALIGN_CENTER));
      editorView->when(FL_WHEN_RELEASE);
    } // EditorView* editorView
    { Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 1280, 25);
      o->menu(menu_);
    } // Fl_Menu_Bar* o
    { Fl_Group* o = new Fl_Group(-10, 25, 330, 780);
      { Fl_Tabs* o = new Fl_Tabs(5, 315, 310, 400);
        { Fl_Group* o = new Fl_Group(5, 340, 310, 375, "Tileset");
          o->box(FL_GLEAM_DOWN_FRAME);
          o->hide();
          { tilesetUI = new TilesetUI(10, 345, 300, 365);
            tilesetUI->box(FL_NO_BOX);
            tilesetUI->color((Fl_Color)44);
            tilesetUI->selection_color(FL_DARK2);
            tilesetUI->labeltype(FL_NORMAL_LABEL);
            tilesetUI->labelfont(0);
            tilesetUI->labelsize(14);
            tilesetUI->labelcolor(FL_FOREGROUND_COLOR);
            tilesetUI->align(Fl_Align(581));
            tilesetUI->when(FL_WHEN_RELEASE);
          } // TilesetUI* tilesetUI
          o->end();
        } // Fl_Group* o
        { Fl_Group* o = new Fl_Group(5, 340, 310, 375, "GameObjects");
          o->hide();
          { BrowserGameObject = new Fl_Browser(15, 355, 290, 345);
            BrowserGameObject->type(2);
            BrowserGameObject->callback((Fl_Callback*)cb_BrowserGameObject);
          } // Fl_Browser* BrowserGameObject
          o->end();
        } // Fl_Group* o
        { Fl_Group* o = new Fl_Group(5, 340, 310, 375, "Layer");
          { layerName = new Fl_Input(55, 360, 250, 25, "Name");
          } // Fl_Input* layerName
          { layerW = new Fl_Value_Input(55, 390, 250, 25, "Width");
          } // Fl_Value_Input* layerW
          { layerH = new Fl_Value_Input(55, 420, 250, 25, "Height");
          } // Fl_Value_Input* layerH
          { layerTexture = new Fl_Input(55, 450, 250, 25, "Tex");
          } // Fl_Input* layerTexture
          { applyLayer = new Fl_Button(55, 485, 115, 25, "Apply");
            applyLayer->callback((Fl_Callback*)cb_applyLayer);
          } // Fl_Button* applyLayer
          o->end();
        } // Fl_Group* o
        o->end();
      } // Fl_Tabs* o
      { BrowserLayer = new Fl_Browser(5, 80, 310, 170);
        BrowserLayer->type(2);
        BrowserLayer->callback((Fl_Callback*)cb_BrowserLayer);
        BrowserLayer->when(3);
      } // Fl_Browser* BrowserLayer
      { Fl_Group* o = new Fl_Group(5, 30, 310, 40);
        o->box(FL_THIN_UP_BOX);
        { btnPencil = new Fl_Button(10, 35, 45, 30);
          btnPencil->image( image_pencil() );
        } // Fl_Button* btnPencil
        { btnEraser = new Fl_Button(65, 35, 45, 30);
          btnEraser->image( image_eraser() );
          btnEraser->callback((Fl_Callback*)cb_btnEraser);
        } // Fl_Button* btnEraser
        { btnCopy = new Fl_Button(120, 35, 45, 30);
          btnCopy->tooltip("Copy block of tiles");
          btnCopy->shortcut(0x40063);
          btnCopy->image( image_copy() );
          btnCopy->callback((Fl_Callback*)cb_btnCopy);
        } // Fl_Button* btnCopy
        { btnPaste = new Fl_Button(175, 35, 45, 30);
          btnPaste->tooltip("Paste");
          btnPaste->shortcut(0x40076);
          btnPaste->image( image_paste() );
          btnPaste->callback((Fl_Callback*)cb_btnPaste);
        } // Fl_Button* btnPaste
        { btnSelect = new Fl_Button(230, 35, 45, 30);
          btnSelect->tooltip("Selection Tool");
          btnSelect->image( image_selection() );
        } // Fl_Button* btnSelect
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(5, 260, 305, 50);
        o->callback((Fl_Callback*)cb_);
        { radioTiles = new Fl_Round_Button(5, 265, 25, 25, "Tiles");
          radioTiles->type(102);
          radioTiles->down_box(FL_ROUND_DOWN_BOX);
          radioTiles->callback((Fl_Callback*)cb_radioTiles);
        } // Fl_Round_Button* radioTiles
        { radioObjects = new Fl_Round_Button(60, 265, 25, 25, "Objects");
          radioObjects->type(102);
          radioObjects->down_box(FL_ROUND_DOWN_BOX);
          radioObjects->callback((Fl_Callback*)cb_radioObjects);
        } // Fl_Round_Button* radioObjects
        o->end();
      } // Fl_Group* o
      o->end();
    } // Fl_Group* o
    Fl::scheme("plastic");
    mainWindow->end();
    mainWindow->resizable(mainWindow);
  } // Fl_Window* mainWindow
}

void EditorUI::show(int argc, char **argv) {
  mainWindow->show(argc,argv);
}

void EditorUI::loadTileset(const char* file) {
  if (file != NULL) {
          Fl_Image *img = nullptr;
  
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
              tilesetUI->image(img);               // Set the image in the box
              tilesetUI->redraw();                 // Redraw the box to show the image
          } else {
              delete img;                    // Clean up if the image was invalid
              fl_alert("Invalid Image file!");
          }
      }
}
