#pragma once
#include <cmath>
#include <DirectXMath.h>

template <typename T>
class Vector2
{
public:
	// X要素
	T x;
	// Y要素
	T y;


	// コンストラクタ
	Vector2() {
		x = T(0);
		y = T(0);
	}
	Vector2(const T& i) {
		x = i;
		y = i;
	}
	Vector2(const T& x, const T& y) {
		this->x = x;
		this->y = y;
	}
	// デストラクタ
	~Vector2() {
	}

	// 長さ
	T Length() const {
		return std::sqrt(x * x + y * y);
	}

	// 内積
	T Dot(const Vector2<T> & vec) const {
		return (x * vec.x + y * vec.y);
	}

	// 距離
	T Distance(const Vector2<T> & vec) const {
		return std::hypot(vec.x - x, vec.y - y);
	}

	// 正規化
	Vector2<T> Normalized() const {
		return Vector2<T>(x / Length(), y / Length());
	}

	// 演算子オーバーロード

	bool operator==(const T & i) const {
		return (x == i && y == i);
	}
	bool operator!=(const T & i) const {
		return !(x == i && y == i);
	}
	bool operator==(const Vector2<T> & vec) const {
		return (x == vec.x && y == vec.y);
	}
	bool operator!=(const Vector2<T> & vec) const {
		return !(x == vec.x && y == vec.y);
	}

	bool operator<(const T & i) const {
		return (x < i && y < i);
	}
	bool operator>(const T & i) const {
		return (x > i && y > i);
	}
	bool operator<(const Vector2<T> & vec) const {
		return (x < vec.x && y < vec.y);
	}
	bool operator>(const Vector2<T> & vec) const {
		return (x > vec.x && y > vec.y);
	}

	bool operator<=(const T & i) const {
		return (x <= i && y <= i);
	}
	bool operator>=(const T & i) const {
		return (x >= i && y >= i);
	}
	bool operator<=(const Vector2<T> & vec) const {
		return (x <= vec.x && y <= vec.y);
	}
	bool operator>=(const Vector2<T> & vec) const {
		return (x >= vec.x && y >= vec.y);
	}

	void operator=(const T & i) {
		x = i;
		y = i;
	}
	void operator+=(const T & i) {
		x += i;
		y += i;
	}
	void operator-=(const T & i) {
		x -= i;
		y -= i;
	}
	void operator*=(const T & i) {
		x *= i;
		y *= i;
	}
	void operator/=(const T & i) {
		x /= i;
		y /= i;
	}
	void operator=(const Vector2<T> & vec) {
		x = vec.x;
		y = vec.y;
	}
	void operator+=(const Vector2<T> & vec) {
		x += vec.x;
		y += vec.y;
	}
	void operator-=(const Vector2<T> & vec) {
		x -= vec.x;
		y -= vec.y;
	}
	void operator*=(const Vector2<T> & vec) {
		x *= vec.x;
		y *= vec.y;
	}
	void operator/=(const Vector2<T> & vec) {
		x /= vec.x;
		y /= vec.y;
	}

	Vector2<T> operator+() const {
		return *this;
	}
	Vector2<T> operator-() const {
		return Vector2<T>(-x, -y);
	}
	Vector2<T> operator+(const T & i) const {
		return Vector2<T>(x + i, y + i);
	}
	Vector2<T> operator-(const T & i) const {
		return Vector2<T>(x - i, y - i);
	}
	Vector2<T> operator*(const T & i) const {
		return Vector2<T>(x * i, y * i);
	}
	Vector2<T> operator/(const T & i) const {
		return Vector2<T>(x / i, y / i);
	}
	Vector2<T> operator+(const Vector2<T> & vec) const {
		return Vector2<T>(x + vec.x, y + vec.y);
	}
	Vector2<T> operator-(const Vector2<T> & vec) const {
		return Vector2<T>(x - vec.x, y - vec.y);
	}
	Vector2<T> operator*(const Vector2<T> & vec) const {
		return Vector2<T>(x * vec.x, y * vec.y);
	}
	Vector2<T> operator/(const Vector2<T> & vec) const {
		return Vector2<T>(x / vec.x, y / vec.y);
	}
};

template<typename T>
Vector2<T> operator+(const T & i, const Vector2<T> & vec) {
	return Vector2<T>(i + vec.x, i + vec.y);
}
template<typename T>
Vector2<T> operator-(const T & i, const Vector2<T> & vec) {
	return Vector2<T>(i - vec.x, i - vec.y);
}
template<typename T>
Vector2<T> operator*(const T & i, const Vector2<T> & vec) {
	return Vector2<T>(i * vec.x, i * vec.y);
}
template<typename T>
Vector2<T> operator/(const T & i, const Vector2<T> & vec) {
	return Vector2<T>(i / vec.x, i / vec.y);
}

typedef Vector2<int> Vec2;
typedef Vector2<float> Vec2f;

inline DirectX::XMFLOAT2 Convert2(const Vec2f & vec) {
	return DirectX::XMFLOAT2(vec.x, vec.y);
}
inline DirectX::XMFLOAT3 Convert3(const Vec2f & vec) {
	return DirectX::XMFLOAT3(vec.x, vec.y, 0.0f);
}