// PhysicalTag.h
#pragma once
#include <unordered_map>
#include <string>

class PhysicalTagTable {
public:
    PhysicalTagTable() = default;
    ~PhysicalTagTable() = default;
    void add(int tag, const std::string& name);
    std::string getName(int tag) const;
protected:
    std::unordered_map<int, std::string> tag_name_map {};
};
