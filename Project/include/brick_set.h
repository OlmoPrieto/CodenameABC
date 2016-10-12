#ifndef __BRICK_SET_H__
#define __BRICK_SET_H__

#include "ball.h"
#include "vectors.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class BrickSet {
public:
  
  BrickSet();
  ~BrickSet();

  void draw();

  bool checkCollisions(Ball *ball);

private:
  uint32 m_minSpawnHeight;
  uint32 m_brickWidth;
  uint32 m_brickHeight;
  uint32 m_horizontalBrickAmount;
  uint32 m_verticalBrickAmount;
  sf::RenderWindow *m_windowRef;
  char *m_brickMatrix;
  sf::Texture m_brickTexture;
  sf::Sprite m_brickSprite;
};

#endif // __BRICK_SET_H__