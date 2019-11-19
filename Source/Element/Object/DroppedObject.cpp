#include "DroppedObject.h"

DroppedObject::DroppedObject() {
	_id = 0;
}

DroppedObject::~DroppedObject() {

}

int DroppedObject::getID() const {
	return _id;
}

sf::Vector2f DroppedObject::getPosition() const {
	return _sprite.getPosition();
}

sf::FloatRect DroppedObject::getHitbox() {
	_sprite.setTexture(_text);
	return _sprite.getGlobalBounds();
}

void DroppedObject::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{

}
