#pragma once 
#include "../mesh/element.h"
#include <vector>
#include <memory>
class CellSOA{
public:
    CellSOA() = default;
    ~CellSOA() = default;
    CellSOA(const size_t& size);
    void sample();

    friend class Run; // Allow Run class to access private members
protected:
    size_t m_size;
    std::vector<std::shared_ptr<Element>> m_elements; // Elements in the cell
    std::vector<int> m_particleNums; // Number of particles in each cell
    std::vector<int> m_particleStartIndex; // Start index of particles in each cell
    std::vector<Eigen::Vector3d> m_velocity; // Velocity of the cell
    std::vector<double> m_density; // Density of the cell
    std::vector<double> m_temperature; // Temperature of the cell
    std::vector<double> m_pressure; // Pressure of the cell
    std::vector<double> m_energy; // Energy of the cell
};