#ifndef SPRITE_H
#define SPRITE_H

#include "Display.h"
class Sprite
{
    public: float vertices[32];
    // public: float[] Vertices()const{return this->vertices;}

    public: unsigned int indices[6];

    public: Sprite(unsigned int width, unsigned int height)
    {
        //Width/screenwidth
        this->vertices[0] = width / Display::Width();
        this->vertices[1] = height / Display::Height();
        this->vertices[2] = 0.0f;
        this->vertices[3] = 1.0f;
        this->vertices[4] = 0.0f;
        this->vertices[5] = 0.0f;
        this->vertices[6] = 1.0f;
        this->vertices[7] = 1.0f;

        this->vertices[8] = width/Display::Width();
        this->vertices[9] = -height/Display::Width();
        this->vertices[10] = 0.0f;
        this->vertices[11] = 0.0f;
        this->vertices[12] = 1.0f;
        this->vertices[13] = 0.0f;
        this->vertices[14] = 1.0f;
        this->vertices[15] = 0.0f;

        this->vertices[16] = -width/Display::Width();
        this->vertices[17] = -height/Display::Height();
        this->vertices[18] = 0.0f;
        this->vertices[19] = 0.0f;
        this->vertices[20] = 0.0f;
        this->vertices[21] = 1.0f;
        this->vertices[22] = 0.0f;
        this->vertices[23] = 0.0f;

        this->vertices[24] = -width/Display::Width();
        this->vertices[25] = height/Display::Width();
        this->vertices[26] = 0.0f;
        this->vertices[27] = 1.0f;
        this->vertices[28] = 1.0f;
        this->vertices[29] = 0.0f;
        this->vertices[30] = 0.0f;
        this->vertices[31] = 1.0f;

        this->indices[0]= 0;
        this->indices[1]= 1;
        this->indices[2]= 3;
        this->indices[3]= 1;
        this->indices[4]= 2;
        this->indices[5]= 3;
    }

    public: void update()
    {

    }

    public: void render()
    {

    }

    public: ~Sprite()
    {
        
    }
};
#endif
