#pragma once
#include <iostream>
#include <vector>

#define TYPE_KILL 0
#define TYPE_FIND 1

class Quest
{
public:
	Quest(std::string qName, int type, std::vector<int> const& list);
	~Quest();

	int getType() const;
	std::vector<int> getList() const;
	bool isFinished() const;
	std::string getName() const;

	void setFinished();
	void setDoneIndex(int index);

private:
	int _questID;
	std::string _questName;
	int _type;
	std::vector<int> _list, _listFinished;
	bool _finished;
};
