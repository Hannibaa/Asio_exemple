#include <iostream>
#include <thread>
#include <future>
#include "MyLib/Console_Library/escape_code.h"

using namespace std::chrono_literals;

void work1() {
	std::this_thread::sleep_for(30ms);
}

void work2() {

}

enum class Unite {
	Length,
	Weight,
	Time,
};

enum class Mesure{
	meter,
	millimeter,
	centimeter,
};

template<typename T, Unite unite, Mesure U>
struct Quantity {
	T value;

	operator T& () { return value; }

	Quantity& operator = (T val) {
		this->value = val;
		return *this;
	}
};

int main()
{
	Quantity<float, Unite::Length, Mesure::meter> l;

	l = 234234;

	print_ << l << end_;


	std::cin.get();
	return 0;
}