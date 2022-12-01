//
//  Text.h
//  myGame
//
//  Created by Deng Tengyu on 2022/11/23.
//  Copyright © 2022 Deng Tengyu. All rights reserved.
//

#ifndef Text_h
#define Text_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "MathUtils.h"

typedef enum {
    ACTIVE,
    DEAD,
    SUCCESS,
} TextState;

class Text{
public:
    Text(
        class Game* game, 
        const std::string& text, 
        const std::string& fontName, int ptsize, 
        const SDL_Color& color,
        int x = 360, int y = 20
    );
    ~Text();

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);
    void ProcessInput(SDL_Keycode key);
    class Game* GetGame() const{return mGame;}
    const Vector2D& GetPosition() const{return mPosition;}
    void SetState(TextState state){mState = state;}

private:
    class Game* mGame;
    class TextSprite* mTextSprite;

    // Position informations
    Vector2D mPosition;
    Vector2D mSpeed;

    // Attribute to check if the text is dead
    TextState mState;

};

class TextSprite{
public:
    TextSprite(
        class Text* owner, 
        const std::string& text, 
        const std::string& fontName, int ptsize, 
        const SDL_Color& color
        );
    ~TextSprite();

    void ProcessInput(SDL_Keycode key);
    void Draw(SDL_Renderer* renderer);

    int GetWidth() const{return mWidthTyped + mWidthRest;}
    int GetHeight() const{return mHeight;}

private:
    SDL_Texture* RenderText(const std::string& text, SDL_Color& color);
    void UpdateTexture();
    class Text* mOwner;
    // Text information
    std::string mText;
    int mTypedIdx;

    // Texture information
    TTF_Font* mFont;
    SDL_Color mTypedColor;
    SDL_Color mRestColor;
    SDL_Texture* mTextureTyped;
    SDL_Texture* mTextureRest;

    // Texture sizes
    int mWidthTyped;
    int mWidthRest;
    int mHeight;
};

#endif /* Text_h */
