#include <iostream>
#include "SFML/Graphics.hpp"

using namespace sf;

void setMossa(Sprite* player,Vector2i* textureSize,int* i);
void muovilo(Sprite* player,Vector2i* textureSize,int* i,float* delta);
void salto(Sprite* player);
void atterra(Sprite* player);

int main() {
    RenderWindow window(VideoMode(600,500),"BOH",Style::Default);
    Texture t1,t2;
    t1.loadFromFile("background.png");
    t1.setRepeated(true);
    t2.loadFromFile("sprite3.png");
    Sprite player(t2);
    Sprite back(t1);

    back.scale(1,1.7);
    player.scale(1.5,1.5);
    
    Vector2i textureSize(t2.getSize().x/8,t2.getSize().y/4);
    player.setTextureRect(IntRect(textureSize.x*0,textureSize.y*2,textureSize.x,textureSize.y));
    player.setPosition(player.getPosition().x*0,(window.getSize().y)-(player.getGlobalBounds().height));
    int i=0;
    float delta=0;


    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type==event.Closed)
                window.close();
            if(event.type==event.KeyReleased) {
                if(event.key.code==Keyboard::Right) {
                    int k=0;
                    setMossa(&player,&textureSize,&k);
                }
            }
        }

        window.clear();
        delta++;
        window.draw(back);
        window.draw(player);
        muovilo(&player,&textureSize,&i,&delta);
        salto(&player);
        window.display();
    }

}

void muovilo(Sprite* player,Vector2i* textureSize,int* i,float* delta) {
    float switchtime=100;
    if(Keyboard::isKeyPressed(Keyboard::Right)) {
       if(*i>=8)
        *i=0;
    player->move(0.1f,0.0f);
        if(*delta>switchtime) {
            *delta=0;
            setMossa(player,textureSize,i);
            *i=*i+1;    
        }
    }   
}

void setMossa(Sprite* player,Vector2i* textureSize,int* i) {
    player->setTextureRect(IntRect(textureSize->x*(*i),textureSize->y*2,textureSize->x,textureSize->y));
}

void salto(Sprite* player) {
    
    double iniziale=player->getPosition().y;
    double attuale=iniziale;
    double arrivo=player->getPosition().y-1.5;
    if(Keyboard::isKeyPressed(Keyboard::Space)) {
        while(arrivo<attuale) {
            player->move(0.0f,-0.001f);
            attuale=player->getPosition().y;
        }
        
        atterra(player);
    }
}

void atterra(Sprite* player) {
    double iniziale=player->getPosition().y+1.5;
    double attuale=player->getPosition().y;
        while(attuale<iniziale) {
            player->move(0.0f,0.001f);
            attuale=player->getPosition().y;
            std::cout << "FINITO" << std::endl;
        }
}