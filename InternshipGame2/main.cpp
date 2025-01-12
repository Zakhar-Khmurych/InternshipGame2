
#include <iostream>
#include <thread>
#include "WindowRenderer.h"

std::atomic<bool> isRunning{ true };

void gameLogicThread(GameHandler* gameHandler) {
    while (isRunning) {
        // Тут можна викликати метод оновлення логіки, якщо він є
        // Наприклад:
        // gameHandler->UpdateGameLogic();
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
}

int main() {
    std::cout << "Hello World!\n";
    GameHandler gameHandler;

    // Запускаємо потік логіки
    std::thread logicThread(gameLogicThread, &gameHandler);

    // Запускаємо рендеринг у головному потоці
    WindowRenderer renderer(1400, 900, &gameHandler);
    renderer.RunTheGame();

    // Після закриття вікна завершимо потік логіки
    isRunning = false;
    logicThread.join();

    return 0;
}
