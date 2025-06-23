#include "face.h"

Face::Face(const size_t &id, const std::vector<int> &nodes, int tag) : m_id(id), m_node_ids(std::move(nodes)), m_physical_tag(tag)
{
}