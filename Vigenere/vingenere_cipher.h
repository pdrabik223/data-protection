//
// Created by piotr on 08/03/2022.
//

#ifndef DATA_PROTECTION_VIGENERE_VINGENERE_CIPHER_H_
#define DATA_PROTECTION_VIGENERE_VINGENERE_CIPHER_H_
#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <map>
#include <ciso646>
static std::map<int, char> kTabulaRecta;
static std::map<int, char> kReversedTabulaRecta;

char NormalizeChar(char val);
struct Alphabet {
  static const std::string k_data;
  static const int alphabet_size;
  char operator[](int id) {

	if (id >= 0)
	  return k_data[id % k_data.size()];

	id = -1 * id;
	id %= k_data.size();
	id = k_data.size() - id;
	return k_data[id];
  }
  static bool IsInAlphabet(char letter) {
	return std::find(Alphabet::k_data.begin(), Alphabet::k_data.end(), letter) != Alphabet::k_data.end();
  }
};

int Hash(char first, char second);
struct Password {
  std::string password;
  size_t counter = 0;
  explicit Password(const std::string &key) {
	password = key;
	for (auto &i: password) {
	  i = NormalizeChar(i);

	}
  }

  void Clear() { counter = 0; }
  size_t Size() {
	return password.size();
  }

  char Next() {
	auto tmp = password[counter % password.size()];
	++counter;
	return tmp;
  }

};

void InitTabulaRecta();
void InitReversedTabulaRecta();
std::string &Encrypt(std::string &message, Password &password);
std::string &Decrypt(std::string &message, Password &password);

/// read file, than correct every small letter to huge
std::string LoadFile(const std::string &path);

void SaveFile(const std::string &message, const std::string &path);
#endif //DATA_PROTECTION_VIGENERE_VINGENERE_CIPHER_H_
