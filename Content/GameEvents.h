#pragma once
#include <queue>
#include <iostream>
#include <mutex>

enum class GameEvent {
    None,
    StartTurn,
    EndTurn,
    SelectCell,
    SkipTurn,
    Exit,
    DoSomethingOnSpace
};

class GameEventManager {
    std::queue<GameEvent> eventQueue;
    mutable std::mutex queueMutex;

public:
    void AddEvent(GameEvent event) {
        std::lock_guard<std::mutex> lock(queueMutex);
        //std::cout << "Adding event: " << static_cast<int>(event) << std::endl;
        eventQueue.push(event);
    }

    bool HasEvents() const {
        std::lock_guard<std::mutex> lock(queueMutex);
        std::cout << "Checking events, queue size: " << eventQueue.size() << std::endl;
        return !eventQueue.empty();
    }

    GameEvent GetNextEvent() {
        std::lock_guard<std::mutex> lock(queueMutex);
        if (eventQueue.empty()) {
            std::cout << "No events in queue.\n";
            return GameEvent::Exit;
        }
        GameEvent nextEvent = eventQueue.front();
        eventQueue.pop();
        std::cout << "Returning event: " << static_cast<int>(nextEvent) << std::endl;
        return nextEvent;
    }
};
