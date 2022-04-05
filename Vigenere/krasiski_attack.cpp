//
// Created by piotr on 22/03/2022.
//
#include <cmath>
#include "kasiski_attack.h"
#include "vingenere_cipher.h"

std::string FilterValuesNotFoundInAlphabet(const std::string &target) {
  std::string result;
  for (auto &i: target)
	if (Alphabet::IsInAlphabet(i))
	  result.push_back(i);
  return result;
}
void AddToNwd(std::map<int, int> &target, int val) {
  for (int i = 1; i <= sqrt(val); i++) {
	if (val % i == 0) {
	  if (val / i == i)
		target[i]++;
	  else {
		target[i]++;
		target[val / i]++;
	  }
	}
  }

}
std::map<int, int> ComputeRepetitions(const std::string &message) {

  std::map<int, int> result = {};
  const int kPasswordMinLength = 2;
  const int kPasswordMaxLength = 20;
  const int kWindowMinLength = 5;
  int current_window_length;
  std::string window_buffer = "";

  auto clean_message = FilterValuesNotFoundInAlphabet(message);

  for (int k = kPasswordMinLength; k < kPasswordMaxLength; k++)
  for (int i = 0; i < clean_message.size() - kWindowMinLength; i++) {

	window_buffer = clean_message.substr(i, k);

	for (int j = i + kWindowMinLength; j < clean_message.size() - kWindowMinLength; j++)

	  if (window_buffer == clean_message.substr(j, kWindowMinLength))

		AddToNwd(result, j - i);
  }
  return result;
}
