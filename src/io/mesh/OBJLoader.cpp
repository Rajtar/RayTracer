//
// Created by jakub on 06.04.2019.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include "OBJLoader.h"
#include "../../static/StringUtils.h"

void OBJLoader::loadMesh(std::string filePath, std::shared_ptr<Mesh> targetMesh) {
    init();
    std::cout << "Parsing file: " << filePath << std::endl;

    std::ifstream inputFile(filePath);
    if(!inputFile || !inputFile.good()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::vector<std::string> splitedLine = StringUtils::split(line, ' ', true);
        if (!splitedLine.empty() && !splitedLine.front().empty()) {
            if(StringUtils::toLower(splitedLine.front()) == "v") {
                std::vector<std::string> vertexLine(splitedLine.begin() + 1, splitedLine.end());
                parseVertex(vertexLine);
            } else if(StringUtils::toLower(splitedLine.front()) == "vn") {
                std::vector<std::string> normalLine(splitedLine.begin() + 1, splitedLine.end());
                parseNormal(normalLine);
            } else if(StringUtils::toLower(splitedLine.front()) == "f") {
                std::vector<std::string> faceLine(splitedLine.begin() + 1, splitedLine.end());
                parseFace(faceLine);
            }
        }
    }

    std::cout << " - Number of vertices acquired: " << vertices.size() << std::endl
              << " - Number of normals acquired: " << normals.size() << std::endl
              << " - Number of faces acquired: " << faces.size() << std::endl;

    targetMesh->faces = this->faces;
}

void OBJLoader::parseVertex(std::vector<std::string> vertexLine) {
    Vector3 vertex = Vector3(std::stod(vertexLine[0]), std::stod(vertexLine[1]), std::stod(vertexLine[2]) + 10);
    this->vertices.push_back(vertex);
}

void OBJLoader::parseNormal(std::vector<std::string> normalLine) {
    Vector3 normal = Vector3(std::stod(normalLine[0]), std::stod(normalLine[1]), std::stod(normalLine[2])).normalize();
    this->normals.push_back(normal);
}

void OBJLoader::parseFace(std::vector<std::string> faceLine) {
    std::vector<int> faceVertexIndices;
    std::vector<int> faceTextureIndices;
    std::vector<int> faceNormalIndices;

    for (const auto &vertexInfo : faceLine) {
        std::vector<std::string> splitVertexInfo = StringUtils::split(vertexInfo, '/', false);

        faceVertexIndices.push_back(std::stoi(splitVertexInfo.front()));

        if(splitVertexInfo.size() == 2) {
            if(!splitVertexInfo[1].empty()) {
                faceTextureIndices.push_back(std::stoi(splitVertexInfo[1]));
            }
        } else if(splitVertexInfo.size() == 3) {
            if(!splitVertexInfo[1].empty()) {
                faceTextureIndices.push_back(std::stoi(splitVertexInfo[1]));
            }
            if(!splitVertexInfo[2].empty()) {
                faceNormalIndices.push_back(std::stoi(splitVertexInfo[2]));
            }
        }
    }

    Triangle face(vertices[(faceVertexIndices[0] - 1)], vertices[(faceVertexIndices[1] - 1)], vertices[(faceVertexIndices[2] - 1)], LightIntensity(1, 0, 0));
    this->faces.push_back(face);
}

void OBJLoader::init() {
    this->vertices.clear();
    this->normals.clear();
    this->faces.clear();
}


