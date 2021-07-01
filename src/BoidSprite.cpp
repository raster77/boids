#include <BoidSprite.hpp>

BoidSprite::BoidSprite()
  : mPosition({0.f, 0.f})
  , lastPosition({0.f, 0.f})
  , mShowTrail(true)
{
  for(auto& v : mTrailVertices)
  {
    v.position = sf::Vector2f(-100.f, -100.f);
  }
}

BoidSprite::~BoidSprite()
{
}

void BoidSprite::setColor(const sf::Color& c)
{
  for(auto& v : mVertices)
    v.color = c;
}

const std::array<sf::Vertex, 3>& BoidSprite::getVertices() const
{
  return mVertices;
}

const std::array<sf::Vertex, 200>& BoidSprite::getTrailVertices() const
{
  return mTrailVertices;
}

const sf::FloatRect& BoidSprite::getBoundingBox() const
{
  return mBoundingBox;
}

void BoidSprite::update(const Boid& b)
{
  mPosition = toSfVec(b.getPosition());
  updateVertices(b);
  if(mShowTrail)
    updateTrail();
}


void BoidSprite::updateTrail()
{
  std::rotate(mTrailVertices.begin(), mTrailVertices.end() - 4, mTrailVertices.end());
  const float sz = 2.f;
  sf::Vector2f p = lastPosition;//toSfVec(lastPosition) + sf::Vector2f(sz, sz) * 0.5f;
  mTrailVertices[0].position = p;
  mTrailVertices[1].position = p + sf::Vector2f(sz, 0);
  mTrailVertices[2].position = p + sf::Vector2f(sz, sz);
  mTrailVertices[3].position = p + sf::Vector2f(0, sz);
  sf::Color c = mVertices[0].color;
  int alpha = 200;
  for(std::size_t i = 0; i < mTrailVertices.size(); i+=4)
  {
	c.a = alpha;
	for(std::size_t j = 0; j < 4; ++j)
	{
	  mTrailVertices[i + j].color = c;
	}
	alpha  = alpha - 4 >= 0 ? alpha - 4 : 0;

  }
}

void BoidSprite::updateVertices(const Boid& b)
{
  Vector2f dir = b.getVelocity();
  dir = dir.normalize();

  const float angle = std::atan2(dir.y, dir.x) * RAD;
  sf::Transform t;
  t.translate(mPosition);
  t.rotate(angle);
  t.scale(sf::Vector2f(3, 1) * 3.f);

  mVertices[0].position = t.transformPoint(sf::Vector2f(0, 0));
  mVertices[1].position = t.transformPoint(sf::Vector2f(0, 2));
  mVertices[2].position = t.transformPoint(sf::Vector2f(1, 1));

  lastPosition = sf::Vector2f(0.f, 0.f);
  for(auto& v : mVertices)
  {
    lastPosition += v.position;
  }

  lastPosition /= 3.f;

  float left = mVertices[0].position.x;
  float top = mVertices[0].position.y;
  float right = mVertices[0].position.x;
  float bottom = mVertices[0].position.y;

  for (std::size_t i = 1; i < mVertices.size(); ++i)
  {
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

  mBoundingBox = sf::FloatRect(left, top, right - left, bottom - top);
}

sf::Vector2f BoidSprite::toSfVec(const Vector2f& v)
{
  return sf::Vector2f(v.x, v.y);
}
