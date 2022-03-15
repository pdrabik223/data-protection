#include <string>
//
// Created by piotr on 08/03/2022.
//
#include <chrono>
std::string Path(const std::string &file) {
  return std::string("../Vigenere/" + file);
}
#include "vingenere_cipher.h"
int main() {

  InitTabulaRecta();
  InitReversedTabulaRecta();

// config
  Password password("Z01");
  std::string message = load_file(Path("in.txt"));



  auto t1 = std::chrono::high_resolution_clock::now();
  Encrypt(message, password);
  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t2).count();

  return 0;
}
