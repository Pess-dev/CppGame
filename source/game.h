#include <math.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <list>
#define _USE_MATH_DEFINES // for C++
#include <cmath> 
#include <vector> 

#include "unit.h" 
#include "gameUnits.h"  
#pragma once


using namespace std;


class Game{    
    
    public:
    short keys[256];
    Vector2D input;

    bool fire=false;

    double fireDelay;
    double fireTime;
    double timer;
    double deltaTime; 
    double spawnRatio;
    double spawnTimer;


    bool shaking;
    bool gameover;
    bool pause;
    bool god;

    double killRange;
    Vector2D topLeftBorder;
    Vector2D bottomRightBorder;

    
    Vector2D targetCoords;


    int points;
    int level; 
    vector<Unit> units; 


    int backgroundUnitsCount;
    vector<Unit> backgroundUnits; 
    
    Color playerColor;

    Vector2D camera;
    double originalScale;
    double pauseScale;
    double cameraScale;


    double playerVelocityMagnitude;

    Game(Vector2D camera, double scale, int scrWidth, int scrHeight)
    { 
        input=*new Vector2D();
        (*this).camera=camera;
        cameraScale=scale;
        originalScale=cameraScale;
        topLeftBorder=*new Vector2D(-(double)scrWidth/2,(double)scrHeight/2)/scale;
        bottomRightBorder=*new Vector2D((double)scrWidth/2,-(double)scrHeight/2)/scale;
        killRange=1.1* sqrt((double)scrWidth*(double)scrWidth+(double)scrHeight*(double)scrHeight)/scale;
        ResetGame();
    }
    void ResetGame(){
        units.clear(); 
        points=0;
        level=1;
        fireDelay=0.5;
        fireTime=0; 
        spawnRatio=0.5;
        spawnTimer=0;
        pause=true;
        shaking=false;
        timer=0;
        god=false;
        cameraScale = originalScale;
        playerColor=Color(0,0.9,0,1);

        Unit pl=Unit(*new Vector2D(),0,7,player,triangle,playerColor,1,*new Vector2D());
        //pl.speed=700;
        pl.speed=100000;
        
        pauseScale = originalScale*15;

        AddUnit(pl);  
        playerVelocityMagnitude=0;
        targetCoords=*new Vector2D(pl.position);

        backgroundUnitsCount=1000;
        resetBackground();
    }

    void resetBackground(){
        backgroundUnits.clear();
        for (int i=0;i<backgroundUnitsCount;i++){
            double s=2;
            double minX=topLeftBorder.x*s,maxX=bottomRightBorder.x*s,minY=bottomRightBorder.y*s,maxY=topLeftBorder.y*s;
    
            double randX=minX + rndmProb()*(maxX-minX);
            double randY=minY + rndmProb()*(maxY-minY);

            if (i>(float)backgroundUnitsCount*0.93)
            backgroundUnits.push_back(U_BackgroundAsteroid(*new Vector2D(randX,randY)));
            else
            backgroundUnits.push_back(U_BackgroundStar(*new Vector2D(randX,randY)));
            
        }
    }

    void updateBackground(){
        double s=2;
        for (Unit &u : backgroundUnits){
            u.position+=u.velocity*deltaTime*u.speed;
          //  cout<<u.velocity.y<<endl;
            if (u.position.y<bottomRightBorder.y*s){
                u.position.y=topLeftBorder.y*s;
                u.position.x=topLeftBorder.x*s + rndmProb()*(bottomRightBorder.x*s-topLeftBorder.x*s);
            }
        }
    }

    void pauseMode(){
        //cout<<targetCoords.x<<" "<<targetCoords.y<<endl;
        camera=Lerp(camera,targetCoords,0.05);
        cameraScale=cameraScale+(pauseScale - cameraScale)*0.05;
        deltaTime=0;
    } 

    int enemyCount(){
        int count=0;
        for (Unit &u : units)
        {if (u.type==enemy) count++;}
        return count; 
    }

