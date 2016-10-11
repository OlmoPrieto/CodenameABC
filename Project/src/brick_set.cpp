#include "brick_set.h"

#include "game_manager.h"

#include <cassert>

BrickSet::BrickSet() {
  m_brickMatrix = nullptr;

  sf::Image image;
  bool success = image.loadFromFile("resources/brick_demo.png");

  assert(success == true && "Failed to load brick texture");

  m_brickTexture.loadFromImage(image);
  m_brickSprite.setTexture(m_brickTexture);
  m_brickSprite.setScale(sf::Vector2f(GameManager::getInstance()->getSpritesScaleFactor().x,
    GameManager::getInstance()->getSpritesScaleFactor().y));

  m_brickWidth = m_brickSprite.getGlobalBounds().width;
  m_brickHeight = m_brickSprite.getGlobalBounds().height;

  Paddle *paddleRef = GameManager::getInstance()->getPaddleRef();

  m_minSpawnHeight = (uint32)(paddleRef->getYPos() - (paddleRef->getHeight() * 4));

  m_horizontalBrickAmount = (uint32)(GameManager::getInstance()->getWindowWidth() / m_brickWidth);

  m_verticalBrickAmount = (uint32)(m_minSpawnHeight / m_brickHeight);
  printf("Brick's vertical amount: %u\n", m_verticalBrickAmount);

  m_brickMatrix = (char*)malloc(m_horizontalBrickAmount * 
    m_verticalBrickAmount * sizeof(char));

  char *ptr = m_brickMatrix;
  for (uint32 i = 0; i < m_verticalBrickAmount; i++) {
    for (uint32 j = 0; j < m_horizontalBrickAmount; j++) {
      if (i < 16) {
        *ptr = 1;
      } else {
        *ptr = 0;
      }

      ptr++;
    }
  }

  m_windowRef = GameManager::getInstance()->getWindowRef();
}

BrickSet::~BrickSet() {
  if (m_brickMatrix != nullptr) {
    free(m_brickMatrix);
  }
}

void BrickSet::draw() {
  char *ptr = m_brickMatrix;
  
  for (uint32 i = 0; i < m_verticalBrickAmount; i++) {
    for (uint32 j = 0; j < m_horizontalBrickAmount; j++) {
      if (*ptr != 0) {
        m_brickSprite.setPosition(j * m_brickWidth, i * m_brickHeight);
        m_windowRef->draw(m_brickSprite);
      }

      ptr++;
    }
  }
}