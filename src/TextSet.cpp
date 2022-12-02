//
//  TextSet.cpp
//  myGame
//
//  Created by Deng Tengyu on 2022/12/02.
//  Copyright © 2022 Deng Tengyu. All rights reserved.
//

#include "TextSet.h"
#include "Game.h"
#include "Text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <algorithm>

TextSet::TextSet(
    class Game* game,
    std::vector<std::string> textList,
    const std::string& fontName, int ptsize,
    const SDL_Color& color
):mGame(game){
    for (auto text : textList){
        mTextList.emplace_back(new Text(this, text, fontName, ptsize, color));
    }
}

TextSet::~TextSet(){
    for (auto text : mTextList){
        delete text;
    }
}

void TextSet::Update(float deltaTime){
    // Generate new texts
    // Update all the texts
    std::vector<class Text*> TextsToRemove;
    for (auto text : mTextList){
        switch (text->GetState()){
            case ACTIVE:
                text->Update(deltaTime);
                break;
            case DEAD:
                mGame->AddScore(-100);
                TextsToRemove.emplace_back(text);
                break;
            case SUCCESS:
                mGame->AddScore(100);
                TextsToRemove.emplace_back(text);
                break;
        }
    }
    for (auto text : TextsToRemove){
        // The deconstructor of Text will remove the text from mTextList
        delete text;
    }
}

void TextSet::Draw(SDL_Renderer* renderer){
    for (auto text : mTextList){
        text->Draw(renderer);
    }
}

void TextSet::ProcessInput(SDL_Keycode key){
    for (auto text : mTextList){
        text->ProcessInput(key);
    }
}

void TextSet::RemoveText(class Text* text){
    // Remove the text from mTextList
    mTextList.erase(
            std::remove(
                mTextList.begin(), mTextList.end(), text
            ), 
            mTextList.end()
        );
}