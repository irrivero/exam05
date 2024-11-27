#include <iostream>

class vect2 {
private:
    int x, y;

public:
    vect2(int x = 0, int y = 0) : x(x), y(y) {};
    vect2(const vect2& oth) : x(oth.x), y(oth.y) {};

    vect2& operator=(const vect2& oth) {
        x = oth.x;
        y = oth.y;
        return *this;
    }

    int& operator[](int i) {
        if (i < 0 || i > 1) throw std::out_of_range("Index out of range");
        return (i == 0 ? x : y);
    }

    int operator[](int i) const {
        if (i < 0 || i > 1) throw std::out_of_range("Index out of range");
        return (i == 0 ? x : y);
    }

    vect2 operator+(const vect2& oth) const {
        return vect2(x + oth.x, y + oth.y);
    }

    vect2 operator-(const vect2& oth) const {
        return vect2(x - oth.x, y - oth.y);
    }

    vect2 operator*(int s) const {
        return vect2(x * s, y * s);
    }

    vect2 operator-() const {
        return vect2(-x, -y);
    }

    bool operator==(const vect2& oth) const {
        return x == oth.x && y == oth.y;
    }

    bool operator!=(const vect2& oth) const {
        return !(*this == oth);
    }

    friend std::ostream& operator<<(std::ostream& os, const vect2& v) {
        os << "{" << v.x << ", " << v.y << "}";
        return os;
    }

    vect2 operator++(int) {
        vect2 tmp = *this;
        x++;
        y++;
        return tmp;
    }

    vect2& operator++() {
        x++;
        y++;
        return *this;
    }

    vect2 operator--(int) {
        vect2 tmp = *this;
        x--;
        y--;
        return tmp;
    }

    vect2& operator--() {
        x--;
        y--;
        return *this;
    }

    vect2& operator+=(const vect2& oth) {
        x += oth.x;
        y += oth.y;
        return *this;
    }

    vect2& operator-=(const vect2& oth) {
        x -= oth.x;
        y -= oth.y;
        return *this;
    }

    friend vect2 operator*(int s, const vect2& v) {
        return vect2(v.x * s, v.y * s);
    }

    vect2& operator*=(int s) {
        x *= s;
        y *= s;
        return *this;
    }

};