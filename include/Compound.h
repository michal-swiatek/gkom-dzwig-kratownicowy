#ifndef COMPOUND_H
#define COMPOUND_H

#include "Object.h"
#include <vector>

class Compound{
protected:
	std::vector<std::unique_ptr<Object>> objects;

public:
	void addObject(std::unique_ptr<Object> object) {
		objects.push_back(object);
	}





};




#endif // !COMPOUND_H