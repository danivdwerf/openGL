#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>

class Display
{
    private: SDL_Window* window;
    public: SDL_Window* Window()const{return this->window;}

    private: SDL_GLContext context;
    public: SDL_GLContext Context()const{return this->context;}

    private: unsigned int width;

    private: unsigned int height;

    public: Display(const char* title, unsigned int width, unsigned int height)
    {
        this->window = nullptr;
        this->context = NULL;
        this->width = 0;
        this->height = 0;

        if(this->init(title, width, height) != 0)
            delete this;

        this->width = width;
        this->height = height;
    }

    private: uint8_t init(const char* title, unsigned int width, int height)
    {
        if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
            return -1;

        //Create window
        this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
        if(window == nullptr)
            return -1;

        //Set GL attributes
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        
        //Create OpenGL context
        this->context = SDL_GL_CreateContext(this->window);
        if(this->context == NULL)
            return -1;

        //Initialzie glad
        if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
            return -1;

        //Turn on v-Sync
        SDL_GL_SetSwapInterval(1);
        SDL_GL_SwapWindow(this->window);
        glViewport(0, 0, width, height);

        #ifndef __APPLE__
        glewExperimental = GL_TRUE;
        glewInit();
        #endif  
        return 0;
    }

    private: void onWindowResize(unsigned int width, unsigned int height)
    {
        this->width = width;
        this->height = height;
        glViewport(0, 0, width, height);
    }

    public: void handleWindowEvents(SDL_Event e)
    {
        if(e.window.event == SDL_WINDOWEVENT_RESIZED)
            onWindowResize(e.window.data1, e.window.data2);
    }
};

#endif