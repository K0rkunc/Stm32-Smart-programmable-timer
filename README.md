# EA_Timer Library

## What is it?
EA_Timer is a simple but powerful timer management library that you can use in STM32 projects. With this library, you can easily manage multiple timers and assign special functions to each. You can set timers to work once or continuously.

## What can it do?
- You can create as many timers as you want
- Each timer has its own number
- You can check if the timer is working
- You can find out how much time is left for the timer
- You can easily manage timers using Lambda functions
- You can set timers to work once or continuously

## How to Use?

### Start
First add the library to your project:
1. Copy `EA_Timer.h` and `EA_Timer.cpp` files to your project
2. Include the header in the file you will use:
```cpp
#include "EA_Timer.h"
```

### Creating a Timer
```cpp
EA_Timer timer;
```

### One-Time Timer
```cpp
uint8_t timerId = timer.startTimer(5000, []() {
// Actions to be taken when the timer expires
// Example: Turn the LED on/off
HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
});
```

### Continuous Timer
```cpp
uint8_t timerId = timer.startAutoRestartTimer(5000, []() {
// Actions to be taken when the timer expires
// This timer will automatically restart
HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
});
```

### Stopping Timer
```cpp
timer.stopTimer(timerId);
```

### Stopping All Timers
```cpp
timer.stopAllTimers();
```

### Checking Timer Status
```cpp
if (timer.isTimerActive(timerId)) {
// Timer is still running
}
```

### Finding the Remaining Time
```cpp
uint32_t remaining = timer.getRemainingTime(timerId);
```

### Running Timers
To check timers in the main loop:
```cpp
while (1) {
timer.processTimers();
// ... other processes ...
}
```

## Examples

### LED Control (One-Time)
```cpp
EA_Timer ledTimer;

// Turn the LED on/off once after 5 seconds
uint8_t ledTimerId = ledTimer.startTimer(5000, []() {
HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
});

// In the main loop
while (1) {
ledTimer.processTimers();
HAL_Delay(1);
}
```

### LED Control (Continuous)
```cpp
EA_Timer ledTimer;

// Turn the LED on/off once every 1 second
uint8_t ledTimerId = ledTimer.startAutoRestartTimer(1000, []() {
HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
});

// In the main loop
while (1) {
ledTimer.processTimers();
HAL_Delay(1);
}
```

### Using Multiple Timers
```cpp
EA_Timer multiTimer;

// Timer 1: Every 2 seconds (continuous)
uint8_t timer1Id = multiTimer.startAutoRestartTimer(2000, []() {
// Process 1
});

// Timer 2: Once after 5 seconds
uint8_t timer2Id = multiTimer.startTimer(5000, []() {
// Process 2
});

// In the main loop
while (1) {
multiTimer.processTimers();
HAL_Delay(1);
}
```

## Things to Note
1. Timers work in milliseconds
2. Each timer has its own unique number
3. One-time timers clean themselves up when they are done
4. Timers that run continuously continue until you stop them
5. Don't forget to call the `processTimers()` function regularly
6. Creating too many timers can fill up RAM

## Error Cases
1. If the timer number is not found:
- `stopTimer()` and `isTimerActive()` functions do nothing
- `getRemainingTime()` function returns 0

2. If memory is insufficient:
- `startTimer()` and `startAutoRestartTimer()` functions return 0
- TR
# EA_Timer Kütüphanesi

## Nedir?
EA_Timer, STM32 projelerinde kullanabileceğiniz basit ama güçlü bir timer yönetim kütüphanesidir. Bu kütüphane sayesinde birden fazla timer'ı kolayca yönetebilir, her birine özel işlevler atayabilirsiniz. Timer'ları tek seferlik veya sürekli çalışacak şekilde ayarlayabilirsiniz.

