#pragma once

template<typename T>
class Vector
{
private:
	T x;
	T y;

public:
	Vector(T x, T y) :x(x), y(y) {}; // �ش� ������ ȣ���� �����ش�.
	//Vector(const T& _x, const T& _y) : x(_x), y(_y){}
	Vector() : Vector((T)0, (T)0) {};
	Vector(const Vector& other) = default;
	~Vector() {};

	void set(T x, T y) { this->x = x; this->y = y; }

	auto operator+(const Vector& other) const
	{
		return Vector{ this->x + other.x, this->y + other.y };
	}

	template<typename S>
	auto operator*(S scale) const {
		return Vector{ static_cast<T>(this->x * scale), static_cast<T>(this->y * scale) };
	}

	auto operator-(const Vector& other) const
	{
		return this + other * (-1);
	}

public:
	



};

