#ifndef __BALL_H__
#define __BALL_H__

#include "paddle.h"
#include "vectors.h"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Ball {
public:

  Ball();
  Ball(sf::RenderWindow *window, const Vector2D &position, 
    const Vector2D &velocity, float speed);
  ~Ball();

  void update(float dt);
  void draw();  // Get ref to window

private:
  float m_speed;
  sf::RenderWindow *m_windowRef;
  Paddle* m_paddleRef;
  Vector2D m_position;
  Vector2D m_velocity;
  sf::Texture m_texture;
  sf::Sprite m_sprite;
};

#endif // __BALL_H__