#include "Logger.h"

Logger::Logger(const std::string& filename, size_t maxLogEntries) : filename(filename), maxLogEntries(maxLogEntries) {
    file.open(filename, std::ios_base::app);
}

Logger::~Logger() {
    if (file.is_open()) {
        file.close();
    }
}

void Logger::log(const std::string& message) {
    std::unique_lock<std::shared_mutex> lock(mutex);
    if (file.is_open()) {
        file << message << "\n";
        file.flush();
        // ��������� ��������� � �������
        logQueue.push_back(message);
        // ���� ������� ����� ������� �������, ������� ����� ������ ���������
        if (logQueue.size() > maxLogEntries) {
            logQueue.pop_front();
        }
    }
}

std::string Logger::readLastLog() {
    std::shared_lock<std::shared_mutex> lock(mutex);
    if (!logQueue.empty()) {
        // ���������� ��������� ��������� �� �������
        return logQueue.back();
    }
    return "No logs available";
}
