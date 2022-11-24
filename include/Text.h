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
#include <string>
#include "MathUtils.h"

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

private:
    class Game* mGame;
    std::string mTextTyped;
    std::string mTextRest;
    SDL_Texture* mTexture;

    // Position informations
    SDL_Rect mRect;
    Vector2D mSpeed;
    // int mWidth;
    // int mHeight;
    // int mPosX;
    // int mPosY;
    // float mSpeedX;
    // float mSpeedY;

    // Attribute to check if the text is dead
    bool mDead;

};

#endif /* Text_h */
