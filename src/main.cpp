//
//  main.cpp
//  myGame 
//
//  Created by Deng Tengyu on 2022/11/01.
//  Copyright © 2022 Deng Tengyu. All rights reserved.
//

#include "Game.h"

int main (int argc, char** argv){
    Game game;
    bool success = game.Initialize();
    if (success)
    {
        game.RunLoop();
    }
    game.Shutdown();
    
    return 0;
}
