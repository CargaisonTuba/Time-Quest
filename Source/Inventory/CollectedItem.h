#pragma once

class ColletedItem
{
public:
	ColletedItem(int id, std::string path);
	~ColletedItem();

private:
	int _id;
};
