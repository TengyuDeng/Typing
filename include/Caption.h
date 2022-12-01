//
//  Caption.h
//  myGame
//
//  Created by Deng Tengyu on 2022/12/01.
//  Copyright © 2022 Deng Tengyu. All rights reserved.
//

#ifndef Caption_h
#define Caption_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "MathUtils.h"

class Caption{
public:
    Caption(
        class Game* game, 
        const std::string& text, 
        const std::string& fontName, int ptsize, 
        const SDL_Color& color,
        int x = 10, int y = 10
    );
    ~Caption();
    
    void SetText(const std::string& text);
    void Draw(SDL_Renderer* renderer);
    class Game* GetGame() const{return mGame;}
    const Vector2D& GetPosition() const{return mPosition;}

private:
    class Game* mGame;
    class CaptionSprite* mCaptionSprite;

    // Position information
    Vector2D mPosition;

};

class CaptionSprite{
public:
    CaptionSprite(
        class Caption* owner, 
        const std::string& text, 
        const std::string& fontName, int ptsize, 
        const SDL_Color& color
        );
    ~CaptionSprite();

    void Draw(SDL_Renderer* renderer);
    void SetText(const std::string& text);
    int GetWidth() const{return mWidth;}
    int GetHeight() const{return mHeight;}

private:
    SDL_Texture* RenderText(const std::string& text, SDL_Color& color);
    class Caption* mOwner;
    // Text information
    std::string mText;

    // Texture information
    TTF_Font* mFont;
    SDL_Color mColor;
    SDL_Texture* mTexture;

    // Texture sizes
    int mWidth;
    int mHeight;
};

#endif /* Caption_h */
