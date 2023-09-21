#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace davidjnevin {

class Particle {
 public:
  // Although we will display at an integral position
  // we will calculate the position using floating point
  // to allow for smoother movement.
  double m_x;
  double m_y;

  // Velocity
  double m_xspeed;
  double m_yspeed;

 public:
  Particle();
  virtual ~Particle();
  void update();
};

} /* namespace davidjnevin */

#endif /* PARTICLE_H_ */
