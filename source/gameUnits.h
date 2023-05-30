#include <math.h>
#include <windows.h>
#include <iostream> 
#include <string>
#include <list>
#include <vector>

#include "tools.h"
#include "unit.h" 

#pragma once

vector<pair<vector<double>,double>> getLvls(){
    vector<pair<vector<double>,double>> lvls;
    lvls.emplace_back(vector<double>{1},0.5);
    lvls.emplace_back(vector<double>{0,1},0.5);
    lvls.emplace_back(vector<double>{0.5,1},0.4);
    lvls.emplace_back(vector<double>{0.1,0.2,1},1);
    lvls.emplace_back(vector<double>{0.2,0.4,0.95,1},1);
    lvls.emplace_back(vector<double>{0,0,0.95,1},1.5);
    lvls.emplace_back(vector<double>{0.25,0.4,0.9,0,1},1);
    lvls.emplace_back(vector<double>{0.5,0.7,0.8,0.9,0.95,1},0.7); 
    lvls.emplace_back(vector<double>{0.3,0.7,0.8,0.85,0.9,1},1); 
    return lvls;
}


double rndmProb(){
    return ((double)rand()/(double)(RAND_MAX));
    }


Unit U_Asteroid( Vector2D &topLeftBorder, Vector2D &bottomRightBorder){
    double X=topLeftBorder.x+rndmProb()*(bottomRightBorder.x - topLeftBorder.x);
    double Y=bottomRightBorder.y+(topLeftBorder.y-bottomRightBorder.y)*1.2;
    Unit spawn= *new Unit(*new Vector2D(X,Y),(rndmProb()-0.5)*45,20,enemy,asteroid,*new Color(0.5,0.5,0.5,1), 300, *new Vector2D(0,-1));
    spawn.behavior=forwardMoving;
    spawn.speed=50;
    spawn.size=rndmProb()*10+15;
    spawn.hp=spawn.size*10;
    spawn.points=4;
    return spawn;
}

Unit U_Sin( Vector2D &topLeftBorder, Vector2D &bottomRightBorder ){
    double X=topLeftBorder.x+rndmProb()*(bottomRightBorder.x - topLeftBorder.x);
    double Y=bottomRightBorder.y+(topLeftBorder.y-bottomRightBorder.y)*1.2;
    Unit spawn= *new Unit(*new Vector2D(X,Y),(rndmProb()-0.5)*45,9,enemy,star,*new Color(1,1,0.5,1), 150, *new Vector2D());
    spawn.behavior=sinMoving;
    spawn.timer=rndmProb()*10;
    spawn.speed=40;
    spawn.points=2;
    return spawn;
}

Unit U_ToTarget( Vector2D &topLeftBorder, Vector2D &bottomRightBorder  ){
    double X=topLeftBorder.x+rndmProb()*(bottomRightBorder.x - topLeftBorder.x);
    double Y=bottomRightBorder.y+(topLeftBorder.y-bottomRightBorder.y)*1.2;
    Unit spawn= *new Unit(*new Vector2D(X,Y),(rndmProb()-0.5)*45,7,enemy,funnyFigure,*new Color(0.5,0.5,1,1), 200, *new Vector2D());
    
    spawn.behavior=toTarget;
    spawn.speed=300; 
    spawn.points=8;

    return spawn;
}

Unit U_SideShooter( Vector2D &topLeftBorder, Vector2D &bottomRightBorder){
    double X=topLeftBorder.x+rndmProb()*(bottomRightBorder.x - topLeftBorder.x);
    double Y=bottomRightBorder.y+(topLeftBorder.y-bottomRightBorder.y)*1.2;
    Unit spawn= *new Unit(*new Vector2D(X,Y), 0,14,enemy,square,*new Color(0.8,0.1,0.1,1), 1000, *new Vector2D(0,-1));
    
    
    spawn.timer=rndmProb()*10;

    spawn.behavior=sideShooter;
    spawn.speed=60;
    spawn.points=15;
    //spawn.velocity=(target-spawn.position).normilized()*spawn.speed;
    return spawn;
}

Unit U_PentagonShooter( Vector2D &topLeftBorder, Vector2D &bottomRightBorder){
    double X=topLeftBorder.x+rndmProb()*(bottomRightBorder.x - topLeftBorder.x);
    double Y=bottomRightBorder.y+(topLeftBorder.y-bottomRightBorder.y)*1.2;
    Unit spawn= *new Unit(*new Vector2D(X,Y), 0,18,enemy,pentagon,*new Color(0.8,0.8,0.8,1), 1500, *new Vector2D(0,-1));
     
    spawn.timer=rndmProb()*10; 
    spawn.behavior=pentagonShooter;
    spawn.speed=45; 
    spawn.points=20;
    return spawn;
}

Unit U_MovingShooter( Vector2D &topLeftBorder, Vector2D &bottomRightBorder){
    double X=topLeftBorder.x+rndmProb()*(bottomRightBorder.x - topLeftBorder.x);
    double Y=bottomRightBorder.y+(topLeftBorder.y-bottomRightBorder.y)*1.2;
    Unit spawn= *new Unit(*new Vector2D(X,Y), 180,20,enemy,triangle,*new Color(1,0,0,1), 700, *new Vector2D(0,-1));
     
    spawn.behavior=movingShooter;
    spawn.speed=45; 
    spawn.points=10;
    return spawn;
}

Unit U_enemyBullet( Vector2D &position, Vector2D &velocity ){ 
    Unit spawn= *new Unit(*new Vector2D(position),(rndmProb()-0.5)*45,7,enemy,star,*new Color(0.65,0.13,0.03,1), 2000, *new Vector2D(velocity));
    
    spawn.behavior=forwardMoving;
    spawn.speed=150;
    
    spawn.points=2;
    //spawn.velocity=(target-spawn.position).normilized()*spawn.speed;
    return spawn;
}

Unit U_playerBullet( Vector2D &position, Vector2D &velocity){ 
    Unit spawn= *new Unit(*new Vector2D(position),0, 3,bullet,circle,*new Color(0,0.7,0,1), 50, *new Vector2D(velocity));
    //spawn.velocity=(target-spawn.position).normilized()*spawn.speed;
    return spawn;
}

Unit U_fireRateBonus( Vector2D &position, Vector2D &velocity ){ 
    Unit spawn= *new Unit(*new Vector2D(position),0, 9,bonus,edging,*new Color(0,0.7,0,1),50, *new Vector2D(velocity));
    //spawn.velocity=(target-spawn.position).normilized()*spawn.speed;
    return spawn;
}


Unit U_BackgroundAsteroid( Vector2D position ){
    Unit spawn= *new Unit(position,(rndmProb()-0.5)*45,20,enemy,asteroid,*new Color(0.05,0.05,0.05,1), 300, *new Vector2D(0,-1));
    spawn.speed=60+rndmProb()*5;
    spawn.size=rndmProb()*15+30;
    return spawn;
}

Unit U_BackgroundStar( Vector2D position ){
    Unit spawn= *new Unit(position,(rndmProb()-0.5)*45,20,enemy,star,*new Color(1,1,1,1), 300, *new Vector2D(0,-1));
    spawn.speed=rndmProb()*30;
    spawn.size=rndmProb()*0.5+0.1;
    return spawn;
}