// 
// Created by igork on 25.03.2024. 
// 
 
#include "Time.h" 
 
#include "GLFW/glfw3.h" 
 
double Time::DeltaTime() const { 
    return deltaTime; 
} 
 
double Time::LastFrame() const { 
    return lastFrame; 
} 
 
void Time::Update() { 
    double currentTime = glfwGetTime(); 
    deltaTime = currentTime - lastFrame; 
    lastFrame = currentTime; 
} 
 
void Time::SetLastFrame(double lastFrame) { 
    this->lastFrame = lastFrame; 
} 
 
Time::Time() { 
    deltaTime = 0.0f; 
    lastFrame = glfwGetTime(); 
} 
