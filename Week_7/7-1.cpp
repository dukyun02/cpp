#include <iostream>
using namespace std;

class Complex {
public:
    double real, imag;

    // 생성자
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // 1. 일반 함수 (void, 참조 전달)
    friend void add1(const Complex& a, const Complex& b, Complex& result);

    // 2. 일반 함수 (값 전달, return)
    friend Complex add2(const Complex& a, const Complex& b);

    // 3. 멤버 함수 (void, 참조 전달)
    void add3(const Complex& b, Complex& result) const;

    // 4. 멤버 함수 (return)
    Complex add4(const Complex& b) const;

    // 5. 연산자 오버로딩
    Complex operator+(const Complex& b) const;
};

// 1. 일반 함수 (void, 참조 전달)
void add1(const Complex& a, const Complex& b, Complex& result) {
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
}

// 2. 일반 함수 (값 전달, return)
Complex add2(const Complex& a, const Complex& b) {
    return Complex(a.real + b.real, a.imag + b.imag);
}

// 3. 멤버 함수 (void, 참조 전달)
void Complex::add3(const Complex& b, Complex& result) const {
    result.real = real + b.real;
    result.imag = imag + b.imag;
}

// 4. 멤버 함수 (return)
Complex Complex::add4(const Complex& b) const {
    return Complex(real + b.real, imag + b.imag);
}

// 5. 연산자 오버로딩
Complex Complex::operator+(const Complex& b) const {
    return Complex(real + b.real, imag + b.imag);
}

int main() {
    Complex a(1, 2);  // a = 1 + 2i
    Complex b(3, 4);  // b = 3 + 4i
    Complex c;        // 결과 저장용

    // 1. 일반 함수 (void, 참조 전달)
    add1(a, b, c);
    cout << "1. add1: " << c.real << " + " << c.imag << "i" << endl;

    // 2. 일반 함수 (값 전달, return)
    c = add2(a, b);
    cout << "2. add2: " << c.real << " + " << c.imag << "i" << endl;

    // 3. 멤버 함수 (void, 참조 전달)
    a.add3(b, c);
    cout << "3. add3: " << c.real << " + " << c.imag << "i" << endl;

    // 4. 멤버 함수 (return)
    c = a.add4(b);
    cout << "4. add4: " << c.real << " + " << c.imag << "i" << endl;

    // 5. 연산자 오버로딩
    c = a + b;
    cout << "5. operator+: " << c.real << " + " << c.imag << "i" << endl;

    return 0;
}