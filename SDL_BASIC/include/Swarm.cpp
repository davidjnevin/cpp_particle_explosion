#include "Swarm.h"

namespace davidjnevin {

Swarm::Swarm() { m_pParticles = new Particle[NPARTICLES]; };
Swarm::~Swarm() { delete[] m_pParticles; };

} /* namespace davidjnevin */
