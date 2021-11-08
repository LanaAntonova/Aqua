#include <SFML/Graphics.hpp>
using namespace sf;

int main(){
    RenderWindow window(VideoMode(500, 500), "Game");

    Event event;
    while (window.isOpen()){
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){	
				window.close();
			}
        }
    }
    return 0;
}