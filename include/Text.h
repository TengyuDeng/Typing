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

class Text{
public:
    Text(class Game* game, const std::string& text, const std::string& fontName, int size, const SDL_Color& color);
    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer, int x, int y);

private:
    class Game* mGame;
    std::string mTextTyped;
    std::string mTextRest;
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

#endif /* Text_h */
