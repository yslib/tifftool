
#ifndef _UTILS_H_
#define _UTILS_H_

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


	using Vec3i = Vec3<int>;
	using Vec2i = Vec2<int>;
	using Size3 = Vec3<size_t>;
	using Size2 = Vec2<size_t>;

}
#endif
