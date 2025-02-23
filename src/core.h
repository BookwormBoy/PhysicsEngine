#pragma once
typedef float real;

class Vector3{
    public:
        real x;
        real y;
        real z;

        Vector3();
        Vector3 (real x, real y, real z);
        void invert();
        real magnitude();
        void normalize();
        void operator*=(real value);
        void operator+=(const Vector3& v);
        Vector3 operator+(const Vector3& v);
        void operator-=(const Vector3& v);
        Vector3 operator-(const Vector3& v);
        void addScaledVector(const Vector3& vector, real scale);
        Vector3 componentProduct(const Vector3& vector);
        void componentVectorUpdate(const Vector3& vector);
        real scalarProduct(const Vector3& vector);
        real operator*(const Vector3& vector);
        Vector3 vectorProduct(const Vector3& vector);
        void operator%=(const Vector3 &vector);
        Vector3 operator%(const Vector3& vector);
        void clear();
};