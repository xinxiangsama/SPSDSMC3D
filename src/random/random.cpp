#include "random.h"

int Random::getRandomInt(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

double Random::getRandomDouble(double min, double max)
{
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

Eigen::Vector3d Random::getMaxwellianVelocity(const double &Vstd)
{
    auto rd1 = getRandomDouble(0, 1.0);
    auto rd2 = getRandomDouble(0, 1.0);

    auto u = sqrt(-log(rd1)) * sin(2 * M_PI * rd2) * Vstd;

    rd1 = getRandomDouble(0, 1.0);
    rd2 = getRandomDouble(0, 1.0);
    auto v = sqrt(-log(rd1)) * sin(2 * M_PI * rd2) * Vstd;

    rd1 = getRandomDouble(0, 1.0);
    rd2 = getRandomDouble(0, 1.0);
    auto w = sqrt(-log(rd1)) * sin(2 * M_PI * rd2) * Vstd;
    
    return Eigen::Vector3d(u, v, w);
}
