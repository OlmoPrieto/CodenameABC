#include "ball.h"

#include "game_manager.h"

#include <cassert>
#include <iostream>

Ball::Ball() {
  m_speed = 0.0f;
  m_windowRef = nullptr;
  m_paddleRef = nullptr;
}

Ball::Ball(sf::RenderWindow *window, const Vector2D &position, 
  const Vector2D &velocity, float speed) {
  Ball();
  
  m_windowRef = window;
  m_paddleRef = GameManager::getInstance()->getPaddleRef();
  m_position = position;
  m_velocity = velocity;
  m_speed = speed;

  sf::Image image;
  bool success = image.loadFromFile("resources/ball_basic1.png");
  //sf::Vector2u imageSize = image.getSize();

  assert(success == true && "Failed to load ball texture");

  m_texture.loadFromImage(image);
  m_sprite.setTexture(m_texture);
  m_sprite.setScale(sf::Vector2f(1.5f, 1.5f));

  m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
}

Ball::~Ball() {

}

void Ball::update(float dt) {
  Paddle *paddle = GameManager::getInstance()->getPaddleRef();
  if (m_position.y > paddle->getYPos() - paddle->getHeight() * 2) {
    
  }

  Vector2D lastPosition = m_position;
  m_position = m_position + (m_velocity * m_speed * dt);

  bool bounced = false;
  sf::Vector2u windowSize = m_windowRef->getSize();
  if (m_position.x > (windowSize.x - m_sprite.getGlobalBounds().width) || m_position.x < 0.0f) {
    m_velocity.x *= -1.0f;
    bounced = true;
  }
  if (m_position.y >(windowSize.y - m_sprite.getGlobalBounds().height) || m_position.y < 0.0f) {
    m_velocity.y *= -1.0f;
    bounced = true;
  }

  if (bounced == true) {
    m_speed *= 1.0025f;  // this increases speed when bouncing in ANY case, change this
  }

  m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
}

void Ball::draw() {
  m_windowRef->draw(m_sprite);
}