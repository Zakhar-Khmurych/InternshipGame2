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

        // ��������� ����� ���, ���������, �������� ����� ��� ��� ����������� ����� ���������
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

        // ��� ����� �������������� ��� ��� ��������� �� �� ������.

        {
            std::lock_guard<std::mutex> lock(mtx);
            cv.notify_all();
        }

    }
}

int main() {
    std::cout << "Game Started!" << std::endl;

    GameHandler gameHandler;
    WindowRenderer renderer(1400, 900, &gameHandler);

    std::thread logicThread(gameLogicThread, &gameHandler);
    std::thread renderThread(renderingThread, &renderer);
    std::thread inputThread(playerInputThread, &gameHandler);

    // �������� ���� ���, ���� ���� �� 䳿 ������
    while (isRunning) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock);  // ������ �� ������, �� ������� ������ ��

        // ����� ���, ��� ���������� ���� ����, �� �������� ��
        // ��� ����� �������� ����� ���, �� �������� �� �������� ������

        // ���������� ��� �� �������� 䳿
    }

    // ������ ���������� ������
    inputThread.join();
    renderThread.join();
    logicThread.join();

    return 0;
}
