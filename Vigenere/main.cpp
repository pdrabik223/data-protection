#include <string>
//
// Created by piotr on 08/03/2022.
//
#include "attack_vingenere.h"
#include <chrono>
std::string Path(const std::string &file) {
  return std::string("../Vigenere/" + file);
}
#include "vingenere_cipher.h"
#include "kasiski_attack.h"


int main() {

  InitTabulaRecta();
  InitReversedTabulaRecta();

// config
  Password password("12345");
  std::string message = load_file(Path("in.txt"));

  for (int j = 2; j <= password.Size(); j++) {

	auto i_cs = IC(message, j);

	double cd_avg = 0;

	for (double i_c : i_cs) {
	  cd_avg += i_c;
	}

	std::cout << j << "\t" << cd_avg / i_cs.size() << "\n";

  }

//  for (auto i: ComputeRepetitions(Encrypt(message,password)))
//	std::cout << i.first << "\t" << i.second << "\n";

//  auto t1 = std::chrono::high_resolution_clock::now();
//  Encrypt(message, password);
//  auto t2 = std::chrono::high_resolution_clock::now();
//  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t2).count();

  return 0;
}
