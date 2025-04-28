class MyTime {
    private:
        int hour, minute, second, millisecond;
    
    public:
        // 매개변수 있는 생성자
        MyTime(int h, int m, int s, int ms) 
            : hour(h), minute(m), second(s), millisecond(ms) {}
    
        // 매개변수 없는 기본 생성자
        MyTime() 
            : hour(0), minute(0), second(0), millisecond(0) {}
    };
    