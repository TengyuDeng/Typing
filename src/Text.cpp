//
//  Text.cpp
//  myGame
//
//  Created by Deng Tengyu on 2022/11/23.
//  Copyright © 2022 Deng Tengyu. All rights reserved.
//

#include "Text.h"
#include "TextSet.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cctype>

Text::Text(
    class TextSet* textset, 
    const std::string& text, 
    const std::string& fontName, int ptsize, 
    const SDL_Color& color,
    int x, int y
):mTextSet(textset),
mSpeed(180.0f, 180.0f),
mPosition(x, y),
mState(ACTIVE){
    mTextSprite = new TextSprite(this, text, fontName, ptsize, color);
}

Text::~Text(){
    // Remove the text from the textset when deleted
    mTextSet->RemoveText(this);
}

void Text::Update(float deltaTime){
    // Update the position
    mPosition.x += static_cast<int>(mSpeed.x * deltaTime);
    if (mPosition.x < 0 || mPosition.x > 960 - mTextSprite->GetWidth()){
        mSpeed.x *= -1;
    }
    mPosition.y += static_cast<int>(mSpeed.y * deltaTime);
    if (mPosition.y < 50){
        mSpeed.y *= -1;
    }
    if (mPosition.y > 720 - mTextSprite->GetHeight()){
        mSpeed.y *= -1;
        // SetState(DEAD);
    }  
}

void Text::Draw(SDL_Renderer* renderer){
    mTextSprite->Draw(renderer);
}

void Text::ProcessInput(SDL_Keycode key){
    mTextSprite->ProcessInput(key);
}

class Game* Text::GetGame() const{
    return mTextSet->GetGame();
    }

TextSprite::TextSprite(
    class Text* owner, 
    const std::string& text, 
    const std::string& fontName, int ptsize, 
    const SDL_Color& color
):mOwner(owner),
mTypedColor(color),
mText(text),
mTypedIdx(0),
mWidthTyped(0),
mTextureTyped(nullptr),
mTextureRest(nullptr){
    // The color of the rest text is more transparent
    mRestColor = mTypedColor;
    mRestColor.a = 0x80;
    // Get font and initialize the textures
    mFont = mOwner->GetGame()->GetFont(fontName, ptsize);
    UpdateTexture();
}

TextSprite::~TextSprite(){
    SDL_DestroyTexture(mTextureTyped);
    SDL_DestroyTexture(mTextureRest);
}

void TextSprite::ProcessInput(SDL_Keycode key){

    if (
        (key >= SDLK_a && key <= SDLK_z) || 
        (key >= SDLK_0 && key <= SDLK_9) ||
        key == SDLK_QUOTE || key == SDLK_COMMA || 
        key == SDLK_PERIOD || key == SDLK_MINUS || 
        key == SDLK_SPACE
        ){
        if (std::tolower(mText[mTypedIdx]) == key){
            mTypedIdx++;
            UpdateTexture();
        } else{
            mTypedIdx = 0;
            UpdateTexture();
        }
    }
    
}

void TextSprite::Draw(SDL_Renderer* renderer){
    
    SDL_Rect rect;
    rect.x = static_cast<int>(mOwner->GetPosition().x);
    rect.y = static_cast<int>(mOwner->GetPosition().y);
    rect.w = mWidthTyped;
    rect.h = mHeight;
    // Draw typed text
    if (mTextureTyped){
        SDL_RenderCopy(renderer, mTextureTyped, NULL, &rect);
    }
    // Draw the rest text to the right of typed text
    if (mTextureRest){
        rect.x += mWidthTyped;
        rect.w = mWidthRest;
        SDL_RenderCopy(renderer, mTextureRest, NULL, &rect);
    }
}

SDL_Texture* TextSprite::RenderText(const std::string& text, SDL_Color& color){
    // Render text from text and text color
    // Return the texture
    SDL_Surface* surf = TTF_RenderText_Solid(mFont, text.c_str(), color);
    if (!surf){
        SDL_Log("Failed to render text %s", text.c_str());
        return nullptr;
    }
    return mOwner->GetGame()->GetTextureFromSurface(surf);
}

void TextSprite::UpdateTexture() {
    // Called when mTypedIdx changed
    // Update mTextureTyped, mTextureRest, and mWidthTyped, mWidthRest
    
    // Destroy the old typed texture
    if (mTextureTyped) {
        SDL_DestroyTexture(mTextureTyped);
    }
    // If mTypedIdx is 0, no typed texture to render
    // else create the typed texture
    if (mTypedIdx == 0) {
        mTextureTyped = nullptr;
        mWidthTyped = 0;
    } else {
        mTextureTyped = RenderText(mText.substr(0, mTypedIdx), mTypedColor);
        SDL_QueryTexture(mTextureTyped, NULL, NULL, &mWidthTyped, &mHeight);
    }
    
    // Destroy the old rest texture
    if (mTextureRest) {
        SDL_DestroyTexture(mTextureRest);
    }
    // If mTypedIdx is at the end, create the rest texture
    // else set the state to SUCCESS
    if (mTypedIdx < mText.size()) {
        mTextureRest = RenderText(mText.substr(mTypedIdx), mRestColor);
        SDL_QueryTexture(mTextureRest, NULL, NULL, &mWidthRest, &mHeight);
    } else {
        mTextureRest = nullptr;        
        mWidthRest = 0;
        mOwner->SetState(SUCCESS);
    }

}