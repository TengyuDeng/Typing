//
//  Game.cpp
//  myGame
//
//  Created by Deng Tengyu on 2022/11/22.
//  Copyright © 2022 Deng Tengyu. All rights reserved.
//

#include "Game.h"
#include "Text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>


Game::Game()
:mWindow(nullptr),
mRenderer(nullptr),
mIsRunning(true),
mTicksCount(0),
mText(nullptr){

}

bool Game::Initialize(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
    {
        std::cout << (SDL_INIT_VIDEO|SDL_INIT_AUDIO);
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Test!", 100, 100, 960, 720, 0);
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
    
    // Update the text object
    mText->Update(deltaTime);

}

void Game::GenerateOutput(){
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(mRenderer);
    
    mText->Draw(mRenderer);
    SDL_RenderPresent(mRenderer);
}

void Game::LoadData(){
    // Create the player
    SDL_Color white = { 0xFF, 0xFF, 0xFF, 0 };
    SDL_Color black = { 0x00, 0x00, 0x00, 0 };
    mText = new Text(this, "Windows XP", "mincho.ttc", 24, { 0xFF, 0xFF, 0xFF, 0 });
}

void Game::UnloadData(){
    // for (auto i: mTextures){
    //     SDL_DestroyTexture(i.second);
    // }
    // mTextures.clear();
    for (auto i: mFonts){
        TTF_CloseFont(i.second);
    }
    mFonts.clear();
}

// SDL_Texture* Game::GetTexture(const std::string& fileName){
//     SDL_Texture* tex = nullptr;
//     // Is the texture alread in the map?
//     auto iter = mTextures.find(fileName);
//     if(iter != mTextures.end()){
//         tex = iter->second;
//     } else{
//         // Load from file
//         SDL_Surface* surf = IMG_Load(fileName.c_str());
//         if (!surf){
//             SDL_Log("Failed to load texture file %s", fileName.c_str());
//             return nullptr;
//         }

//         //Create texture from surface
//         tex = SDL_CreateTextureFromSurface(mRenderer, surf);
//         SDL_FreeSurface(surf);
//         if (!tex){
//             SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
//             return nullptr;
//         }

//         // Add to map
//         mTextures.emplace(fileName.c_str(), tex);
//     }
//     return tex;
// }

TTF_Font* Game::GetFont(const std::string& fontName, int ptsize){
    TTF_Font* font = nullptr;
    std::string fontFileName = "res/Fonts/" + fontName;
    auto iter = mFonts.find(fontFileName);
    // If already in the map, no need to load
    if(iter != mFonts.end()){
        font = iter->second;
        TTF_SetFontSize(font, ptsize);
        
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

