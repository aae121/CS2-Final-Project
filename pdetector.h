#ifndef PDETECTOR_H
#define PDETECTOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>

class PDetector {
public:
    PDetector();
    int hamming_distance(std::string s1, std::string s2);
    std::vector<int> brute_force(std::string pattern, std::vector<std::string> text, int max_distance);
    std::vector<int> rabin_karp(std::string pattern, std::vector<std::string> text);
    std::string read_file(std::string filename);
    std::vector<std::string> split_sentences(std::string text);
    void run();
};

#endif /* PDETECTOR_H */
