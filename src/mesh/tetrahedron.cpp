#include "tetrahedron.h"
#include "../random/random.h"
#include "mesh.h"
extern std::shared_ptr<Random> rng;
extern std::shared_ptr<Mesh> mesh;

Tetrahedron::Tetrahedron(const size_t &id, std::vector<int>& node_ids) : Element(id, node_ids) 
{   
    m_type = ElementType::tetrahedron;
    // Ensure that the tetrahedron has exactly 4 nodes
    if (m_nodes.size() != 4) {
        throw std::invalid_argument("Tetrahedron must have exactly 4 nodes.");
    }
    


}

bool Tetrahedron::checkIfParticleInside(const Eigen::Vector3d &position) const
{
    return false; // Placeholder for actual implementation
}

void Tetrahedron::computeVolume(const std::vector<Point>& points)
{

    // Get the coordinates of the tetrahedron's vertices
    const auto& p1 = points[m_nodes[0] - 1].getPosition();
    const auto& p2 = points[m_nodes[1] - 1].getPosition();
    const auto& p3 = points[m_nodes[2] - 1].getPosition();
    const auto& p4 = points[m_nodes[3] - 1].getPosition();

    // Calculate the volume using the determinant method
    m_volume = std::abs((p2 - p1).dot((p3 - p1).cross(p4 - p1))) / 6.0;

}

Eigen::Vector3d Tetrahedron::getRandomPosition() const
{
    // Generate a random point inside the tetrahedron using barycentric coordinates
    double r1 = rng->getRandomDouble(0.0, 1.0);
    double r2 = rng->getRandomDouble(0.0, 1.0);
    double r3 = rng->getRandomDouble(0.0, 1.0);
    // Ensure the sum of barycentric coordinates is less than or equal to 1
    if (r1 + r2 + r3 > 1.0) {
        r1 = 1.0 - r1;
        r2 = 1.0 - r2;
        r3 = 1.0 - r3;
    }

    const auto& points = mesh->m_points; // Access the mesh points
    // std::cout << points.size() << std::endl;
    // Get the vertices of the tetrahedron
    const auto& p1 = points[m_nodes[0] - 1].getPosition();
    const auto& p2 = points[m_nodes[1] - 1].getPosition();
    const auto& p3 = points[m_nodes[2] - 1].getPosition();
    const auto& p4 = points[m_nodes[3] - 1].getPosition();

    // Calculate the random position using barycentric coordinates
    return r1 * p1 + r2 * p2 + r3 * p3 + (1 - r1 - r2 - r3) * p4;

}