#include "ball.h"

#include <cassert>
#include <iostream>

Ball::Ball() {
  m_speed = 0.0f;
  m_windowRef = nullptr;
}

Ball::Ball(sf::RenderWindow *window, const Vector2D &position, 
  const Vector2D &velocity, float speed) {
  Ball();
  
  m_windowRef = window;
  m_position = position;
  m_velocity = velocity;
  m_speed = speed;

  sf::Image image;
  bool success = image.loadFromFile("resources/ball_basic1.png");
  //sf::Vector2u imageSize = image.getSize();

  assert(success == true && "Failed to load ball texture");

  m_texture.loadFromImage(image);
  m_sprite.setTexture(m_texture);

  m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
}

Ball::~Ball() {

}

void Ball::update(float dt) {
  Vector2D lastPosition = m_position;
  m_position = m_position + (m_velocity * m_speed * dt);

  sf::Vector2u windowSize = m_windowRef->getSize();
  if (m_position.x > (windowSize.x - m_sprite.getLocalBounds().width) || m_position.x < 0.0f) {
    m_velocity.x *= -1.0f;
  }
  if (m_position.y > (windowSize.y - m_sprite.getLocalBounds().height) || m_position.y < 0.0f) {
    m_velocity.y *= -1.0f;
  }

  m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
}

void Ball::draw() {
  m_windowRef->draw(m_sprite);
}