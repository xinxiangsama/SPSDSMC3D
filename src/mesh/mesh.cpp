#include "mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>

int getNumNodesFromElementType(int type) {
    switch (type) {
        case 15: return 1; // point
        case 1: return 2; // line
        case 2: return 3; // triangle
        case 3: return 4; // quadrilateral
        case 4: return 4; // tetrahedron
        case 5: return 8; // hexahedron
        default:
            std::cerr << "Unknown element type: " << type << std::endl;
            return 0;
    }
}


Mesh::Mesh()
{
    m_physical_tags = std::make_shared<PhysicalTagTable>();
}
void Mesh::load_from_msh(const std::string &filename)
{
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Cannot open file: " << filename << "\n";
        return;
    }else{
        std::cout <<"Open mesh  "<<filename<<" successful!"<<std::endl;
    }
    std::string line;
    while (std::getline(infile, line)) {
        if (line == "$PhysicalNames") {
            int n;
            infile >> n;
            for (int i = 0; i < n; ++i) {
                int dim, tag;
                std::string name;
                infile >> dim >> tag;
                infile.ignore(); // skip space
                std::getline(infile, name);
                name.erase(std::remove(name.begin(), name.end(), '"'), name.end());
                m_physical_tags->add(tag, name);
            }
        }
        else if (line == "$Nodes") {
            int numEntityBlocks, numNodes, minNodeTag, maxNodeTag;
            infile >> numEntityBlocks >> numNodes >> minNodeTag >> maxNodeTag;
            std::getline(infile, line); // consume newline
            for (int i = 0; i < numEntityBlocks; ++i) {
                int entityDim, entityTag, parametric, numNodesInBlock;
                infile >> entityDim >> entityTag >> parametric >> numNodesInBlock;
                std::getline(infile, line); // consume newline
                if(numNodesInBlock != 0){
                    std::vector<int> nodeTags(numNodesInBlock);
                    for (int j = 0; j < numNodesInBlock; ++j) {
                        infile >> nodeTags[j];
                    }
                    std::getline(infile, line); // consume newline

                    for (int j = 0; j < numNodesInBlock; ++j) {
                        double x, y, z;
                        infile >> x >> y >> z;
                        m_points.emplace_back(nodeTags[j], Eigen::Vector3d{x, y, z});
                    }
                    std::getline(infile, line); // consume newline
                }
            }
        }else if (line == "$Elements") {
            int numEntityBlocks, numElements, minTag, maxTag;
            infile >> numEntityBlocks >> numElements >> minTag >> maxTag;
            std::getline(infile, line); // consume newline

            for (int i = 0; i < numEntityBlocks; ++i) {
                int entityDim, entityTag, elementType, numElementsInBlock;
                infile >> entityDim >> entityTag >> elementType >> numElementsInBlock;
                std::getline(infile, line); // consume newline

                for (int j = 0; j < numElementsInBlock; ++j) {
                    int elementTag;
                    infile >> elementTag;

                    std::vector<int> node_ids;
                    int numNodes = getNumNodesFromElementType(elementType);
                    node_ids.resize(numNodes);
                    for (int k = 0; k < numNodes; ++k) {
                        infile >> node_ids[k];
                    }

                    // construct face
                    if (entityDim == 2) {
                        Face face(elementTag, node_ids, entityTag);
                        m_faces.emplace_back(face); 
                    }
                    // construct tetrahedron
                    else if (entityDim == 3 && elementType == 4) {
                        m_elements.emplace_back(std::make_shared<Tetrahedron>(elementTag, node_ids));
                    }
                }
            }

            // wating for $EndElements
            while (std::getline(infile, line)) {
                if (line == "$EndElements") break;
            }
        }

    }
}

void Mesh::meshInfo()
{
    // Info
    std::cout << "Mesh loaded successfully!" << std::endl;
    std::cout << "Number of points: " << m_points.size() << std::endl;
    std::cout << "Number of faces: " << m_faces.size() << std::endl;
    std::cout << "Number of elements: " << m_elements.size() << std::endl;

    // for(const auto& element : m_elements) {
    //     std::cout << "Element ID: " << element->m_id << ", Type: " << element->getType() << ", Nodes: ";
    //     for (const auto& node : element->m_nodes) {
    //         std::cout << node << " ";
    //     }
    //     std::cout << ", Volume: " << element->m_volume << std::endl;
    //     std::cout << std::endl;

    //     for(int i = 0; i < 4; ++i){
    //         const auto& point = m_points[element->m_nodes[i]];
    //         std::cout << "Node ID: " << point.m_id << ", Position: (" 
    //                   << point.m_position.x() << ", " 
    //                   << point.m_position.y() << ", " 
    //                   << point.m_position.z() << ")" << std::endl;
    //     }
    // }

    // for(const auto& point : m_points) {
    //     std::cout << "Point ID: " << point.m_id << ", Position: (" 
    //               << point.m_position.x() << ", " 
    //               << point.m_position.y() << ", " 
    //               << point.m_position.z() << ")" << std::endl;
    // }

}
void Mesh::computeAllElementVolumes()
{
    for (const auto& element : m_elements) {
        element->computeVolume(m_points);
    }
}