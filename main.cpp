#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <iomanip>
#include <functional>
#include "replace_algos.h"

std::string loadFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "Erreur d'ouverture du fichier.\n";
        return "";
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

int main() {
    int choix;
    std::string text, target, replacement;

    std::cout << "--- BENCHMARK DE REMPLACEMENT DE TEXTE ---\n";
    std::cout << "1. Saisir une phrase manuellement\n";
    std::cout << "2. Charger un fichier texte\n";
    std::cout << "Choix (1 ou 2) : ";
    std::cin >> choix;
    std::cin.ignore();

    if (choix == 1) {
        std::cout << "Saisissez votre texte : ";
        std::getline(std::cin, text);
    } else {
        std::string filename;
        std::cout << "Chemin du fichier : ";
        std::getline(std::cin, filename);
        text = loadFile(filename);
        if (text.empty()) return 1;
        std::cout << "[INFO] Fichier charge (" << text.length() << " caracteres).\n";
    }

    std::cout << "Mot ou phrase a rechercher : ";
    std::getline(std::cin, target);
    std::cout << "Remplacer par : ";
    std::getline(std::cin, replacement);

    std::cout << "\nLancement du Benchmark...\n";
    std::cout << "--------------------------------------------------------\n";
    std::cout << std::left << std::setw(25) << "Algorithme" 
              << std::setw(25) << "Temps (Microsecondes)" << "\n";
    std::cout << "--------------------------------------------------------\n";

    std::vector<std::pair<std::string, std::function<std::string()>>> algos = {
        {"1. In-Place (replace)", [&]() { return replaceInPlace(text, target, replacement); }},
        {"2. Buffer (append)", [&]() { return replaceWithBuffer(text, target, replacement); }},
        {"3. Regex (regex_replace)", [&]() { return replaceWithRegex(text, target, replacement); }}
    };

    for (const auto& algo : algos) {
        auto start = std::chrono::high_resolution_clock::now();
        
        std::string result = algo.second(); 
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Blocage de l'optimisation : force le compilateur à évaluer "result"
        volatile size_t dummy = result.length(); 

        std::cout << std::left << std::setw(25) << algo.first 
                  << std::setw(25) << duration << "\n";
    }
    std::cout << "--------------------------------------------------------\n";

    return 0;
}