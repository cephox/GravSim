#include "vec2.h"

#include <cmath>

/*
 * Vec2d implementation
 */

Vec2d::Vec2d(): x(0), y(0) {}
Vec2d::Vec2d(double x, double y): x(x), y(y) {}

Vec2d Vec2d::fromAngle(double angle) {
	return Vec2d::fromAngle(angle, 1);
}
Vec2d Vec2d::fromAngle(double angle, double magnitude) {
	return Vec2d(magnitude * std::cos(angle), magnitude * std::sin(angle));
}

double Vec2d::dot(Vec2d &other) {
	return this->x * other.x + this->y * other.y;
}
double Vec2d::cross(Vec2d &other) {
	return this->x * other.y - this->y * other.x;
}

void Vec2d::zero() {
	this->x = 0;
	this->y = 0;
}

double Vec2d::magnitude() {
	return std::sqrt(this->magnitudeSq());
}

double Vec2d::magnitudeSq() {
	return this->x * this->x + this->y * this->y;
}

double Vec2d::distance(Vec2d& other) {
	return std::sqrt(this->distanceSq(other));
}

double Vec2d::distanceSq(Vec2d &other) {
	double dx = this->x - other.x;
	double dy = this->y - other.y;
	return dx * dx + dy * dy;
}

double Vec2d::angle() {
	return -std::atan2(-y, -x) + PI;
}

void Vec2d::normalize() {
	double mag = this->magnitude();
	this->operator/=(mag);
}

void Vec2d::setMagnitude(double magnitude) {
	this->normalize();
	this->operator*=(magnitude);
}

// Operator overloads
Vec2d Vec2d::operator+(Vec2d v) { return Vec2d(this->x + v.x, this->y + v.y); }
void Vec2d::operator+=(Vec2d v) { this->x += v.x; this->y += v.y; }

Vec2d Vec2d::operator-(Vec2d v) { return Vec2d(this->x - v.x, this->y - v.y); }
Vec2d Vec2d::operator-() { return Vec2d(-this->x, -this->y); }
void Vec2d::operator-=(Vec2d v) { this->x -= v.x; this->y -= v.y; }

Vec2d Vec2d::operator*(double scalar) { return Vec2d(this->x * scalar, this->y * scalar); }
void Vec2d::operator*=(double scalar) { this->x *= scalar; this->y *= scalar; }

Vec2d Vec2d::operator/(double scalar) { return Vec2d(this->x / scalar, this->y / scalar); }
void Vec2d::operator/=(double scalar) { this->x /= scalar; this->y /= scalar; }

bool operator==(const Vec2d& v1, const Vec2d& v2) {
	return v1.x == v2.x && v1.y == v2.y;
}
