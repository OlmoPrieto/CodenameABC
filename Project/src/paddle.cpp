#include "paddle.h"

#include "game_manager.h"

#include <cassert>

Paddle::Paddle() {
  m_yPos = 0.0f;
  m_halfWidth = 0.0f;
  m_windowRef = nullptr;
}

Paddle::Paddle(sf::RenderWindow *window) {
  Paddle();
  
  m_yPos = 688.0f;
  m_windowRef = window;
  //m_position = position;
  m_position.x = (float)(640 / 2);
  m_position.y = m_yPos;

  sf::Image image;
  bool success = image.loadFromFile("resources/pad.png");

  assert(success == true && "Failed to load pad texture");

  m_texture.loadFromImage(image);
  m_sprite.setTexture(m_texture);
  m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));

  m_halfWidth = m_sprite.getLocalBounds().width / 2.0f;
}

Paddle::~Paddle() {

}

void Paddle::update(float dt) {
  m_position = GameManager::getInstance()->mousePos();
  m_position.y = m_yPos;
  
  m_sprite.setPosition(m_position.x - m_halfWidth, m_position.y);
}

void Paddle::draw() {
  m_windowRef->draw(m_sprite);
}