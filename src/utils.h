
#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <opencv2/core/matx.hpp>

namespace tiff
{
	template<typename T>
	struct Vec3
	{
		T x, y, z;
		Vec3() = default;
		Vec3(T x, T y, T z) :x(x), y(y), z(z) {}
		Vec3 operator+(const Vec3 & v)const { return Vec3{ x + v.x,y + v.y,z + v.z }; }
		Vec3 & operator+=(const Vec3 & v) { x += v.x; y += v.y; z += z.y; return *this; }
		Vec3 operator-(const Vec3 & v)const { return Vec3{ x - v.x,y - v.y,z - v.z }; }
		Vec3 & operator-=(const Vec3 & v) { x -= v.x; y -= v.y; z -= z.y; return *this; }
		Vec3 operator*(const Vec3 & v)const { return Vec3{ x*v.x,y*v.y,z*v.z }; }
		Vec3 & operator*=(const Vec3 & v) { x *= v.x; y *= v.y; z *= z.y; return *this; }
	};

	template<typename T>
	struct Vec2
	{
		T x, y;
		Vec2() = default;
		Vec2(T x, T y) :x(x), y(y) {}
		Vec2 operator+(const Vec2 & v)const { return Vec2{ x + v.x,y + v.y}; }
		Vec2 & operator+=(const Vec2 & v) { x += v.x; y += v.y; return *this; }
		Vec2 operator-(const Vec2 & v)const { return Vec2{ x - v.x,y - v.y }; }
		Vec2 & operator-=(const Vec2 & v) { x -= v.x; y -= v.y; return *this; }
		Vec2 operator*(const Vec2 & v)const { return Vec2{ x*v.x,y*v.y }; }
		Vec2 & operator*=(const Vec2 & v) { x *= v.x; y *= v.y; return *this; }
	};



	template<typename T>
	std::ostream & operator<<(std::ostream & os, const Vec3<T> & vec)
	{
		os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]\n";
		return os;
	}


	template<typename T>
	std::ostream & operator<<(std::ostream & os, const Vec2<T> & vec)
	{
		os << "[" << vec.x << ", " << vec.y<<"]\n";
		return os;
	}


	using Vec3i = Vec3<int>;
	using Vec2i = Vec2<int>;
	using Size3 = Vec3<size_t>;
	using Size2 = Vec2<size_t>;


	inline
		std::size_t
		Linear(const Vec3i &p, const Size2 &dimension)
	{
		return p.x + dimension.x*(p.y + p.z*dimension.y);
	}

	//inline std::size_t
	//Linear(const Vector3i &v, const Size2 &dimension)
	//{
	//	return Linear(Point3i{v.x,v.y,v.z},dimension);
	//}

	inline
		std::size_t
		Linear(const Vec2i &p, std::size_t width)
	{
		return p.x + p.y * width;
	}


}
#endif
