#include "Vector2.h"
#include <math.h>

Vector2::Vector2(){
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(float x, float y){
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2& v){
	this->x = v.x;
	this->y = v.y;
}

Vector2::~Vector2(){}

double Vector2::Lenght(){
	return sqrt(this->x * this->x + this->y * this->y);
}

double Vector2::LenghtSquared(){
	return (this->x * this->x + this->y * this->y);
}

double Vector2::DotProduct(const Vector2& a, const Vector2& b){
	return a.x * b.x + a.y * b.y;
}

Vector2 Vector2::Normalized(){
	double lenght = Lenght();
	Vector2 normal(2, 2);
	if (lenght != 0) {
		normal.x = this->x / lenght;
		normal.y = this->y / lenght;
	}
	return normal;
}

//VECTOR <-> VECTOR OPERATORS
Vector2& Vector2::operator=(const Vector2& v){
	if (this != &v) {
		this->x = v.x;
		this->y = v.y;
	}
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& v){
	this->x = this->x + v.x;
	this->y = this->y + v.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v){
	this->x = this->x - v.x;
	this->y = this->y - v.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& v){
	Vector2 temp(*this);
	temp += v;
	return temp;
}

Vector2 Vector2::operator-(const Vector2& v){
	Vector2 temp(*this);
	temp -= v;
	return temp;
}

//VECTOR <-> FLOAT OPERATORS

Vector2& Vector2::operator*=(float j){
	this->x *= j;
	this->y *= j;

	return *this;
}

Vector2& Vector2::operator/=(float j){
	this->x /= j;
	this->y /= j;

	return *this;
}

Vector2 operator*(const Vector2& v, float j){
	Vector2 temp(v);
	temp *= j;

	return temp;
}

Vector2 operator*(const float j, const Vector2& v){
	Vector2 temp(v);
	temp *= j;

	return temp;
}

Vector2 operator/(const Vector2& v, float j){
	Vector2 temp(v);
	temp /= j;

	return temp;
}

Vector2 operator/(const float j, const Vector2& v){
	Vector2 temp(v);
	temp /= j;

	return temp;
}

//VECTOR <-> INT OPERATORS

Vector2& Vector2::operator*=(int j) {
	this->x *= j;
	this->y *= j;

	return *this;
}

Vector2& Vector2::operator/=(int j) {
	this->x /= j;
	this->y /= j;

	return *this;
}

Vector2 operator*(const Vector2& v, int j){
	Vector2 temp(v);
	temp *= j;

	return temp;
}

Vector2 operator*(const int j, const Vector2& v){
	Vector2 temp(v);
	temp *= j;

	return temp;
}

Vector2 operator/(const Vector2& v, int j){
	Vector2 temp(v);
	temp /= j;

	return temp;
}

Vector2 operator/(const int j, const Vector2& v){
	Vector2 temp(v);
	temp /= j;

	return temp;
}

