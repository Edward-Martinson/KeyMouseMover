#include "windows.h"

#include <iostream>
#include <chrono>

using namespace std::chrono;

class timeManager{
    public:
    static timeManager& getInstance(){
        static timeManager instance;
        return instance;
    }

    void start(){
        startTimePoint = high_resolution_clock::now();
    }
    void end(){
        endTimePoint = high_resolution_clock::now();
    }

    template <typename T>
    T getDuration(){
        T dur = duration<T, std::milli>(endTimePoint - startTimePoint).count();
        return dur;
    }

    private:
    timeManager() {}

    std::chrono::_V2::system_clock::time_point startTimePoint, endTimePoint;
    
    public:
        timeManager(timeManager const&) = delete;
        void operator=(timeManager const&) = delete;
};

POINT cursorPos;
int curVel = 1;
void processFrame(double deltaTime);

int main(){
    timeManager& timeMan = timeManager::getInstance();

    GetCursorPos(&cursorPos);
    double delta = 0.1;

    while(true){
        timeMan.start();
        
        processFrame(delta);
        Sleep(1);

        timeMan.end();
        
        delta = timeMan.getDuration<double>();
        //std::cout << curPosX << " " << curPosY << std::endl;
    }
    return 0;
}

void processFrame(double deltaTime){
    if (GetKeyState(VK_UP) & 0x8000){
        cursorPos.y -= curVel * deltaTime;
        SetCursorPos(cursorPos.x, cursorPos.y);
    }
    if (GetKeyState(VK_DOWN) & 0x8000){
        cursorPos.y += curVel * deltaTime;
        SetCursorPos(cursorPos.x, cursorPos.y);
    }
    if (GetKeyState(VK_RIGHT) & 0x8000){
        cursorPos.x += curVel * deltaTime;
        SetCursorPos(cursorPos.x, cursorPos.y);
    }
    if (GetKeyState(VK_LEFT) & 0x8000){
        cursorPos.x -= curVel * deltaTime;
        SetCursorPos(cursorPos.x, cursorPos.y);
    }
    if (GetKeyState(VK_RETURN) & 0x8000){
        INPUT input[2];

        input[0].type = INPUT_MOUSE;
        input[0].mi.dx = 0;
        input[0].mi.dy = 0;
        input[0].mi.mouseData = 0;
        input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        input[0].mi.time = 0;
        input[0].mi.dwExtraInfo = 0;

        input[1].type = INPUT_MOUSE;
        input[1].mi.dx = 0;
        input[1].mi.dy = 0;
        input[1].mi.mouseData = 0;
        input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        input[1].mi.time = 0;
        input[1].mi.dwExtraInfo = 0;

        SendInput(2, input, sizeof(INPUT));
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_KEYDOWN:
            // Check if the pressed key is an arrow key
            if (wParam == VK_LEFT || wParam == VK_RIGHT || 
                wParam == VK_UP || wParam == VK_DOWN) {
                // Ignore the arrow key by not processing it further
                return 0; // Indicate that the message has been processed
            }
            break;
        // ... other message handling
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}