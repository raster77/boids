#ifndef SEEKBEHAVIOR_HPP
#define SEEKBEHAVIOR_HPP

#include "MoveBehavior.hpp" // Base class: MoveBehavior

class SeekBehavior : public MoveBehavior
{
  public:
    SeekBehavior()
      : MoveBehavior()
      , mTarget(0.f)
      , mDistance(50.f)
    {
    }

    SeekBehavior(const float distance)
      : MoveBehavior()
      , mTarget(0.f)
      , mDistance(distance)
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

    const float getDistance()
    {
      return mDistance;
    }

    void setDistance(const float distance)
    {
      mDistance = distance;
    }

    Vector2f compute(const Boid& b)
    {
      Vector2f force = (mTarget - b.getPosition()); //;.normalize() * mMaxSpeed;
      float d = force.length();
      force = d < mDistance ?
	      force.normalize() * map(d, 0.f, mDistance, 0.f, b.getMaxSpeed()) :
	      force.normalize() * b.getMaxSpeed();
      Vector2f steer = force - b.getVelocity();
      limit(steer, b.getMaxForce());
      return steer;
    }

  private:
    Vector2f mTarget;
    float mDistance;

    float map(const float value, const float istart, const float istop,
	      float const ostart, float const ostop)
    {
      return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
    }
};

#endif // SEEKBEHAVIOR_HPP
