#include "point.h"

Point::Point(const size_t &id, const double &x, const double &y, const double &z) : m_id(id), m_position({x, y, z})
{
}

Point::Point(const size_t &id, const Eigen::Vector3d &position) : m_id(id), m_position(position)
{
}

const Eigen::Vector3d &Point::getPosition() const
{
    return m_position;
}
