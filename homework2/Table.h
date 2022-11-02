#pragma once
#include <vector>
#include <iostream>

class Table {
public:
	Table() {}
	Table(std::vector<int> values) {
		value_ = values;
		for (size_t i = 0; i < value_.size(); ++i) {
			id_.push_back(i);
		}
	}
	~Table() {}

	void push(int value) {
		value_.push_back(value);
		id_.push_back(value_.size() - 1);
	}

	int pop(void) {
		int returnValue = value_.back();
		value_.pop_back();
		id_.pop_back();
	}

	const std::vector<int>& getValues() {
		return value_;
	}

	friend Table& operator+(Table& first, Table& other) {
		std::vector<int> result = first.getValues();
		for (size_t i = 0; i < other.getValues().size(); ++i) {
			result.push_back(other.getValues()[i]);
		}
		Table table = Table(result);

		return table;
	}

	Table& operator=(Table& other) {
		std::vector<unsigned> newId;
		value_ = other.getValues();
		for (size_t i = 0; i < other.getValues().size(); ++i) {
			newId.push_back(other.getValues()[i]);
		}
		id_ = newId;
	}

	Table& operator++() {
		value_.push_back(1);
		id_.push_back(value_.size() - 1);
		return *this;
	}

	Table operator++(int) {
		Table prev = *this;
		++* this;
		return prev;
	}

	int operator[](unsigned id) {
		return value_[id];
	}

	friend std::ostream& operator<<(std::ostream& os, Table& other);

private:
	std::vector<unsigned> id_{};
	std::vector<int> value_{};
};

std::ostream& operator<<(std::ostream& os, Table& other) {
	for (size_t i = 0; i < other.getValues().size(); ++i) {
		os << i << '\t' << other.getValues()[i];
	}
	return os;
}