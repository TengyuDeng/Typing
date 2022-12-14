//
//  Game.cpp
//  myGame
//
//  Created by Deng Tengyu on 2022/11/22.
//  Copyright © 2022 Deng Tengyu. All rights reserved.
//

#include "Game.h"
#include "TextSet.h"
#include "Caption.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>


Game::Game()
:mWindow(nullptr),
mRenderer(nullptr),
mIsRunning(true),
mTicksCount(0),
mTextSet(nullptr),
mScoreCaption(nullptr),
mScore(0){

}

bool Game::Initialize(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
    {
        std::cout << (SDL_INIT_VIDEO|SDL_INIT_AUDIO);
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Typing!", 100, 100, 960, 720, 0);
    if (!mWindow){
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer){
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0){
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() != 0){
        SDL_Log("Unable to initialize SDL_ttf: %s", SDL_GetError());
        return false;
    }
    
    LoadData();

    mTicksCount = SDL_GetTicks();

    return true;
}

void Game::RunLoop(){
    while (mIsRunning){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type)
        {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            
            case SDL_KEYDOWN:
                // Handle key down event
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    mIsRunning = false;
                } else {
                    
                    mTextSet->ProcessInput(event.key.keysym.sym);
                }
                break;
            // case SDL_KEYUP:
            //         break;
        }
    }
    
    // Get state of keyboard
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_SPACE]){
        
    }

}

void Game::UpdateGame(){
    // Compute delta time
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
    
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();
    if (mTextSet->GetSize() == 0){
        mEndCaption->SetVisible(true);
        mScoreCaption->SetText("Score: " + std::to_string(mScore));
    } else {
        // Update the text object
        mTextSet->Update(deltaTime);
        // Update the score
        mScoreCaption->SetText("Score: " + std::to_string(mScore));
    }
    
}

void Game::GenerateOutput(){
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(mRenderer);
    
    mTextSet->Draw(mRenderer);
    mScoreCaption->Draw(mRenderer);
    mEndCaption->Draw(mRenderer);
    SDL_RenderPresent(mRenderer);
}

void Game::LoadData(){
    // Create the components
    SDL_Color white = { 0xFF, 0xFF, 0xFF, 0 };
    SDL_Color green = { 0x00, 0xFF, 0x00, 0 };
    mTextSet = new TextSet(this, "OxygenMono-Regular.otf", 24, white);
    mScoreCaption = new Caption(this, "Score: ", "OxygenMono-Regular.otf", 24, green, 10, 10);
    mEndCaption = new Caption(this, "YOU WIN!", "OxygenMono-Regular.otf", 60, white, 480, 360, false);
    mEndCaption->SetPosition(480 - mEndCaption->GetWidth() / 2, 360 - mEndCaption->GetHeight() / 2);
}

void Game::UnloadData(){

    for (auto i: mFonts){
        TTF_CloseFont(i.second);
    }
    mFonts.clear();
}


TTF_Font* Game::GetFont(const std::string& fontName, int ptsize){
    TTF_Font* font = nullptr;
    std::string key = fontName + std::to_string(ptsize);
    std::string fontFileName = "" + fontName;
    // std::string fontFileName = "res/Fonts/" + fontName;
    auto iter = mFonts.find(key);
    // If already in the map, no need to load
    if(iter != mFonts.end()){
        font = iter->second;        
    } else{
        // Load from file
        font = TTF_OpenFont(fontFileName.c_str(), ptsize);
        if (!font){
            SDL_Log("Failed to load font %s", fontFileName.c_str());
            return nullptr;
        }

        // Add to map
        mFonts.emplace(fontFileName.c_str(), font);
    }
    return font;
}

SDL_Texture* Game::GetTextureFromSurface(SDL_Surface* surf){
    SDL_Texture* tex = nullptr;
    // Create texture from surface
    tex = SDL_CreateTextureFromSurface(mRenderer, surf);
    SDL_FreeSurface(surf);
    if (!tex){
        SDL_Log("Failed to convert surface to texture");
        return nullptr;
    }
    return tex;
}

void Game::Shutdown(){
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

