#pragma once

class Display
{
private:
    const static int dim = 20;
    const int sleep = 20;
    char window[dim][dim];

public:
    Display(){};

    void Setup();
    void Draw(Camera&);
};