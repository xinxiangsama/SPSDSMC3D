#include "particle.h"

ParticleSOA::ParticleSOA(const size_t &size) : m_size(size)
{
    m_mass.resize(size);
    m_position.resize(size);
    m_velocity.resize(size);
    m_Erot.resize(size);
    m_Evib.resize(size);
    m_valid.resize(size, true); // Initialize all particles as valid
    m_cellid.resize(size);
    m_localorder.resize(size);

}

void ParticleSOA::insert(const double &mass, const Eigen::Vector3d &position, const Eigen::Vector3d &velocity, const double &Erot, const double &Evib)
{
    m_size++;
    m_mass.push_back(mass);
    m_position.push_back(position);
    m_velocity.push_back(velocity);
    m_Erot.push_back(Erot);
    m_Evib.push_back(Evib); 
    m_valid.push_back(true); // New particle is valid by default
}

void ParticleSOA::insert(const std::vector<double> &mass, const std::vector<Eigen::Vector3d> &position, const std::vector<Eigen::Vector3d> &velocity, const std::vector<double> &Erot, const std::vector<double> &Evib)
{
    for (size_t i = 0; i < mass.size(); ++i)
    {
        insert(mass[i], position[i], velocity[i], Erot[i], Evib[i]);
    }
}

Particle::Particle(const double &mass, const Eigen::Vector3d &position, const Eigen::Vector3d &velocity, const double &Erot, const double &Evib) : m_mass(mass), m_position(position), m_velocity(velocity), m_Erot(Erot), m_Evib(Evib), m_valid(true)
{
}
