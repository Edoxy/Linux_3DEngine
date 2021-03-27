#include "headers/Display.hpp"
#include <iostream>

Display::Display()
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            window[i][j] = ' ';
        }
    }
}

void Display::Clear()
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            window[i][j] = ' ';
        }
    }
}

void Display::Draw(Camera& cam)
{
    for (int i = 0; i < cam.getNview(); i++)
    {
        Point2d *p = cam.getView(i);
        int x = int(round(p->Getx() * dim));
        int y = int(round(p->Gety() * dim));

        window[x][y] = '*';
    }
    for(int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            std::cout << window[i][j] << " ";
        }
        std::cout << std::endl;
    }
}