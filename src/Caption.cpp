//
//  Text.cpp
//  myGame
//
//  Created by Deng Tengyu on 2022/11/23.
//  Copyright © 2022 Deng Tengyu. All rights reserved.
//

#include "Game.h"
#include "Caption.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cctype>

Caption::Caption(
    class Game* game, 
    const std::string& text, 
    const std::string& fontName, int ptsize, 
    const SDL_Color& color,
    int x, int y,
    bool isVisible
):mGame(game),
mPosition(x, y),
mIsVisible(isVisible){
    mCaptionSprite = new CaptionSprite(this, text, fontName, ptsize, color);
}

void Caption::SetText(const std::string& text){
    mCaptionSprite->SetText(text); 
}

void Caption::Draw(SDL_Renderer* renderer){
    if (mIsVisible){
        mCaptionSprite->Draw(renderer);
    }
}

int Caption::GetWidth() const{
    return mCaptionSprite->GetWidth();
    }
int Caption::GetHeight() const{
    return mCaptionSprite->GetHeight();
    }

CaptionSprite::CaptionSprite(
    class Caption* owner, 
    const std::string& text, 
    const std::string& fontName, int ptsize, 
    const SDL_Color& color
):mOwner(owner),
mColor(color),
mText(text){
    // Get font and initialize the textures
    mFont = mOwner->GetGame()->GetFont(fontName, ptsize);
    mTexture = RenderText(mText, mColor);
    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
}

CaptionSprite::~CaptionSprite(){
    SDL_DestroyTexture(mTexture);
}

void CaptionSprite::SetText(const std::string& text){
    mText = text; 
    mTexture = RenderText(mText, mColor);
    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
}

void CaptionSprite::Draw(SDL_Renderer* renderer){
    
    SDL_Rect rect;
    rect.x = static_cast<int>(mOwner->GetPosition().x);
    rect.y = static_cast<int>(mOwner->GetPosition().y);
    rect.w = mWidth;
    rect.h = mHeight;
    // Draw the text
    if (mTexture){
        SDL_RenderCopy(renderer, mTexture, NULL, &rect);
    }
    // Draw the rectangle border
}

SDL_Texture* CaptionSprite::RenderText(const std::string& text, SDL_Color& color){
    // Render text from text and text color
    // Return the texture
    SDL_Surface* surf = TTF_RenderText_Solid(mFont, text.c_str(), color);
    if (!surf){
        SDL_Log("Failed to render text %s", text.c_str());
        return nullptr;
    }
    return mOwner->GetGame()->GetTextureFromSurface(surf);
}
