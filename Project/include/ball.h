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

  void setVelocity(const Vector2D &velocity);
  void setVelocity(float xDir, float yDir);
  void setXVelocity(float xDir);
  void setYVelocity(float yDir);

  Vector2D getPosition() const;
  Vector2D getVelocity() const;
  uint32 getWidth() const;
  uint32 getHeight() const;
  uint32 getNumBounces() const;

  void update(float dt);
  void draw();  // Get ref to window
  
  void invertVelocity();
  void invertXVelocity();
  void invertYVelocity();

private:
  Ball();
  
  uint32 m_numBounces;
  float m_speed;
  sf::RenderWindow *m_windowRef;
  Paddle* m_paddleRef;
  Vector2D m_position;
  Vector2D m_velocity;
  sf::Texture m_texture;
  sf::Sprite m_sprite;
};

#endif // __BALL_H__