#ifndef SEEKBEHAVIOR_HPP
#define SEEKBEHAVIOR_HPP

#include "MoveBehavior.hpp" // Base class: MoveBehavior

class SeekBehavior : public MoveBehavior
{
  public:
    SeekBehavior()
      : MoveBehavior()
      , mTarget(0.f)
    {
    }

    SeekBehavior(const float distance)
      : MoveBehavior()
      , mTarget(0.f)
    {
    }

    ~SeekBehavior()
    {
    }

    const Vector2f& getTarget()
    {
      return mTarget;
    }

    void setTarget(const Vector2f& target)
    {
      mTarget = target;
    }

    Vector2f compute(const Boid& b)
    {
      Vector2f force = (mTarget - b.getPosition());
      force.setLength(b.getMaxSpeed());
      force -= b.getVelocity();
      limit(force, b.getMaxForce());
      return force;
    }

  private:
    Vector2f mTarget;
};

#endif // SEEKBEHAVIOR_HPP
