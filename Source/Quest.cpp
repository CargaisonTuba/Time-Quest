#include "Quest.h"

Quest::Quest(std::string qName, int type, std::vector<int> const& list)
{
	_questID = rand() % 1000;
	_type = type;
	_list = list;
	_questName = qName;
}

Quest::~Quest()
{

}

int Quest::getType() const {
	return _type;
}

std::vector<int> Quest::getList() const {
	return _list;
}

std::string Quest::getName() const {
	return _questName;
}

bool Quest::isFinished() const {
	return _finished;
}

void Quest::setFinished() {
	_finished = true;
}

void Quest::setDoneIndex(int index) {
	if (index < _list.size()) {
		_listFinished.push_back(_list[index]);
		_list.erase(_list.begin() + index);
	}
}