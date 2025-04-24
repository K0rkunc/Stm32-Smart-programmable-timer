#include "EA_Timer.h"

EA_Timer::EA_Timer() : m_nextId(1) {}

EA_Timer::~EA_Timer() {
    stopAllTimers();
}

uint8_t EA_Timer::getNextId() {
    return m_nextId++;
}

uint8_t EA_Timer::startTimer(uint32_t interval, std::function<void()> callback) {
    TimerInfo timer;
    timer.startTime = HAL_GetTick();
    timer.interval = interval;
    timer.callback = callback;
    timer.isActive = true;
    timer.id = getNextId();
    timer.autoRestart = false;  // Tek seferlik timer
    
    m_timers.push_back(timer);
    return timer.id;
}

uint8_t EA_Timer::startAutoRestartTimer(uint32_t interval, std::function<void()> callback) {
    TimerInfo timer;
    timer.startTime = HAL_GetTick();
    timer.interval = interval;
    timer.callback = callback;
    timer.isActive = true;
    timer.id = getNextId();
    timer.autoRestart = true;  // Otomatik yeniden başlatmalı timer
    
    m_timers.push_back(timer);
    return timer.id;
}

void EA_Timer::stopTimer(uint8_t timerId) {
    for (auto& timer : m_timers) {
        if (timer.id == timerId) {
            timer.isActive = false;
            break;
        }
    }
}

void EA_Timer::stopAllTimers() {
    for (auto& timer : m_timers) {
        timer.isActive = false;
    }
    m_timers.clear();
}

void EA_Timer::processTimers() {
    uint32_t currentTime = HAL_GetTick();
    
    for (auto it = m_timers.begin(); it != m_timers.end();) {
        if (it->isActive) {
            if ((currentTime - it->startTime) >= it->interval) {
                it->callback();
                
                if (it->autoRestart) {
                    // Otomatik yeniden başlatma
                    it->startTime = currentTime;
                    ++it;
                } else {
                    // Tek seferlik timer'ı sil
                    it = m_timers.erase(it);
                }
            } else {
                ++it;
            }
        } else {
            it = m_timers.erase(it);
        }
    }
}

bool EA_Timer::isTimerActive(uint8_t timerId) const {
    for (const auto& timer : m_timers) {
        if (timer.id == timerId && timer.isActive) {
            return true;
        }
    }
    return false;
}

uint32_t EA_Timer::getRemainingTime(uint8_t timerId) const {
    for (const auto& timer : m_timers) {
        if (timer.id == timerId && timer.isActive) {
            uint32_t elapsed = HAL_GetTick() - timer.startTime;
            return (elapsed >= timer.interval) ? 0 : (timer.interval - elapsed);
        }
    }
    return 0;
} 