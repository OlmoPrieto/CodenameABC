#include "game_manager.h"

#include <SFML/Window/Mouse.hpp>

#include <iostream>

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager() {
  m_windowRef = nullptr;
  m_paddleRef = nullptr;
  m_ballRef = nullptr;
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

void GameManager::setPaddleRef(Paddle *paddle) {
  m_paddleRef = paddle;
}

void GameManager::setBallRef(Ball *ball) {
  m_ballRef = ball;
}

sf::RenderWindow* GameManager::getWindowRef() const {
  return m_windowRef;
}

Paddle* GameManager::getPaddleRef() const {
  return m_paddleRef;
}

Ball* GameManager::getBallRef() const {
  return m_ballRef;
}

Vector2D GameManager::mousePos() {
  // maybe update it only each few milliseconds with a chrono
  sf::Vector2i mousePos = sf::Mouse::getPosition(*m_windowRef);

  return Vector2D((float)mousePos.x, (float)mousePos.y);
}