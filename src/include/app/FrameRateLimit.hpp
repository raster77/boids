#ifndef FRAMERATELIMIT_HPP_
#define FRAMERATELIMIT_HPP_

#include <chrono>
#include <thread>

class FrameRateLimit {
  public:
    FrameRateLimit(const float fps = 60.f)
      : mStart(std::chrono::steady_clock::now())
      , mLimit(fps > 0.f ? 1.f / fps : 0.f)
      , mDuration(std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<float>(mLimit))) {
    }

    void update() {
      if (mLimit > 0.f) {
        std::chrono::steady_clock::duration elapsed = std::chrono::steady_clock::now() - mStart;
        std::this_thread::sleep_for(mDuration - elapsed);
        mStart = std::chrono::steady_clock::now();
      }
    }

    const float getMaxFrameRate() const {
      return mLimit;
    }

  private:
    std::chrono::steady_clock::time_point mStart;
    const float mLimit;
    const std::chrono::steady_clock::duration mDuration;
};

#endif /* FRAMERATELIMIT_HPP_ */
