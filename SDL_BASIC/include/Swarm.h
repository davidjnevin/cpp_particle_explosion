#ifndef SWARM_H_
#define SWARM_H_
#include "Particle.h"
namespace davidjnevin {

class Swarm {
 public:
  const static int NPARTICLES = 1000;

 private:
  Particle* m_pParticles;

 public:
  Swarm();
  virtual ~Swarm();

  const Particle* const getParticles() { return m_pParticles; };
  void update();
};

} /* namespace davidjnevin */

#endif /* SWARM_H_ */
