#pragma once
#include <random>
#include <Eigen/Dense>
class Random {
public:
    // Constructor to initialize the random number generator with a seed
    Random(unsigned int seed = std::random_device{}()) : generator(seed) {}

    // Function to generate a random integer in the range [min, max]
    int getRandomInt(int min, int max);

    // Function to generate a random double in the range [min, max)
    double getRandomDouble(double min, double max);

    // Maxwell distribution for generating random velocities
    Eigen::Vector3d getMaxwellianVelocity(const double& Vstd);
protected:
    std::mt19937 generator; // Mersenne Twister random number generator
};