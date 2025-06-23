#pragma once
#include "element.h"

class Hexahedron {
public:
    Hexahedron() = default;
    Hexahedron(const size_t& id, std::vector<int>& node_ids);
    virtual ~Hexahedron() = default;
    virtual bool checkIfParticleInside(const Eigen::Vector3d& position) const;
    virtual void computeVolume(const std::vector<Point>& points);
protected:
};