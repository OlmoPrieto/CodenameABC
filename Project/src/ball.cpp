#include "ball.h"

#include "game_manager.h"
#include "paddle.h"

#include <cassert>
#include <iostream>

Ball::Ball() {
  m_speed = 0.0f;
  m_windowRef = nullptr;
  m_paddleRef = nullptr;
}

Ball::Ball(const Vector2D &position, 
  const Vector2D &velocity, float speed) {
  Ball();
  
  GameManager *gm = GameManager::getInstance();

  m_windowRef = gm->getWindowRef();
  m_paddleRef = gm->getPaddleRef();
  m_position = position;
  m_velocity = velocity;
  m_speed = speed;

  sf::Image image;
  bool success = image.loadFromFile("resources/ball_basic1.png");
  //sf::Vector2u imageSize = image.getSize();

  assert(success == true && "Failed to load ball texture");

  m_texture.loadFromImage(image);
  m_sprite.setTexture(m_texture);
  m_sprite.setScale(sf::Vector2f(gm->getSpritesScaleFactor().x, 
    gm->getSpritesScaleFactor().y));

  m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
}

Ball::~Ball() {

}

Vector2D Ball::getPosition() const {
  return m_position;
}

Vector2D Ball::getVelocity() const {
  return m_velocity;
}

uint32 Ball::getWidth() const {
  return (m_sprite.getGlobalBounds().width);
}

uint32 Ball::getHeight() const {
  return (m_sprite.getGlobalBounds().height);
}

void Ball::setVelocity(const Vector2D &velocity) {
  m_velocity = velocity;
}

void Ball::setVelocity(float xDir, float yDir) {
  m_velocity.x = xDir;
  m_velocity.y = yDir;
}

void Ball::setXVelocity(float xDir) {
  m_velocity.x = xDir;
}

void Ball::setYVelocity(float yDir) {
  m_velocity.y = yDir;
}

void Ball::update(float dt) {
  Paddle *paddle = GameManager::getInstance()->getPaddleRef();
  
  Vector2D lastPosition = m_position;
  m_position = m_position + (m_velocity * m_speed * dt);

  bool bounced = false;

  {
    bool collided = GameManager::getInstance()->getBrickSetRef()->checkCollisions(this);
    if (collided == true) {
      bounced = true;
      m_velocity.y *= -1.0f;
    }
  }

  if (m_velocity.y > 0.0f) {  // only check when the ball is going down
    if (m_position.y > paddle->getYPos() - paddle->getHeight() * 2) {
      bool collided = paddle->checkCollision(this);

      if (collided == true) {
        bounced = true;
        //m_velocity = m_velocity * -1.0f;
      }
    }
  }

  sf::Vector2u windowSize = m_windowRef->getSize();
  if (m_position.x > (windowSize.x - m_sprite.getGlobalBounds().width) || m_position.x < 0.0f) {
    m_velocity.x *= -1.0f;
    //bounced = true;
  }
  if (m_position.y >(windowSize.y - m_sprite.getGlobalBounds().height) || m_position.y < 0.0f) {
    m_velocity.y *= -1.0f;
    //bounced = true;
  }

  if (bounced == true) {
    m_position = lastPosition;
    m_speed *= 1.005f;  // this increases speed when bouncing in ANY case, change this
  }

  m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
}

void Ball::draw() {
  m_windowRef->draw(m_sprite);
}

void Ball::invertVelocity() {
  m_velocity = m_velocity * -1.0f;
}

void Ball::invertXVelocity() {
  m_velocity.x *= -1.0f;
}

void Ball::invertYVelocity() {
  m_velocity.y *= -1.0f;
}