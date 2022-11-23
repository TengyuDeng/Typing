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
mPosX(x), mPosY(y),
mSpeedX(360.0f), mSpeedY(360.0f){
    TTF_Font* font = mGame->GetFont(fontName, ptsize);

    SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surf){
        
        SDL_Log("Failed to render text %s", text.c_str());
        return;
    }
    mTexture = mGame->GetTextureFromSurface(surf);
    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
}

Text::~Text(){
    SDL_DestroyTexture(mTexture);
}

void Text::Update(float deltaTime){
    mPosX += static_cast<int>(mSpeedX * deltaTime);
    if (mPosX < 0 || mPosX > 960 - mWidth){
        mSpeedX *= -1;
    }
    mPosY += static_cast<int>(mSpeedY * deltaTime);
    if (mPosY < 0 || mPosY > 720 - mHeight){
        mDead = true;
    }
}

void Text::Draw(SDL_Renderer* renderer){
    // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    // SDL_RenderClear(renderer);
    SDL_Rect dest;
    dest.x = mPosX;
    dest.y = mPosY;
    dest.w = mWidth;
    dest.h = mHeight;
    SDL_RenderCopy(renderer, mTexture, NULL, &dest);
    // SDL_RenderPresent(renderer);

}
