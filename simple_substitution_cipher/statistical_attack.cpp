//
// Created by piotr on 04/03/2022.
//

#include "statistical_attack.h"
#include <cassert>
#include <vector>
#include <iostream>
FrequencyTable FromEnglishLanguage() {

  FrequencyTable frequency_table;

  frequency_table.insert({'E', 12.7});
  frequency_table.insert({'T', 9.1});
  frequency_table.insert({'A', 8.2});
  frequency_table.insert({'O', 7.5});
  frequency_table.insert({'I', 7.0});
  frequency_table.insert({'N', 6.7});
  frequency_table.insert({'S', 6.3});
  frequency_table.insert({'H', 6.1});
  frequency_table.insert({'R', 6.0});
  frequency_table.insert({'D', 4.3});
  frequency_table.insert({'L', 4.0});
  frequency_table.insert({'C', 4.8});
  frequency_table.insert({'U', 2.8});
  frequency_table.insert({'M', 2.4});
  frequency_table.insert({'w', 2.3});
  frequency_table.insert({'F', 2.2});
  frequency_table.insert({'G', 2.0});
  frequency_table.insert({'Y', 2.0});
  frequency_table.insert({'P', 1.9});
  frequency_table.insert({'B', 1.5});
  frequency_table.insert({'V', 1.0});
  frequency_table.insert({'K', 0.08});
  frequency_table.insert({'J', 0.02});
  frequency_table.insert({'Q', 0.01});
  frequency_table.insert({'X', 0.01});
  frequency_table.insert({'Z', 0.01});

  for (char i = '0'; i <= '9'; i++)
	frequency_table.insert({i, 0});

  return frequency_table;
}
FrequencyTable FromText(const std::string &text) {
  FrequencyTable frequency_table;
  for (char i = 'A'; i <= 'Z'; i++)
	frequency_table.insert({i, 0});

  for (char i = '0'; i <= '9'; i++)
	frequency_table.insert({i, 0});

  for (char i: text) {
	if ((i >= 'A' && i <= 'Z') || (i >= '0' && i <= '9')) frequency_table[i] += 1;
	else if (i >= 'a' && i <= 'z')frequency_table[i + 32] += 1;

  }
  float sum = 0;
  for (auto &i: frequency_table)
	sum += i.second;

  for (auto &i: frequency_table)
	i.second /= sum;
  return frequency_table;
}
std::string ToString(const FrequencyTable &frequency_table) {

  std::string output;
  for (auto i: frequency_table) {
	output.push_back(i.first);
	output.push_back('\t');
	output += std::to_string(i.second);
	output.push_back('\n');
  }
  return output;
}
int calculate_average_shift(const FrequencyTable &encrypted_frequencies, const FrequencyTable &template_frequencies) {

  assert(encrypted_frequencies.size() == template_frequencies.size());

  std::map<float, char> encrypted_data, template_data;
  for (const auto &i: encrypted_frequencies) encrypted_data.insert({i.second, i.first});
  for (const auto &i: template_frequencies) template_data.insert({i.second, i.first});

  std::cout << ToString(encrypted_frequencies) << "encrypted\n template" << ToString(template_frequencies);

  std::vector<int> shifts;

  for (auto i: encrypted_data) {
	int shift = 0;
	for (auto j: template_data) {
	  if (i.second == j.second) break;
	  shift++;
	}
	shifts.push_back(shift);
  }
  return shifts[0];
}