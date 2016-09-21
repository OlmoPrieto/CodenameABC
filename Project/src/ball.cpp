#include "ball.h"

Ball::Ball() {
  m_speed = 0.0f;
  m_windowRef = nullptr;
}

Ball::Ball(sf::RenderWindow *window, Vector2D position, 
  Vector2D velocity, float speed) {
  m_windowRef = window;
  m_position = position;
  m_velocity = velocity;
  m_speed = speed;

  sf::Image image;
  image.loadFromFile("resources/ball_basic1.png");
  //sf::Vector2u imageSize = image.getSize();

  m_texture.loadFromImage(image);
  m_sprite.setTexture(m_texture);
  m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
}

Ball::~Ball() {

}

void Ball::update(float dt) {
  m_position = m_position + (m_velocity * m_speed * dt);

  m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
}

void Ball::draw() {
  m_windowRef->draw(m_sprite);
}