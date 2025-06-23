#include "cell.h"

CellSOA::CellSOA(const size_t &size) : m_size(size)
{
    m_elements.resize(size);
    m_particleNums.resize(size, 0);
    m_particleStartIndex.resize(size, 0);
    m_velocity.resize(size, Eigen::Vector3d::Zero());
    m_density.resize(size, 0.0);
    m_temperature.resize(size, 0.0);
    m_pressure.resize(size, 0.0);
    m_energy.resize(size, 0.0);
}
