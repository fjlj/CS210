// Clock.cpp : a program that demonstrates a simple clock class that is able to output its values based on weather it should be a 24 hour clock or not
// allows for the user to add hour, add minute, add second, or quit via keypress. program initializes with a two clock display, one in 12 hour format one in 24 hour format of current time.
//Frank Lewis
//CS210 03/24/2021

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <time.h>


using namespace std;

//class for clocks
class Clock {
private:
    //variables to hold hours, minutes, seconds, and weather it is 24hr clock or not

    bool is24hr;  //allows for creating a clock that will output its time in 12 hour format with AM and PM
    int  hr;
    int  min;
    int  sec;

public:

    //function to add an hour to the clock.. if it is less than 23 then add an hour, otherwise reset to 00
    void addHr() {
        if (this->hr >= 23) {
            this->hr = 0;
        }
        else {
            this->hr += 1;
        }
    }

    //function to add a minute, if the minute is 59 rather than adding a minute.. add an hour and zero the minutes
    void addMin() {
        if (this->min >= 59) {
            this->addHr();
            this->min = 0;
        }
        else {
            this->min += 1;
        }
    }

    //function to add a second or if seconds is 59 add a minute and zero the seconds.
    void addSec() {
        if (this->sec >= 59) {
            this->addMin();
            this->sec = 0;
        }
        else {
            this->sec += 1;
        }
    }

    //function for return the time string in correct format.. weather clock is a 24 hour clock or not.
    std::string getTime() {
        std::ostringstream stringStream;
        std::string amPm = (hr / 12 >= 1) ? " PM" : " AM";

        stringStream << std::setfill('0') << std::setw(2) << ((this->is24hr) ? this->hr : this->hr % 12) << ":"
            << std::setfill('0') << std::setw(2) << this->min << ":"
            << std::setfill('0') << std::setw(2) << this->sec
            << ((this->is24hr) ? "" : amPm);

        return stringStream.str();
    }
    Clock(bool);
};

//overload constructor to default 24 hour clock to false and initialize to current time.
Clock::Clock(bool doAmPm = false) {
    is24hr = doAmPm;
    time_t curTime;
    struct tm locTime;

    time(&curTime);
    localtime_s(&locTime, &curTime);

    hr = locTime.tm_hour;
    min = locTime.tm_min;
    sec = locTime.tm_sec;
}


//function to draw the menu
void drawMenu() {
    cout << "                *************************" << endl;
    cout << "                *  1 - Add One Hour     *" << endl;
    cout << "                *  2 - Add One Minute   *" << endl;
    cout << "                *  3 - Add One Second   *" << endl;
    cout << "                *  4 - Exit Program     *" << endl;
    cout << "                *************************" << endl;
}

//function to draw the clocks (clears screen and then calls draw menu) by ref to catch changes while drawing...
void drawClocks(int& drawmenu, string clock12, string clock24) {
    system("cls");
    cout << "*************************\t*************************" << endl;
    cout << "*     12-Hour Clock     *\t*     24-Hour Clock     *" << endl;
    cout << "*      " << clock12 << "      *\t*       " << clock24 << "        *" << endl;
    cout << "*************************\t*************************" << endl;
    if (drawmenu == 1) {
        drawMenu();
    }
    else if (drawmenu == -1) {
        cout << "               Press Space For Instructions" << endl;
    }

}

//function to check if either 1-4 or num1-num4 is or has been pressed since last check and updates the variable acoordingly, as well as updates the redraw variable
void testKeyPress(int& drawmenu, bool& redraw, int& selection) {

    //calling these once in the beginning rather than twice per test allows them to not alter eachothers state since last check.
    short one = GetAsyncKeyState(0x31) | GetAsyncKeyState(VK_NUMPAD1);
    short two = GetAsyncKeyState(0x32) | GetAsyncKeyState(VK_NUMPAD2);
    short three = GetAsyncKeyState(0x33) | GetAsyncKeyState(VK_NUMPAD3);
    short four = GetAsyncKeyState(0x34) | GetAsyncKeyState(VK_NUMPAD4);
    short space = GetAsyncKeyState(VK_SPACE);

    //if the value is less than 0 the most significant bit is set and this will result in a negative number compairison
    //if the value is 1 the button has been pressed since we last called the function
    if (one < 0 || one == 1) {
        redraw = true;
        selection = 1;
    }
    else if (two < 0 || two == 1) {
        redraw = true;
        selection = 2;
    }
    else if (three < 0 || three == 1) {
        redraw = true;
        selection = 3;
    }
    else if (four < 0 || four == 1) {
        selection = 4;
    }
    else if (space < 0 || space == 1) {
        drawmenu = (drawmenu == 1) ? 0 : 1;   //allow toggling the menu with space
        selection = 0;
    }
    else {
        selection = 0;
    }
}

int main()
{
    int menuSelection = 0;     //variable that holds our menu selection
    double timeInSec = 0.0;    //keeps track of execution time to keep seconds in sync
    bool redraw = false;       //variable used to determine if we need to re-draw within the loop
    int drawmenu = -1;         //determine weather menu should be drawn
    clock_t timer;             //used to track execution time (not as precise as it could be, however prooves functional)

    // create our two clocks, one as a standard clock, one with the is24hr flag set
    Clock twelvHrClock;
    Clock twentyFourHrClock(true);

    //start timer used to account for initial draw time before entering loop
    timer = clock();

    drawClocks(drawmenu, twelvHrClock.getTime(), twentyFourHrClock.getTime());


    //main program loop
    while (menuSelection != 4) {
        timer = clock() - timer;                               //new clock - old clock = number of clocks passed 
        timeInSec += ((float)timer) / CLOCKS_PER_SEC;          //add time in seconds that has passed since starting or since last loop
                                                               //found from different divided by const CLOCKS_PER_SEC
        testKeyPress(drawmenu, redraw, menuSelection);                   //check for keypresses 

        timer = clock();                                       //initialize next clock

        // switch will carryout requested functions for both clocks, ignoring any other return values. reseting the menu being drawn...
        switch (menuSelection) {
        case 1:
            twelvHrClock.addHr();
            twentyFourHrClock.addHr();
            drawmenu = 0;
            break;
        case 2:
            twelvHrClock.addMin();
            twentyFourHrClock.addMin();
            drawmenu = 0;
            break;
        case 3:
            twelvHrClock.addSec();
            twentyFourHrClock.addSec();
            drawmenu = 0;
            break;
        default:
            break;
        }

        //if a key was pressed lets redraw the screen to show the new values. we do this before time elapsed checking as this itself will if needed add additional time..
        if (redraw) {
            drawClocks(drawmenu, twelvHrClock.getTime(), twentyFourHrClock.getTime());
            redraw = false;
        }

        //check to see if we need to add a second and redraw the clock or not
        if (timeInSec - 1.0 >= 0.000001) {
            twelvHrClock.addSec();
            twentyFourHrClock.addSec();
            drawClocks(drawmenu, twelvHrClock.getTime(), twentyFourHrClock.getTime());

            timeInSec = max(timeInSec - 1.0, 0.0);  //subtract 1 second from timer
        }
        Sleep(275); //dont consume 100% cpu
    }

    cout << "Good Bye...";
    return 0;
}
