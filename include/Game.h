//
//  Game.h
//  myGame
//
//  Created by Deng Tengyu on 2022/11/22.
//  Copyright © 2022 Deng Tengyu. All rights reserved.
//

#ifndef Game_h
#define Game_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <vector>
#include <string>

class Game
{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
 
    // SDL_Texture* GetTexture(const std::string& fileName);
    TTF_Font* GetFont(const std::string& fontFileName, int ptsize);
    SDL_Texture* GetTextureFromSurface(SDL_Surface* surf);

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();

    // Map of fonts loaded
    // std::unordered_map<std::string, SDL_Texture*> mTextures;
    std::unordered_map<std::string, TTF_Font*> mFonts;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mIsRunning;
    Uint32 mTicksCount;
    
    class Text* mText;

};

#endif /* Game_h */
