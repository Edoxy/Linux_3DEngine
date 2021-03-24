#pragma once
#include "Camera.hpp"

class Display
{
private:
    const static int dim = 80;
    const int sleep = 20;
    char window[dim][dim];

public:
    Display();

    void Setup(){};
    void Clear();
    void Draw(Camera&);
};