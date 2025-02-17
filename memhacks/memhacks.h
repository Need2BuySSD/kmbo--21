﻿#pragma once

#include <ostream>
#include <string>

class B;	// чтобы можно было объявить printInternals() как friend в классе A

class A {
	std::string a_s;
	int foo;
	friend void printInternals(const B&);
public:
	A();
	std::string getBString() const;
	void printData(std::ostream& os) const;
	void printData2(std::ostream& os) const;
	virtual const std::string* getBStr() const = 0;
	virtual const float* getBData() const = 0;
};

class B : public A {
	std::string b_s;
	float data[7];
	friend void printInternals(const B&);
public:
	B();
	virtual const std::string* getBStr() const { return &b_s; }
	virtual const float* getBData() const { return data; }
};

void printInternals(const B& b);
