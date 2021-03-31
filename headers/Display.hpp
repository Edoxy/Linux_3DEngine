#pragma once
#include "Camera.hpp"

class Display
{
private:
    const static int dim = 30;
    const int sleep = 20;
    char window[dim][dim];

public:
    static int n;

    Display();

    void Setup(){};
    void Clear();
    void Draw(Camera&);
};