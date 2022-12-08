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
        const std::string& fontName, int ptsize,
        const SDL_Color& color,
        int num = 8
    );
    ~TextSet();

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);
    void ProcessInput(SDL_Keycode key);
    class Game* GetGame() const{return mGame;}
    int GetSize() const{return mTextList.size();}
    void RemoveText(class Text* text);

private:
    void GenerateText();
    class Game* mGame;
    int mNumTexts;
    std::vector<class Text*> mTextList;
    std::string mFontName;
    int mPtsize;
    SDL_Color mColor;
    std::vector<std::string> mTextAvailableList = {
        "WindowsXP", "macOS", "Cpp", "Kyoto", "Demachiyanagi",
        "Higashiyama", "Imadegawa", "Kawaramachimarutamachi", 
        "Oosaka", "Keihan", "Hankyuu", "Hanshin", 
        "Nankai", "Kintetsu","JR",  "Tokaidou",
        };
    std::vector<std::string> mTextInUseList = {};

};

#endif /* TextSet_h */
