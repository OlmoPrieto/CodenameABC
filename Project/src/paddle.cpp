#include "paddle.h"

#include "ball.h"
#include "game_manager.h"

#include <cassert>
#include <iostream>

Paddle::Paddle() {
  m_yPos = 0.0f;
  m_halfWidth = 0.0f;
  m_windowRef = nullptr;
}

Paddle::Paddle(sf::RenderWindow *window) {
  Paddle();
  
  GameManager *gm = GameManager::getInstance();

  m_yPos = gm->getWindowHeight() * 0.9f;
  //m_yPos = 688.0f;
  m_windowRef = window;
  //m_position = position;
  m_position.x = (float)(640 / 2);
  m_position.y = m_yPos;

  sf::Image image;
  bool success = image.loadFromFile("resources/pad.png");

  assert(success == true && "Failed to load pad texture");

  m_texture.loadFromImage(image);
  m_sprite.setTexture(m_texture);
  m_sprite.setScale(sf::Vector2f(gm->getSpritesScaleFactor(), 
    gm->getSpritesScaleFactor()));

  m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));

  m_halfWidth = m_sprite.getGlobalBounds().width / 2.0f;
}

Paddle::~Paddle() {

}

float Paddle::getYPos() const {
  return m_yPos;
}

uint32 Paddle::getWidth() const {
  return (m_sprite.getGlobalBounds().width);
}

uint32 Paddle::getHeight() const {
  return (m_sprite.getGlobalBounds().height);
}

bool Paddle::checkCollision(Ball *ball) {
  Vector2D ballPos = ball->getPosition();

  return (ballPos.x + ball->getWidth() > m_position.x && ballPos.x < m_position.x + m_sprite.getGlobalBounds().width
    && ballPos.y + ball->getHeight() > m_position.y && ballPos.y < m_position.y + m_sprite.getGlobalBounds().height);
}

void Paddle::update(float dt) {
  m_position = GameManager::getInstance()->mousePos();
  m_position.x -= m_halfWidth;
  m_position.y = m_yPos;
  
  m_sprite.setPosition(m_position.x, m_position.y);
}

void Paddle::draw() {
  m_windowRef->draw(m_sprite);
}