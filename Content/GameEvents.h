#pragma once
#include <queue>

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

public:
    void AddEvent(GameEvent event) {
        eventQueue.push(event);
    }

    bool HasEvents() const {
        return !eventQueue.empty();
    }

    GameEvent GetNextEvent() {
        if (eventQueue.empty()) return GameEvent::Exit;
        GameEvent nextEvent = eventQueue.front();
        eventQueue.pop();
        return nextEvent;
    }
};
