#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "ball.h"
#include "brick_set.h"
#include "paddle.h"
#include "vectors.h"

#include <SFML/Graphics/RenderWindow.hpp>

class GameManager {
public:

  static GameManager* getInstance();
  void setBrickSetRef(BrickSet *brickSet);
  void setWindowRef(sf::RenderWindow *window);
  void setPaddleRef(Paddle *paddle);
  void setBallRef(Ball *ball);


  sf::RenderWindow* getWindowRef() const;
  Paddle* getPaddleRef() const;
  Ball* getBallRef() const;
  BrickSet* getBrickSetRef() const;
  uint32 getWindowWidth() const;
  uint32 getWindowHeight() const;
  Vector2D getSpritesScaleFactor() const;

  Vector2D mousePos();

private:
  
  GameManager();
  ~GameManager();

  static GameManager *m_instance;
  sf::RenderWindow *m_windowRef;
  Paddle *m_paddleRef;
  Ball *m_ballRef;
  BrickSet *m_brickSetRef;
  Vector2D m_spritesScaleFactor;
};

#endif // __GAME_MANAGER_H__