#include <iostream>
#include <cstdio>
#include "MyTime.h"
using namespace std;

MyTime::MyTime(int h, int m, int s) : hour(h), minute(m), second(s) {}
MyTime::MyTime(const MyTime& t) : hour(t.hour), minute(t.minute), second(t.second) {}

void MyTime::reset() {
    hour = 0; minute = 0; second = 0;
}

void MyTime::convert(double duration) {
    hour = static_cast<int>(duration) / 3600;
    minute = (static_cast<int>(duration) % 3600) / 60;
    second = static_cast<int>(duration) % 60;
}

void MyTime::print() const {
    printf("%02d:%02d:%02d\n", hour, minute, second);
}

void MyTime::add(MyTime t) {
    hour += t.hour;
    minute += t.minute;
    second += t.second;

    minute += second / 60;
    second %= 60;
    hour += minute / 60;
    minute %= 60;
}

void MyTime::add(MyTime t1, MyTime t2) {
    hour = t1.hour + t2.hour;
    minute = t1.minute + t2.minute;
    second = t1.second + t2.second;

    minute += second / 60;
    second %= 60;
    hour += minute / 60;
    minute %= 60;
}

void MyTime::set(MyTime t) {
    hour = t.hour;
    minute = t.minute;
    second = t.second;
}

void MyTime::read() {
    cout << "시간을 입력하세요 (시 분 초): ";
    cin >> hour >> minute >> second;
}

