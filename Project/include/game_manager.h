#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "ball.h"
#include "paddle.h"
#include "vectors.h"

#include <SFML/Graphics/RenderWindow.hpp>

class GameManager {
public:

  static GameManager* getInstance();

  void setWindowRef(sf::RenderWindow *window);
  void setPaddleRef(Paddle *paddle);
  void setBallRef(Ball *ball);

  sf::RenderWindow* getWindowRef() const;
  Paddle* getPaddleRef() const;
  Ball* getBallRef() const;
  uint32 getWindowWidth() const;
  uint32 getWindowHeight() const;
  float getSpritesScaleFactor() const;

  Vector2D mousePos();

private:
  
  GameManager();
  ~GameManager();

  static GameManager *m_instance;
  sf::RenderWindow *m_windowRef;
  Paddle *m_paddleRef;
  Ball *m_ballRef;
  float m_spritesScaleFactor;
};

#endif // __GAME_MANAGER_H__