#include <iostream>

#include <SFML/Graphics.hpp>

#include "ball.h"
#include "chrono.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(1280, 720), "WINDOW");

  Chrono c;
  c.start();
  float currentTime = 0.0f;

  Ball ball(&window, Vector2D(300, 300), Vector2D(1.0f, 1.0f), 100.0f);

  while (window.isOpen()) {
    sf::Event e;
    while (window.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();

    c.stop();
    float auxTime = c.timeAsSeconds();

    ball.update(auxTime - currentTime);
    ball.draw();

    //printf("%f\n", auxTime - currentTime);
    currentTime = auxTime;

    window.display();
  }

  return 0;
}