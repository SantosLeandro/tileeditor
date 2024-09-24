#include "gl_render.h"
#include "layer.h"
#include "texture.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

void GLRender::UpdateViewPort(int w, int h)
{
  this->w = w;
  this->h = h;
  glViewport(0, 0, w, h);
}

void GLRender::Prepare2D()
{
  // glLoadIdentity();
  // glOrtho(-1, 1, -1, 1, -1, 1);
  // glViewport(0, 0, w, h);
  // glLoadIdentity;
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, w, h, 0);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  //glScalef(scale, scale, scale);
}

void GLRender::DrawTest()
{
  glLoadIdentity();
  glScalef(scale, scale, 0);
  DrawBackground(10, 5, 16);
  DrawGrid(10, 5, 16);

  // Render a triangle

  // glBegin(GL_TRIANGLES);
  // glColor3f(1.0f, 0.0f, 0.0f);
  // glVertex2f(0.0f, 0.0f);
  // glVertex2f(32.0f, 32.0f);
  // glVertex2f(0.0f, 32.0f);
  // glEnd();
}

void GLRender::DrawLayer(const Layer *layer, int t)
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, layer->texture->Id());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glColor3f(1, 1, 1);
  glBegin(GL_QUADS);
  for (int h=0; h < layer->data.size(); h++ )
  {
    for (int w=0; w < layer->data[0].size(); w++)
    {
      if (layer->data[h][w] < 0) {
        continue;
      }
      float srcY = (float)(layer->data[h][w] / (layer->texture->Width() / t) * t) / layer->texture->Height();
      float srcX = (float)(layer->data[h][w] % (layer->texture->Width() / t) * t) / layer->texture->Width();
      float srcW = (float)t / layer->texture->Width();
      float srcH = (float)t / layer->texture->Height();
      //glColor3f(1, layer->data[h][w] / 10, 0);
      int tile = t;

      
      // std::cout << "textureW "<<layer->texture->Width() <<"\n";
      // std::cout << "textureH "<<layer->texture->Height() <<"\n";
      // std::cout <<" tileY "<<srcY<<"\n";
      // std::cout <<" tileX "<<srcX<<"\n";
      // std::cout <<" tileW "<<srcW<<"\n";
      // std::cout <<" tileH "<<srcH<<"\n\n";
      
      
      //**
      glTexCoord2f(srcX, srcY);
      glVertex3f(w * tile, h * tile, 0);
      //**
      glTexCoord2f(srcX, srcY + srcH);
      glVertex3f(w * tile, h * tile + tile, 0);
      //**
      glTexCoord2f(srcX + srcW, srcY + srcH);
      glVertex3f(w * tile + tile, h * tile + tile, 0);
      //**
      glTexCoord2f(srcX + srcW, srcY);
      glVertex3f(w * tile + tile, h * tile, 0);
    }
}
  glEnd();
}

void GLRender::DrawLevel(const Level *level)
{
  if(!level){
    return;
  }
  glLoadIdentity();
  glTranslatef(x,y,0);
  glScalef(scale, scale, scale);
  
  DrawBackground(level->w,level->h,level->tileSize);
  DrawGrid(level->w,level->h,level->tileSize);
  for (int i = 0; i < level->layer.size(); i++)
  {
    if(level->layer[i].texture != nullptr) {
      DrawLayer(&level->layer[i], level->tileSize);
    }
    
  }
}

void GLRender::DrawGrid(int width, int height, int t)
{
  glBindTexture(GL_TEXTURE_2D, 0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.9f, 0.9f, 0.9f);
  glBegin(GL_QUADS);
  int tile = t;
  for (int h = 0; h < height; h++)
  {
    for (int w = 0; w < width; w++)
    {
      // tile := t * FScale;
      //**
      glVertex3f(w * tile, h * tile, 0);
      //**
      glVertex3f(w * tile, h * tile + tile, 0);
      //**
      glVertex3f(w * tile + tile, h * tile + tile, 0);
      //**
      glVertex3f(w * tile + tile, h * tile, 0);
    }
  }
  glEnd();
}

void GLRender::DrawBackground(int w, int h, int t)
{
  glBindTexture(GL_TEXTURE_2D, 0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_QUADS);
  glColor3f(0.1f, 0.1f, 0.1f);
  glVertex3f(0, 0, 0);
  glVertex3f(0, h * t, 0);
  glVertex3f(w * t, h * t, 0);
  glVertex3f(w * t, 0, 0);
  glEnd();
}

void GLRender::ClearScreen()
{
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.27, 0.53, 0.71, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  
  // glLoadIdentity();
}

void GLRender::ScaleUp()
{
  if (scale > 1.0f)
  {
    scale = scale - 1;
  }
}

void GLRender::ScaleDown()
{
  scale += 1.0f;
}

void GLRender::Translate(int x, int y)
{
  this->x += x;
  this->y += y;
}
