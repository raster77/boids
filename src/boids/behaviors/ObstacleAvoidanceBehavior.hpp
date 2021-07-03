#ifndef BOIDS_BEHAVIORS_OBSTACLEAVOIDANCEBEHAVIOR_HPP_
#define BOIDS_BEHAVIORS_OBSTACLEAVOIDANCEBEHAVIOR_HPP_

#include "MoveBehavior.hpp"
#include "Obstacle.hpp"
#include <algorithm>
#include <vector>

class ObstacleAvoidanceBehavior : public MoveBehavior
{
  public:
    ObstacleAvoidanceBehavior()
      : MoveBehavior()
      , mDistance(0.f)
    {
    }

    ObstacleAvoidanceBehavior(const float distance)
      : MoveBehavior()
      , mDistance(distance)
    {
    }

    ~ObstacleAvoidanceBehavior()
    {
    }

    Vector2f compute(const Boid& b)
    {
      Vector2f force;
      Vector2f dir = b.getVelocity();
      dir = dir.normalize() * mDistance;
      Vector2f projection = b.getPosition() + dir;
      const float radius = b.getRadius() * 1.5f;

      std::sort(mObstacles.begin(), mObstacles.end(), [b](Obstacle* o1, Obstacle* o2) -> bool {
	return o1->getPosition().distanceSquared(b.getPosition()) < o2->getPosition().distanceSquared(b.getPosition());
      });

      for(auto& o : mObstacles)
      {
	Vector2f diff = projection - o->getPosition();
	const float dist = diff.lengthSquared();
	const float r = radius + o->getRadius();
	if(dist <= r * r)
	{
	  Vector2f v = projection - o->getPosition();
	  force = v.normalize() * b.getMaxSpeed();
	}
      }

      return force;
    }

    const float getDistance() const
    {
      return mDistance;
    }

    void setDistance(const float distance)
    {
      mDistance = distance;
    }

    void setObstacles(const std::vector<Obstacle*> obstacles)
    {
      mObstacles = obstacles;
    }

  private:
    float mDistance;
    std::vector<Obstacle*> mObstacles;

    Obstacle* findNearest(const Vector2f position, const float radius)
    {
      Obstacle* oPtr(nullptr);
      float lastDist = -999999.f;

      for(auto& o : mObstacles)
      {
	Vector2f diff = position - o->getPosition();
	const float dist = diff.lengthSquared();
	const float r = (radius * 1.5f + o->getRadius()) * (radius * 1.5f + o->getRadius());
	if(dist <= r && (oPtr == nullptr || dist < lastDist))
	{
	  oPtr = o;
	  lastDist = dist;
	}
      }

      return oPtr;

    }

    bool collision(const Vector2f pos1, const float radius1, const Vector2f pos2, const float radius2)
    {
      Vector2f diff = pos1 - pos2;
      const float dist = diff.lengthSquared();
      const float r = (radius1 + radius2) * 2.f;
      return dist <= r;
    }

};

#endif /* BOIDS_BEHAVIORS_OBSTACLEAVOIDANCEBEHAVIOR_HPP_ */