## Neler Yapabilir?
- İstediğiniz kadar timer oluşturabilirsiniz
- Her timer'ın kendine özel bir numarası olur
- Timer'ın çalışıp çalışmadığını kontrol edebilirsiniz
- Timer'ın ne kadar süresi kaldığını öğrenebilirsiniz
- Lambda fonksiyonları kullanarak timer'ları kolayca yönetebilirsiniz
- Timer'ları tek seferlik veya sürekli çalışacak şekilde ayarlayabilirsiniz

## Nasıl Kullanılır?

### Başlangıç
Önce kütüphaneyi projenize ekleyin:
1. `EA_Timer.h` ve `EA_Timer.cpp` dosyalarını projenize kopyalayın
2. Kullanacağınız dosyada header'ı dahil edin:
```cpp
#include "EA_Timer.h"
```

### Timer Oluşturma
```cpp
EA_Timer timer;
```

### Tek Seferlik Timer
```cpp
uint8_t timerId = timer.startTimer(5000, []() {
    // Timer süresi dolduğunda yapılacak işlemler
    // Örnek: LED'i yak/söndür
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
});
```

### Sürekli Çalışan Timer
```cpp
uint8_t timerId = timer.startAutoRestartTimer(5000, []() {
    // Timer süresi dolduğunda yapılacak işlemler
    // Bu timer otomatik olarak yeniden başlayacak
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
});
```

### Timer Durdurma
```cpp
timer.stopTimer(timerId);
```

### Tüm Timer'ları Durdurma
```cpp
timer.stopAllTimers();
```

### Timer Durumunu Kontrol Etme
```cpp
if (timer.isTimerActive(timerId)) {
    // Timer hala çalışıyor
}
```

### Kalan Süreyi Öğrenme
```cpp
uint32_t remaining = timer.getRemainingTime(timerId);
```

### Timer'ları Çalıştırma
Ana döngüde timer'ları kontrol etmek için:
```cpp
while (1) {
    timer.processTimers();
    // ... diğer işlemler ...
}
```

## Örnekler

### LED Kontrolü (Tek Seferlik)
```cpp
EA_Timer ledTimer;

// LED'i 5 saniye sonra bir kez yak/söndür
uint8_t ledTimerId = ledTimer.startTimer(5000, []() {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
});

// Ana döngüde
while (1) {
    ledTimer.processTimers();
    HAL_Delay(1);
}
```

### LED Kontrolü (Sürekli)
```cpp
EA_Timer ledTimer;

// LED'i her 1 saniyede bir yak/söndür
uint8_t ledTimerId = ledTimer.startAutoRestartTimer(1000, []() {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
});

// Ana döngüde
while (1) {
    ledTimer.processTimers();
    HAL_Delay(1);
}
```

### Birden Fazla Timer Kullanımı
```cpp
EA_Timer multiTimer;

// Timer 1: Her 2 saniyede bir (sürekli)
uint8_t timer1Id = multiTimer.startAutoRestartTimer(2000, []() {
    // İşlem 1
});

// Timer 2: 5 saniye sonra bir kez
uint8_t timer2Id = multiTimer.startTimer(5000, []() {
    // İşlem 2
});

// Ana döngüde
while (1) {
    multiTimer.processTimers();
    HAL_Delay(1);
}
```

## Dikkat Edilmesi Gerekenler
1. Timer'lar milisaniye cinsinden çalışır
2. Her timer'ın kendine özel bir numarası vardır
3. Tek seferlik timer'lar işi bitince kendini temizler
4. Sürekli çalışan timer'lar siz durdurana kadar devam eder
5. `processTimers()` fonksiyonunu düzenli olarak çağırmayı unutmayın
6. Çok fazla timer oluşturmak RAM'i doldurabilir

## Hata Durumları
1. Timer numarası bulunamazsa:
   - `stopTimer()` ve `isTimerActive()` fonksiyonları hiçbir şey yapmaz
   - `getRemainingTime()` fonksiyonu 0 döndürür

2. Bellek yetersizse:
   - `startTimer()` ve `startAutoRestartTimer()` fonksiyonları 0 döndürür
