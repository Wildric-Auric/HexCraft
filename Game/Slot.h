#pragma once
#include <unordered_map>
#include <iostream>
#include <cassert>
#include "Item.h"

class Slot {
public:
	Slot();

	Item getItem();
	int getQuantit�();

	void setItem(Item pItem);
	void setQuantiti�(int pQuantit�);

	bool isFull();
	bool isEmpty();

private:
	const Item nonItem = Item(0);

	Item aItem;
	int aQuantit�;
};
