#ifndef BOIDS_BEHAVIORS_FLOCKBEHAVIOR_HPP_
#define BOIDS_BEHAVIORS_FLOCKBEHAVIOR_HPP_

#include "MoveBehavior.hpp"
#include "SeekBehavior.hpp"

class FlockBehavior : public MoveBehavior
{
  public:
    FlockBehavior()
      : mSeparation(0.f)
      , mDistance(0.f)
    {
    }

    ~FlockBehavior()
    {
    }

    const float getSeparation() const
    {
      return mSeparation;
    }

    void setSeparation(const float separation)
    {
      mSeparation = separation;
    }

    const float getDistance() const
    {
      return mDistance;
    }

    void setDistance(const float distance)
    {
      mDistance = distance;
      update();
    }

    Vector2f compute(const Boid& b)
    {
      Vector2f align;
      Vector2f separation;
      Vector2f cohesion;
      const float total = static_cast<float>(b.getNeighbours().size());
      for(Boid* bPtr : b.getNeighbours())
      {
	const float dist = b.getPosition().distance(bPtr->getPosition());
	if(dist > 0)
	{
	  if(dist < mDistance)
	  {
	    align += bPtr->getVelocity();
	    cohesion += bPtr->getPosition();
	  }

	  if(dist < mSeparation)
	  {
	    Vector2f diff = b.getPosition() - bPtr->getPosition();
	    diff = diff.normalize() / dist;
	    separation += diff;
	  }
	}
      }

      if(total > 0.f)
      {
	align /= total;
	align = align.normalize() * b.getMaxSpeed();
	align -= b.getVelocity();
	limit(align, b.getMaxForce());

	separation /= total;

	cohesion /= total;
	seekBehavior.setTarget(cohesion);
	cohesion = seekBehavior.compute(b);
      }

      if(separation.length() > 0.f)
      {
	separation = separation.normalize() * b.getMaxSpeed();
	separation -= b.getVelocity();
	limit(separation, b.getMaxForce());
      }

      return separation + cohesion + align;

    }

  protected:
    void update()
    {
      seekBehavior.setDistance(mDistance);
    }

  private:
    float mSeparation;
    float mDistance;
    SeekBehavior seekBehavior;

};

#endif /* BOIDS_BEHAVIORS_FLOCKBEHAVIOR_HPP_ */
