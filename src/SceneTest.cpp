#include <SceneTest.hpp>

SceneTest::SceneTest()
  : Scene()
{
}

SceneTest::SceneTest(sf::RenderWindow* window)
: Scene(window)
{
}

SceneTest::~SceneTest()
{
}

void SceneTest::load()
{
  target.setRadius(25.f);
  target.setOrigin(target.getRadius(), target.getRadius());
  target.setFillColor(sf::Color::Transparent);
  target.setOutlineColor(sf::Color::Green);
  target.setOutlineThickness(1.f);

  rnd::Random* rnd = rnd::Random::getInstance();
  seekBehavior.setTarget(Vector2f(rnd->getInstance()->getUniformFloat(100.f, 1400.f), rnd->getInstance()->getUniformFloat(100.f, 800.f)));

  arriveBehavior.setDistance(200.f);
  arriveBehavior.setTarget(seekBehavior.getTarget());

  target.setPosition(seekBehavior.getTarget().x, seekBehavior.getTarget().y);

  wanderBehavior.setDistance(150.f);
  wanderBehavior.setRadius(50.f);
  wanderBehavior.setRandomRange(150.f);

  boundaryBehavior.setMin(Vector2f(0.f, 0.f));
  boundaryBehavior.setMax(Vector2f(1600.f, 900.f));

  boid.setPosition(rnd->getUniformFloat(100.f, 1500.f), rnd->getUniformFloat(100.f, 800.f));
  boid.setMaxForce(10.f);
  boid.setMaxSpeed(100.f);
  boid.addBehavior(&wanderBehavior);
  //boid.addBehavior(&seekBehavior);
  //boid.addBehavior(&arriveBehavior);

  boidSprite.setBoid(&boid);
  boidSprite.setSize(6.f);
  boidSprite.setColor(sf::Color(255, 0, 120));
}

void SceneTest::update(const float dt)
{
  boid.update(dt);
  boidSprite.update();
  checkBounds(boid);
}

void SceneTest::draw()
{
  window->draw(target);
  boidSprite.render(window);
}

void SceneTest::handleEvent(sf::Event& event)
{
  if(event.type == sf::Event::KeyPressed) {
    if(event.key.code == sf::Keyboard::Escape) {
      window->close();
    }

    if(event.key.code == sf::Keyboard::T) {
      boidSprite.showTrail(!boidSprite.isShowTrail());
    }
  }

  if(event.type == sf::Event::MouseButtonPressed) {
    if(event.mouseButton.button == sf::Mouse::Button::Left)
    {
      seekBehavior.setTarget(Vector2f(getMousePosition().x, getMousePosition().y));
      arriveBehavior.setTarget(Vector2f(getMousePosition().x, getMousePosition().y));
      target.setPosition(seekBehavior.getTarget().x, seekBehavior.getTarget().y);
    }
  }
}

void SceneTest::checkBounds(Boid& b)
{
  const float x = b.getPosition().x < 0.f ? window->getSize().x : b.getPosition().x > window->getSize().x ? 0.f : b.getPosition().x;
  const float y = b.getPosition().y < 0.f ? window->getSize().y : b.getPosition().y > window->getSize().y ? 0.f : b.getPosition().y;
  b.setPosition(x, y);
}
