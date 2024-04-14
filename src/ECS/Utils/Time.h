#ifndef TIME_H
#define TIME_H

class Time {
public:
    static Time& Instance() {
        static Time instance;
        return instance;
    }

    double DeltaTime() const;
    double LastFrame() const;
    void Update();
    void SetLastFrame(double lastFrame);


private:
    Time();

    Time(const Time&) = delete; // Delete copy constructor
    Time& operator=(const Time&) = delete; // Delete assignment operator

    double deltaTime;
    double lastFrame = 0.0f;
};

#endif //TIME_H
