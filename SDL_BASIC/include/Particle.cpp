#include "Particle.h"

#include <stdlib.h>

namespace davidjnevin {

Particle::Particle() {
  // A range of -1 to 1
  m_x = ((2.0 * rand()) / RAND_MAX) - 1;
  m_y = ((2.0 * rand()) / RAND_MAX) - 1;
};

Particle::~Particle(){};

void Particle::update() {
  // A range of -1 to 1
  const double speed = 0.01;
  m_x += 0.01;
  m_y += 0.01;
};

} /* namespace davidjnevin */
