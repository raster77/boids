#ifndef BOIDS_BEHAVIORS_MOVEBEHAVIOR_HPP_
#define BOIDS_BEHAVIORS_MOVEBEHAVIOR_HPP_

#include "Vector2.hpp"

class Boid;

class MoveBehavior {
  public:

    MoveBehavior()
      : mEnabled(true) {
    }

    virtual ~MoveBehavior() {
    }

    void enable() {
      mEnabled = true;
    }

    void disable() {
      mEnabled = false;
    }

    const bool isEnable() const {
      return mEnabled;
    }

    virtual Vector2f compute(const Boid& b) = 0;

  protected:

    bool mEnabled;

    virtual void update() {
    }

    void limit(Vector2f& v, const float f) {
      float l = v.lengthSquared();
      if (l > f * f) {
        v /= std::sqrt(l);
        v *= f;
      }
    }
};

#endif /* BOIDS_BEHAVIORS_MOVEBEHAVIOR_HPP_ */
