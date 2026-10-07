#ifndef REPLACE_ALGOS_H
#define REPLACE_ALGOS_H

#include <string>
#include <regex>

// Algo 1 : Remplacement direct (In-place) - Modifie la chaîne existante
std::string replaceInPlace(std::string text, const std::string& target, const std::string& replacement) {
    if (target.empty()) return text;
    size_t pos = 0;
    while ((pos = text.find(target, pos)) != std::string::npos) {
        text.replace(pos, target.length(), replacement);
        pos += replacement.length();
    }
    return text;
}

// Algo 2 : Construction de Buffer (Ultra-rapide) - Construit une nouvelle chaîne
std::string replaceWithBuffer(const std::string& text, const std::string& target, const std::string& replacement) {
    if (target.empty()) return text;
    std::string result;
    // Pré-allocation de la mémoire pour éviter les réallocations coûteuses
    result.reserve(text.length()); 
    
    size_t lastPos = 0;
    size_t findPos;
    while ((findPos = text.find(target, lastPos)) != std::string::npos) {
        result.append(text, lastPos, findPos - lastPos);
        result.append(replacement);
        lastPos = findPos + target.length();
    }
    result.append(text, lastPos, text.length() - lastPos);
    return result;
}

// Algo 3 : Expression régulière (Regex) - Pratique mais souvent plus lourd
std::string replaceWithRegex(const std::string& text, const std::string& target, const std::string& replacement) {
    if (target.empty()) return text;
    std::regex reg(target);
    return std::regex_replace(text, reg, replacement);
}

#endif