#include "ParseObject.h"


//---- Child Elements ----
#include "ParseObjList.h"


ParseObject::ParseObject() : ParseGroup("ObjGroup")
{
	for (int i = 0; i < 8; ++i)
		addElement(new ParseObjList(i));
}

bool ParseObject::match(std::string tag)
{
	if (tag == "obj" || tag == "Object")
		return true;
	return false;
}
