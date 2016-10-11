#ifndef __BALL_H__
#define __BALL_H__

#include "vectors.h"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Paddle;

class Ball {
public:

  Ball(const Vector2D &position, 
    const Vector2D &velocity, float speed);
  ~Ball();

  Vector2D getPosition() const;
  uint32 getWidth() const;
  uint32 getHeight() const;

  void update(float dt);
  void draw();  // Get ref to window

private:
  Ball();

  float m_speed;
  sf::RenderWindow *m_windowRef;
  Paddle* m_paddleRef;
  Vector2D m_position;
  Vector2D m_velocity;
  sf::Texture m_texture;
  sf::Sprite m_sprite;
};

#endif // __BALL_H__