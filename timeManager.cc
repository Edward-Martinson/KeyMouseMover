#include "timeManager.hpp"

#include <chrono>

timeManager& timeManager::getInstance(){
    static timeManager instance;
    return instance;
}

void timeManager::start(){
    startTimePoint = std::chrono::_V2::high_resolution_clock::now();
}
void timeManager::end(){
    endTimePoint = std::chrono::_V2::high_resolution_clock::now();
}

std::chrono::_V2::system_clock::time_point startTimePoint, endTimePoint;