    void FrameTick(double deltaTime){
        
        if (deltaTime<0)deltaTime=0;
        (*this).deltaTime=deltaTime; 

        getInput();
        levelUpdate();

        if(!pause)
        if(shaking) 
        camera=Lerp(camera,Vector2D(cos(timer*(100)*deltaTime),sin(timer*(100)*deltaTime))*(10+10*playerVelocityMagnitude),0.1);
        else
        camera=Lerp(camera,Vector2D(0,0),0.01);

        cameraScale=cameraScale+(originalScale-cameraScale)*0.1;

        if (pause)pauseMode();

        fireTime+=(*this).deltaTime;
        spawnTimer+=(*this).deltaTime;
        timer+=(*this).deltaTime;
 

        if(spawnTimer>spawnRatio){//enemyCount()<maxUnitsAtLevel(level)&&
            spawnTimer=0;
            AddUnit(spawnEnemy());
        }


        gameover=true;
        for (Unit &u : units){
            for (Unit &uCollision : units ){ 
                double m=(u.position-uCollision.position).magnitude();
                if (m<=u.size+uCollision.size&&m>0)
                {
                    // u.Collision(uCollision);
                    // uCollision.Collision(u);
                    if (uCollision.type==enemy&&u.type==player){
                     //   cout<<"fasd\n";
                        if(u.hitted<=0){uCollision.hp=0;uCollision.hitted=0;u.hp=1;u.hitted=10;}
                        else {u.hp=0;}
                    }
                    if (uCollision.type==enemy&&u.type==enemy){
                     //   cout<<"fasd\n";
                        if (uCollision.behavior==Behavior::movingShooter&&u.behavior==Behavior::movingShooter)
                        {
                            uCollision.position=u.position+(uCollision.position-u.position).normilized()*(u.size+uCollision.size);
                        }
                    }

                    if(uCollision.type == bullet && u.type == enemy&&uCollision.hp>0&&u.hp>0){
                        double dHp=u.hp;
                        u.hp-=uCollision.hp;
                        uCollision.hp-=dHp;
                         
                        if (u.type==enemy&&u.hp<=0){ points+=u.points; if (rndmProb()>0.8)AddUnit(U_fireRateBonus(u.position,u.velocity));}
                        u.hitted=0.3;  
                        uCollision.hitted=0.3;  
                        if (uCollision.type==bullet&&uCollision.hp<=0) {uCollision.hitted=0; } 
                        
                    }
                    if(u.type==player&&uCollision.type==bonus){
                        fireDelay*=0.97;
                        uCollision.hp=0;
                    }
                    
                } 
            }   
            unitControl(u);
             
            if ((u.position-Vector2D(0,0)).magnitude()>killRange)
            {  
                KillUnit(u);
            }
        }  
        ClearDeadUnits(); 

        updateBackground();

        if (gameover)ResetGame();
    }
 
    void AddUnit(Unit u){
        units.emplace_back(u);
    } 
 
    void KillUnit(Unit &u){
        u.hp=0;
        if (u.type==player)ResetGame();
    } 

    void ClearDeadUnits( ){ 
        vector<Unit> newUnits;
        for (Unit &u : units){
            if (u.hp>0||u.hitted>0)
            {  
                newUnits.emplace_back(u);
            } 
        }  

        units.clear();
        units=newUnits;
        newUnits.clear(); 
    }

    void GetKEYS( )
    {
        int i = 0;
        while(i < 256)
        {
            if(GetAsyncKeyState(i)) 
            {
                keys[i] = 1;
                //cout<<i<<endl;
            } else keys[i] = 0;
            i++;
        }
    }

    void getInput( ){
        fire=false;
        input.toZero();

        bool oldPause=keys[80];
        bool oldGod=keys[71];

        GetKEYS();
        if (keys[32]==1) fire = true;
        if (keys[80]==1&&!oldPause) pause = !pause;
        if (keys[71]==1&&!oldGod) god = !god;
        if (keys[37]==1||keys[65]==1) input.x -= 1;
        if (keys[39]==1||keys[68]==1) input.x += 1;
        if (keys[40]==1||keys[83]==1) input.y -= 1;
        if (keys[38]==1||keys[87]==1) input.y += 1; 

        if (keys[160]==1)  deltaTime *= 5; 

        input.normilize(); 
        if(input.x!=0||input.y!=0||fire)pause=false;
    }

    void unitControl(Unit &u){
        switch(u.type){
            case player:  
                { 
                    if(god){
                        if(u.hp<=0)u.hp=1;
                        u.color=Color(1,1,0,1);
                        u.hitted=0;
                    }
                    else {
                        u.color=playerColor;
                    }
                    
                    gameover=false;
                    
                    double smoothMoving=0.01;
                    if(u.hitted>0){ 
                        shaking=true;
                        smoothMoving*=0.1; 
                    }else 
                        shaking=false; 

                    if(u.hp<=0){if( u.hitted>1)u.hitted=1; break;};
                    targetCoords=* new Vector2D(u.position);
                    if (u.position.x>bottomRightBorder.x*0.95)u.position.x=bottomRightBorder.x*0.95;
                    if (u.position.x<topLeftBorder.x*0.95)u.position.x=topLeftBorder.x*0.95;
                    if (u.position.y<bottomRightBorder.y*0.95)u.position.y=bottomRightBorder.y*0.95;
                    if (u.position.y>topLeftBorder.y*0.95)u.position.y=topLeftBorder.y*0.95;
                    if (fire&&fireTime>fireDelay) 
                    { 
                        fireTime=0;
                        Unit bullet=U_playerBullet(u.position,* new Vector2D(0,1000));
                        if (god)bullet.hp=5000;
                        else bullet.hp=50;
                        AddUnit(bullet);
                    };  
                    u.velocity = Lerp(u.velocity,input*u.speed*deltaTime, smoothMoving);
                    playerVelocityMagnitude=input.magnitude();
                    break;
                }
            case enemy:
                {
                    updateUnit(u);
                    break;
                } 
            default: {break;}
        }
        u.timer+=deltaTime;
        u.position+=u.velocity*deltaTime;

        if(u.hitted>0)
        {
            u.color.a=0.6;
            u.hitted-=deltaTime;
            if(u.hp<=0){//v1+v2*t-v1*t
                u.size=u.size+(3-u.size)*deltaTime;
                u.color.a=0.3;
            }
        }
        else u.color.a=1;
    }

