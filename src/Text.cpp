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


Text::Text(class Game* game, const std::string& text, const std::string& fontName, int ptsize, const SDL_Color& color)
:mGame(game),
mTextTyped(""),
mTextRest(text)
{
    TTF_Font* font = mGame->GetFont(fontName, ptsize);

    SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surf){
        
        SDL_Log("Failed to render text %s", text.c_str());
        return;
    }
    mTexture = mGame->GetTextureFromSurface(surf);
    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
}

void Text::Update(float deltaTime){

}

void Text::Draw(SDL_Renderer* renderer, int x, int y){
    // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    // SDL_RenderClear(renderer);
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = mWidth;
    dest.h = mHeight;
    SDL_RenderCopy(renderer, mTexture, NULL, &dest);
    // SDL_RenderPresent(renderer);

}
