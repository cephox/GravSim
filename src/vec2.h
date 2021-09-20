#pragma once

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164

class Vec2d {
public:
	double x;
	double y;

	Vec2d();
	Vec2d(const Vec2d& v);
	Vec2d(double x, double y);

	static Vec2d fromAngle(double angle);
	static Vec2d fromAngle(double angle, double magnitude);

	double dot(Vec2d& other);
	double cross(Vec2d& other);

	void zero();

	double magnitude();
	double magnitudeSq();

	double distance(Vec2d& other);
	double distanceSq(Vec2d& other);

	double angle();
	void setAngle(float rad);

	void normalize();
	void setMagnitude(double magnitude);

	Vec2d operator+(Vec2d v);
	void operator+=(Vec2d v);

	Vec2d operator-(Vec2d v);
	Vec2d operator-();
	void operator-=(Vec2d v);

	Vec2d operator*(double scalar);
	void operator*=(double scalar);

	Vec2d operator/(double divisor);
	void operator/=(double divisor);

	friend bool operator==(const Vec2d& v1, const Vec2d& v2);
};
