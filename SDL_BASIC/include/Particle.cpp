#include "Particle.h"

#include <stdlib.h>

#include <cmath>

namespace davidjnevin {

Particle::Particle() : m_x(0), m_y(0) {
  // Direction
  m_direction = (2 * M_PI * rand()) / RAND_MAX;
  // Speed
  m_speed = (0.004 * rand()) / RAND_MAX;
};

Particle::~Particle(){};

void Particle::update() {
  double xspeed = m_speed * cos(m_direction);
  double yspeed = m_speed * sin(m_direction);

  m_x += xspeed;
  m_y += yspeed;
};

} /* namespace davidjnevin */
