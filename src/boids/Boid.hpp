#ifndef BOIDS_BOID_HPP_
#define BOIDS_BOID_HPP_

#include "behaviors/MoveBehavior.hpp"
#include "Vector2.hpp"
#include <array>
#include <vector>

class Boid
{
  public:
    Boid()
      : mPosition(0.f)
      , lastPosition(0.f)
      , mAcceleration(0.f)
      , mVelocity(0.f)
      , mMaxForce(10.f)
      , mMaxSpeed(200.f)
    {
    }

    ~Boid()
    {
    }

    void setPosition(const Vector2f& p)
    {
      mPosition = p;
    }

    void setPosition(const float x, const float y)
    {
      mPosition = Vector2f(x, y);
    }

    const Vector2f& getPosition() const
    {
      return mPosition;
    }

    const float getMaxForce() const
    {
      return mMaxForce;
    }

    void setMaxForce(const float force)
    {
      mMaxForce = force;
    }

    const float getMaxSpeed() const
    {
      return mMaxSpeed;
    }

    void setMaxSpeed(const float speed)
    {
      mMaxSpeed = speed;
    }

    const Vector2f& getVelocity() const
    {
      return mVelocity;
    }

    void apply(const Vector2f& force)
    {
      mAcceleration += force;
    }

    void update(const float dt)
    {
      for (auto& b : behaviors)
      {
	apply(b->compute(*this));
      }

      mVelocity += mAcceleration;
      limit(mVelocity, mMaxSpeed);
      mPosition += mVelocity * dt;

      mAcceleration.set(0.f);
    }

    void findNeighbours(const std::vector<Boid*>& boids, const float radius)
    {
      if(!boids.empty())
      {
	mNeighbours.clear();
	mNeighbours.reserve(boids.size() - 1);
	for(auto& b : boids) {
	  if(b != this && mPosition.distanceSquared(b->getPosition()) <= radius * radius)
	  {
	    mNeighbours.emplace_back(b);
	  }
	}
      }
    }

    void findNeighbours(std::vector<Boid>& boids, const float radius)
    {
      if(!boids.empty())
      {
	mNeighbours.clear();
	mNeighbours.reserve(boids.size() - 1);
	for(auto& b : boids) {
	  if(&b != this && mPosition.distanceSquared(b.getPosition()) <= radius * radius)
	  {
	    mNeighbours.emplace_back(&b);
	  }
	}
      }
    }

    const std::vector<Boid*>& getNeighbours() const
    {
      return mNeighbours;
    }

    void addBehavior(MoveBehavior* moveBehavior)
    {
      behaviors.emplace_back(moveBehavior);
    }

  private:
    Vector2f mPosition;
    Vector2f lastPosition;
    Vector2f mAcceleration;
    Vector2f mVelocity;
    float mMaxForce;
    float mMaxSpeed;
    std::vector<MoveBehavior*> behaviors;
    std::vector<Boid*> mNeighbours;

    void limit(Vector2f& v, const float f)
    {
      const float l = v.lengthSquared();
      if (l > f * f) {
	v /= std::sqrt(l);
	v *= f;
      }
    }
};

#endif /* BOIDS_BOID_HPP_ */
