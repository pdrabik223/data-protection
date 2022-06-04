//
// Created by piotr on 10/05/2022.
//

#include <cstdint>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <cmath>

uint32_t ADLER32(const std::vector<uint8_t> &ascii_array) {
  uint32_t A = 1, B = 0;
  for (const uint8_t kCharacter: ascii_array) {
	A += kCharacter;
	A %= 65521;
	B += A;
	B %= 65521;
  }
  return B << 16 | A;
}
uint64_t DJB(const std::vector<uint8_t> &ascii_array) {
  uint64_t hash = 5381;

  for (const uint8_t kCharacter: ascii_array) {
	hash = hash * 33 + kCharacter;
  }
  return hash;
}

std::vector<uint8_t> GenCharacterString(const uint32_t string_length) {
  static std::string legal_characters = {"0123456789abcdefghijklmnoprstABCDEFGHIJKLMNOPRST"};
  std::vector<uint8_t> ascii_array(string_length);
  for (uint8_t &character: ascii_array) {
	character = legal_characters[rand() % legal_characters.size()];
  }
  return ascii_array;
}

uint64_t SQRT(uint64_t first) {
  return (uint64_t)(sqrt(first));
}
int main() {
  uint32_t M = 100'000, D = 2;
  {
	std::vector<std::vector<uint8_t>> results;
	std::vector<uint64_t> djbs;
	std::vector<uint32_t> adler32s;
	std::pair<uint64_t, uint64_t> collisions = {0, 0};
	for (uint32_t i = 0; i < M; i++) {
	  results.emplace_back(GenCharacterString(D));
	  auto djb = DJB(results.back());
	  auto adler32 = ADLER32(results.back());
	  adler32s.emplace_back(adler32);
	  djbs.emplace_back(djb);
	}
	for (const auto djb: djbs) {
	  auto djb_collision = std::count(djbs.begin(), djbs.end(), djb);

	  if (djb_collision == 1) continue;
	  else collisions.first += djb_collision - 1;
	}
	for (const auto adler32: adler32s) {
	  auto adler32_collision = std::count(adler32s.begin(), adler32s.end(), adler32);
	  if (adler32_collision == 1) continue;
	  collisions.second += adler32_collision - 1;
	}
	auto c = SQRT(collisions.first);
	collisions.first = c * (c * (c - 3)) / 2;
	c = SQRT(collisions.second);
	collisions.second = c * (c * (c - 3)) / 2;

	std::cout << "d = " << D << " " << collisions.first << "   " << collisions.second << std::endl;
  }
  {
	D = 20;
	std::vector<std::vector<uint8_t>> results;
	std::vector<uint64_t> djbs;
	std::vector<uint32_t> adler32s;
	std::pair<uint64_t, uint64_t> collisions = {0, 0};
	for (uint32_t i = 0; i < M; i++) {
	  results.emplace_back(GenCharacterString(D));
	  auto djb = DJB(results.back());
	  auto adler32 = ADLER32(results.back());
	  adler32s.emplace_back(adler32);
	  djbs.emplace_back(djb);
	}
	for (const auto djb: djbs) {
	  auto djb_collision = std::count(djbs.begin(), djbs.end(), djb);

	  if (djb_collision == 1) continue;
	  else collisions.first += djb_collision - 1;
	}
	for (const auto adler32: adler32s) {
	  auto adler32_collision = std::count(adler32s.begin(), adler32s.end(), adler32);
	  if (adler32_collision == 1) continue;
	  collisions.second += adler32_collision - 1;
	}

	auto c = SQRT(collisions.first);
	collisions.first = c * (c * (c - 3)) / 2;

	c = SQRT(collisions.second);
	collisions.second = c * (c * (c - 3)) / 2;

	std::cout << "d = " << D << " " << collisions.first << "   " << collisions.second;
  }
}
/*
 * 1. gen M character strings, with specific length D
 * 2. calculate control sum for every using DJB and ADLER32
 * 3. across M = 100'000 repetitions, count all collisions with strings of length D = 8 and D = 100
 *
 *
 */