#ifndef BOIDS_BEHAVIORS_OBSTACLE_HPP_
#define BOIDS_BEHAVIORS_OBSTACLE_HPP_

#include "Vector2.hpp"

class Obstacle {
  public:

    Obstacle()
      : mPosition(0.f)
      , mRadius(0.f) {
    }

    Obstacle(const Vector2f& position, const float radius)
      : mPosition(position)
      , mRadius(radius) {
    }

    ~Obstacle() {
    }

    const Vector2f& getPosition() const {
      return mPosition;
    }

    void setPosition(const Vector2f& position) {
      mPosition = position;
    }

    const float getRadius() const {
      return mRadius;
    }

    void setRadius(float radius) {
      mRadius = radius;
    }

  private:
    Vector2f mPosition;
    float mRadius;
};

#endif /* BOIDS_BEHAVIORS_OBSTACLE_HPP_ */
