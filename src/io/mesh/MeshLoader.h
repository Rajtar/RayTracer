//
// Created by jakub on 06.04.2019.
//

#ifndef RENDERER_MESHLOADER_H
#define RENDERER_MESHLOADER_H


#include "../../geometry/Mesh.h"

class MeshLoader {
public:
    virtual void loadMesh(std::string filePath, std::shared_ptr<Mesh> targetMesh) = 0;
};


#endif //RENDERER_MESHLOADER_H
