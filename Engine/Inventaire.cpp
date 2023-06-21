#include "Inventaire.h"
#include "Slot.h"

Inventaire::Inventaire() {
}

Slot Inventaire::getSlot(int pEmplacement) {
	return this->aSlots[pEmplacement];
}

void Inventaire::take(Item pItem) { //a faire + tard
	int a = 0;
}
void Inventaire::drop(Item pItem) { //a faire + tard
	int b = 0;
}