//
// Created by jakub on 06.04.2019.
//

#ifndef RENDERER_OBJLOADER_H
#define RENDERER_OBJLOADER_H


#include <bits/shared_ptr.h>
#include "MeshLoader.h"

class OBJLoader : public MeshLoader {
public:
    void loadMesh(const std::string &filePath, std::shared_ptr<Mesh> targetMesh, const Vector3 &positionOffset = Vector3()) override;

private:
    std::vector<Vector3> vertices;
    std::vector<Vector3> normals;
    std::vector<Triangle> faces;

    void parseVertex(std::vector<std::string> vertexLine, Vector3 positionOffset);
    void parseNormal(std::vector<std::string> normalLine);
    void parseFace(std::vector<std::string> faceLine);
    void init();
};


#endif //RENDERER_OBJLOADER_H
