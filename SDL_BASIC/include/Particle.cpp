#include "Particle.h"

#include <math.h>
#include <stdlib.h>

namespace davidjnevin {

Particle::Particle() : m_x(0), m_y(0) {
  // Direction
  m_direction = (2 * M_PI * rand()) / RAND_MAX;
  // Speed
  m_speed = (0.001 * rand()) / RAND_MAX;
};

Particle::~Particle(){};

void Particle::update(int interval) {
  double xspeed = m_speed * cos(m_direction);
  double yspeed = m_speed * sin(m_direction);

  m_x += xspeed * interval;
  m_y += yspeed * interval;
};

} /* namespace davidjnevin */
