#include "Logger.h"
#include <iostream>
#include <thread>

int main() {
    Logger logger("log.txt", 10); // Создать логгер, хранящий до 10 последних логов


    // Потоки для демонстрации потокобезопасности
    std::thread thread1([&]() {
        for (int i = 0; i < 5; ++i) {
            logger.log("Thread 1: Message " + std::to_string(i));
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        });

    std::thread thread2([&]() {
        for (int i = 0; i < 5; ++i) {
            logger.log("Thread 2: Message " + std::to_string(i));
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        });

    thread1.join();
    thread2.join();

    std::cout << "Last log entry: " << logger.readLastLog() << std::endl;

    return 0;
}
