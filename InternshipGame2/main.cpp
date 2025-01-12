
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include "WindowRenderer.h"

std::atomic<bool> isRunning{ true };

void gameLogicThread(GameHandler* gameHandler) {
    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void renderingThread(WindowRenderer* renderer) {
    while (isRunning) {
        renderer->RenderGame();

        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
    isRunning = false;
}

int main() {
    std::cout << "Hello World!\n";
    GameHandler gameHandler;

    std::thread logicThread(gameLogicThread, &gameHandler);

    WindowRenderer renderer(1400, 900, &gameHandler);
    std::thread renderThread(renderingThread, &renderer);

    renderThread.join();
    logicThread.join();

    return 0;
}
