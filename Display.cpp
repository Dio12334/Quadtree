#include "Display.h"
#include "AABB.h"
#include "Quadtree.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_video.h>
#include <iostream>

Display::Display(): isRunning(false), window(nullptr), renderer(nullptr), quad(nullptr){}

bool Display::initialize(){
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    double dim = 800;
    if(sdlResult != 0){
        SDL_Log("No se pudo inicializar SDL: %s", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Quadtree", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dim, dim,0);
    if(!window){
        SDL_Log("Falla en la creación de la ventana: %s", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    isRunning = true;
    AABB boundary({dim/2, dim/2}, dim/2);
    quad = new Quadtree(boundary);
    return true;
}

void Display::runLoop(){
    while(isRunning){
        processInputs();
        updateDisplay();
        generateOutput();
    }
}

void Display::shutdown(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Display::processInputs(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    quad->insert({static_cast<double>(x),static_cast<double>(y)});
                }

        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_ESCAPE])
        isRunning = false;
}

void Display::updateDisplay(){

}

void Display::generateOutput(){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    quad->draw(renderer);
    SDL_RenderPresent(renderer);
}
