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
  double m_speed;
  // Direction
  double m_direction;

 public:
  Particle();
  virtual ~Particle();
  void update(int interval);

 private:
  void init();
};

} /* namespace davidjnevin */

#endif /* PARTICLE_H_ */
