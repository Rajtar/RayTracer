//
// Created by jakub on 06.04.2019.
//

#ifndef RENDERER_STRINGUTILS_H
#define RENDERER_STRINGUTILS_H


#include <string>
#include <vector>

class StringUtils {
public:
    static std::vector<std::string> split(const std::string &string, char delimiter, bool removeEmpty);
    static std::string toLower(std::string string);
    static std::string toUpper(std::string string);

private:
    StringUtils() = default;
};


#endif //RENDERER_STRINGUTILS_H
