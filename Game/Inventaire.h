#pragma once
#include "Item.h"
#include "Slot.h"
#include <iostream>

class Inventaire {
public:
	static const int nbSlots = 5;
	Slot aSlots[nbSlots];

	Inventaire();

	Slot getSlot(int pEmplacement);

	void take(Item pItem);
	void drop(Item pItem);
};
