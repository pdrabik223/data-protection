//
// Created by piotr on 04/03/2022.
//

#ifndef DATA_PROTECTION_SIMPLE_SUBSTITUTION_CIPHER_STATISTICAL_ATTACK_H_
#define DATA_PROTECTION_SIMPLE_SUBSTITUTION_CIPHER_STATISTICAL_ATTACK_H_

#include <map>
#include <string>
using FrequencyTable = std::map< char,float>;

FrequencyTable FromEnglishLanguage();
FrequencyTable FromText(const std::string &text);
std::string ToString(const FrequencyTable &frequency_table);
int calculate_average_shift(const FrequencyTable &encrypted_frequencies, const FrequencyTable &correct_frequencies);


#endif //DATA_PROTECTION_SIMPLE_SUBSTITUTION_CIPHER_STATISTICAL_ATTACK_H_
