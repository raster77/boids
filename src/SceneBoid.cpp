#include "SceneBoid.hpp"

SceneBoid::SceneBoid()
  : Scene()
  , grid(50)
  , showGrid(true)
  , showInfo(true)
{
}

SceneBoid::SceneBoid(sf::RenderWindow* window)
  : Scene(window)
  , grid(50)
  , showGrid(true)
  , showInfo(true)
{
}

SceneBoid::~SceneBoid()
{
}

void SceneBoid::load()
{
  seekBehavior.setDistance(100.f);
  seekBehavior.setTarget(Vector2f(1500.f, 150.f));

  wanderBehavior.setDistance(150.f);
  wanderBehavior.setRadius(50.f);
  wanderBehavior.setRandomRange(150.f);

  boundaryBehavior.setMin(Vector2f(0.f, 0.f));
  boundaryBehavior.setMax(Vector2f(1600.f, 900.f));

  flockBehavior.setSeparation(20.f);
  flockBehavior.setDistance(80.f);

  rnd::Random* rnd = rnd::Random::getInstance();

  for(std::size_t i = 0; i < 1000; ++i)
  {
    Boid b;
    b.setPosition(rnd->getUniformFloat(100.f, 1500.f), rnd->getUniformFloat(100.f, 800.f));
    b.setColor(sf::Color(255, 0, 120));
    b.setMaxForce(10.f);
    b.setMaxSpeed(250.f);
    b.addBehavior(&wanderBehavior);
    b.addBehavior(&flockBehavior);
//      b.addBehavior(&boundaryBehavior);
    b.apply(Vector2f(rnd->getUniformFloat(-300.f, 300.f), rnd->getUniformFloat(-300.f, 300.f)));
    boids.emplace_back(b);
  }
  const float size = static_cast<float>(grid.getCellSize());
  const sf::Color gridColor(100, 100, 100, 255);
  for(unsigned int x = 0; x <= window->getSize().x; x+= grid.getCellSize())
  {
    for(unsigned int y = 0; y <= window->getSize().y; y+= grid.getCellSize())
    {
      gridVertices.emplace_back(sf::Vertex(sf::Vector2f(x, y), gridColor));
      gridVertices.emplace_back(sf::Vertex(sf::Vector2f(x + size, y), gridColor));
      gridVertices.emplace_back(sf::Vertex(sf::Vector2f(x + size, y), gridColor));
      gridVertices.emplace_back(sf::Vertex(sf::Vector2f(x + size, y + size), gridColor));
      gridVertices.emplace_back(sf::Vertex(sf::Vector2f(x + size, y + size), gridColor));
      gridVertices.emplace_back(sf::Vertex(sf::Vector2f(x, y + size), gridColor));
      gridVertices.emplace_back(sf::Vertex(sf::Vector2f(x, y + size), gridColor));
      gridVertices.emplace_back(sf::Vertex(sf::Vector2f(x, y), gridColor));
    }
  }

  times.emplace_back(TimeMeasure("Grid update"));
  times.emplace_back(TimeMeasure("Boid update"));

  infoPanel.loadFont("res/Roboto-Regular.ttf");
  infoPanel.setTextSize(13);

  mRunning = true;
}

void SceneBoid::preUpdate(const float dt)
{

}

void SceneBoid::update(const float dt)
{
  fps.update();
  if(mRunning)
  {
    times[0].start();
    grid.clear();
    for(auto& b : boids) {
      grid.add(b.getPosition().x, b.getPosition().y, &b);
    }
    times[0].stop();

    times[1].start();
    vertices.clear();
    vertices.reserve(boids.size() * 3);
    for(auto& b : boids) {
      std::vector<Boid*> res = grid.get(b.getPosition().x, b.getPosition().y);

      b.findNeighbours(res, flockBehavior.getDistance());
      b.update(dt);
      checkBounds(b);

      b.updateVertices();

      vertices.insert(vertices.end(), b.getVertices().begin(), b.getVertices().end());
    }
    times[1].stop();
    if(showInfo && clock.getElapsedTime().asSeconds() > 0.25f)
    {
      std::string str("Fps: ");
      str.append(std::to_string(static_cast<unsigned int>(fps.getFPS()))).append("\n");
      str.append("Boids: ").append(std::to_string(boids.size())).append("\n");
      for(auto& t: times)
      {
	str.append(t.getInfo()).append("\n");
      }

      infoPanel.setText(str);
      clock.restart();
    }
  }
}

void SceneBoid::draw()
{
  if(showGrid)
  {
    window->draw(gridVertices.data(), gridVertices.size(), sf::Lines);
  }

  window->draw(vertices.data(), vertices.size(), sf::Triangles);

  if(showInfo)
  {
    infoPanel.render(window);
  }
}

void SceneBoid::handleEvent(sf::Event& event)
{
  if(event.type == sf::Event::Closed) {
      window->close();
  }

  if(event.type == sf::Event::KeyPressed) {
      if(event.key.code == sf::Keyboard::Escape) {
          window->close();
      }

      if(event.key.code == sf::Keyboard::G) {
          showGrid = !showGrid;
      }

      if(event.key.code == sf::Keyboard::I) {
	showInfo = !showInfo;
      }

      if(event.key.code == sf::Keyboard::P) {
	mRunning = !mRunning;
      }
  }
}

void SceneBoid::checkBounds(Boid& b)
{
  float x = b.getPosition().x;
  float y = b.getPosition().y;
  if(x < 0.f)
  {
    x = window->getSize().x;
  } else if(x > window->getSize().x) {
    x = 0.f;
  }

  if(y < 0.f)
  {
    y = window->getSize().y;
  } else if(y > window->getSize().y) {
    y = 0.f;
  }
  b.setPosition(x, y);
}
