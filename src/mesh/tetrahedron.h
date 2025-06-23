#pragma once
#include "element.h"
#include <array>

class Tetrahedron: public Element{
public:
    Tetrahedron() = default;
    Tetrahedron(const size_t& id, std::vector<int>& node_ids);
    virtual ~Tetrahedron() = default;

    virtual bool checkIfParticleInside(const Eigen::Vector3d& position) const override;
    virtual void computeVolume(const std::vector<Point>& points) override;
    virtual Eigen::Vector3d getRandomPosition() const override;
protected:
};