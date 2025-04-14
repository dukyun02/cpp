#ifndef MYTIME_H
#define MYTIME_H

class MyTime {
private:
    int hour;
    int minute;
    int second;

public:
    MyTime(int h = 0, int m = 0, int s = 0);
    MyTime(const MyTime& t);

    void reset();
    void convert(double duration);
    void print() const;
    void add(MyTime t);
    void add(MyTime t1, MyTime t2);
    void set(MyTime t);
    void read();
};

#endif

