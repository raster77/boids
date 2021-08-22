#include <SceneFlock.hpp>
#include "app/Application.hpp"
#include "SceneTest.hpp"

class MyApp : public Application
{
  public:
    MyApp()
	: Application()
    {
    }

    ~MyApp()
    {
    }

    void setup()
    {
      scene.setWindow(window());
      scene.load();
      currentScene = &scene;
    }

  private:
    SceneFlock scene;
};

int main()
{
  MyApp app;
  app.run(sf::VideoMode(1920, 1080), "Boids");
  return 0;
}
