#pragma once
#include <string>
#include <memory>
#include "Shape.h"
#include "ShapeUnion.h"
#include "Interfaces.h"
#include "ShapeFactory.h"

class Memento {
private:
	std::string _filePath;
	std::ofstream _outFile;
	std::ifstream _inFile;
	
	void serializeHelper(ICanvasComponent* item);
	
	void deserializeHelper();
	std::unique_ptr<Shape> createShapeFormStream(const std::string& type, int& parentId);
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
	void serialize(ICanvasComponent* item);
	ShapeUnion deserialize();
	
};

