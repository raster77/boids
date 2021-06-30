/*
 * MoveBehavior.hpp
 *
 *  Created on: 29 mai 2021
 *      Author: thierry
 */

#ifndef BOIDS_BEHAVIORS_MOVEBEHAVIOR_HPP_
#define BOIDS_BEHAVIORS_MOVEBEHAVIOR_HPP_

#include "Vector2.hpp"

class Boid;

class MoveBehavior
{
  public:

    MoveBehavior()
    {
    }

    virtual ~MoveBehavior()
    {
    }

    virtual Vector2f compute(const Boid& b) = 0;

  protected:

    virtual void update()
    {
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

#endif /* BOIDS_BEHAVIORS_MOVEBEHAVIOR_HPP_ */
