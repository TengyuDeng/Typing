//
//  TextSet.h
//  myGame
//
//  Created by Deng Tengyu on 2022/12/02.
//  Copyright © 2022 Deng Tengyu. All rights reserved.
//

#ifndef TextSet_h
#define TextSet_h
#include <SDL2/SDL.h>
#include <string>
#include <vector>

class TextSet{
public:
    TextSet(
        class Game* game,
        std::vector<std::string> textList,
        const std::string& fontName, int ptsize,
        const SDL_Color& color
    );
    ~TextSet();

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);
    void ProcessInput(SDL_Keycode key);
    class Game* GetGame() const{return mGame;}
    int GetSize() const{return mTextList.size();}
    void RemoveText(class Text* text);

private:
    class Game* mGame;
    std::vector<class Text*> mTextList;

};

#endif /* TextSet_h */
