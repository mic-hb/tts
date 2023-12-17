#pragma once
#include <string>

// Entry class to store key-value pairs
class Entry {
public:
    std::string key;
    int value;

    Entry(const std::string& key, int value) : key(key), value(value) {}
};

