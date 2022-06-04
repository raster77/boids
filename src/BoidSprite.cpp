#include <BoidSprite.hpp>
#include <SFML/System/Angle.hpp>
#include <algorithm>

BoidSprite::BoidSprite()
  : mPosition({0.f, 0.f})
  , lastPosition({0.f, 0.f})
  , mSize(3.f)
  , mBoidPtr(nullptr)
  , mShowTrail(true) {
}

BoidSprite::BoidSprite(Boid* b)
  : mPosition({0.f, 0.f})
  , lastPosition({0.f, 0.f})
  , mSize(b->getRadius())
  , mBoidPtr(b)
  , mShowTrail(true) {
}

BoidSprite::~BoidSprite() {
}

void BoidSprite::setColor(const sf::Color& c) {
  for (auto &v : mVertices)
    v.color = c;
}

const std::array<sf::Vertex, 3>& BoidSprite::getVertices() const {
  return mVertices;
}

const std::array<sf::Vertex, 300>& BoidSprite::getTrailVertices() const {
  return mTrailVertices;
}

const sf::FloatRect& BoidSprite::getBoundingBox() const {
  return mBoundingBox;
}

void BoidSprite::update() {
  if (mBoidPtr != nullptr) {
    mPosition = toSfVec(mBoidPtr->getPosition());
    updateVertices();
    if (mShowTrail)
      updateTrail();
  }
}

void BoidSprite::updateTrail() {
  std::rotate(mTrailVertices.begin(), mTrailVertices.end() - 6, mTrailVertices.end());
  const float sz = 1.5f;
  sf::Vector2f p = lastPosition / 3.f;
  mTrailVertices[0].position = p + sf::Vector2f(-sz, -sz);
  mTrailVertices[1].position = p + sf::Vector2f(sz, -sz);
  mTrailVertices[2].position = p + sf::Vector2f(sz, sz);
  mTrailVertices[3].position = p + sf::Vector2f(sz, sz);
  mTrailVertices[4].position = p + sf::Vector2f(-sz, sz);
  mTrailVertices[5].position = p + sf::Vector2f(-sz, -sz);
  sf::Color c = mVertices[0].color;
  int alpha = 200;
  for (std::size_t i = 0; i < mTrailVertices.size(); i += 4) {
    c.a = alpha;
    for (std::size_t j = 0; j < 4; ++j) {
      mTrailVertices[i + j].color = c;
    }
    alpha = alpha - 4 >= 0 ? alpha - 4 : 0;
  }
}

void BoidSprite::updateVertices() {
  Vector2f dir = mBoidPtr->getVelocity();
  dir = dir.normalize();
  const sf::Angle angle = sf::radians(std::atan2(dir.y, dir.x));
  sf::Transform t;
  sf::Vector2f offset(mSize * 0.25f, mSize * 0.25f);
  t.translate(mPosition + offset);
  t.rotate(angle);
  t.scale(sf::Vector2f(2, 1) * mSize);

  mVertices[0].position = t.transformPoint(sf::Vector2f(0, 0));
  mVertices[1].position = t.transformPoint(sf::Vector2f(0, 2));
  mVertices[2].position = t.transformPoint(sf::Vector2f(1, 1));

  lastPosition = sf::Vector2f(0.f, 0.f);
  for (auto &v : mVertices) {
    lastPosition += v.position;
  }

  float left = mVertices[0].position.x;
  float top = mVertices[0].position.y;
  float right = mVertices[0].position.x;
  float bottom = mVertices[0].position.y;

  for (std::size_t i = 1; i < mVertices.size(); ++i) {
    sf::Vector2f position = mVertices[i].position;

    // Update left and right
    if (position.x < left)
      left = position.x;
    else if (position.x > right)
      right = position.x;

    // Update top and bottom
    if (position.y < top)
      top = position.y;
    else if (position.y > bottom)
      bottom = position.y;
  }

  mBoundingBox = sf::FloatRect(sf::Vector2f(left, top),
                               sf::Vector2f(right - left, bottom - top));
  mLineVertices[0].position = sf::Vector2f(
      mBoundingBox.left + mBoundingBox.width * 0.5f,
      mBoundingBox.top + mBoundingBox.height * 0.5f);
  mLineVertices[1].position = mLineVertices[0].position + toSfVec(dir * 100.f);
}

sf::Vector2f BoidSprite::toSfVec(const Vector2f& v) {
  return sf::Vector2f(v.x, v.y);
}

void BoidSprite::showTrail(const bool v) {
  mShowTrail = v;
  if (mShowTrail) {
    update();
  }
}
void BoidSprite::setBoid(Boid* b) {
  mBoidPtr = b;
  mSize = b->getRadius();
}

void BoidSprite::render(sf::RenderWindow* window) {
  window->draw(mVertices.data(), mVertices.size(), sf::Triangles);
  if (mShowTrail)
    window->draw(mTrailVertices.data(), mTrailVertices.size(), sf::Triangles);
  window->draw(mLineVertices.data(), mLineVertices.size(), sf::Lines);
}
