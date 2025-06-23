#include "element.h"

Element::Element(const size_t &id, const std::vector<int> &nodes) : m_id(id), m_nodes(nodes) 
{
    if (nodes.empty()) {
        throw std::invalid_argument("Element must have at least one node.");
    }
}
const std::string& Element::getType() 
{
    return ElementTypeTable.at(m_type);
}

bool Element::checkIfParticleInside(const Eigen::Vector3d &position) const
{
    return false;
}

void Element::computeVolume(const std::vector<Point> &points)
{
    m_volume = 0.0; // Default implementation, can be overridden by derived classes
}


Eigen::Vector3d Element::getRandomPosition() const
{
    if (m_nodes.empty()) {
        throw std::runtime_error("Element has no nodes to compute a random position.");
    }
    
    // For simplicity, return the position of the first node
    // In a real implementation, you would compute a random position within the element
    return Eigen::Vector3d::Zero();
}