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

bool BrickSet::checkCollisions(Ball *ball) {
  Vector2D bSize(ball->getWidth(), ball->getHeight());
  Vector2D bPos(ball->getPosition());

  bool collided = false;
  char *ptr = m_brickMatrix;

  for (uint32 i = 0; i < m_verticalBrickAmount; i++) {
    for (uint32 j = 0; j < m_horizontalBrickAmount; j++) {
      if (*ptr != 0) {
        Vector2D brickPos(j * m_brickWidth, i * m_brickHeight);

        if (bPos.x + bSize.x > (brickPos.x) && bPos.x < (brickPos.x + m_brickWidth)
          && bPos.y + bSize.y > (brickPos.y) && bPos.y < (brickPos.y + m_brickHeight)) {
          collided = true;

          *ptr = 0;

          Vector2D ballCenter(bPos.x + bSize.x / 2.0f, bPos.y + bSize.y / 2.0f);

          bool atLeft = false;
          bool atTop = false;
          bool atRight = false;
          bool atBottom = false;

          if (ballCenter.x < brickPos.x) {
            atLeft = true;
          }
          if (ballCenter.y < brickPos.y) {
            atTop = true;
          }
          if (ballCenter.x > brickPos.x + m_brickWidth) {
            atRight = true;
          }
          if (ballCenter.y > brickPos.y + m_brickHeight) {
            atBottom = true;
          }
          
          bool aside = false;
          bool upDown = false;

          if (atLeft == true) {
            // collided with left side
            // in between left side bounds
            if (bPos.y + bSize.y > brickPos.y || bPos.y < brickPos.y + m_brickHeight) {
              aside = true;
            }
          } else if (atRight == true) {
            // collided with right side
            if (bPos.y + bSize.y > brickPos.y || bPos.y < brickPos.y + m_brickHeight) {
              aside = true;
            }
          } else if (atTop == true) {
            // collided with top
            if (bPos.x + bSize.x > brickPos.x || bPos.x < brickPos.x + m_brickWidth) {
              upDown = true;
            }
          } else if (atBottom == true) {
            // collided with bottom
            if (bPos.x + bSize.x > brickPos.x || bPos.x < brickPos.x + m_brickWidth) {
              upDown = true;
            }
          } else {
            printf("\nups\n");
            ball->invertVelocity();
          }

          if (aside == true) {
            ball->invertXVelocity();
          } else if (upDown == true) {
            ball->invertYVelocity();
          }

          return collided;
        }
      }

      ptr++;
    }
  }


  return collided;
}