#pragma once
#include <iostream>


class Item {
public:
	Item();
	Item(std::string pNomItem, int pMaxStack);
	Item(int pId);

	int getMaxStack();
	int getDurete();

	void setDurete(int pDurete);

private:
	int Id;
	std::string nomItem;
	int maxStack;
	int aDurete;
};

