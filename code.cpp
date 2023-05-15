#include "pdetector.h"

using namespace std;

PDetector::PDetector() {}

// Hamming Distance Algorithm
int PDetector::hamming_distance(string s1, string s2) {
    int count = 0;
    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] != s2[i]) {
            count++;
        }
    }
    return count;
}

// Brute Force Algorithm
vector<int> PDetector::brute_force(string pattern, vector<string> text, int max_distance) {
    vector<int> matches;
    int m = pattern.length();
    for (int k = 0; k < text.size(); k++) {
        int n = text[k].length();
        for (int i = 0; i <= n - m; i++) {
            int distance = hamming_distance(pattern, text[k].substr(i, m));
            if (distance <= max_distance) {
                matches.push_back(k);
            }
        }
    }
    return matches;
}

// Rabin-Karp Algorithm
vector<int> PDetector::rabin_karp(string pattern, vector<string> text) {
    vector<int> matches;
    int m = pattern.length();
    int p = 31;
    int mod = pow(10, 9) + 9;
    int p_pow = 1;
    int pattern_hash = 0;
    for (int i = 0; i < m; i++) {
        pattern_hash = (pattern_hash + (pattern[i] - 'a' + 1) * p_pow) % mod;
        p_pow = (p_pow * p) % mod;
    }
    for (int k = 0; k < text.size(); k++) {
        int n = text[k].length();
        int text_hash = 0;
        p_pow = 1;
        for (int i = 0; i < m; i++) {
            text_hash = (text_hash + (text[k][i] - 'a' + 1) * p_pow) % mod;
            p_pow = (p_pow * p) % mod;
        }
        for (int i = 0; i <= n - m; i++) {
            if (pattern_hash == text_hash) {
                if (text[k].substr(i, m) == pattern) {
                    matches.push_back(k);
                }
            }
            if (i < n - m) {
                text_hash = (p * (text_hash - (text[k][i] - 'a' + 1) * p_pow) + (text[k][i + m] - 'a' + 1)) % mod;
                if (text_hash < 0) {
                    text_hash += mod;
                }
            }
        }
    }
    return matches;
}

// Read file into a string
string PDetector::read_file(string filename) {
    ifstream infile(filename);
    string content((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    return content;
}

// Split string into sentences
vector<string> PDetector::split_sentences(string text) {
    vector<string> sentences;
    int start = 0;
    int end = 0;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!') {
            end = i;
            sentences.push_back(text.substr(start, end - start + 1));
            start = i + 1;
        }
    }
    if (start < text.length()) {
        sentences.push_back(text.substr(start));
    }
    return sentences;
}

// Main function
void PDetector::run() {
    // Read the potentially plagiarized document
    string test_doc = read_file("test.txt");

    // Split the test document into sentences
    vector<string> sentences = split_sentences(test_doc);

    // Perform plagiarism detection for each sentence
    for (int i = 0; i < sentences.size(); i++) {
        string sentence = sentences[i];
        cout << "Checking sentence: " << sentence << endl;

        // Brute force algorithm
        vector<int> brute_force_matches = brute_force(sentence, sentences, 3);
        if (!brute_force_matches.empty()) {
            cout << "Matches found using brute force: ";
            for (int j = 0; j < brute_force_matches.size(); j++) {
                cout << "Doc" << brute_force_matches[j] << " ";
            }
            cout << endl;
        }

        // Rabin-Karp algorithm
        vector<int> rabin_karp_matches = rabin_karp(sentence, sentences);
        if (!rabin_karp_matches.empty()) {
            cout << "Matches found using Rabin-Karp: ";
            for (int j = 0; j < rabin_karp_matches.size(); j++) {
                cout << "" << rabin_karp_matches[j] << " ";
            }
            cout << endl;
        }
    }
}
