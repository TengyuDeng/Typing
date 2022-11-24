//
//  Text.cpp
//  myGame
//
//  Created by Deng Tengyu on 2022/11/23.
//  Copyright © 2022 Deng Tengyu. All rights reserved.
//

#include "Game.h"
#include "Text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


Text::Text(
    class Game* game, 
    const std::string& text, 
    const std::string& fontName, int ptsize, 
    const SDL_Color& color,
    int x, int y
):mGame(game),
mTextTyped(""),
mTextRest(text),
mRect({x, y, 0, 0}),
mSpeed(180.0f, 180.0f){
    TTF_Font* font = mGame->GetFont(fontName, ptsize);

    SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surf){
        
        SDL_Log("Failed to render text %s", text.c_str());
        return;
    }
    mTexture = mGame->GetTextureFromSurface(surf);
    SDL_QueryTexture(mTexture, NULL, NULL, &mRect.w, &mRect.h);
}

Text::~Text(){
    SDL_DestroyTexture(mTexture);
}

void Text::Update(float deltaTime){
    mRect.x += static_cast<int>(mSpeed.x * deltaTime);
    if (mRect.x < 0 || mRect.x > 960 - mRect.w){
        mSpeed.x *= -1;
    }
    mRect.y += static_cast<int>(mSpeed.y * deltaTime);
    if (mRect.y < 0 || mRect.y > 720 - mRect.h){
        mSpeed.y *= -1;
        // mDead = true;
    }
}

void Text::Draw(SDL_Renderer* renderer){
    // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    // SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, mTexture, NULL, &mRect);
    // SDL_RenderPresent(renderer);

}
