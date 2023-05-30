#include <math.h>
#include <windows.h>
#include <iostream> 
#include <string>
#include <list>
#include <vector>  

#include "unit.h"
#include "tools.h"

#pragma once

class Bullet : public Unit
{
    public:
    Bullet(Vector2D position, double rotation=0, double size=1, int team=0, int shape = circle, Color color=Color(1,1,1),int hp=100) 
    :Unit(position, rotation, size,  team,  shape, color, hp){}

    void Start(){
        
    }

    void Collision(Unit &u){ 
        if (team==u.team)return;
        u.hp-=hp;
        hp=0;
    }
};