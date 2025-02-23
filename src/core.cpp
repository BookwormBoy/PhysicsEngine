#include "core.h"
#include <cmath>
Vector3::Vector3(){
    x=0;
    y=0;
    z=0;
}

Vector3::Vector3(real x, real y, real z){
    this->x=x;
    this->y=y;
    this->z=z;
}

void Vector3::invert(){
    x=-x;
    y=-y;
    z=-z;
}

real Vector3::magnitude(){
    return sqrt(x*x+y*y+z*z);
}

void Vector3::normalize(){
    real l = magnitude();
    if(l>0){
        (*this)*=((real)1)/l;
    }
}

void Vector3::operator*=(real value){
    x*=value;
    y*=value;
    z*=value;
}

void Vector3::operator+=(const Vector3& v){
    x+=v.x;
    y+=v.y;
    z+=v.z;
}

Vector3 Vector3::operator+(const Vector3& v){
    return Vector3(x+v.x, y+v.y, z+v.z);
}

void Vector3::operator-=(const Vector3& v){
    x-=v.x;
    y-=v.y;
    z-=v.z;
}

Vector3 Vector3::operator-(const Vector3& v){
    return Vector3(x-v.x, y-v.y, z-v.z);
}


void Vector3::addScaledVector(const Vector3& vector, real scale){
    x+= vector.x*scale;
    y+=vector.y*scale;
    z+=vector.z*scale;
}

Vector3 Vector3::componentProduct(const Vector3& vector){
    return Vector3(x*vector.x, y*vector.y, z*vector.z);
}

void Vector3::componentVectorUpdate(const Vector3& vector){
    x*=vector.x;
    y*=vector.y;
    z*=vector.z;
}

real Vector3::scalarProduct(const Vector3& vector){
    return x*vector.x+y*vector.y+z*vector.z;
}

real Vector3::operator*(const Vector3& vector){
    return x*vector.x+y*vector.y+z*vector.z;
}

Vector3 Vector3::vectorProduct(const Vector3& vector){
    return Vector3(y*vector.z-z*vector.y,
                    z*vector.x-x*vector.z,
                    x*vector.y-y*vector.z);
}

void Vector3::operator%=(const Vector3 &vector){
    (*this)=vectorProduct(vector);
}

Vector3 Vector3::operator%(const Vector3& vector){
    return vectorProduct(vector);
}

void Vector3::clear(){
    x=y=z=0;
}



