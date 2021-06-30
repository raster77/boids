#ifndef BOUNDARYBEHAVIOR_HPP
#define BOUNDARYBEHAVIOR_HPP

#include "MoveBehavior.hpp"

class BoundaryBehavior : public MoveBehavior
{
  public:
    BoundaryBehavior()
	: MoveBehavior()
    {
    }

    ~BoundaryBehavior()
    {
    }

    const Vector2f& getMin()
    {
      return mMin;
    }

    void setMin(const Vector2f& min)
    {
      mMin = min;
    }

    const Vector2f& getMax()
    {
      return mMax;
    }

    void setMax(const Vector2f& max)
    {
      mMax = max;
    }

    Vector2f compute(const Boid& b)
    {
      float x = 0.f;
      float y = 0.f;

      if (b.getPosition().x < mMin.x)
      {
	x = b.getMaxSpeed();
	y = b.getVelocity().y;
      }
      else if (b.getPosition().x > mMax.x)
      {
	x = -b.getMaxSpeed();
	y = b.getVelocity().y;
      }

      if (b.getPosition().y < mMin.y)
      {
	y = b.getMaxSpeed();
	x = b.getVelocity().x;
      }
      else if (b.getPosition().y > mMax.y)
      {
	y = -b.getMaxSpeed();
	x = b.getVelocity().x;
      }
      return
	  (x != 0 || y != 0) ?
	      Vector2f(x, y).normalize() * b.getMaxSpeed() - b.getVelocity() :
	      Vector2f(0.f);
    }

  protected:
    void update()
    {
    }

  private:
    Vector2f mMin;
    Vector2f mMax;
};

#endif // BOUNDARYBEHAVIOR_HPP
