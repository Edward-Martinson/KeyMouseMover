#pragma once
#include <chrono>

class timeManager{
    public:
    static timeManager& getInstance();
    void start();
    void end();

    template <typename T>
    T getDuration(){
        T dur = std::chrono::duration<T, std::milli>(endTimePoint - startTimePoint).count();
        return dur;
    }

    private:
    timeManager() {}

    std::chrono::_V2::high_resolution_clock::time_point startTimePoint, endTimePoint;
    
    public:
        timeManager(timeManager const&) = delete;
        void operator=(timeManager const&) = delete;
};