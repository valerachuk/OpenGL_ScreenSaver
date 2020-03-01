#include "Memento.h"

#include "ShapeFactory.h"

Memento::Memento(const std::string& filePath) : _filePath(filePath) { }

void Memento::serialize(ICanvasComponent* item)
{
	_outFile.open(_filePath);
	serializeHelper(item);
	_outFile.close();
}

void Memento::serializeHelper(ICanvasComponent* item)
{
	Shape* shape = dynamic_cast<Shape*>(item);
	if (shape)
	{
		_outFile << 
			" type " << shape->_buffer->getName() <<
			" id " << shape->_id <<
			" scale " << shape->_scale.x << " " << shape->_scale.y <<
			" pos " << shape->_position.x << " " << shape->_position.y <<
			" color " << shape->_color.r << " " << shape->_color.g << " " << shape->_color.b << " " << shape->_color.a <<
			" isDeformed " << shape->_isDeformed <<
			" isHidden " << shape->_isHidden <<
			" hasTrail " << shape->_hasTrail <<
			std::endl;
		return;
	}

	auto shapeUnion = dynamic_cast<ShapeUnion*>(item);

	if (!shapeUnion)
	{
		throw std::invalid_argument("can't be converted to shape or shapeUnion");
	}

	_outFile << 
		" type union " << 
		" id " << shapeUnion->_id << 
		std::endl;

	shapeUnion->forEach([this, &shapeUnion](std::unique_ptr<ICanvasComponent>& iShapePtr) {
		_outFile << " parent " << shapeUnion->_id;
		serializeHelper(iShapePtr.get());
	});
}

std::unique_ptr<Shape> Memento::createShapeFormStream(const std::string& type, int& parentId)
{
	auto shapeUnq = std::unique_ptr<Shape>(ShapeFactory::getShape(type));
	if (!shapeUnq)
	{
		throw std::runtime_error("file: " + _filePath + "is corrupter");
	}
	
	checkNextWord("id");
	shapeUnq->setId(readItem<int>());

	checkNextWord("scale");
	glm::vec2 scale(0.0f);
	scale.x = readItem<float>();
	scale.y = readItem<float>();
	shapeUnq->setScale(scale);
	
	checkNextWord("pos");
	glm::vec2 position(0.0f);
	position.x = readItem<float>();
	position.y = readItem<float>();
	shapeUnq->setPos(position);

	checkNextWord("color");
	glm::vec4 color(0.0f);
	color.r = readItem<float>();
	color.g = readItem<float>();
	color.b = readItem<float>();
	color.a = readItem<float>();
	shapeUnq->setColor(color);

	checkNextWord("isDeformed");
	shapeUnq->setDeformed(readItem<bool>());
	
	checkNextWord("isHidden");
	shapeUnq->setHidden(readItem<bool>());
	
	checkNextWord("hasTrail");
	shapeUnq->setTrail(readItem<bool>());

	return shapeUnq;
}


void Memento::checkNextWord(const std::string& str)
{
	if (_inFile.eof())
		throw std::runtime_error("EOF reached, file " + _filePath + " is corrupted");
	
	std::string newStr;
	_inFile >> newStr;
	if (newStr != str)

		throw std::invalid_argument("string mismatch: " + str + " != " + newStr);
}
