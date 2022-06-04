#ifndef FPS_HPP
#define FPS_HPP

#include <SFML/System/Clock.hpp>

class Fps {
  public:
    Fps()
        : frame(0), mFps(0) {
    }

    ~Fps() {
    }

    void update() {
      if (clock.getElapsedTime().asSeconds() >= 1.f) {
        mFps = frame;
        frame = 0;
        clock.restart();
      }

      ++frame;
    }

    const unsigned int getFPS() const {
      return mFps;
    }

  private:
    unsigned int frame;
    unsigned int mFps;
    sf::Clock clock;
};

#endif // FPS_HPP
