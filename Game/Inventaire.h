#pragma once
#include "Item.h"
#include "Slot.h"
#include <iostream>

#define NB_SLOT 5

class Inventaire {
public:

	Slot aSlots[NB_SLOT];

	Inventaire();
	Slot getSlot(int pEmplacement);

	void take(Item pItem);
	void drop(Item pItem);
};
