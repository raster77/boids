#include "app/Application.hpp"
#include "SceneBoid.hpp"

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
    SceneBoid scene;
};
/*
static constexpr int64_t prime1 = 73856093;
static constexpr int64_t prime2 = 19349663;
static constexpr int64_t prime3 = 734687;
static constexpr int64_t prime4 = 234713;

static constexpr int64_t hash(const int64_t row, const int64_t col)
{
  //return static_cast<int64_t>((row * prime1 * prime3) ^ (col * prime2 * prime4));
  return int64_t(((row + prime3) * prime1) ^ ((col + prime4) * prime2));

}

void test()
{
  robin_hood::unordered_map<int64_t, std::pair<int64_t, int64_t>> map;
  std::size_t count = 0;
  int64_t s = 100000;
  for(int64_t x = -s; x <= s; x += 50)
  {
    for(int64_t y = -s; y <= s; y += 50)
    {
      int64_t h = hash(x, y);
      if(map.find(h) == map.end())
      {
	map[h] = std::make_pair(x, y);
      } else {
	count++;
//	std::pair<int64_t, int64_t> p = map[h];
//	std::cout << "H collision " << h << " first " << p.first << "." << p.second << " - " << x << "." << y << std::endl;
      }
    }
  }
  std::cout << count << " collisions" << std::endl;
  std::cout << "done" << std::endl;
}
*/
int main()
{
//  test();
  MyApp app;
  app.run(sf::VideoMode(1600, 900), "Boids");
  return 0;
}
