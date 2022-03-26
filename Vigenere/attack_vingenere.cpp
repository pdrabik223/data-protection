//
// Created by piotr on 15/03/2022.
//
#include "attack_vingenere.h"
#include "vingenere_cipher.h"
double IC(const std::map<char, uint32_t> &counter) {
  double sum = 0;

  for (auto i: counter)
	sum += i.second * (i.second - 1);

  return sum / (counter.size() * (counter.size() - 1));
}
std::vector<double> IC(const std::string &message, const int no_groups) {
  std::vector<std::string> groups(no_groups, std::string());
  uint32_t group_counter = 0;

  for (char c: message) {
	groups[group_counter++].push_back(c);
	if (group_counter == no_groups) group_counter = 0;
  }

  std::vector<double> i_c;
  for (const auto &i: groups) {
	std::map<char, uint32_t> counter = {};

	for (char c: Alphabet::k_data) { counter[c] = 0; }
	for (char j: i)
	  counter[j]++;

	i_c.push_back(IC(counter));
  }
  return i_c;
}
