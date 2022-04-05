//
// Created by piotr on 05/04/2022.
//



#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
uint64_t Pow2(uint32_t power) {
  if (power == 0) return 1;
  if (power == 1) return 2;
  return 1 << (power - 1);
}
std::vector<uint8_t> Split(uint32_t value) {
  uint32_t remainder, product = 1;
  std::vector<uint8_t> binary;
  while (value != 0) {
	remainder = value % 2;
	binary.push_back(remainder);
	value /= 2;
	product *= 10;
  }
  return binary;
}
template<class T>
std::string ToString(const std::vector<T> &target, char split = ' ') {
  std::string solution;
  if (split == 0)
	solution.reserve(target.size());
  else
	solution.reserve(target.size() * 2);

  for (int i = 0; i < target.size(); i++) {
	solution += (std::to_string(target[i]));
	solution.push_back(split);
  }
  return solution;

}

std::vector<uint64_t> ModuloPowers(uint64_t base, uint64_t binary_distribution_size, uint64_t modulo) {
  std::vector<uint64_t> modulo_powers;
  modulo_powers.push_back(base % modulo);
  modulo_powers.push_back((base * base) % modulo);
  for (int i = 2; i < binary_distribution_size; i++) {
	modulo_powers.push_back((modulo_powers[i - 1] * modulo_powers[i - 1]) % modulo);
  }
  return modulo_powers;
}
uint64_t ModuloPower(uint64_t base, uint64_t power, uint64_t modulo) {
  auto binary_distribution = Split(power);
  auto modulo_powers = ModuloPowers(base, binary_distribution.size(), modulo);
  uint64_t result = 1;
  for (int i = 0; i < binary_distribution.size(); i++)
	if (binary_distribution[i] == 1) {
	  result = (result * modulo_powers[i]) % modulo;
	}
  return result;
}

//	 todo protokół diffiego-hellmana
int main() {

//  std::cout<<"01110011"<<"\t0 1 1 1 0 0 1 1 "<<"\t0  1  1  1  0  0  1  1  ";
  std::cout << ToString(Split(456)) << "\n";
  std::cout << ToString(ModuloPowers(123, Split(456).size(), 789), ' ') << '\n';
  std::cout << ModuloPower(123, 456, 789);
  std::cout << "\tshould be " << 699;
}