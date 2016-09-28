#include "game_manager.h"

#include <SFML/Window/Mouse.hpp>

#include <iostream>

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager() {
  
}

GameManager::~GameManager() {
  if (m_instance != nullptr) {
    delete m_instance;
  }
}

GameManager* GameManager::getInstance() {
  if (m_instance == nullptr) {
    m_instance = new GameManager();
  }

  return m_instance;
}

void GameManager::setWindowRef(sf::RenderWindow *window) {
  m_windowRef = window;
}

Vector2D GameManager::mousePos() {
  // maybe update it only each few milliseconds with a chrono
  sf::Vector2i mousePos = sf::Mouse::getPosition(*m_windowRef);

  return Vector2D((float)mousePos.x, (float)mousePos.y);
}