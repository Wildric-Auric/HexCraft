#include "Item.h"
#include "Slot.h"

Slot::Slot() {
}

Item Slot::getItem() {
	return this->aItem;
}
int Slot::getQuantit�() {
	return this->aQuantit�;
}

void Slot::setItem(Item pItem) {
	this->aItem = pItem;
}
void Slot::setQuantiti�(int pQuantit�) {
	this->aQuantit� = pQuantit�;
}

bool Slot::isFull() {
	if (this->aQuantit� == this->aItem.getMaxStack()) {
		return 1;
	}
	else {
		return 0;
	}
}
bool Slot::isEmpty() {
	if (this->aQuantit� == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
