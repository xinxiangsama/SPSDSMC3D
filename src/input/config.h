#pragma once
#include "json.hpp"
#include <fstream>
#include <string>
class Config {
public:
    Config() = default;
    ~Config() = default;
    static Config& getInstance() {
        static Config instance;
        return instance;
    }
    void load(const std::string& filename);

    
};