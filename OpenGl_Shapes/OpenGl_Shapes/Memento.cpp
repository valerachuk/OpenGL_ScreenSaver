#include "Memento.h"

Memento::Memento(const std::string& filePath) : _filePath(filePath) { }

void Memento::serialize(ICanvasComponent* item)
{
	std::ofstream file(_filePath);
	serializeHelper(item, file);
	file.close();
}

void Memento::serializeHelper(ICanvasComponent* item, std::ostream& stream) const
{
	Shape* shape = dynamic_cast<Shape*>(item);
	if (shape)
	{
		stream << " id " << shape->_id <<
			" type " << shape->_buffer->getName() <<
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
		throw std::invalid_argument("Can't be converted to Shape or ShapeUnion");
	}

	stream << " id " << shapeUnion->_id << " type union " << std::endl;

	shapeUnion->forEach([this, &stream, &shapeUnion](std::unique_ptr<ICanvasComponent>& iShapePtr) {
		stream << " parent " << shapeUnion->_id;
		serializeHelper(iShapePtr.get(), stream);
	});
}
