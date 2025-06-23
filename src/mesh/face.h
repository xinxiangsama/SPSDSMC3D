#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Dense>
class Face{
public:
    Face() = default;
    Face(const size_t& id, const std::vector<int>& nodes, int tag = -1);
    friend class Mesh;
protected:
    size_t m_id {};
    std::vector<int> m_node_ids {};
    int m_physical_tag {-1}; // if physical Surface in Gmesh
    Eigen::Vector3d m_normal {Eigen::Vector3d::Zero()}; // Normal vector of the face
};