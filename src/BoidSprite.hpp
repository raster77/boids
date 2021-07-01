#ifndef BOIDSPRITE_HPP_
#define BOIDSPRITE_HPP_

#include "boids/Boid.hpp"
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <array>

class BoidSprite final
{
  public:
    BoidSprite();
    ~BoidSprite();

    const std::array<sf::Vertex, 3>& getVertices() const;
    const std::array<sf::Vertex, 200>& getTrailVertices() const;
    const sf::FloatRect& getBoundingBox() const;
    void setColor(const sf::Color& c);
    void update(const Boid& b);
    void showTrail(const bool v)
    {
      mShowTrail = v;
    }

  private:
    sf::Vector2f mPosition;
    sf::Vector2f lastPosition;
    sf::FloatRect mBoundingBox;
    static constexpr float RAD = (180.f / 3.141592653f);
    std::array<sf::Vertex, 3> mVertices;
    std::array<sf::Vertex, 200> mTrailVertices;
    bool mShowTrail;

    void updateTrail();
    void updateVertices(const Boid& b);
    sf::Vector2f toSfVec(const Vector2f& v);
};

#endif /* BOIDSPRITE_HPP_ */
