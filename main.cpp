
#include "timeManager.hpp"

#include "windows.h"
#include <iostream>


POINT cursorPos;
int curVel = 1;

void processFrame(double deltaTime);

int main(){
    timeManager& timeMan = timeManager::getInstance();

    double delta = 0.1; // This represent the duration of the last loop. This is used to keep a constant movement regardless of the delay.
    
    
    while(!GetAsyncKeyState(VK_DELETE)){

        timeMan.start();

        processFrame(delta);

        timeMan.end();
        
        delta = timeMan.getDuration<double>();
        //std::cout << "Delta: " << delta << std::endl;
    }
    return 0;
}

void processFrame(double deltaTime){
    if(!GetCursorPos(&cursorPos)) 
        return;

    if (GetKeyState(VK_RIGHT) & 0x8000){
        cursorPos.x += curVel * deltaTime;
        SetCursorPos(cursorPos.x, cursorPos.y);
    }
    if (GetKeyState(VK_LEFT) & 0x8000){
        cursorPos.x -= curVel * deltaTime;
        SetCursorPos(cursorPos.x, cursorPos.y);
    }
    if (GetKeyState(VK_UP) & 0x8000){
        cursorPos.y -= curVel * deltaTime;
        SetCursorPos(cursorPos.x, cursorPos.y);
    }
    if (GetKeyState(VK_DOWN) & 0x8000){
        cursorPos.y += curVel * deltaTime;
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
    Sleep(1);
}