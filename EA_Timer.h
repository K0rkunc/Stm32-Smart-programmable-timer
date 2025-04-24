#ifndef EA_TIMER_H
#define EA_TIMER_H

#include "main.h"
#include <functional>
#include <vector>

struct TimerInfo {
    uint32_t startTime;
    uint32_t interval;
    std::function<void()> callback;
    bool isActive;
    uint8_t id;
    bool autoRestart;  // Otomatik yeniden başlatma özelliği
};

class EA_Timer {
public:
    EA_Timer();
    ~EA_Timer();

    // Timer başlatma (tek seferlik)
    uint8_t startTimer(uint32_t interval, std::function<void()> callback);
    
    // Timer başlatma (otomatik yeniden başlatmalı)
    uint8_t startAutoRestartTimer(uint32_t interval, std::function<void()> callback);
    
    // Timer durdurma
    void stopTimer(uint8_t timerId);
    
    // Tüm timer'ları durdurma
    void stopAllTimers();
    
    // Timer'ları kontrol etme
    void processTimers();
    
    // Timer aktif mi kontrol etme
    bool isTimerActive(uint8_t timerId) const;
    
    // Timer kalan süresini alma
    uint32_t getRemainingTime(uint8_t timerId) const;

private:
    std::vector<TimerInfo> m_timers;
    uint8_t m_nextId;
    
    uint8_t getNextId();
};

#endif // EA_TIMER_H 