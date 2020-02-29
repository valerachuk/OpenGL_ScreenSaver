#pragma once
#include <string>
#include "Shape.h"
#include "ShapeUnion.h"
#include "Interfaces.h"

class Memento {
private:
	std::string _filePath;
	void serializeHelper(ICanvasComponent* item, std::ostream& stream) const;

public:
	Memento(const std::string& filePath);
	void serialize(ICanvasComponent* item);
};