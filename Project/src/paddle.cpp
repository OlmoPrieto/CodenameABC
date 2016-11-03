#include "paddle.h"

#include "ball.h"
#include "game_manager.h"

#include <cassert>
#include <iostream>

Paddle::Paddle() {
  
  GameManager *gm = GameManager::getInstance();

  m_yPos = gm->getWindowHeight() * 0.9f;
  
  //m_yPos = 688.0f;
  m_windowRef = gm->getWindowRef();
  //m_position = position;
  m_position.x = (float)(640 / 2);
  m_position.y = m_yPos;

  sf::Image image;
  bool success = image.loadFromFile("resources/pad.png");

  assert(success == true && "Failed to load pad texture");

  m_texture.loadFromImage(image);
  m_sprite.setTexture(m_texture);
  m_sprite.setScale(sf::Vector2f(gm->getSpritesScaleFactor().x, 
    gm->getSpritesScaleFactor().y));

  m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
  
  m_halfWidth = m_sprite.getGlobalBounds().width / 2.0f;
}

Paddle::~Paddle() {

}

float Paddle::getYPos() const {
  return m_yPos;
}

float Paddle::getWidth() const {
  return (m_sprite.getGlobalBounds().width);
}

float Paddle::getHeight() const {
  return (m_sprite.getGlobalBounds().height);
}

bool Paddle::checkCollision(Ball *ball) {
  Vector2D ballPos = ball->getPosition();

  bool collided = false;

  if (ballPos.x + ball->getWidth() > m_position.x && ballPos.x < m_position.x + m_sprite.getGlobalBounds().width
    && ballPos.y + ball->getHeight() > m_position.y && ballPos.y < m_position.y + m_sprite.getGlobalBounds().height) {
    collided = true;  // !!
    
    float paddleCenterX = m_position.x + m_halfWidth;
    uint32 ballXPosition = (uint32)(ballPos.x + (ball->getWidth() / 2.0f));
    Vector2D ballVelocity(ball->getVelocity());
    Vector2D newBallVelocity;

    float percentage = abs(((float)(ballXPosition) - paddleCenterX)) / (uint32)(m_halfWidth);
    printf("percentage: %f\n", percentage);
    if (percentage > 0.75f) {
      percentage = 0.75f;
    }
    
    newBallVelocity.y = (1.0f - percentage) * -1.0f;
    newBallVelocity.x = percentage;
    
    if (ballXPosition < (uint32)(paddleCenterX)) {
      newBallVelocity.x *= -1.0f;
    } else if (ballXPosition > (uint32)(paddleCenterX)) {
      // keep this for if using the center of the paddle
    }

    ball->setVelocity(newBallVelocity);
  }

  return collided;
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