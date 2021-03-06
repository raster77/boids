#ifndef INCLUDE_VECTOR2_HPP_
#define INCLUDE_VECTOR2_HPP_

#include <cmath>
#include <iostream>
#include <limits>

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  struct alignas(2 * sizeof(T)) Vector2 {

      Vector2()
        : x(0)
        , y(0) {
      }

      Vector2(const T v)
        : x(v)
        , y(v) {
      }

      Vector2(const T x, const T y)
        : x(x)
        , y(y) {
      }

      void set(const T v) {
        x = v;
        y = v;
      }

      void set(const T x, const T y) {
        this->x = x;
        this->y = y;
      }

      friend std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) {
        return os << "[" << v.x << ", " << v.y << "]";
      }

      Vector2<T> operator+(const Vector2<T>& v) const {
        return Vector2<T>(x + v.x, y + v.y);
      }

      Vector2<T> operator-(const Vector2<T>& v) const {
        return Vector2<T>(x - v.x, y - v.y);
      }

      Vector2<T> operator-() {
        return Vector2<T>(-x, -y);
      }

      Vector2<T> operator*(const Vector2<T>& v) const {
        return Vector2<T>(x * v.x, y * v.y);
      }

      template<typename U, typename = typename std::enable_if<std::is_arithmetic<U>::value, U>::type>
        Vector2<T> operator*(const U v) const {
          return Vector2<T>(x * static_cast<T>(v), y * static_cast<T>(v));
        }

      Vector2<T> operator/(const Vector2<T>& v) const {
        return Vector2<T>(x / v.x, y / v.y);
      }

      void operator+=(const Vector2<T>& v) {
        x += v.x;
        y += v.y;
      }

      void operator-=(const Vector2<T>& v) {
        x -= v.x;
        y -= v.y;
      }

      void operator*=(const Vector2<T>& v) {
        x *= v.x;
        y *= v.y;
      }

      template<typename U, typename = typename std::enable_if<std::is_arithmetic<U>::value, U>::type>
        void operator*=(const U v) {
          x *= v;
          y *= v;
        }

      void operator/=(const Vector2<T>& v) {
        x /= v.x;
        y /= v.y;
      }

      bool operator==(const Vector2<T>& v) {
        return x == v.x && y == v.y;
      }

      bool operator!=(const Vector2<T>& v) {
        return x != v.x || y != v.y;
      }

      bool operator<(const Vector2<T>& v) const {
        return x < v.x && y < v.y;
      }

      T lengthSquared() {
        return x * x + y * y;
      }

      T length() {
        return std::sqrt(lengthSquared());
      }

      void setLength(const T v) {
        *this = normalize() * v;
      }

      T distanceSquared(const Vector2<T>& v) const {
        const T dx = x - v.x;
        const T dy = y - v.y;
        return dx * dx + dy * dy;
      }

      T distance(const Vector2<T>& v) const {
        return std::sqrt(distanceSquared(v));
      }

      T dot(const Vector2<T>& v) {
        return x * v.x + y * v.y;
      }

      Vector2<T> normalize() {
        T l = length();
        return l > std::numeric_limits<T>::epsilon() ? Vector2<T>(x / l, y / l) : *this;
      }

      T x;
      T y;
  };

typedef Vector2<double> Vector2d;
typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;

#endif /* INCLUDE_VECTOR2_HPP_ */
