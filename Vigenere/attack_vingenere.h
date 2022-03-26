//
// Created by piotr on 15/03/2022.
//

// coincidence aproach

#ifndef DATA_PROTECTION_VIGENERE_ATTACK_VINGENERE_H_
#define DATA_PROTECTION_VIGENERE_ATTACK_VINGENERE_H_

#include <string>
#include <array>
#include <map>
#include <vector>
double IC(const std::map<char, uint32_t> &counter);

std::vector<double> IC(const std::string &message, const int no_groups);

#endif //DATA_PROTECTION_VIGENERE_ATTACK_VINGENERE_H_
