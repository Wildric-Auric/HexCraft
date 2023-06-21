#include "Item.h"
#include "Slot.h"

Slot::Slot() {
}

Item Slot::getItem() {
	return this->aItem;
}
int Slot::getQuantité() {
	return this->aQuantité;
}

void Slot::setItem(Item pItem) {
	this->aItem = pItem;
}
void Slot::setQuantitié(int pQuantité) {
	this->aQuantité = pQuantité;
}

bool Slot::isFull() {
	if (this->aQuantité == this->aItem.getMaxStack()) {
		return 1;
	}
	else {
		return 0;
	}
}
bool Slot::isEmpty() {
	if (this->aQuantité == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
