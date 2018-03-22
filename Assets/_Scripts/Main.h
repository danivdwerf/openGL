#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <SDL2/SDL.h>
#include "../includes/glad.h"

#include "Vector3.h"
#include "Display.h"
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Main
{
    Display* display;

    //Framerate data;
    private: uint8_t maxFrameRate;
    private: double frame;

    private: double deltatime;
    public: double Deltatime()const{return this->deltatime;}

    public: Main(const char* title, int width, int height)
    {
        this->display = new Display(title, width, height);
        if(this->display == nullptr)
        {
            std::cout << "FAILED TO CREATE DISPLAY" << '\n';
            return;
        }
    }

    private: bool handleEvents(SDL_Event event)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_WINDOWEVENT)
                display->handleWindowEvents(event);
            
            if(event.type == SDL_QUIT)
            {
                return false;
                break;
            }

            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return false;
                    break;
                }
            }
        } 
        return true;
    }

    public: void mainloop()
    {
        SDL_Window* window = display->Window();

        bool loop = true;
        SDL_Event event;

        uint64_t lastFrame;
        uint64_t currentFrame;

        float vertices[] = 
        {
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
        };
        
        unsigned int indices[] = 
        {  
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        unsigned int vbo, vao, ebo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        //Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //Colour attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); 
        glEnableVertexAttribArray(1);

        //Texure attribute
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0); 

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);

        int texWidth, texHeight, texChannels;
        unsigned char* data = stbi_load("./Assets/Textures/test.jpeg", &texWidth, &texHeight, &texChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
            std::cout << "Failed to load texture" << '\n';
        stbi_image_free(data);

        Shader standard("Assets/shaders/basic2DTextured/vertex.v", "Assets/shaders/basic2DTextured/fragment.f");

        while(loop)
        {
            lastFrame = currentFrame;
            currentFrame = SDL_GetPerformanceCounter(); 
            this->deltatime = (double)(currentFrame - lastFrame)*1000/SDL_GetPerformanceCounter();

            loop = handleEvents(event);

            //Render
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glBindTexture(GL_TEXTURE_2D, texture);
            standard.use();
            glBindVertexArray(vao);

            // WIRFRAME
            // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            
            SDL_GL_SwapWindow(window);
        }

        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }

    public: void setFramerate(uint8_t newFramerate)
    {
        this->maxFrameRate = newFramerate;
        this->frame = 1000/newFramerate;
    }

    public: ~Main()
    {
        // SDL_DestroyWindow(this->window);
        // SDL_Quit();
    }
};

#endif