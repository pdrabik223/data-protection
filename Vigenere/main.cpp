#include <string>
//
// Created by piotr on 08/03/2022.
//
#include "attack_vingenere.h"

std::string Path(const std::string &file) {
  return std::string("../Vigenere/" + file);
}
#include "vingenere_cipher.h"

int main() {

// config
  InitTabulaRecta();
  InitReversedTabulaRecta();

  Password password("12345");

  std::string message = "message123";
  std::cout << message << "\n";

  message = Encrypt(message, password);
  std::cout << message << "\n";
  message = Decrypt(message, password);
  std::cout << message << "\n";

  std::cout << "from file\n";
  message = LoadFile(Path("simple_in.txt"));
  std::cout << message << "\n";

  message = Encrypt(message, password);
  std::cout << message << "\n";
  message = Decrypt(message, password);
  std::cout << message << "\n";

  return 0;
}
