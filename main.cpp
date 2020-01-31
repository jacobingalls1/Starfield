#include <iostream>
#include "point.h"
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;

int main() {

    srand(time(NULL));

    const int SCREEN_SIZE = 1000, MAX_POINTS = 1000, SPAWN_RAD = 50, SPAWN_RATE = 100;
    point CENTER(0, SCREEN_SIZE / 2, SCREEN_SIZE / 2, 0, 0, false);
    int mouseX = SCREEN_SIZE / 2, mouseY = SCREEN_SIZE / 2;

    vector<point> points;

    RenderWindow window(VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Starfield");
    window.requestFocus();
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    while( window.isOpen() ) {
        Vector2i mouse = Mouse::getPosition(window);
        if (0 < mouse.x and mouse.x < SCREEN_SIZE and 0 < mouse.y and mouse.y < SCREEN_SIZE) {
            mouseX = mouse.x;
            mouseY = mouse.y;
        } else {
            mouseX = SCREEN_SIZE / 2;
            mouseY = SCREEN_SIZE / 2;
        }

        window.clear(Color::Black);

        for (int i = 0; i < SPAWN_RATE; i++) {
            if (points.size() < MAX_POINTS) {
                points.push_back(point(SPAWN_RAD, mouseX, mouseY, SCREEN_SIZE, SCREEN_SIZE));
            }
        }

        for (int i = 0; i < points.size(); i++) {
            points[i].move(mouseX, mouseY);
            if (!points[i].within(SCREEN_SIZE)) {
                points.erase(points.begin() + i);
            }
            RectangleShape rect;
            rect.setPosition(points[i].x, points[i].y);
            rect.setSize(Vector2f(1, 1));
            rect.setFillColor(Color::White);
            window.draw(rect);
        }

        window.display();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::Escape:
                    case Keyboard::Q:
                        window.close();
                        break;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}