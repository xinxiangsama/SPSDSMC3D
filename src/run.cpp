#include "run.h"

#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPoints.h>
#include <vtkTetra.h>
#include <vtkCellArray.h>
#include <vtkXMLUnstructuredGridWriter.h>  // 用于写 .vtu 文件
#include <vtkIntArray.h>
#include <vtkCellData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkQuad.h>
#include <vtkCellData.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkDoubleArray.h>
std::shared_ptr<Mesh> mesh;
std::shared_ptr<ParticleSOA> particles;
std::shared_ptr<CellSOA> cells;
std::shared_ptr<Random> rng;

void Run::initialize()
{
    m_mesh = std::make_shared<Mesh>(); // Initialize the mesh
    m_particles = std::make_shared<ParticleSOA>(); // Initialize the particles
    m_cells = std::make_shared<CellSOA>(); // Initialize the cells

    // Initialize the mesh
    m_mesh->load_from_msh("mesh/box.msh");
    m_mesh->computeAllElementVolumes();
    m_mesh->meshInfo();
    mesh = m_mesh; // Set the mesh pointer
    
    m_rng = std::make_shared<Random>(std::random_device{}()); // Initialize the random number generator
    rng = m_rng; // Set the random number generator pointer
    std::cout << "Mesh initialized with " << mesh->m_points.size() << " points and "
              << mesh->m_elements.size() << " elements." << std::endl;
    m_cells = std::make_shared<CellSOA>(m_mesh->m_elements.size());
    for(size_t i = 0; i < m_mesh->m_elements.size(); ++i) {
        m_cells->m_elements[i] = m_mesh->m_elements[i];
    }
    cells = m_cells; // Set the cells pointer
    // Initialize the particles
    double Rho = 1.0; // Density
    double particle_mass = 1.0e-5; // Mass of each particle

    for(size_t i = 0; i < mesh->m_elements.size(); ++i) {
        auto& element = cells->m_elements[i];
        // std::cout << "Element ID: " << element->m_id << ", Type: " << element->getType() << std::endl;
        double volume = element->m_volume;
        int num_particles = static_cast<int>(std::ceil(volume * Rho / particle_mass));
        
        std::vector<double> masses(num_particles, particle_mass);
        std::vector<Eigen::Vector3d> positions(num_particles, Eigen::Vector3d::Zero());
        std::vector<Eigen::Vector3d> velocities(num_particles, Eigen::Vector3d::Zero());
        for(size_t i = 0; i < num_particles; ++i) {
            // Generate a random position inside the element
            // positions[i] = element->getRandomPosition();
            // element->getRandomPosition();
            std::cout <<"random position: " << element->getRandomPosition().transpose() << std::endl;
            // Generate a random velocity using Maxwellian distribution
            // velocities[i] = rng->getMaxwellianVelocity(1.0); // Assuming Vstd = 1.0 for simplicity
        }
        std::vector<double> Erot(num_particles, 0.0);
        std::vector<double> Evib(num_particles, 0.0);

        m_particles->insert(masses, positions, velocities, Erot, Evib);
        m_cells->m_particleNums[i] = num_particles;
    }

    particles = m_particles; // Set the particles pointer
}

void Run::finalize()
{
    auto points = vtkSmartPointer<vtkPoints>::New();
    points->SetDataTypeToDouble(); // 设置输出精度为 double

    for(const auto& point : mesh->m_points) {
        auto position = point.getPosition();
        points->InsertNextPoint(position[0], position[1], position[2]);
    }
    auto grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    grid->SetPoints(points);

    // 创建用于存储体积的数组
    auto volumeArray = vtkSmartPointer<vtkDoubleArray>::New();
    volumeArray->SetName("Volume");
    volumeArray->SetNumberOfComponents(1);
    // 创建用于储存粒子数的数组
    auto particleNumArray = vtkSmartPointer<vtkIntArray>::New();
    particleNumArray->SetName("ParticleNum");
    particleNumArray->SetNumberOfComponents(1);

    for(size_t i = 0; i < cells->m_elements.size(); ++i) {
        auto element = cells->m_elements[i];
        auto vtkTetraCell = vtkSmartPointer<vtkTetra>::New();
        for (size_t i = 0; i < 4; ++i) {
            vtkTetraCell->GetPointIds()->SetId(i, element->m_nodes[i] - 1);
        }
        grid->InsertNextCell(vtkTetraCell->GetCellType(), vtkTetraCell->GetPointIds());
        // 假设 element->m_volume 存储了体积
        volumeArray->InsertNextValue(element->m_volume);
        // 假设 cells->m_particleNums 存储了每个单元的粒子数
        particleNumArray->InsertNextValue(cells->m_particleNums[i]);
    }

    // 将体积数据添加到单元数据中
    grid->GetCellData()->AddArray(volumeArray);
    // 将粒子数数据添加到单元数据中
    grid->GetCellData()->AddArray(particleNumArray);

    auto writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
    writer->SetFileName("output.vtu");
    writer->SetInputData(grid);
    writer->SetDataModeToAscii();  // 设置为ASCII模式
    writer->Write();  // 写入文件
}