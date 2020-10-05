#include "time.h"
#include <string>
#include <sstream>
#include <iostream>

//TODO: Complementary work neeed, 8-8: The post/prefix operators are
//not correctly implemented.


using namespace std;



void setTime(Time& time, int const Hour, int const Minute, int const Second)
{
    time.Hour = Hour;
    time.Minute = Minute;
    time.Second = Second;
}

//Other functions

bool isInvalid(Time const& time)
{
    if (time.Hour < 24 &&  time.Hour >= 0 && time.Minute < 60
        && time.Minute >= 0 && time.Second < 60 && time.Second >= 0)
    {
        return false;
    }
    return true;
}

void reset(Time& time) {
    setTime(time, 0, 0, 0);
}

bool isAM(Time const& time)
{
    if(time.Hour > 12)
    {
        return false;
    }
    return true;
}

string toString(Time const& time, bool const am)
{
    string returned{};
    int tmp = time.Hour;
    if(tmp > 12){
        tmp = tmp - 12;
    }
    if(am)
    {
        if(tmp < 10)
        {
            returned += "0" + to_string(tmp);
        } 
        else 
        {
            returned += to_string(tmp);
        }
        if(time.Minute < 10)
        {
            returned += ":0" + to_string(time.Minute);
        }
        else
        {
            returned += ":" + to_string(time.Minute);
        }
        if(time.Second < 10)
        {
            returned += ":0" + to_string(time.Second);
        }
        else
        {
            returned += ":" + to_string(time.Second);
        }
        if(isAM(time))
        {
            return returned + " am";
        }
        else
        {
            return returned + " pm";
        }
        
    }
    if(!am)
    {
        if(time.Hour < 10)
        {
            returned += "0" + to_string(time.Hour);
        } 
        else 
        {
            returned += to_string(time.Hour);
        }
        if(time.Minute < 10)
        {
            returned += ":0" + to_string(time.Minute);
        }
        else
        {
            returned += ":" + to_string(time.Minute);
        }
        if(time.Second < 10)
        {
            returned += ":0" + to_string(time.Second);
        }
        else
        {
            returned += ":" + to_string(time.Second);
        }
        return returned;
        
    }
    return "";
}

//Operators
 
Time operator+(Time const& time, int const n) {
    Time dummy = time;

    dummy.Second = time.Second + n;
    while(dummy.Second > 59) {
        dummy.Second = dummy.Second - 60;
        dummy.Minute = dummy.Minute + 1; 
        while(dummy.Minute > 59) {
            dummy.Minute = 0;
            dummy.Hour = dummy.Hour + 1;
            while(dummy.Hour > 23) {
                dummy.Hour = 0;
            }
        }
    }
    return dummy;
}

Time operator-(Time const& time, int const n)
{
    Time dummy = time;
    dummy.Second = time.Second - n;
    while(dummy.Second < 0) {
        dummy.Second = dummy.Second + 60;
        dummy.Minute = dummy.Minute - 1; 
        while(dummy.Minute < 0) {
            dummy.Minute = 59;
            dummy.Hour = dummy.Hour - 1;
            while(dummy.Hour < 0) {
                dummy.Hour = 23;
            }
        }
    }
    return dummy;
}
    
bool operator<(Time const& timeOne, Time const& timeTwo)
{
    if(timeOne.Hour < timeTwo.Hour)
    {
        return true;
    }
    if(timeOne.Hour ==  timeTwo.Hour && timeOne.Minute < timeTwo.Minute)
    {
        return true;
    }
    if(timeOne.Hour ==  timeTwo.Hour && timeOne.Minute == timeTwo.Minute && timeOne.Second < timeTwo.Second)
    {
        return true;
    }
    return false;
}

bool operator>(Time const& timeOne, Time const& timeTwo)
{
    if(timeOne < timeTwo || timeOne == timeTwo)
    {
        return false;
    }
    return true;
}

bool operator==(Time const& timeOne, Time const& timeTwo)
{
    if(timeOne.Hour == timeTwo.Hour)
    {
        if(timeOne.Minute == timeTwo.Minute)
        {
            if(timeOne.Second == timeTwo.Second)
            {
                return true;
            }
        }
    }
    return false;
}

bool operator!=(Time const& timeOne, Time const& timeTwo)
{
    if(timeOne == timeTwo)
    {
        return false;
    }
    return true;
}


bool operator>=(Time const& timeOne, Time const& timeTwo) {
    if (timeOne > timeTwo || timeOne == timeTwo) {
        return true;   
    }
    return false;
}

bool operator<=(Time const& timeOne, Time const& timeTwo) {
    if (timeOne < timeTwo || timeOne == timeTwo) {
        return true;   
    }
    return false;
}

//Pre
Time& operator++(Time& time)
{
    Time& tmp{time};
    time = time + 1;
    return tmp;
}
//Post
Time operator++(Time& time, int)
{
    Time tmp{time};
    tmp = tmp + 1;
    return tmp;
}
//Pre
Time& operator--(Time& time)
{
    Time& tmp{time};
    time = time - 1;
    return tmp;
}
//Post
Time operator--(Time& time, int)
{
    Time tmp{time};
    tmp = tmp - 1;
    return tmp;
}

ostream &operator<<(ostream& output, Time const& time)
{
    output << to_string(time.Hour) + ":" + to_string(time.Second) + ":" + to_string(time.Minute);
    return output;
}


istream &operator>>(istream& input, Time& time)
{ 
    char temp{};
    int tmpInt{};

    // 11:12:13
    input >> tmpInt >> temp;
    time.Hour = tmpInt;

    input >> tmpInt >> temp;
    time.Minute = tmpInt;

    input >> tmpInt;
    time.Second = tmpInt;
    if(isInvalid(time)){
        input.setstate(ios_base::failbit);
    } 

    

    /* input >> tmpInt >> temp; 
    if(tmpInt > 23 || tmpInt < 0){
        input.setstate(ios_base::failbit);
    } else {
        time.Hour = tmpInt;
    }
    
    input >> tmpInt >> temp;
    if(tmpInt > 60 || tmpInt < 0){
        input.setstate(ios_base::failbit);
    } else {
        time.Minute = tmpInt;
    }

    input >> tmpInt;
    if(tmpInt > 60 || tmpInt < 0){
        input.setstate(ios_base::failbit);
    } else {
        time.Second = tmpInt;
    } */

    if(input.fail()){
        throw invalid_argument("\nTHE TIME EXCEEDS THE ALLOWED LIMITS.");
    }


   // input >> time.Hour >> temp >> time.Minute >> temp >> time.Second;
    return input;
}






