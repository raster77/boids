#ifndef SCENETEST_HPP_
#define SCENETEST_HPP_

#include "boids/Boid.hpp"
#include "boids/behaviors/SeekBehavior.hpp"
#include "boids/behaviors/WanderBehavior.hpp"
#include "boids/behaviors/BoundaryBehavior.hpp"
#include "boids/behaviors/ArriveBehavior.hpp"
#include "hashgrid/HashGrid.hpp"
#include "InfoPanel.hpp"
#include "BoidSprite.hpp"
#include <scene/Scene.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class SceneTest final : public Scene
{
  public:
    SceneTest();
    SceneTest(sf::RenderWindow* window);
    ~SceneTest();

    void load();
    void update(const float dt);
    void draw();
    void handleEvent(sf::Event& event);

  private:
    Boid boid;
    BoidSprite boidSprite;
    SeekBehavior seekBehavior;
    WanderBehavior wanderBehavior;
    ArriveBehavior arriveBehavior;
    BoundaryBehavior boundaryBehavior;
    sf::CircleShape target;

    void checkBounds(Boid& b);
};

#endif /* SCENETEST_HPP_ */
