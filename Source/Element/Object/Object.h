#pragma once
class Object
{
public:
	Object();
	~Object();
	void setNextOne(Object &nextOne);
	bool isNextOneEqualTo(Object *comparedObject);
	bool update();

public:
	Object *_nextOne;

};

