#pragma once
class Vector2{
public:
	double x;
	double y;

	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2&);
	~Vector2();

	double Lenght();
	double LenghtSquared();
	static double DotProduct(const Vector2& a, const Vector2& b);
	Vector2 Normalized();

	Vector2& operator =(const Vector2& v);

	Vector2& operator +=(const Vector2& v);
	Vector2& operator -=(const Vector2& v);
	Vector2 operator +(const Vector2& v);
	Vector2 operator -(const Vector2& v);

	Vector2& operator *= (const float j);
	Vector2& operator /= (const float j);
	friend Vector2 operator *(const Vector2& v, const float j);
	friend Vector2 operator *(const float j, const Vector2& v);
	friend Vector2 operator /(const Vector2& v, const float j);
	friend Vector2 operator /(const float j, const Vector2& v);

	Vector2& operator *= (int j);
	Vector2& operator /= (int j);
	friend Vector2 operator *(const Vector2& v, int j);
	friend Vector2 operator *(const int j, const Vector2& v);
	friend Vector2 operator /(const Vector2& v, int j);
	friend Vector2 operator /(const int j, const Vector2& v);
};

