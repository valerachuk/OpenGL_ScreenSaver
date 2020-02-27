#pragma once
#include <iostream>
#include "Shape.h"

class Memento {
public:
	void serialize(std::istream&, const Shape*);
	void deserialize(std::ostream&, const Shape*);
};