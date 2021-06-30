#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

namespace rnd
{

  class Random
  {
    public:
      static Random* getInstance()
      {
	static rnd::Random instance;
	return &instance;
      }

      float getUniformFloat()
      {
	return realDist(gen);
      }

      float getUniformFloat(const float min, const float max)
      {
	setFloatRange(min, max);
	return realDist(gen);
      }

      void setFloatRange(const float min, const float max)
      {
	std::uniform_real_distribution<float>::param_type p(min, max);
	realDist.param(p);
      }

      int getUniformInt()
      {
	return intDist(gen);
      }

      int getUniformInt(const int min, const int max)
      {
	setIntRange(min, max);
	return intDist(gen);
      }

      void setIntRange(const int min, const int max)
      {
	std::uniform_int_distribution<int>::param_type p(min, max);
	intDist.param(p);
      }

    private:
      std::random_device rd;
      std::mt19937 gen;
      std::uniform_real_distribution<float> realDist;
      std::uniform_int_distribution<int> intDist;

      Random()
	: rd()
	, gen(rd())
      {
      }

      ~Random()
      {
      }

      Random(const Random&) = delete;
      Random& operator=(const Random&) = delete;
      Random(Random&&) = delete;
      Random& operator=(Random&&) = delete;
  };
}

#endif // RANDOM_HPP
