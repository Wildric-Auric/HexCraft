#include "Item.h"
#include <iostream>

Item::Item() {
}

Item::Item(std::string pNomItem, int pMaxStack) {
	this->nomItem = pNomItem;
	this->maxStack = pMaxStack;
}
Item::Item(int pId) {
	this->Id = pId;
}

int Item::getMaxStack() {
	return this->maxStack;
}
int Item::getDurete() {
	return this->aDurete;
}

void Item::setDurete(int pDurete) {
	this->aDurete = pDurete;
}

