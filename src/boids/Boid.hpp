#ifndef BOIDS_BOID_HPP_
#define BOIDS_BOID_HPP_

#include "behaviors/MoveBehavior.hpp"
#include "Vector2.hpp"
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <array>
#include <vector>

class Boid
{
  public:
    Boid()
      : mPosition(0.f)
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

    void setColor(const sf::Color& c)
    {
      for(auto& v : mVertices)
	v.color = c;
    }

    void apply(const Vector2f& force)
    {
      mAcceleration += force;
    }

    void update(const float dt)
    {
      for (auto &b : behaviors)
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
      mNeighbours.clear();
      mNeighbours.reserve(boids.size() - 1);
      for(auto& b : boids) {
	if(b != this)
	{
	  if(mPosition.distanceSquared(b->getPosition()) <= radius * radius)
	  {
	    mNeighbours.emplace_back(b);
	  }
	}
      }
    }

    void findNeighbours(std::vector<Boid>& boids, const float radius)
    {
      mNeighbours.clear();
      mNeighbours.reserve(boids.size() - 1);
      for(auto& b : boids) {
	if(&b != this)
	{
	  if(mPosition.distanceSquared(b.getPosition()) <= radius * radius)
	  {
	    mNeighbours.emplace_back(&b);
	  }
	}
      }
    }

    void updateVertices()
    {
      const Vector2f dir = mVelocity.normalize();
      const float angle = std::atan2(dir.y, dir.x) * RAD;
      sf::Transform t;
      t.translate(toSfVec(mPosition));
      t.rotate(angle);
      t.scale(sf::Vector2f(3, 1) * 3.f);

      mVertices[0].position = t.transformPoint(sf::Vector2f(0, 0));
      mVertices[1].position = t.transformPoint(sf::Vector2f(0, 2));
      mVertices[2].position = t.transformPoint(sf::Vector2f(1, 1));
    }

    const std::array<sf::Vertex, 3>& getVertices() const
    {
      return mVertices;
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
    Vector2f mAcceleration;
    Vector2f mVelocity;
    float mMaxForce;
    float mMaxSpeed;
    std::vector<MoveBehavior*> behaviors;
    std::vector<Boid*> mNeighbours;
    const float RAD = (180.f / 3.141592653f);
    std::array<sf::Vertex, 3> mVertices;

    sf::Vector2f toSfVec(const Vector2f& v)
    {
      return sf::Vector2f(v.x, v.y);
    }

    void limit(Vector2f& v, const float f)
    {
      float l = v.lengthSquared();
      if (l > f * f) {
	v /= std::sqrt(l);
	v *= f;
      }
    }
};

#endif /* BOIDS_BOID_HPP_ */
