#include "physicalTag.h"
#include <iostream>

void PhysicalTagTable::add(int tag, const std::string &name)
{  
    tag_name_map.insert_or_assign(tag, name);
}

std::string PhysicalTagTable::getName(int tag) const
{
    auto it = tag_name_map.find(tag);
    return it != tag_name_map.end() ? it->second : "unknown";
}