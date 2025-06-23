#pragma once 
#include "tetrahedron.h"
#include "physicalTag.h"
#include <memory>

class Mesh{
public:
    Mesh();
    ~Mesh() = default;
    void load_from_msh(const std::string& filename);
    void meshInfo();
    void computeAllElementVolumes();
// protected:
    std::vector<Point> m_points;
    std::vector<Face> m_faces;
    std::vector<std::shared_ptr<Element>> m_elements;
    std::shared_ptr<PhysicalTagTable> m_physical_tags;
};