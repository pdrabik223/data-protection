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
// 101
//
//  std::cout<<"01110011"<<"\t0 1 1 1 0 0 1 1 "<<"\t0  1  1  1  0  0  1  1  ";
// x = b^p % m
// 123^456 % 789 = 699


//  std::cout << ToString(Split(40)) << "\n";
//  std::cout << ToString(ModuloPowers(40, Split(12).size(), 11), ' ') << '\n';
//  std::cout << ModuloPower(4321, 5678, 9876);
  // std::cout << "\tshould be " << 699;

  uint64_t g = 8992; // public const
  uint64_t p = 3889;  // public const prime?

  uint64_t a = 13579; // private generated randomly, should


  uint64_t B = 307307; // received number
  uint64_t A = ModuloPower(g, a, p); // this number is passed
  std::cout << "A = " << A << std::endl;
//
  uint64_t k_a = ModuloPower(B, a, p); // this should be same as theis
  std::cout << "k_a: " << k_a;

  printf("Alice\n");
  std::cout << "\ng = ";
  std::cin >> g;
  std::cout << "p = ";
  std::cin >> p;

  while (true) {
	std::cout << "\na = ";
	std::cin >> a;
	std::cout << "\nA = " << ModuloPower(g, a, p);
	std::cout << "\nB = ";
	std::cin >> B;
	std::cout << "k_a =" << ModuloPower(B, a, p);
  }

}
