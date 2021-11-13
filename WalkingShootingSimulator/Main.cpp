#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int main()
{
	cout << "Hello World" << endl;

    sf::RenderWindow window(sf::VideoMode(720, 360), "Hello World!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

	return 0;
}
