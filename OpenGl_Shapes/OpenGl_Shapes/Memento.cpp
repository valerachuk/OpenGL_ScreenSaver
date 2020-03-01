#include "memento.h"

memento::memento(const std::string& filepath) : _filepath(filepath) { }

void memento::serialize(icanvascomponent* item)
{
	_outfile.open(_filepath);
	serializehelper(item);
	_outfile.close();
}

std::unique_ptr<shape> memento::createshapeformstream(const std::string& type, int& parentid)
{
	auto shapeunq = std::unique_ptr<shape>(shapefactory::getshape(type));
	if (!shapeunq)
	{
		throw std::runtime_error("file: " + _filepath + "is corrupter");
	}
	
	checknextword("id");
	shapeunq->setid(readitem<int>());

	checknextword("scale");
	glm::vec2 scale(0.0f);
	scale.x = readitem<float>();
	scale.y = readitem<float>();
	shapeunq->setscale(scale);
	
	checknextword("pos");
	glm::vec2 position(0.0f);
	position.x = readitem<float>();
	position.y = readitem<float>();
	shapeunq->setpos(position);

	checknextword("color");
	glm::vec4 color(0.0f);
	color.r = readitem<float>();
	color.g = readitem<float>();
	color.b = readitem<float>();
	color.a = readitem<float>();
	shapeunq->setcolor(color);

	checknextword("isdeformed");
	shapeunq->setdeformed(readitem<bool>());
	
	checknextword("ishidden");
	shapeunq->sethidden(readitem<bool>());
	
	checknextword("hastrail");
	shapeunq->settrail(readitem<bool>());

	return shapeunq;
}

void memento::checknextword(const std::string& str)
{
	if (_infile.eof())
		throw std::runtime_error("eof reached, file " + _filepath + " is corrupted");
	
	std::string newstr;
	_infile >> newstr;

	if (newstr != str)
		throw std::invalid_argument("string mismatch: " + str + " != " + newstr);
}

void memento::serializehelper(icanvascomponent* item)
{
	shape* shape = dynamic_cast<shape*>(item);
	if (shape)
	{
		_outfile << 
			" type " << shape->_buffer->getname() <<
			" id " << shape->_id <<
			" scale " << shape->_scale.x << " " << shape->_scale.y <<
			" pos " << shape->_position.x << " " << shape->_position.y <<
			" color " << shape->_color.r << " " << shape->_color.g << " " << shape->_color.b << " " << shape->_color.a <<
			" isdeformed " << shape->_isdeformed <<
			" ishidden " << shape->_ishidden <<
			" hastrail " << shape->_hastrail <<
			std::endl;
		return;
	}

	auto shapeunion = dynamic_cast<shapeunion*>(item);

	if (!shapeunion)
	{
		throw std::invalid_argument("can't be converted to shape or shapeunion");
	}

	_outfile << 
		" type union " << 
		" id " << shapeunion->_id << 
		std::endl;

	shapeunion->foreach([this, &shapeunion](std::unique_ptr<icanvascomponent>& ishapeptr) {
		_outfile << " parent " << shapeunion->_id;
		serializehelper(ishapeptr.get());
	});
}