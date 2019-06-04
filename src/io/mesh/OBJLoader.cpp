#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include "OBJLoader.h"
#include "../../static/StringUtils.h"

void OBJLoader::loadMesh(const std::string &filePath, std::shared_ptr<Mesh> targetMesh, bool loadNormals,
                         const Vector3 &positionOffset) {
    init();
    std::cout << "Parsing file: " << filePath << std::endl;

    std::ifstream inputFile(filePath);
    if(!inputFile || !inputFile.good()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::vector<std::string> splitLine = StringUtils::split(line, ' ', true);
        if (!splitLine.empty() && !splitLine.front().empty()) {
            if(StringUtils::toLower(splitLine.front()) == "v") {
                std::vector<std::string> vertexLine(splitLine.begin() + 1, splitLine.end());
                parseVertex(vertexLine, positionOffset);
            } else if(StringUtils::toLower(splitLine.front()) == "vn") {
                std::vector<std::string> normalLine(splitLine.begin() + 1, splitLine.end());
                parseNormal(normalLine);
            } else if(StringUtils::toLower(splitLine.front()) == "f") {
                std::vector<std::string> faceLine(splitLine.begin() + 1, splitLine.end());
                parseFace(faceLine, loadNormals);
            }
        }
    }

    std::cout << " - Number of vertices acquired: " << vertices.size() << std::endl
              << " - Number of normals acquired: " << normals.size() << std::endl
              << " - Number of faces acquired: " << faces.size() << std::endl;

    targetMesh->faces = this->faces;
}

void OBJLoader::parseVertex(std::vector<std::string> vertexLine, Vector3 positionOffset) {
    Vector3 vertex = Vector3(std::stod(vertexLine[0]) + positionOffset.x, std::stod(vertexLine[1]) + positionOffset.y, std::stod(vertexLine[2]) + positionOffset.z);
    this->vertices.push_back(vertex);
}

void OBJLoader::parseNormal(std::vector<std::string> normalLine) {
    Vector3 normal = Vector3(std::stod(normalLine[0]), std::stod(normalLine[1]), std::stod(normalLine[2])).normalized();
    this->normals.push_back(normal);
}

void OBJLoader::parseFace(std::vector<std::string> faceLine, bool loadNormals) {
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

    Triangle face;
    if(faceNormalIndices.empty() || !loadNormals) {
        face = Triangle(vertices[(faceVertexIndices[0] - 1)], vertices[(faceVertexIndices[1] - 1)], vertices[(faceVertexIndices[2] - 1)], Material());
    } else {
        Vector3 faceNormal;
        for (const auto &vertexNormalIndex : faceNormalIndices) {
            faceNormal += normals[vertexNormalIndex - 1];
        }
        faceNormal /= faceNormalIndices.size();
        face = Triangle(vertices[(faceVertexIndices[0] - 1)], vertices[(faceVertexIndices[1] - 1)], vertices[(faceVertexIndices[2] - 1)], faceNormal, Material());
    }

    this->faces.push_back(face);
}

void OBJLoader::init() {
    this->vertices.clear();
    this->normals.clear();
    this->faces.clear();
}


