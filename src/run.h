#pragma once
#include "mesh/mesh.h"
#include "particle/particle.h"
#include "cell/cell.h"
#include "random/random.h"

extern std::shared_ptr<Mesh> mesh;
extern std::shared_ptr<ParticleSOA> particles;
extern std::shared_ptr<CellSOA> cells;
extern std::shared_ptr<Random> rng;


class Run{
public:
    Run() = default;
    ~Run() = default;

    void initialize();
    void run();
    void finalize();

    std::shared_ptr<Mesh> m_mesh {}; // Mesh pointer, shared across the application
    std::shared_ptr<ParticleSOA> m_particles {}; // Particle data in SOA format
    std::shared_ptr<CellSOA> m_cells {}; // Cell data in SOA format
    std::shared_ptr<Random> m_rng {}; // Random number generator
};