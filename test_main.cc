#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <string>
#include "time.h"
#include <sstream>



//TODO: Complementary work neeed, 8-8: Your tests are insufficent,
//prefix/postfix should be tested in a correct way to show that they
//are implemented correctly.

TEST_CASE("Create a Time-variable")
{
    Time testTime{};
    REQUIRE(testTime.Hour == 0);
    REQUIRE(testTime.Minute == 0);
    REQUIRE(testTime.Second == 0);
}

TEST_CASE("Invalidity and reset check")
{
    Time testTime{};

    reset(testTime);
    REQUIRE(testTime.Hour == 0);
    REQUIRE(testTime.Minute == 0);
    REQUIRE(testTime.Second == 0);

    testTime.Hour = 24;
    CHECK(isInvalid(testTime));
    reset(testTime);

    testTime.Minute = 60;
    CHECK(isInvalid(testTime));
    reset(testTime);

    testTime.Second = 60;
    CHECK(isInvalid(testTime));

    testTime.Second = 59;
    CHECK_FALSE(isInvalid(testTime));
}

TEST_CASE("To string")
{
    Time testTime{};

    CHECK(toString(testTime, true) == "00:00:00 am");

    setTime(testTime, 13, 30, 30);
    CHECK(toString(testTime, false) == "13:30:30");
    CHECK(toString(testTime, true) == "01:30:30 pm");
}

TEST_CASE("AM or PM")
{
    Time testTime{13, 30, 30};
    testTime.Second = 60;


    CHECK_FALSE(isAM(testTime));

    testTime.Hour = 5;
    CHECK(isAM(testTime));

    reset(testTime);
    CHECK(isAM(testTime));
}

TEST_CASE("Plus operator")
{
    Time testTime{};

    CHECK(toString(testTime + 5, true) == "00:00:05 am");

    CHECK(toString(testTime + 20000, true) == "05:33:20 am");

    CHECK_FALSE(toString(testTime + 250000, 12) == "06:26:40 pm");
}

TEST_CASE("Minus operator")
{
    Time testTime{};

    CHECK(toString(testTime - 5, false) == "23:59:55");

    CHECK(toString(testTime - 20000, true) == "06:26:40 pm");

    CHECK_FALSE(toString(testTime - 250000, true) == "10:26:40 pm");
}

TEST_CASE("Increment operator")
{
    Time testTime{};

    testTime++;
    CHECK(toString(testTime, true) == "00:00:01 am");

    reset(testTime);
    ++testTime;
    CHECK(toString(testTime, true) == "00:00:01 am");
}

TEST_CASE("Decrement operator")
{
    Time testTime{};

    testTime--;
    CHECK(toString(testTime, false) == "23:59:59");

    reset(testTime);
    --testTime;
    CHECK(toString(testTime, false) == "23:59:59");
}

TEST_CASE("Comparisons")
{
    Time timeOne{0, 0, 1};
    Time timeTwo{12, 30, 40};

    CHECK_FALSE(timeOne > timeTwo);
    CHECK(timeOne != timeTwo);
    CHECK(timeOne < timeTwo);
    CHECK_FALSE(timeOne == timeTwo);
    CHECK(timeOne <= timeTwo);
    CHECK_FALSE(timeOne >= timeTwo);
}

TEST_CASE("<<")
{
    Time testTime{};
    std::string str{};
    setTime(testTime, 0, 0, 0);
    std::stringstream test{};

    test << toString(testTime, false);
    test >> str;
    CHECK(str == "00:00:00");
}

TEST_CASE(">>")
{
    Time testTime{};
    std::stringstream test{"23:12:13"};

    

    test >> testTime;
    CHECK(std::stringstream::failbit  != 0);
    CHECK(toString(testTime, false) == "23:12:13");
}
