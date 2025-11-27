#include "fractions.h"
#include <numeric>
#include <cmath>
#include <sstream>

namespace {

    int64_t gcd(int64_t a, int64_t b) {
        a = std::abs(a);
        b = std::abs(b);
        while (b != 0) {
            int64_t temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

}

Rational::Rational() : num_(0), den_(1) {}

Rational::Rational(int64_t value) : num_(value), den_(1) {}

Rational::Rational(int64_t numerator, int64_t denominator) {
    if (denominator == 0) {

        den_ = 1;
        num_ = 0;
    }
    else if (denominator < 0) {
        num_ = -numerator;
        den_ = static_cast<uint64_t>(-denominator);
    }
    else {
        num_ = numerator;
        den_ = static_cast<uint64_t>(denominator);
    }
    reduce();
}

void Rational::reduce() {
    if (num_ == 0) {
        den_ = 1;
        return;
    }

    int64_t common = gcd(num_, den_);
    num_ /= common;
    den_ /= common;
}

int64_t Rational::numerator() const {
    return num_;
}

uint64_t Rational::denominator() const {
    return den_;
}

Rational::operator double() const {
    return static_cast<double>(num_) / static_cast<double>(den_);
}

std::string Rational::str() const {
    std::ostringstream oss;
    oss << num_;
    if (den_ != 1) {
        oss << "/" << den_;
    }
    return oss.str();
}

Rational Rational::operator-() const {
    return Rational(-num_, static_cast<int64_t>(den_));
}

Rational Rational::operator+(const Rational& other) const {
    Rational result = *this;
    result += other;
    return result;
}

Rational Rational::operator-(const Rational& other) const {
    Rational result = *this;
    result -= other;
    return result;
}

Rational Rational::operator*(const Rational& other) const {
    Rational result = *this;
    result *= other;
    return result;
}

Rational Rational::operator/(const Rational& other) const {
    Rational result = *this;
    result /= other;
    return result;
}

// a/b + c/d = (a*d + c*b)/(b*d)
Rational& Rational::operator+=(const Rational& other) {
    int64_t new_num = num_ * static_cast<int64_t>(other.den_) +
        other.num_ * static_cast<int64_t>(den_);
    uint64_t new_den = den_ * other.den_;

    num_ = new_num;
    den_ = new_den;
    reduce();
    return *this;
}

// a/b - c/d = (a*d - c*b)/(b*d)
Rational& Rational::operator-=(const Rational& other) {
    int64_t new_num = num_ * static_cast<int64_t>(other.den_) -
        other.num_ * static_cast<int64_t>(den_);
    uint64_t new_den = den_ * other.den_;

    num_ = new_num;
    den_ = new_den;
    reduce();
    return *this;
}

// (a/b) * (c/d) = (a*c)/(b*d)
Rational& Rational::operator*=(const Rational& other) {
    num_ *= other.num_;
    den_ *= other.den_;
    reduce();
    return *this;
}

// (a/b) / (c/d) = (a*d)/(b*c)
Rational& Rational::operator/=(const Rational& other) {
    int64_t new_num = num_ * static_cast<int64_t>(other.den_);
    int64_t new_den = static_cast<int64_t>(den_) * other.num_;

    if (new_den < 0) {
        new_num = -new_num;
        new_den = -new_den;
    }

    num_ = new_num;
    den_ = static_cast<uint64_t>(new_den);
    reduce();
    return *this;
}

bool Rational::operator==(const Rational& other) const {
    return num_ == other.num_ && den_ == other.den_;
}

bool Rational::operator!=(const Rational& other) const {
    return !(*this == other);
}

// a/b < c/d <=> a*d < c*b
bool Rational::operator<(const Rational& other) const {
    return num_ * static_cast<int64_t>(other.den_) <
        other.num_ * static_cast<int64_t>(den_);
}

bool Rational::operator<=(const Rational& other) const {
    return *this < other || *this == other;
}

bool Rational::operator>(const Rational& other) const {
    return !(*this <= other);
}

bool Rational::operator>=(const Rational& other) const {
    return !(*this < other);
}



//проверка 

#include <iostream>
#include <vector>

void basic_operations() {

    setlocale(LC_ALL,"RUS");

    Rational a;
    Rational b(5);
    Rational c(1, 2);

    std::cout << "a = " << a.str() << std::endl;
    std::cout << "b = " << b.str() << std::endl;
    std::cout << "c = " << c.str() << std::endl;

}

void arithmetic_operations() {

    Rational a(1, 3);
    Rational b(1, 6);


    Rational sum = a + b;
    std::cout << a.str() << " + " << b.str() << " = " << sum.str() << std::endl;


    Rational diff = a - b;
    std::cout << a.str() << " - " << b.str() << " = " << diff.str() << std::endl;


    Rational product = a * b;
    std::cout << a.str() << " * " << b.str() << " = " << product.str() << std::endl;


    Rational quotient = a / b;
    std::cout << a.str() << " / " << b.str() << " = " << quotient.str() << std::endl;


    Rational neg = -a;
    std::cout << "-" << a.str() << " = " << neg.str() << std::endl;
}

void assignment() {

    Rational x(1, 4);

    x += Rational(1, 4);
    std::cout << x.str() << std::endl;

    x -= Rational(1, 8);
    std::cout << x.str() << std::endl;

    x *= Rational(2, 1);
    std::cout << x.str() << std::endl;

    x /= Rational(3, 2);
    std::cout << x.str() << std::endl;
}

void comparison_operations_example() {

    Rational a(1, 2);
    Rational b(2, 4);
    Rational c(3, 4);

    std::cout << a.str() << " == " << b.str() << " : " << (a == b) << std::endl;
    std::cout << a.str() << " != " << c.str() << " : " << (a != c) << std::endl;
    std::cout << a.str() << " < " << c.str() << " : " << (a < c) << std::endl;
    std::cout << c.str() << " > " << a.str() << " : " << (c > a) << std::endl;

}

void conversion() {
    setlocale(LC_ALL, "RUS");
    Rational a(1, 2);

    double a_double = static_cast<double>(a);

    std::cout << a.str() << " как double: " << a_double << std::endl;

}

void expressions() {

    Rational result = (Rational(1, 2) + Rational(1, 3)) *
        (Rational(3, 4) - Rational(1, 6)) /
        Rational(2, 3);

    std::cout << result.str() << std::endl;

}


void reduction() {

    Rational a(4, 8);
    Rational b(9, 12);

    std::cout << "4/8 = " << a.str() << std::endl;
    std::cout << "9/12 = " << b.str() << std::endl;

    Rational d = a * b;

    std::cout << a.str() << " * " << b.str() << " = " << d.str() << std::endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    std::cout << "Демонстрация класса Rational\n" << std::endl;

    basic_operations();
    arithmetic_operations();
    assignment();
    comparison_operations_example();
    conversion();
    expressions();
    reduction();

    return 0;
}