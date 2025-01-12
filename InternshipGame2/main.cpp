
#include <iostream>
#include <thread>
#include "WindowRenderer.h"

std::atomic<bool> isRunning{ true };

void gameLogicThread(GameHandler* gameHandler) {
    while (isRunning) {
        // ��� ����� ��������� ����� ��������� �����, ���� �� �
        // ���������:
        // gameHandler->UpdateGameLogic();
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
}

int main() {
    std::cout << "Hello World!\n";
    GameHandler gameHandler;

    // ��������� ���� �����
    std::thread logicThread(gameLogicThread, &gameHandler);

    // ��������� ��������� � ��������� ������
    WindowRenderer renderer(1400, 900, &gameHandler);
    renderer.RunTheGame();

    // ϳ��� �������� ���� ��������� ���� �����
    isRunning = false;
    logicThread.join();

    return 0;
}
