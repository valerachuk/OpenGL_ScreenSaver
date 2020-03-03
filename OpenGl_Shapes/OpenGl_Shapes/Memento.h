#pragma once
#include <string>
#include <memory>
#include "Interfaces.h"
#include "ShapeFactory.h" 
#include "ShapeUnion.h"
#include "Shape.h"

class Memento {
private:
	std::string _filePath;
	std::ofstream _outFile;
	std::ifstream _inFile;
	
	void serializeHelper(ICanvasComponent* item);
	
	ShapeUnion deserializeHelper();
	std::unique_ptr<Shape> createShapeFormStream(const std::string& type);
	void checkNextWord(const std::string& str);

	template<typename T>
	T readItem()
	{
		if (_inFile.eof())
			throw std::runtime_error("EOF reached, file is corrupted");

		T item;
		_inFile >> item;
		return item;
	}

public:
	explicit Memento(const std::string& filePath);
	void serialize(ShapeUnion* item);
	ShapeUnion deserialize();

};

