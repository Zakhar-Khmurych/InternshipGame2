#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include "WindowRenderer.h"
#include "GameHandler.h"

std::atomic<bool> isRunning{ true };
std::mutex mtx;
std::condition_variable cv;

void gameLogicThread(GameHandler* gameHandler) {
    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS

        // Оновлення логіки гри, наприклад, перевірка стану гри або ініціалізація черги ініціативи
        gameHandler->current_session->PlayRound();
    }
}

void renderingThread(WindowRenderer* renderer) {
    while (isRunning) {
        renderer->RenderGame();
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
}

void playerInputThread(GameHandler* gameHandler) {
    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Затримка для імітації очікування на дію гравця

        // Тут можна імплементувати код для отримання дій від гравця.
        std::cout << "Waiting for player action..." << std::endl;

        // Коли гравець натискає, або інша подія відбувається, сигналізуємо основному потоку
        {
            std::lock_guard<std::mutex> lock(mtx);
            // Сигналізація, що дія гравця отримана
            cv.notify_all();
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));  // Затримка між діями
    }
}

int main() {
    std::cout << "Game Started!" << std::endl;

    GameHandler gameHandler;
    WindowRenderer renderer(1400, 900, &gameHandler);

    std::thread logicThread(gameLogicThread, &gameHandler);
    std::thread renderThread(renderingThread, &renderer);
    std::thread inputThread(playerInputThread, &gameHandler);

    // Основний цикл гри, який чекає на дії гравця
    while (isRunning) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock);  // Чекаємо на сигнал, що гравець зробив дію

        // Логіка гри, яка відбувається після того, як отримано дію
        std::cout << "Player action received, processing..." << std::endl;
        // Далі можна додавати кроки гри, які залежать від введення гравця

        // Продовжуємо гру до наступної дії
    }

    // Чекаємо завершення потоків
    inputThread.join();
    renderThread.join();
    logicThread.join();

    return 0;
}
