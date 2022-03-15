//
// Created by piotr on 08/03/2022.
//

#ifndef DATA_PROTECTION_VIGENERE_VINGENERE_CIPHER_H_
#define DATA_PROTECTION_VIGENERE_VINGENERE_CIPHER_H_
#include <iostream>
#include <string>
#include <array>
#include <map>
#include <ciso646>
static std::map<int, char> kTabulaRecta;
static std::map<int, char> kReversedTabulaRecta;
char NormalizeChar(char val);

int Hash(char first, char second);
struct Password {
  std::string password;
  size_t counter = 0;
  explicit Password(const std::string &key) {
	password = key;
	for (auto &i: password)
	  i = NormalizeChar(i);
  }

  void Clear() { counter = 0; }

  char Next() {
	auto tmp = password[counter % password.size()];
	++counter;
	return tmp;
  }

};

struct Alphabet;
void InitTabulaRecta();
void InitReversedTabulaRecta();
std::string &Encrypt(std::string &message, Password &password);
std::string &Decrypt(std::string &message, Password &password);

/// read file, than correct every small letter to huge
std::string load_file(const std::string &path);

void save_file(const std::string &message, const std::string &path);
#endif //DATA_PROTECTION_VIGENERE_VINGENERE_CIPHER_H_
