#pragma once
class shop
{
public:
	void refresh();
	void choseItem();
	void addItem();
	void unavailableItem(int item); // When player had already buy a item or don't have money to buy it.
	void availableItem(int item); // When player can buy a item.
	shop();
	~shop();
};

