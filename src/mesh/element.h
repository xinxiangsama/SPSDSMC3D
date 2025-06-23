// Element.h
#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include "face.h"
#include "point.h"
#include <Eigen/Dense>
#include <memory>


enum class ElementType{
    Default, // Default type
    tetrahedron,
    hexahedron
};
const std::unordered_map<ElementType, std::string> ElementTypeTable{
    {ElementType::tetrahedron, "Tetrahedron"},
    {ElementType::hexahedron, "Hexahedron"},
    {ElementType::Default, "Default"}
};

class Element {
public:
    Element() = default;
    Element(const size_t& id, const std::vector<int>& nodes);
    virtual ~Element() = default;

    const std::string& getType();
    virtual bool checkIfParticleInside(const Eigen::Vector3d& position) const;
    virtual void computeVolume(const std::vector<Point>& points);
    virtual Eigen::Vector3d getRandomPosition() const;

// protected:
    size_t m_id{};
    ElementType m_type {ElementType::Default};
    std::vector<int> m_nodes; // Node IDs
    std::vector<Face> m_faces; // Faces of the element
    double m_volume{0.0}; // Volume of the element, default is 0.0
};

