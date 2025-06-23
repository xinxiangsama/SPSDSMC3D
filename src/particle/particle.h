#pragma once
#include <vector>
#include <iostream>
#include <Eigen/Dense>

class ParticleSOA{
public:
    ParticleSOA() = default;
    ParticleSOA(const size_t& size);
    ~ParticleSOA() = default;

    // Insert single particle data
    void insert(const double& mass, const Eigen::Vector3d& position,
                const Eigen::Vector3d& velocity, const double& Erot, const double& Evib);
    // Insert multiple particles data
    void insert(const std::vector<double>& mass, const std::vector<Eigen::Vector3d>& position,
                const std::vector<Eigen::Vector3d>& velocity, const std::vector<double>& Erot, const std::vector<double>& Evib);
    friend class Run; // Allow Run class to access private members
protected:
    size_t m_size;
    std::vector<double> m_mass;
    std::vector<Eigen::Vector3d> m_position;
    std::vector<Eigen::Vector3d> m_velocity;
    std::vector<double> m_Erot;
    std::vector<double> m_Evib;
    std::vector<bool> m_valid;
    std::vector<int> m_cellid;
    std::vector<int> m_localorder;
};


// use for mpi communication
class Particle{
public:
    Particle() = default;
    Particle(const double& mass, const Eigen::Vector3d& position,
             const Eigen::Vector3d& velocity, const double& Erot, const double& Evib);
    ~Particle() = default;

    // Getters
    double mass() const { return m_mass; }
    Eigen::Vector3d position() const { return m_position; }
    Eigen::Vector3d velocity() const { return m_velocity; }
    double Erot() const { return m_Erot; }
    double Evib() const { return m_Evib; }
    bool isValid() const { return m_valid; }
    // Setters
    void setMass(double mass) { m_mass = mass; }
    void setPosition(const Eigen::Vector3d& position) { m_position = position; }
    void setVelocity(const Eigen::Vector3d& velocity) { m_velocity = velocity; }
    void setErot(double Erot) { m_Erot = Erot; }
    void setEvib(double Evib) { m_Evib = Evib; }
    void setValid(bool valid) { m_valid = valid; }
protected:
    double m_mass;
    Eigen::Vector3d m_position;
    Eigen::Vector3d m_velocity;
    double m_Erot;
    double m_Evib;
    bool m_valid;
};