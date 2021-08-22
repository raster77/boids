#ifndef BOIDSPRITE_HPP_
#define BOIDSPRITE_HPP_

#include "boids/Boid.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <array>

class BoidSprite final
{
  public:
    BoidSprite();
    BoidSprite(Boid* b);
    ~BoidSprite();

    const std::array<sf::Vertex, 3>& getVertices() const;
    const std::array<sf::Vertex, 200>& getTrailVertices() const;
    const sf::FloatRect& getBoundingBox() const;
    void update();
    void setColor(const sf::Color& c);
    void showTrail(const bool v);
    const bool isShowTrail() { return mShowTrail; }
    void setBoid(Boid* b);
    const float getSize() const { return mSize; }
    void render(sf::RenderWindow* window);

  private:
    sf::Vector2f mPosition;
    sf::Vector2f lastPosition;
    sf::FloatRect mBoundingBox;
    float mSize;
    Boid* mBoidPtr;
    static constexpr float RAD = (180.f / 3.141592653f);
    std::array<sf::Vertex, 3> mVertices;
    std::array<sf::Vertex, 200> mTrailVertices;
    std::array<sf::Vertex, 2> mLineVertices;
    bool mShowTrail;

    void updateTrail();
    void updateVertices();
    sf::Vector2f toSfVec(const Vector2f& v);
};

#endif /* BOIDSPRITE_HPP_ */
