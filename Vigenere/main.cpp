//
// Created by piotr on 08/03/2022.
//
#include "vingenere_cipher.h"
int main() {

  InitTabulaRecta();
  InitReversedTabulaRecta();

  Password password("password");
  std::cout << password.password.size() << "\n";

  std::string message = "some really cool text coming your way m8";

//  for (auto i: tabula_recta) {
//	std::cout << i.first / NO_LETTERS << "\t" << i.first % NO_LETTERS << " -> " << i.second << "\n";
//  }


  std::cout << Encrypt(message, password) << "\n";

  std::cout << Decrypt(message, password);
  return 0;
}
