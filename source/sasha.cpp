#include <SFML/Graphics.hpp>
#include <time.h> 
#include <string> 
using namespace sf;

const int W = 1240;
const int H = 720;
int timer=0;
int speed = 4;
bool field[W][H] = { 0 };

struct player
{
    int x, y, dir;
    Color color;
    player(Color c)
    {
        x = rand() % W;
        y = rand() % H;
        color = c;
        dir = rand() % 4;
    }
    void tick()
    {
        if (dir == 0) y += 1;
        if (dir == 1) x -= 1;
        if (dir == 2) x += 1;
        if (dir == 3) y -= 1;

        if (x >= W) x = 0;  if (x < 0) x = W - 1;
        if (y >= H) y = 0;  if (y < 0) y = H - 1;
    }

    Vector3f getColor()
    {
        return Vector3f(color.r, color.g, color.b);
    }
};

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(W, H), "The Tron Game!");
    window.setFramerateLimit(60);

    player p1(Color::Red), p2(Color::Green);

    Sprite sprite;
    RenderTexture t;
    t.create(W, H);
    t.setSmooth(true);
    sprite.setTexture(t.getTexture());
    t.clear();  

    Texture texture;
    texture.loadFromFile("superidol.png"); 

    Sprite pobeda1; 
    Texture texture2;
    texture2.loadFromFile("shrek.png"); 
     
    Texture texture3;
    texture3.loadFromFile("skala.png"); 

    bool Game = false;
    
    sprite.setTexture(texture); 
 
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) if (p1.dir != 2) p1.dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) if (p1.dir != 1)  p1.dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) if (p1.dir != 0) p1.dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) if (p1.dir != 3) p1.dir = 0;

        if (Keyboard::isKeyPressed(Keyboard::A)) if (p2.dir != 2) p2.dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::D)) if (p2.dir != 1) p2.dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::W)) if (p2.dir != 0) p2.dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::S)) if (p2.dir != 3) p2.dir = 0;

        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            if(Game==false)
                {
                    timer=0; 
                    t.clear(); 
                    for(int i=0;i<W;i++)for(int j=0;j<H;j++)field[i][j]=false;
                    p1=*new player(Color::Red);
                    p2=*new player(Color::Green);
                    sprite.setTexture(t.getTexture());
                }
                Game=true;
            }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
         
        if(Game)
        for (int i = 0; i < speed; i++)
        {
            p1.tick(); p2.tick();
            if (field[p1.x][p1.y] == 1) {Game = 0; sprite.setTexture(texture2);}// победа 2 игрока}
            if (field[p2.x][p2.y] == 1) {Game = 0; sprite.setTexture(texture3);}// победа 1 игрока}
            field[p1.x][p1.y] = 1;
            field[p2.x][p2.y] = 1;

            CircleShape c(3);
            c.setPosition(p1.x, p1.y); c.setFillColor(p1.color);    t.draw(c);
            c.setPosition(p2.x, p2.y); c.setFillColor(p2.color);    t.draw(c);
            
            t.display();
        }  
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
