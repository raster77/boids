#ifndef SCENEBOID_HPP_
#define SCENEBOID_HPP_

#include <scene/Scene.hpp>
#include "utils/Fps.hpp"
#include "boids/Boid.hpp"
#include "boids/behaviors/SeekBehavior.hpp"
#include "boids/behaviors/WanderBehavior.hpp"
#include "boids/behaviors/BoundaryBehavior.hpp"
#include "boids/behaviors/FlockBehavior.hpp"
#include "hashgrid/HashGrid.hpp"
#include "InfoPanel.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <string>

class SceneBoid final : public Scene
{
  public:
    SceneBoid();
    SceneBoid(sf::RenderWindow* window);
    ~SceneBoid();

    void load();
    void preUpdate(const float dt);
    void update(const float dt);
    void draw();
    void handleEvent(sf::Event& event);

  private:
    struct TimeMeasure
    {
        std::string info;

        TimeMeasure()
    	: info(""), duration(0.f), oldDuration(0.f)
        {
        }

        TimeMeasure(const std::string& s)
    	: info(s), duration(0.f), oldDuration(0.f)
        {
        }

        void start()
        {
          t1 = std::chrono::high_resolution_clock::now();
        }

        void stop()
        {
          oldDuration = duration;
          std::chrono::duration<float, std::milli> d =
    	  std::chrono::high_resolution_clock::now() - t1;
          duration = d.count();
        }

        float getDuration()
        {
          return duration;
        }

        bool hasChanged()
        {
          return oldDuration != duration;
        }

        std::string getInfo()
        {
	  std::string durationStr = std::to_string(getDuration());
          return std::string(info + ": " + durationStr.substr(0, durationStr.find(".") + 5) + "ms");
        }

      private:
        std::chrono::time_point<std::chrono::high_resolution_clock> t1;
        float duration;
        float oldDuration;
    };

    Fps fps;
    SeekBehavior seekBehavior;
    WanderBehavior wanderBehavior;
    BoundaryBehavior boundaryBehavior;
    FlockBehavior flockBehavior;
    std::vector<Boid> boids;
    std::vector<sf::Vertex> vertices;
    std::vector<sf::Vertex> gridVertices;
    HashGrid<Boid> grid;
    bool showGrid;
    bool showInfo;
    std::vector<TimeMeasure> times;
    InfoPanel infoPanel;
    sf::Clock clock;

    void checkBounds(Boid& b);
};

#endif /* SCENEBOID_HPP_ */
