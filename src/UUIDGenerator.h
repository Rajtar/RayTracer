#ifndef RENDERER_UUIDGENERATOR_H
#define RENDERER_UUIDGENERATOR_H

#include <string>
#include <cstdlib>

class UUIDGenerator {
public:
    static std::string generateUUID();

private:
    static const std::string CHARS;

};


#endif //RENDERER_UUIDGENERATOR_H
