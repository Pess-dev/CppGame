#include <math.h>
#include <windows.h>
#include <iostream> 
#include <string>
#include <list>
#include <vector>
 
#pragma once
 
using namespace std;

class Vector2D{
    
    public:
    double x=0,y=0;
    
    Vector2D(const Vector2D & v){ 
        x=v.x;
        y=v.y;
    }
    Vector2D(){ 
        x=0;
        y=0; 
    }
    Vector2D(double x_, double y_){ 
        x=x_;
        y=y_; 
    }   
    double magnitude(){ 
        return sqrt(x*x+y*y);
    }
    Vector2D normilized(){ 
        Vector2D newVector=Vector2D();
        double m=magnitude();
        if(m==0 || m != m) return newVector; 
        newVector.x=x/m;
        newVector.y=y/m;
        return newVector;
    }
    void normilize(){
        double m=magnitude();
        if (m==0 || m != m)return;
        x=x/m;
        y=y/m; 
    }
    void toZero(){
        x=0;
        y=0;
    } 

};

Vector2D operator+(const Vector2D& left, const Vector2D& right) {
    return Vector2D(left.x + right.x,left.y + right.y);
}
Vector2D operator-(const Vector2D& left, const Vector2D& right) {
    return Vector2D(left.x - right.x,left.y - right.y);
}
Vector2D operator*(const Vector2D& left, const double& right) {
    return Vector2D(left.x * right,left.y * right);
}
Vector2D operator/(const Vector2D& left, const double& right) {
    return Vector2D(left.x / right,left.y / right);
}
Vector2D& operator+=(Vector2D& left, const Vector2D& right) {
    left.x += right.x;
    left.y += right.y;
    return left;
}
Vector2D& operator-=(Vector2D& left, const Vector2D& right) {
    left.x -= right.x;
    left.y -= right.y;
    return left;
}

bool operator== (const Vector2D & first, const Vector2D & second) { 
        return (first.x==second.x)&&(first.y==second.y);
}
bool operator!= (const Vector2D & first, const Vector2D & second) { 
        return !(first.x==second.x)&&(first.y==second.y);
}


Vector2D Lerp(const Vector2D &  v1, const Vector2D &  v2,const double  & t){
   // cout<<v1.x<<" "<<v1.y<<" | "<<v2.x<<" "<<v2.y<<" t: "<<t<<endl;
    return  v1+v2*t-v1*t;
}

struct Color{
    double r,b,g,a;
    Color(double r, double g, double b, double a){
        (*this).r=r;
        (*this).g=g;
        (*this).b=b;
        (*this).a=a;
    }
    Color( ){
        (*this).r=0;
        (*this).b=0;
        (*this).g=0;
        (*this).a=0;
    }
};
