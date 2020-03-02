#include "Memento.h"

Memento::Memento(const std::string& filePath) : _filePath(filePath) { }

void Memento::serialize(ICanvasComponent* item)
{
	_outFile.open(_filePath);
	if (!_outFile.is_open())
		throw std::runtime_error("Cannot open file: " + _filePath);
	
	serializeHelper(item);
	_outFile.close();
}

//ShapeUnion Memento::deserialize()
//{
//	_inFile.open(_filePath);
//	if (!_inFile.is_open())
//		throw std::runtime_error("Cannot open file: " + _filePath);
//
//	ShapeUnion toRet = deserializeHelper();
//
//	_inFile.close();
//
//	return toRet;
//}

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
//
//ShapeUnion Memento::deserializeHelper()
//{
//	ShapeUnion mainUnion;
//	mainUnion.setId(0);
//	
//	//read first line
//	checkNextWord("type");
//	checkNextWord("union");
//	checkNextWord("id");
//	mainUnion.setId(readItem<int>());
//	
//	while (!_inFile.eof())
//	{
//		checkNextWord("parent");
//		const int parentId = readItem<int>();
//		ShapeUnion* itemsParent = dynamic_cast<ShapeUnion*>(mainUnion.getById(parentId));
//		if (itemsParent == nullptr)
//			throw std::runtime_error("File reading error, new parent with id " + std::to_string(parentId) + " is not ShapeUnion");
//
//		checkNextWord("type");
//		const std::string type = readItem<std::string>();
//
//		if (type == "union")
//		{
//			std::unique_ptr<ICanvasComponent> newUnion = std::make_unique<ShapeUnion>();
//
//			checkNextWord("id");
//			const int newId = readItem<int>();
//			newUnion->setId(newId);
//			
//			itemsParent->add(newUnion);
//		}
//		else
//		{
//			std::unique_ptr<ICanvasComponent> newShape = createShapeFormStream(type);
//			itemsParent->add(newShape);
//		}
//	}
//
//	return mainUnion;
//}

std::unique_ptr<Shape> Memento::createShapeFormStream(const std::string& type)
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
	const std::string newStr = readItem<std::string>();
	if (newStr != str)
		throw std::invalid_argument("string mismatch: " + str + " != " + newStr);
}
