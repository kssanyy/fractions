#pragma once
#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <cstdint>
#include <string>
#include <iostream>

class Rational {
private:
    int64_t num_;
    uint64_t den_;

    void reduce();

public:
    Rational();
    explicit Rational(int64_t value);
    Rational(int64_t numerator, int64_t denominator);

    int64_t numerator() const;
    uint64_t denominator() const;

    explicit operator double() const;
    std::string str() const;

    // Унарный минус
    Rational operator-() const;

    // Арифметические операции
    Rational operator+(const Rational& other) const;
    Rational operator-(const Rational& other) const;
    Rational operator*(const Rational& other) const;
    Rational operator/(const Rational& other) const;

    // Составные присваивания
    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator*=(const Rational& other);
    Rational& operator/=(const Rational& other);

    // Операции сравнения
    bool operator==(const Rational& other) const;
    bool operator!=(const Rational& other) const;
    bool operator<(const Rational& other) const;
    bool operator<=(const Rational& other) const;
    bool operator>(const Rational& other) const;
    bool operator>=(const Rational& other) const;
};

#endif // RATIONAL_HPP