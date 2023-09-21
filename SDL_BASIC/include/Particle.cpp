#include "Particle.h"

#include <stdlib.h>

namespace davidjnevin {

Particle::Particle() {
  // A range of -1 to 1
  m_x = ((2.0 * rand()) / RAND_MAX) - 1;
  m_y = ((2.0 * rand()) / RAND_MAX) - 1;
};

Particle::~Particle(){};

} /* namespace davidjnevin */
