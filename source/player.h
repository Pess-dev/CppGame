#include <math.h>
#include <windows.h>
#include <iostream> 
#include <string>
#include <list>
#include <vector> 
  
#include "unit.h"
#include "bullet.h"
#include "tools.h"

#pragma once

class Player : public Unit{
    int keys[256]={0};

    Vector2D speed=Vector2D();
    Vector2D input=Vector2D();
    bool fire=false;

    double fireDelay=0.5;
    double fireTime=0;

    void GetKEYS( )
    {
        int i = 0;
        while(i < 256)
        {
            if(GetAsyncKeyState(i)) {keys[i] = 1;} else keys[i] = 0;
            i++;
        }
    }

    void getInput( ){
        fire=false;
        speed.toZero();
        GetKEYS();
        if (keys[32]==1) fire = true;
        if (keys[37]==1) speed.x -= 1;
        if (keys[38]==1) speed.y += 1;
        if (keys[39]==1) speed.x += 1;
        if (keys[40]==1) speed.y -= 1;
        speed.normilize();
    }
    void Fire(){
        newUnits.push_back(Bullet(position,0,0.5,team,circle,Color(1,0,0),1000));
    } 
    public:
    Player(Vector2D position, double rotation=0, double size=1, int team=0, int shape = circle, Color color=Color(1,1,1),int hp=100) :  Unit(position, rotation, size,  team,  shape, color, hp){}

    void Start(){
        shape=triangle; 
        team=1;
    }

    

    virtual void Update(double deltaTime){ 
        cout<<"playerUpdate"<<endl;
        newUnits.clear();
        getInput();
        position=position+speed*deltaTime;
        
        fireTime+=deltaTime;
        if (fireTime>fireDelay){
            fireTime=0;
            Fire();
        }
    }
};