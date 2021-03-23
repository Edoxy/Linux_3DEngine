#include <iostream>
#include <vector>
#include <string>
#include "headers/Points2d.hpp"

using namespace std;

int main()
{
    vector <string> msg {"hello", "world"};
    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
    //Fine test

    Points2d *point = new Points2d(1, 4);
    cout << point->Getx() << " " << point->Gety() << endl;
    
}