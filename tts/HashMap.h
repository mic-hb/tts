#pragma once
#include <vector>
#include <string>
#include "entry.h"

// HashMap class
public class HashMap {
private:
	std::vector<std::vector<Entry>> table;
	int size;

	int hash(const std::string& key) {
		int hash = 0;
		for (char c : key) {
			hash += c;
		}
		return hash % size;
	}

public:
	HashMap(int size) : size(size) {
		table.resize(size);
	}

	void put(const std::string& key, int value) {
		int index = hash(key);
		for (Entry& entry : table[index]) {
			if (entry.key == key) {
				entry.value = value;
				return;
			}
		}
		table[index].push_back(Entry(key, value));
	}

	int get(const std::string& key) {
		int index = hash(key);
		for (const Entry& entry : table[index]) {
			if (entry.key == key) {
				return entry.value;
			}
		}
		return -1; // Key not found
	}

	void remove(const std::string& key) {
		int index = hash(key);
		std::vector<Entry>& entries = table[index];

		for (auto it = entries.begin(); it != entries.end(); ++it) {
			if (it->key == key) {
				entries.erase(it);
				break;
			}
		}
	}

	std::vector<Entry> get_all() {
		std::vector<Entry> allEntries;
		for (const std::vector<Entry>& entries : table) {
			for (const Entry& entry : entries) {
				allEntries.push_back(entry);
			}
		}
		return allEntries;
	}
};

