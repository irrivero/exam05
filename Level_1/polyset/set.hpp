#pragma once
#include "searchable_bag.hpp"

class set {
	private:
		searchable_bag &bag;
	public:
		set(searchable_bag &bg) : bag(bg) {}
		~set() {}
		void insert(int item) {
			if (!bag.has(item))
				bag.insert(item);
		}
		void insert(int *items, int count) {
			for (int i = 0; i < count; i++)
				insert(items[i]);
		}
		bool has(int item) const {
			return bag.has(item);
		}
		void print() {
			bag.print();
		}
		void clear() {
			bag.clear();
		}
		searchable_bag &get_bag() {
			return bag;
		}

};