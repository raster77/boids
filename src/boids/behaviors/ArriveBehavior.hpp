#ifndef BOIDS_BEHAVIORS_ARRIVEBEHAVIOR_HPP_
#define BOIDS_BEHAVIORS_ARRIVEBEHAVIOR_HPP_

#include "MoveBehavior.hpp" // Base class: MoveBehavior

class ArriveBehavior : public MoveBehavior {
  public:
    ArriveBehavior()
      : MoveBehavior()
      , mTarget(0.f)
      , mDistance(50.f) {
    }

    ArriveBehavior(const float distance)
      : MoveBehavior()
      , mTarget(0.f)
      , mDistance(distance) {
    }

    ~ArriveBehavior() {
    }

    const Vector2f& getTarget() {
      return mTarget;
    }

    void setTarget(const Vector2f& target) {
      mTarget = target;
    }

    const float getDistance() {
      return mDistance;
    }

    void setDistance(const float distance) {
      mDistance = distance;
    }

    Vector2f compute(const Boid& b) {
      Vector2f force = (mTarget - b.getPosition());
      float d = force.length();
      if (d < mDistance) {
        force = force.normalize() * map(d, 0.f, mDistance, 0.f, b.getMaxSpeed());
      }
      else {
        force = force.normalize() * b.getMaxSpeed();
      }
      force -= b.getVelocity();
      limit(force, b.getMaxForce());
      return force;
    }

  private:
    Vector2f mTarget;
    float mDistance;

    float map(const float value, const float istart, const float istop, float const ostart, float const ostop) {
      return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
    }
};
#endif /* BOIDS_BEHAVIORS_ARRIVEBEHAVIOR_HPP_ */
