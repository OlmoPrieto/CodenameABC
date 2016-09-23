#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "vectors.h"

#include <SFML/Graphics/RenderWindow.hpp>

class GameManager {
public:

  static GameManager* getInstance();

  void setWindowRef(sf::RenderWindow *window);

  Vector2D mousePos();

private:
  
  GameManager();
  ~GameManager();

  static GameManager *m_instance;
  sf::RenderWindow *m_windowRef;
};

#endif // __GAME_MANAGER_H__