//
// Created by piotr on 04/03/2022.
//

#ifndef DATA_PROTECTION_SIMPLE_SUBSTITUTION_CIPHER_SUBSTITUTION_CIPHER_H_
#define DATA_PROTECTION_SIMPLE_SUBSTITUTION_CIPHER_SUBSTITUTION_CIPHER_H_
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using Encoding = std::vector<std::pair<char, char>>;

std::string ToString(const Encoding& encoding);

/// read file, than correct every small letter to huge
std::string LoadFile(const std::string &path);

void SaveFile(const std::string &message, const std::string &path);

/// create encoding lib, that uses all letters in caps, and numbers
/// \param shift
/// \return
Encoding from_shift(int shift);

std::string encode(std::string &message, const Encoding &encoding);

std::string decode(const std::string &message, const Encoding &encoding);

#endif //DATA_PROTECTION_SIMPLE_SUBSTITUTION_CIPHER_SUBSTITUTION_CIPHER_H_
