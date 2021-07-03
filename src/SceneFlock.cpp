#include <SceneFlock.hpp>

SceneFlock::SceneFlock()
  : Scene()
  , grid(50)
  , showGrid(true)
  , showInfo(true)
  , showTrail(true)
{
}

SceneFlock::SceneFlock(sf::RenderWindow* window)
  : Scene(window)
  , grid(50)
  , showGrid(true)
  , showInfo(true)
  , showTrail(true)
{
}

SceneFlock::~SceneFlock()
{
}

void SceneFlock::load()
{
  seekBehavior.setTarget(Vector2f(1500.f, 150.f));

  wanderBehavior.setDistance(150.f);
  wanderBehavior.setRadius(50.f);
  wanderBehavior.setRandomRange(150.f);

  flockBehavior.setSeparation(25.f);
  flockBehavior.setDistance(50.f);

  rnd::Random* rnd = rnd::Random::getInstance();
  const std::size_t N = 500;
  sprites.reserve(N);
  boids.reserve(N);

  for(std::size_t i = 0; i < N; ++i)
  {
    Boid b;
    b.setPosition(rnd->getUniformFloat(100.f, 1500.f), rnd->getUniformFloat(100.f, 800.f));
    b.setMaxForce(10.f);
    b.setMaxSpeed(200.f);
    b.addBehavior(&wanderBehavior);
    b.addBehavior(&flockBehavior);
    b.apply(Vector2f(rnd->getUniformFloat(-300.f, 300.f), rnd->getUniformFloat(-300.f, 300.f)));

    boids.emplace_back(b);
    sprites.emplace_back(&boids.back());
    sprites.back().setColor(sf::Color(255, 0, 120));
    sprites.back().update();
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

void SceneFlock::preUpdate(const float dt)
{

}

void SceneFlock::update(const float dt)
{
  fps.update();
  if(mRunning)
  {
    times[0].start();
    grid.clear();
    std::size_t idx = 0;
    for(auto& b : sprites) {
      //grid.add(b.getBoundingBox().left, b.getBoundingBox().top, b.getBoundingBox().width, b.getBoundingBox().height, &b);
      grid.add(b.getBoundingBox().left, b.getBoundingBox().top, &boids[idx]);
      idx++;
    }
    times[0].stop();

    times[1].start();
    vertices.clear();
    vertices.reserve(boids.size() * 3);
    trailVertices.clear();
    trailVertices.reserve(boids.size() * 200);

    idx = 0;
    for(auto& b : boids) {
      //std::vector<Boid*> res = grid.get(b.getBoundingBox().left, b.getBoundingBox().top, b.getBoundingBox().width, b.getBoundingBox().height);
      std::vector<Boid*> res = grid.get(sprites[idx].getBoundingBox().left, sprites[idx].getBoundingBox().top);

      b.findNeighbours(res, flockBehavior.getDistance());
      b.update(dt);
      checkBounds(b);

      sprites[idx].update();

      vertices.insert(vertices.end(), sprites[idx].getVertices().begin(), sprites[idx].getVertices().end());
      if(showTrail)
	trailVertices.insert(trailVertices.end(), sprites[idx].getTrailVertices().begin(), sprites[idx].getTrailVertices().end());
      idx++;
    }
    times[1].stop();
    if(showInfo && clock.getElapsedTime().asSeconds() > 0.5f)
    {
      std::string str("Fps: ");
      str.append(std::to_string(fps.getFPS())).append("\n");
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

void SceneFlock::draw()
{
  if(showGrid)
  {
    window->draw(gridVertices.data(), gridVertices.size(), sf::Lines);
  }

  window->draw(vertices.data(), vertices.size(), sf::Triangles);
  if(showTrail)
    window->draw(trailVertices.data(), trailVertices.size(), sf::Quads);

  if(showInfo)
  {
    infoPanel.render(window);
  }
}

void SceneFlock::handleEvent(sf::Event& event)
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

      if(event.key.code == sf::Keyboard::T) {
	showTrail = !showTrail;
	if(showTrail)
	{
	  for(auto& b : sprites) {
	    b.showTrail(showTrail);
	  }
	}
      }
  }
}

void SceneFlock::checkBounds(Boid& b)
{
  const float x = b.getPosition().x < 0.f ? window->getSize().x : b.getPosition().x > window->getSize().x ? 0.f : b.getPosition().x;
  const float y = b.getPosition().y < 0.f ? window->getSize().y : b.getPosition().y > window->getSize().y ? 0.f : b.getPosition().y;
  b.setPosition(x, y);
}
