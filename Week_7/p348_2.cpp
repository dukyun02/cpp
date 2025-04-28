class MyTime {
    private:
        int hour, minute, second, millisecond;
    
    public:
        // 1번에서 작성한 생성자들
        MyTime(int h, int m, int s, int ms) 
            : hour(h), minute(m), second(s), millisecond(ms) {}
    
        MyTime() 
            : hour(0), minute(0), second(0), millisecond(0) {}
    
        // double형 duration을 받는 생성자
        MyTime(double duration) {
            hour = static_cast<int>(duration) / 3600;
            duration -= hour * 3600;
    
            minute = static_cast<int>(duration) / 60;
            duration -= minute * 60;
    
            second = static_cast<int>(duration);
            duration -= second;
    
            millisecond = static_cast<int>(duration * 1000);
        }
    };
    