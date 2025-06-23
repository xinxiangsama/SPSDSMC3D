#pragma once 
#include <Eigen/Dense>

// class Mesh;
class Point{
public:
    Point() = default;
    Point(const size_t& id, const double& x, const double& y, const double& z);
    Point(const size_t& id, const Eigen::Vector3d& position);
    ~Point() = default;

    const Eigen::Vector3d& getPosition() const;

    friend class Mesh;
protected:
    Eigen::Vector3d m_position {};
    size_t m_id {};
};