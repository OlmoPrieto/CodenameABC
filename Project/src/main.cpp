#include <iostream>

#include <SFML/Graphics.hpp>

#include "ball.h"
#include "brick_set.h"
#include "chrono.h"
#include "game_manager.h"
#include "paddle.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(640, 720), "WINDOW");
  
  GameManager::getInstance()->setWindowRef(&window);

  Chrono c;
  c.start();
  float currentTime = 0.0f;

  Ball ball(Vector2D(300.0f, 300.0f), Vector2D(0.5f, 0.5f), 200.0f);
  Paddle paddle;

  GameManager::getInstance()->setBallRef(&ball);
  GameManager::getInstance()->setPaddleRef(&paddle);

  BrickSet b;

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
    float dt = auxTime - currentTime;

    paddle.update(dt);
    paddle.draw();

    ball.update(dt);
    ball.draw();

    b.draw();

    //printf("%f\n", auxTime - currentTime);
    currentTime = auxTime;

    window.display();
  }

  return 0;
}