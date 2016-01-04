#include <iostream>
#include <unistd.h>
#include <cstdio>

#include "ev3dev.h"
#include "DriveTest.h"

using namespace std;
using namespace ev3dev;

int ButtonTest()
{

    bool buttons[6] = {false};
    bool history[6] = {false};
    std::string names[6] = {"UP", "DOWN", "LEFT", "RIGHT", "ENTER", "ESCAPE"};

    bool enterPressed = false;
    int i = 0;
    cout << "=== BUTTONS ===\n";
    while (buttons[5] == 0)
    {
        //cout << "\033[2K\033[0GBUTTONS: " << flush;

        i = 0;
        buttons[i++] = button::up.pressed();
        buttons[i++] = button::down.pressed();
        buttons[i++] = button::left.pressed();
        buttons[i++] = button::right.pressed();
        buttons[i++] = button::enter.pressed();
        buttons[i++] = button::back.pressed();

        for (int b = 0; b < 6; b++)
        {
            if (buttons[b] && !history[b])
            {
                cout << names[b] << "\n";
                history[b] = true;
            }
            else if (!buttons[b])
            {
                if (b == 4 && history[b])
                    cout << "\033[1A]" << flush;
                else
                    cout << "\033[2K\033[0G" << flush;
                history[b] = false;
            }
        }

        //cout << "\033[2K\033[0G" << up << down << left << right << enter << escape << flush;
        //      if (enter)
        //          enterPressed = true;
        //      
        //      if (!enter && enterPressed)
        //      {
        //          cout << "\033[1A" << flush;
        //          enterPressed = false;
        //      }
        usleep(100000);
    }

    driveTest();
}