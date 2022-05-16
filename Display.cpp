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
#include "QuadtreeJSON.h"

Display::Display(): isRunning(false), window(nullptr), renderer(nullptr), quad(nullptr){}

bool Display::initialize(double dim){

    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
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

    // creamos el Quadtree con las dimensiones de la ventana
    AABB boundary({dim/2, dim/2}, dim, dim);
    quad = new Quadtree(boundary, 1 , nullptr);
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
    AABB mouseRange({0,0}, 4);
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(event.button.button == SDL_BUTTON_LEFT){
                        quad->insert({static_cast<double>(x),static_cast<double>(y)});
                        makeJSON(quad);
                    }
                    if(event.button.button == SDL_BUTTON_RIGHT){
                        mouseRange.center.x = x;
                        mouseRange.center.y = y;
                        Point toRemove = quad->getClosestPointToCenter(mouseRange);
                        quad->remove(toRemove);
                        makeJSON(quad);
                    }
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
