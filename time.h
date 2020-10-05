#ifndef TIME_H
#define TIME_H

#include <string>
#include <sstream>


//TODO: Complementary work needed, Prefix increment/decrement should
//return a reference.


struct Time
{
    int Hour;
    int Minute;
    int Second;
};


void setTime(Time& time, int const Hour, int const Minute, int const Second);

//Other functions

bool isInvalid(Time const& time);
void reset(Time& time);
std::string toString(Time const& time, bool const am);
bool isAM(Time const& time);

//Operator overloads

Time operator+(Time const& time, int const n);
Time operator-(Time const& time, int const n);
bool operator<(Time const& timeOne, Time const& timeTwo);
bool operator>(Time const& timeOne, Time const& timeTwo);
bool operator<=(Time const& timeOne, Time const& timeTwo);
bool operator>=(Time const& timeOne, Time const& timeTwo);
bool operator==(Time const& timeOne, Time const& timeTwo);
bool operator!=(Time const& timeOne, Time const& timeTwo);
Time& operator++(Time& time);
Time operator++(Time& time, int);
Time& operator--(Time& time);
Time operator--(Time& time, int);

std::ostream &operator<<(std::ostream& output, Time const& time);
std::istream &operator>>(std::istream& input, Time& time);

#endif
