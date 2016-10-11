#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "vectors.h"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Ball;

class Paddle {
public:

  Paddle();
  ~Paddle();

  float getYPos() const;
  uint32 getWidth() const;
  uint32 getHeight() const;

  bool checkCollision(Ball *ball);

  void update(float dt);
  void draw();

private:
  
  float m_yPos;
  float m_halfWidth;
  sf::RenderWindow *m_windowRef;
  Vector2D m_position;
  sf::Texture m_texture;
  sf::Sprite m_sprite;
};

#endif // __PADDLE_H__