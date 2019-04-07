//
// Created by jakub on 06.04.2019.
//

#include <sstream>
#include <algorithm>
#include "StringUtils.h"

std::vector<std::string> StringUtils::split(const std::string &string, char delimiter, bool removeEmpty) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(string);
    while (std::getline(tokenStream, token, delimiter)) {
        if(removeEmpty) {
            if(!token.empty()) {
                tokens.push_back(token);
            }
        } else {
            tokens.push_back(token);
        }
    }
    return tokens;
}

std::string StringUtils::toLower(std::string string) {
//    std::transform(string.begin(), string.end(), string.begin(), ::tolower);
    return string;
}

std::string StringUtils::toUpper(std::string string) {
//    std::transform(string.begin(), string.end(), string.begin(), ::toupper);
    return string;
}
