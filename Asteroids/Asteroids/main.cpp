#include "GameLogic.h"

int main()
{
    //Init Game Engine
    GameLogic gameLogic;

    while (gameLogic.isWindowOpen())
    {
        //---------------------------
        // Update

        gameLogic.update();

        //----------------------------
        // Render
        gameLogic.render();
    }

    return 0;
}