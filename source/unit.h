#include <math.h>
#include <windows.h>
#include <iostream> 
#include <string>
#include <list>
#include <vector> 


#include "tools.h"

#pragma once

using namespace std;

enum Shape{
    circle,
    square,
    triangle,
    star,
    funnyFigure,
    pentagon,
    asteroid,
    edging
};

enum UnitType{
        player,
        bullet,
        enemy,
        bonus
    };

enum Behavior{
        noBehavior,
        forwardMoving,
        sinMoving,
        toTarget,
        sideShooter,
        pentagonShooter,
        movingShooter
    };

class Unit{ 
    
    public:   
    bool operator==(const Unit& right) const {
        return  (position.y == right.position.y&&position.x == right.position.x&& hp==right.hp &&  rotation==right.rotation &&  shape==right.shape&& type==right.type);
    }
    
    bool operator!=( const Unit& right) const {
        return !((*this) == right);
    }

    double hp;
    Shape shape; 
    UnitType type;
    Color color; 
    double rotation;
    double size;  
    float speed;
    float hitted;
    float timer;
    int points;
    Behavior behavior;
    

    
    Vector2D velocity;
    Vector2D position; 

   // Unit(){}
    
    Unit(const Unit &u)
    { 
        (*this).rotation=u.rotation;
        (*this).size=u.size;
        (*this).shape=u.shape;
        (*this).color=u.color;
        (*this).hp=u.hp;
        (*this).type=u.type; 
        (*this).velocity = u.velocity;
        (*this).position = u.position;
         
        (*this).speed=u.speed;
        (*this).behavior=u.behavior;
        (*this).hitted=u.hitted;
        (*this).timer=u.timer;
        (*this).points=u.points;
    }

    Unit(Vector2D position, double rotation, double size, UnitType type, Shape shape, Color color,double hp, Vector2D velocity){
        (*this).velocity = velocity; 
        (*this).position = position; 
        (*this).rotation=rotation;
        (*this).size=size; 
        (*this).shape=shape; 
        (*this).color=color; 
        (*this).hp=hp; 
        (*this).type=type;    
        speed=0;
        hitted=0;
        behavior=noBehavior;
        timer=0;
        points=0;
    }
    
    // void Collision(Unit &u){
        
    //     if((type==enemy&&u.type!=enemy||type!=enemy&&u.type==enemy)&&u.type==enemy&&u.hp>0){
    //         hp-=u.hp;
    //     }

    // }
};
