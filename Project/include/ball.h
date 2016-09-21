#ifndef __BALL_H__
#define __BALL_H__

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "vectors.h"

class Ball {
public:

  Ball();
  Ball(sf::RenderWindow *window, Vector2D position, 
    Vector2D velocity, float speed);
  ~Ball();

  void update(float dt);
  void draw();  // Get ref to window

private:
  float m_speed;
  sf::RenderWindow *m_windowRef;
  Vector2D m_position;
  Vector2D m_velocity;
  sf::Texture m_texture;
  sf::Sprite m_sprite;
};

#endif // __BALL_H__