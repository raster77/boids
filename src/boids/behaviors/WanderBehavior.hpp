#ifndef WANDERBEHAVIOR_HPP
#define WANDERBEHAVIOR_HPP

#include "utils/Random.hpp"
#include "MoveBehavior.hpp" // Base class: MoveBehavior
#include "SeekBehavior.hpp"
#include "Vector2.hpp"
#include <cmath>

class WanderBehavior : public MoveBehavior
{

  public:
    WanderBehavior()
      : MoveBehavior()
      , mRadius(0.f)
      , mDistance(0.f)
      , wandertheta(0.f)
      , mRandomRange(0.f)
    {
    }

    ~WanderBehavior()
    {
    }

    const float getDistance()
    {
      return mDistance;
    }

    void setDistance(const float distance)
    {
      mDistance = distance;
      update();
    }

    const float getRadius()
    {
      return mRadius;
    }

    void setRadius(const float radius)
    {
      mRadius = radius;
    }

    const float getRandomRange()
    {
      return mRandomRange;
    }

    void setRandomRange(const float range)
    {
      mRandomRange = range;
    }

    Vector2f compute(const Boid& b)
    {
      rnd::Random::getInstance()->setFloatRange(-mRandomRange, mRandomRange);
      wandertheta += rnd::Random::getInstance()->getUniformFloat();

      Vector2f pos = b.getVelocity();
      pos = pos.normalize() * mDistance;

      pos += b.getPosition();
      float h = heading(b.getVelocity());
      Vector2f target = pos + Vector2f(mRadius * std::cos(wandertheta + h), mRadius * std::sin(wandertheta + h));
      seekBehavior.setTarget(target);
      return seekBehavior.compute(b);
    }

  protected:

    void update()
    {
    }

  private:

    float mRadius;
    float mDistance;
    float wandertheta;
    float mRandomRange;
    SeekBehavior seekBehavior;

    float heading(const Vector2f& v)
    {
      return std::atan2(v.y, v.x);
    }
};

#endif // WANDERBEHAVIOR_HPP
