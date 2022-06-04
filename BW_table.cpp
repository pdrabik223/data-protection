//
// Created by piotr on 30/05/2022.
//

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <map>
std::string alphabet = {"abcdefghijklmnoprst"};

uint64_t DJB(const std::string &ascii_array) {
  uint64_t hash = 5381;

  for (const uint8_t kCharacter: ascii_array) {
	hash = hash * 33 + kCharacter;
  }

  return hash;
}
uint64_t Pow(uint64_t base, uint64_t pow) {
  if (pow == 0) return 1;
  if (pow == 1) return base;
  for (int i = 0; i < pow; i++)
	base *= base;

  return base;

}

std::string UnDJB(uint64_t hash) {
  std::string result;
  for (int i = 0; i < 8; i++) {

//	if (hash < Pow(alphabet.size(), i)) return result;

	result.push_back('a' + (hash / Pow(alphabet.size(), i)) % alphabet.size());
  }
  return result;
}

std::string GenString(uint64_t length) {
  std::string random_string;
  for (int i = 0; i < length; i++)
	random_string.push_back(alphabet[rand() % alphabet.size()]);
  return random_string;
}

void Tostring(const std::vector<std::pair<std::string, uint64_t>> &bw_table) {
  std::string output;
  for (auto &y: bw_table) {
	std::clog << y.first << " : ... :" << y.second << "\n";
  }
}

int main() {
  srand(time(NULL));
  std::map<uint64_t, std::string> bw_table;
//  std::vector<std::pair<std::string, uint64_t>> bw_table;
  uint64_t height = 10'000; // no passwords generated at the beginning
  uint64_t width = 10'000; // no password to hash conversions pairs
  uint64_t password_length = 5;

  printf("creating black & white table...\t");
  for (int y = 0; y < height; y++) {
	auto original_password = GenString(password_length);
	uint64_t hash = DJB(original_password);

	for (int x = 1; x < width; x++) {
	  hash = DJB(UnDJB(hash));
	}
	if(bw_table.find(hash) == bw_table.end())
		bw_table.insert({hash, original_password});
  }
//  Tostring(bw_table);
  printf(" done\n");
  std::string password_of_interest = "piotr";
  const auto hash = DJB(password_of_interest);
  printf("commencing search for piotr...\n");

  auto local_hash = hash;

//  pass -> hash

  for (int w = 0; w < width; w++) {

	local_hash = DJB(UnDJB(local_hash));

	for (int y = 0; y < height; y++) {

	  if (bw_table.find(local_hash) != bw_table.end()) {
		std::clog << " original password: "
				  << password_of_interest
				  << " hit:\t";

		std::string solution = bw_table.find(local_hash)->second;

		for (int i = 0; i < width - w; i++)
		  solution = UnDJB(DJB(solution));

		std::clog << solution << "\n";

	  }
	}
  }
  return 0;
}