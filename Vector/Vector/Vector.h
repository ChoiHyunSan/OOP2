#pragma once

template<typename T>
class Vector
{
private:
	T x;
	T y;

public:
	Vector() : x((T)0.f), y((T)0.f) {};
	Vector(const T& _x, const T& _y) : x(_x),y(_y){}

	template<typename U>
	Vector(const Vector<U>& other) : Vector(static_cast<T>(other.X()), static_cast<T>(other.Y())) {}
	~Vector() {};

private:


public:
	void printValue() const
	{
		std::cout << "X: " << x << " " << "Y: " << y << std::endl;
	}

	Vector operator+(const Vector& other) const
	{
		return Vector(this->x + other.X(), this->y + other.Y());
	}

	template<typename U>
	Vector operator*(U scale) const
	{
		return Vector(this->x * static_cast<T>(scale), this->y * static_cast<T>(scale));
	}

	Vector operator*(const Vector& other) const
	{
		return Vector(this->x * other.X(), this->y * other.Y());
	}

	template<typename U>
	Vector operator/(U scale) const
	{
		return Vector(this->x / scale, this->y / scale);
	}

	Vector operator-(const Vector& other) const
	{
		return Vector(this->x - other.X(), this->y - other.Y());
	}


	T X() const { return x; }
	T Y() const { return y; }
};

