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
#include <random>

TextSet::TextSet(
    class Game* game,
    const std::string& fontName, int ptsize,
    const SDL_Color& color,
    int numTexts
):mGame(game),
mFontName(fontName),
mPtsize(ptsize),
mColor(color),
mNumTexts(numTexts){
    // Generate initial texts
    for (int i = 0; i < mNumTexts; i++){
        GenerateText();
    }
}

TextSet::~TextSet(){
    for (auto text : mTextList){
        delete text;
    }
}

void TextSet::Update(float deltaTime){
    // Generate new texts
    if (mTextList.size() < mNumTexts){
        GenerateText();
        }
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
    // Remove the text from mTextInUseList
    // and add to mTextAvailableList
    std::string text_content = text->GetText();
    mTextInUseList.erase(
            std::remove(
                mTextInUseList.begin(), mTextInUseList.end(), text_content
            ), 
            mTextInUseList.end()
        );
    // Remove the text from mTextList
    mTextList.erase(
            std::remove(
                mTextList.begin(), mTextList.end(), text
            ), 
            mTextList.end()
        );
    mTextAvailableList.emplace_back(text_content);
    // When a text is removed, reset all other texts
    for (auto text : mTextList){
        text->Reset();
    }
}

void TextSet::GenerateText(){
    // Randomly select a text from mTextAvailableList, and generate a new text at random position
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, mTextAvailableList.size() - 1);
    int index = dist(mt);
    std::string text = mTextAvailableList[index];
    std::uniform_int_distribution<int> distX(20, 960 - 10 * text.size());
    std::uniform_int_distribution<int> distY(100, 720 - 100);
    std::uniform_real_distribution<float> distSpeed(100.0f, 300.0f);
    int x = distX(mt);
    int y = distY(mt);
    float speedX = distSpeed(mt);
    float speedY = distSpeed(mt);
    mTextList.emplace_back(new Text(this, text, mFontName, mPtsize, mColor, x, y, speedX, speedY));
    // Remove the text from mTextAvailableList
    // and add to mTextInUseList
    mTextAvailableList.erase(mTextAvailableList.begin() + index);
    mTextInUseList.emplace_back(text);
}