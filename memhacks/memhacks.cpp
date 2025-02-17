﻿#include <iostream>
#include "memhacks.h"

using namespace std;

A::A() : foo(42), a_s("It's a!") {}

B::B() : b_s("It's b!") {
	for (auto i = 0; i < sizeof(data) / sizeof(data[0]); i++)
		data[i] = i * 2.0;
}

/// <summary>
/// Выводит на экран адреса и размеры объекта типа <see cref="B"/> и его содержимого.
/// Можно модифицировать для собственных отладочных целей.
/// </summary>
/// <param name="b">Изучаемый объект</param>
void printInternals(const B& b) {
	const A* a = &b;
	cout << "Address of b is 0x" << &b << ", address of b.a_s is 0x" << &b.a_s << ", address of b.b_s is 0x" << &b.b_s << endl;
	cout << "Size of A is " << sizeof(A) << ", size of B is " << sizeof(B) << endl;
	cout << "B string is '" << b.getBString() << "'" << endl;
	cout << "B data: "; b.printData(cout); cout << endl;
	cout << "B data: "; b.printData2(cout); cout << endl;
}

/// <summary>
/// Извлекает значение <see cref="B::b_s"/> из текущего объекта.
/// Подразумевается, что текущий объект на самом деле представлено классом <see cref="B"/>.
/// </summary>
/// <returns>Значение B::b_s</returns>
string A::getBString() const {
	return *((string*)(this + 1));
}

/// <summary>
/// Извлекает значения <see cref="A::a_s"/>, <see cref="B::b_s"/> и <see cref="B::data"/>
/// из текущего объекта и выводит их в текстовом виде в указанный выходной поток
/// с помощью адресной арифметики.
/// Подразумевается, что текущий объект на самом деле представлено классом <see cref="B"/>.
/// </summary>
void A::printData(ostream& os) const {
	os << "a_s is " << a_s << std::endl;
	os << "b_s is " << getBString() << endl;
	float* b_Data = ((float*)(((string*)(this + 1)) + 1));
	os << "data is: ";
	for (auto i = 0; i < sizeof(b_Data) - 1; i++)
	{
		os << b_Data[i] << " ";
	}
	os << endl;
}
/// <summary>
/// Извлекает значения <see cref="A::a_s"/>, <see cref="B::b_s"/> и <see cref="B::data"/>
/// из текущего объекта и выводит их в текстовом виде в указанный выходной поток
/// с помощью виртуальных функций, предусмотренных в классе <see cref="A"/>.
/// </summary>
void A::printData2(ostream& os) const {
	os << "a_s is " << a_s << std::endl;
	os << "b_s is " << *getBStr() << std::endl;
	const float* b_Data = getBData();
	os << "data is: ";
	for (auto i = 0; i < sizeof(b_Data) - 1; i++)
	{
		os << b_Data[i] << " ";
	}
	os << std::endl;
}


int main()
{
	B b;
	printInternals(b);
	return 0;
}