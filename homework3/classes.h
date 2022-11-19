#pragma once

#include <string>
#include <iostream>

class Product {
public:
	Product() {}

	~Product() {}

	void setProduct(std::string name, unsigned price, unsigned weight) {
		name_ = name;
		price_ = price;
		weight_ = weight;
	}

	std::string getProductName() {
		return name_;
	}

	unsigned getProductPrice() {
		return price_;
	}

	unsigned getProductWeight() {
		return weight_;
	}

private:
	std::string name_{};
	unsigned price_{};
	unsigned weight_{};
};

class Buy : public Product {
public:
	Buy() {}

	~Buy() {}

	void setBuy(unsigned amount) {
		amount_ = amount;
		totalPrice_ = this->getProductPrice() * amount;
		totalWeight_ = this->getProductWeight() * amount;
	}

	unsigned getBuyAmount() {
		return amount_;
	}

	unsigned getBuyTotalPrice() {
		return totalPrice_;
	}

	unsigned getBuyTotalWeight() {
		return totalWeight_;
	}

private:
	unsigned amount_{};
	unsigned totalPrice_{};
	unsigned totalWeight_{};
};

class Check : public Buy {
public:
	Check() {}

	~Check() {}

	void show() {
		std::cout << "Product: " << this->getProductName() << std::endl <<
			"Price: " << this->getProductPrice() << "uah" << std::endl <<
			"The weight: " << this->getProductWeight() << "kg" << std::endl << std::endl <<
			"Product purchased: " << this->getBuyAmount() << "pcs" << std::endl <<
			"For the amount: " << this->getBuyTotalPrice() << "uah" << std::endl <<
			"Total weight " << this->getBuyTotalWeight() << "kg" << std::endl << std::endl;
	}
};
