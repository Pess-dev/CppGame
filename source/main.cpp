#include <iostream>
#include <conio.h>
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <string>
#include "game.h"  
#include <windows.h>

#include <SFML/Graphics.hpp>
  

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
string windowTitle="Kill Geometry!"; 
 
 
sf::Vector2f coordsConvert(Vector2D v,Vector2D camera,float size,float rotation,float scale, sf::RenderWindow &window){
	const float degToRad=M_PI/180.0;
	v.y=-v.y;
	v.x-=camera.x;
	v.y+=camera.y;
	v.x+=((double)window.getSize().x)/(2*scale);
	v.y+=((double)window.getSize().y)/(2*scale);   
	return sf::Vector2f( v.x - size * sqrt(2) *cosf(rotation*degToRad), v.y+size * sqrt(2)* sinf(rotation * degToRad) )*scale;
}

sf::Color colorConvert(Color c){
	return sf::Color((int)(c.r*255),(int)(c.g*255),(int)(c.b*255),(int)(c.a*255));
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{    
	sf::ContextSettings settings;
   	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), windowTitle,sf::Style::Close,settings);
	window.setFramerateLimit(300);
 
	sf::Event event;

    Game game=Game(Vector2D(),1,SCR_WIDTH,SCR_HEIGHT); 

    sf::Clock deltaClock;
	double oldTime=clock();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{ 
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}
		}
 
		double currentTime=(double)clock()/(double)CLOCKS_PER_SEC; 
 		double deltaTime = currentTime - oldTime;   
		oldTime = currentTime; 
        game.FrameTick(deltaTime);  
		 

		window.clear(); 
			
		//window.setTitle(windowTitle+" Level: "+to_string(game.level)+" points: "+to_string(game.points));
		window.setTitle(windowTitle);


		/////////////////////////////////
		for (Unit &u: game.backgroundUnits)
		{ 
			float size=(float)u.size*game.cameraScale;
			float rotation=-u.rotation;
			sf::Vector2f position=coordsConvert(u.position,game.camera,u.size,u.rotation-45.0,  game.cameraScale, window);
			sf::Vector2f position45=coordsConvert(u.position,game.camera,u.size,u.rotation-90.0,  game.cameraScale, window);
			sf::Vector2f position180=coordsConvert(u.position,game.camera,u.size,u.rotation-45.0+180.0,  game.cameraScale, window);
        	
			switch (u.shape)
			{
				case asteroid:{
					sf::CircleShape shape=sf::CircleShape(size,4);
					shape.rotate(rotation);
					shape.setPosition(position); 
					shape.setFillColor(colorConvert(u.color)); 
					window.draw(shape);
					sf::CircleShape shape2=sf::CircleShape(size,4);
					shape2.rotate(rotation+45);
					shape2.setPosition(position45); 
					shape2.setFillColor(colorConvert(u.color)); 
					window.draw(shape2);
				 	break;
				}
				case star:{
					sf::CircleShape shape=sf::CircleShape(size,3);
					shape.rotate(rotation);
					shape.setPosition(position); 
					shape.setFillColor(colorConvert(u.color)); 
					window.draw(shape);
					sf::CircleShape shape2=sf::CircleShape(size,3);
					shape2.rotate(rotation-180);
					shape2.setPosition(position180); 
					shape2.setFillColor(colorConvert(u.color)); 
					window.draw(shape2);
				 	break;
				}
				
				default:
				break;
			} 
			
		}   
		/////////////////////////////////

        for (Unit &u: game.units)
		{ 
			float size=(float)u.size*game.cameraScale;
			float rotation=-u.rotation;
			sf::Vector2f position=coordsConvert(u.position,game.camera,u.size,u.rotation-45.0,  game.cameraScale, window);
			sf::Vector2f position180=coordsConvert(u.position,game.camera,u.size,u.rotation-45.0+180.0,  game.cameraScale, window);
			sf::Vector2f position30=coordsConvert(u.position,game.camera,u.size,u.rotation-45.0-30.0,  game.cameraScale, window);
			sf::Vector2f position90=coordsConvert(u.position,game.camera,u.size,u.rotation-45.0-90.0,  game.cameraScale, window);
			sf::Vector2f position45=coordsConvert(u.position,game.camera,u.size,u.rotation-90.0,  game.cameraScale, window);
        	
			switch (u.shape)
			{
				case circle: {
					sf::CircleShape shape=sf::CircleShape(size);
					shape.rotate(rotation);  
					shape.setPosition(position); 
					shape.setFillColor(colorConvert(u.color)); 
					window.draw(shape);
				 	break;
				}
				case square:{
					sf::CircleShape shape=sf::CircleShape(size,4);
					shape.rotate(rotation);  
					shape.setPosition(position); 
					shape.setFillColor(colorConvert(u.color)); 
					window.draw(shape);
				 	break;
				}
				case triangle:{
					sf::CircleShape shape=sf::CircleShape(size,3);
					shape.rotate(rotation);  
					shape.setPosition(position); 
					shape.setFillColor(colorConvert(u.color)); 
					window.draw(shape);
				 	break;
				}
				case pentagon:{
					sf::CircleShape shape=sf::CircleShape(size,5);
					shape.rotate(rotation);  
					shape.setPosition(position); 
					shape.setFillColor(colorConvert(u.color)); 
					window.draw(shape);
				 	break;
				}
				case star:{
					sf::CircleShape shape=sf::CircleShape(size,3);
					shape.rotate(rotation);
					shape.setPosition(position); 
					shape.setFillColor(colorConvert(u.color)); 
					window.draw(shape);
					sf::CircleShape shape2=sf::CircleShape(size,3);
					shape2.rotate(rotation-180);
					shape2.setPosition(position180); 
					shape2.setFillColor(colorConvert(u.color)); 
					window.draw(shape2);
				 	break;
				}
				case funnyFigure:{
					sf::CircleShape shape=sf::CircleShape(size,3);
					shape.rotate(rotation);
					shape.setPosition(position); 
					shape.setFillColor(colorConvert(u.color)); 
					window.draw(shape);
					sf::CircleShape shape2=sf::CircleShape(size,3);
					shape2.rotate(rotation+30);
					shape2.setPosition(position30); 
					shape2.setFillColor(colorConvert(u.color)); 
					window.draw(shape2);
				 	break;
				}
				case asteroid:{
					sf::CircleShape shape=sf::CircleShape(size,4);
					shape.rotate(rotation);
					shape.setPosition(position); 
					shape.setFillColor(colorConvert(u.color)); 
					window.draw(shape);
					sf::CircleShape shape2=sf::CircleShape(size,4);
					shape2.rotate(rotation+45);
					shape2.setPosition(position45); 
					shape2.setFillColor(colorConvert(u.color)); 
					window.draw(shape2);
				 	break;
				}
				case edging:{ 
					sf::CircleShape shape=sf::CircleShape(size);
					shape.rotate(rotation);  
					shape.setPosition(position); 
					shape.setFillColor(colorConvert(u.color)); 
					window.draw(shape);
					sf::CircleShape shape2=sf::CircleShape(size*0.5);
					shape2.rotate(rotation);  
					shape2.setPosition(coordsConvert(u.position,game.camera,u.size*0.5,u.rotation-45.0,  game.cameraScale, window)); 
					shape2.setFillColor(sf::Color(255,255,255,255)); 
					window.draw(shape2);
				 	break;
				}
				default:
				break;
			} 
			
		}   

	if(game.pause){
		sf::Text text;
		sf::Font MyFont;
		MyFont.loadFromFile("impact.ttf");
 		//if (!MyFont.loadFromFile("impact.ttf"))
		//{
    	// Error...
		//}
		text.setFont(MyFont);
		//text.scale=sf::Vector2f(100,100);
		text.setString("\t\t\tTo continue\npress \"space\" or \"arrows\"");
		text.setPosition(250,150);
		window.draw(text);
	}
	else{
		
		sf::Text text;
		sf::Font MyFont;
		MyFont.loadFromFile("impact.ttf");
 		//if (!MyFont.loadFromFile("impact.ttf"))
		//{
    	// Error...
		//}
		text.setFont(MyFont);
		
		text.setString("Level: "+to_string(game.level)+" \npoints: "+to_string(game.points));
		//text.setPosition(,150);
		window.draw(text);
	}


		window.display();
	}
	return 0; 
}