#pragma once
#include "Vector2.h"

template <typename T>
class Vector3
{
public:
	// X要素
	T x;

	// Y要素
	T y;

	// Z要素
	T z;


	// コンストラクタ
	Vector3() {
		x = T(0);
		y = T(0);
		z = T(0);
	}
	Vector3(const T& i) {
		x = i;
		y = i;
		z = i;
	}
	Vector3(const T& x, const T& y, const T& z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3(const Vector2<T>& vec) {
		x = vec.x;
		y = vec.y;
		z = T(0);
	}
	Vector3(const Vector2<T>& vec, const T& i) {
		x = vec.x;
		y = vec.y;
		z = i;
	}
	// デストラクタ
	~Vector3() {
	}

	// 長さ
	T Length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	// 内積
	T Dot(const Vector3<T> & vec) const {
		return (x * vec.x + y * vec.y + z * vec.z);
	}

	// 距離
	T Distance(const Vector3<T> & vec) const {
		return std::sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z));
	}

	// 正規化
	Vector3<T> Normalized(const Vector3<T> & vec) const {
		return Vector3(x / Length(), y / Length(), z / Length());
	}

	// 演算子オーバーロード

	bool operator==(const T & i) const {
		return (x == i && y == i && z == i);
	}
	bool operator!=(const T & i) const {
		return !(x == i && y == i && z == i);
	}
	bool operator==(const Vector3<T> & vec) const {
		return (x == vec.x && y == vec.y && z == vec.z);
	}
	bool operator!=(const Vector3<T> & vec) const {
		return !(x == vec.x && y == vec.y && z == vec.z);
	}

	bool operator<(const T & i) const {
		return (x < i && y < i && z < i);
	}
	bool operator>(const T & i) const {
		return (x > i && y > i && z > i);
	}
	bool operator<(const Vector3<T> & vec) const {
		return (x < vec.x && y < vec.y && z < vec.z);
	}
	bool operator>(const Vector3<T> & vec) const {
		return (x > vec.x && y > vec.y && z > vec.z);
	}

	bool operator<=(const T & i) const {
		return (x <= i && y <= i && z <= i);
	}
	bool operator>=(const T & i) const {
		return (x >= i && y >= i && z >= i);
	}
	bool operator<=(const Vector3<T> & vec) const {
		return (x <= vec.x && y <= vec.y && z <= vec.z);
	}
	bool operator>=(const Vector3<T> & vec) const {
		return (x >= vec.x && y >= vec.y && z >= vec.z);
	}

	void operator=(const T & i) {
		x = i;
		y = i;
		z = i;
	}
	void operator+=(const T & i) {
		x += i;
		y += i;
		z += i;
	}
	void operator-=(const T & i) {
		x -= i;
		y -= i;
		z -= i;
	}
	void operator*=(const T & i) {
		x *= i;
		y *= i;
		z *= i;
	}
	void operator/=(const T & i) {
		x /= i;
		y /= i;
		z /= i;
	}
	void operator=(const Vector3<T> & vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}
	void operator+=(const Vector3<T> & vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}
	void operator-=(const Vector3<T> & vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
	}
	void operator*=(const Vector3<T> & vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
	}
	void operator/=(const Vector3<T> & vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
	}

	Vector3<T> operator+() const {
		return *this;
	}
	Vector3<T> operator-() const {
		return Vector3<T>(-x, -y, -z);
	}

	Vector3<T> operator+(const T & i) const {
		return Vector3<T>(x + i, y + i, z + i);
	}
	Vector3<T> operator-(const T & i) const {
		return Vector3<T>(x - i, y - i, z - i);
	}
	Vector3<T> operator*(const T & i) const {
		return Vector3<T>(x * i, y * i, z * i);
	}
	Vector3<T> operator/(const T & i) const {
		return Vector3<T>(x / i, y / i, z / i);
	}
	Vector3<T> operator+(const Vector3<T> & vec) const {
		return Vector3<T>(x + vec.x, y + vec.y, z + vec.z);
	}
	Vector3<T> operator-(const Vector3<T> & vec) const {
		return Vector3<T>(x - vec.x, y - vec.y, z - vec.z);
	}
	Vector3<T> operator*(const Vector3<T> & vec) const {
		return Vector3<T>(x * vec.x, y * vec.y, z * vec.z);
	}
	Vector3<T> operator/(const Vector3<T> & vec) const {
		return Vector3<T>(x / vec.x, y / vec.y, z / vec.z);
	}
};

template<typename T>
Vector3<T> operator+(const T & i, const Vector3<T> & vec) {
	return Vector3<T>(i + vec.x, i + vec.y, i + vec.z);
}
template<typename T>
Vector3<T> operator-(const T & i, const Vector3<T> & vec) {
	return Vector3<T>(i - vec.x, i - vec.y, i - vec.z);
}
template<typename T>
Vector3<T> operator*(const T & i, const Vector3<T> & vec) {
	return Vector3<T>(i * vec.x, i * vec.y, i * vec.z);
}
template<typename T>
Vector3<T> operator/(const T & i, const Vector3<T> & vec) {
	return Vector3<T>(i / vec.x, i / vec.y, i / vec.z);
}

typedef Vector3<int> Vec3;
typedef Vector3<float> Vec3f;

inline DirectX::XMFLOAT2 Convert2(const Vec3f & vec) {
	return DirectX::XMFLOAT2(vec.x, vec.y);
}
inline DirectX::XMFLOAT3 Convert3(const Vec3f & vec) {
	return DirectX::XMFLOAT3(vec.x, vec.y, vec.z);
}