    void levelUpdate(){
        level=(int)(pow( (double)points,0.8)/(25)+1);
        //spawnRatio=1/((double)level+1)+0.05;
    }

    void updateUnit(Unit &u)
    {
     
    switch (u.behavior)
    {
    case forwardMoving:
    {
        u.rotation += u.speed*deltaTime*(u.rotation>0?1:-1); 
        u.velocity= u.velocity.normilized()*(u.speed+(double)level/2); 
     break;
    }
        
    case sinMoving:{
        u.rotation += u.speed*deltaTime*(u.rotation>0?1:-1); 
        Vector2D sinV=*new Vector2D(sin(u.timer) , -1);//sin(u.livingTime)/2-0.5 );
        u.velocity=sinV*(u.speed+(double)level/2);
         break; 
    }
       
    case toTarget:
    {  
        if ((targetCoords-u.position).magnitude()>250)
        u.velocity=(targetCoords-u.position).normilized()*(u.speed+(double)level/2);
        else u.behavior=forwardMoving;
       // u.velocity=(target-u.position)*u.speed; 
        //u.velocity=*new Vector2D(0,-1)*(speed+(double)level); 
        break;
    }
    case movingShooter:
    {   
        Vector2D newTarget=targetCoords;
        newTarget.y=(topLeftBorder.y+targetCoords.y)/2;
        u.velocity=(newTarget-u.position).normilized()*(u.speed+(double)level/2);
        
        if (u.timer>1.5){
            u.timer=0;
            AddUnit(U_enemyBullet(u.position, *new Vector2D(0,-1))); 
        }
        break;
    }
    case sideShooter:
    {  
        if (u.timer>1.5){
            u.timer=0; 
            AddUnit(U_enemyBullet(u.position, *new Vector2D(1,0) ));
            AddUnit(U_enemyBullet(u.position, *new Vector2D(-1,0) ));
        } 
        u.velocity= u.velocity.normilized()*(u.speed+(double)level/2); 
        // u.velocity=(target-u.position)*u.speed; 
        //u.velocity=*new Vector2D(0,-1)*(speed+(double)level); 
        break;
    }

    case pentagonShooter:
    {  
        if (u.timer>2){
            u.timer=0; 
            double degToRad=M_PI/180.0;            
            double rot=u.rotation;
            Vector2D vel=*new Vector2D(cos(rot*degToRad),sin(rot*degToRad)); 
            AddUnit(U_enemyBullet(u.position, vel ));

            rot+=72;
            vel=*new Vector2D(cos(rot*degToRad),sin(rot*degToRad)); 
            AddUnit(U_enemyBullet(u.position, vel ));
            
            rot+=72;
            vel=*new Vector2D(cos(rot*degToRad),sin(rot*degToRad)); 
            AddUnit(U_enemyBullet(u.position, vel ));
            
            rot+=72;
            vel=*new Vector2D(cos(rot*degToRad),sin(rot*degToRad)); 
            AddUnit(U_enemyBullet(u.position, vel ));
            
            rot+=72;
            vel=*new Vector2D(cos(rot*degToRad),sin(rot*degToRad)); 
            AddUnit(U_enemyBullet(u.position, vel ));
        } 
        u.velocity = u.velocity.normilized()*(u.speed+(double)level/2);
        u.rotation += 50*deltaTime*(u.rotation>0?1:-1);
        // u.velocity=(target-u.position)*u.speed; 
        //u.velocity=*new Vector2D(0,-1)*(speed+(double)level); 
        break;
    }
    
    default:
        break;
        }
    }
    
    Unit spawnEnemy( )
    {
        vector<pair<vector<double>,double>> lvls=getLvls();
        int mx=min(level-1,(int)lvls.size()-1);
        vector<double> probs=lvls[mx].first;

        spawnRatio=lvls[mx].second;
        if (level>(int)lvls.size()){spawnRatio=1/((double)level+1)+0.5;}

        double r= rndmProb()*(double)lvls[mx].first[lvls[mx].first.size()-1];
        
             if (r<=probs[0]){ return        U_Asteroid(topLeftBorder, bottomRightBorder);}
        else if (r<=probs[1]){ return             U_Sin(topLeftBorder, bottomRightBorder);}
        else if (r<=probs[2]){ return        U_ToTarget(topLeftBorder, bottomRightBorder);}
        else if (r<=probs[3]){ return     U_SideShooter(topLeftBorder, bottomRightBorder);}
        else if (r<=probs[4]){ return   U_MovingShooter(topLeftBorder, bottomRightBorder);}
        else if (r<=probs[5]){ return U_PentagonShooter(topLeftBorder, bottomRightBorder);}

        return U_Asteroid(topLeftBorder, bottomRightBorder);
    }
};

