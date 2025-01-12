
#include <iostream>
#include "WindowRenderer.h"


int main()
{
    std::cout << "Hello World!\n";
    GameEventManager eventManager;
    GameHandler gameHandler;
    WindowRenderer renderer(1400, 900, &gameHandler);
    renderer.RunTheGame();
}
