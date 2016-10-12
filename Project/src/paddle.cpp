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

uint32 Paddle::getWidth() const {
  return (m_sprite.getGlobalBounds().width);
}

uint32 Paddle::getHeight() const {
  return (m_sprite.getGlobalBounds().height);
}

bool Paddle::checkCollision(Ball *ball) {
  Vector2D ballPos = ball->getPosition();

  bool collided = false;

  if (ballPos.x + ball->getWidth() > m_position.x && ballPos.x < m_position.x + m_sprite.getGlobalBounds().width
    && ballPos.y + ball->getHeight() > m_position.y && ballPos.y < m_position.y + m_sprite.getGlobalBounds().height) {
    collided = true;

    uint32 ballXPosition = (uint32)(ballPos.x);
    Vector2D ballVelocity = ball->getVelocity();

    /* CAREFUL */
    //m_position.x += m_halfWidth;

    if (ballXPosition > (uint32)(m_position.x)  // left side of the paddle minus 10% of total's width
      && ballXPosition < (uint32)(m_position.x + (m_halfWidth - m_halfWidth * 0.2f))) {
      printf("left\n");
      if (ballVelocity.x < 0.0f) {
        ball->invertYVelocity();
      } else if (ballVelocity.x > 0.0f) {
        ball->invertVelocity();
      }
    } else if (ballXPosition > (uint32)(m_position.x + (m_halfWidth - m_halfWidth * 0.2f))
      && ballXPosition < (uint32)(m_position.x + (m_halfWidth + m_halfWidth * 0.2f))) {
      printf("center\n");
    } else {
      printf("right\n");
      if (ballVelocity.x < 0.0f) {
        ball->invertVelocity();
      } else if (ballVelocity.x > 0.0f) {
        ball->invertYVelocity();
      }
    }
  }

  /* CAREFUL */
  //m_position.x -= m_halfWidth;

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