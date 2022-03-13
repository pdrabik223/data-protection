//
// Created by piotr on 08/03/2022.
//
#include <cassert>
#include "vingenere_cipher.h"

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

};
const std::string Alphabet::k_data = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int Alphabet::alphabet_size = Alphabet::k_data.size();

static bool IsInAlphabet(char val) {
  if (val >= 'A' and val <= 'Z') return true;
  if (val >= '0' and val <= '9') return true;
  return false;

}
char NormalizeChar(char val) {
  return val >= 'a' and val <= 'z' ? val - 32 : val;
}

void InitTabulaRecta() {
  int shift = 0;
  Alphabet alphabet;
  for (char a: Alphabet::k_data) {
	int i = 0;
	for (char b: Alphabet::k_data) {
//	  kTabulaRecta[Hash(a, b)] = alphabet[shift + i];
	  kTabulaRecta.insert({Hash(a, b), alphabet[shift + i]});
	  i++;

	}
	shift++;
  }
}

void InitReversedTabulaRecta() {
  int shift = 0;
  Alphabet alphabet;
  for (char a: Alphabet::k_data) {
	int i = 0;
	for (char b: Alphabet::k_data) {
//	  kReversedTabulaRecta[Hash(a, b)] = alphabet[shift + i];
	  kReversedTabulaRecta.insert({Hash(a, b), alphabet[shift + i]});
	  i++;
	}
	shift--;
  }
}

int Hash(char first, char second) {
  int i_first = (int)first;
  int i_second = (int)second;

  if (i_first >= 'A' and i_first <= 'Z') i_first -= 55;
  else if (i_first >= '0' and i_first <= '9') i_first -= 48;
  else
	assert(false and "first is not in dict");
  // A = 10;

  if (i_second >= 'A' and i_second <= 'Z') i_second -= 55;
  else if (i_second >= '0' and i_second <= '9') i_second -= 48;
  else
	assert(false and "second is not in dict");

  return i_first * Alphabet::alphabet_size + i_second;
}
std::string &Encrypt(std::string &message, Password &password) {
//  std::string encrypted_message;
  password.Clear();

  for (char &c: message) {
	if (IsInAlphabet(NormalizeChar(c))) {
	  c = kTabulaRecta[Hash(NormalizeChar(c), password.Next())];
	}
  }
  return message;
}
std::string &Decrypt(std::string &message, Password &password) {
  password.Clear();

  for (char &c: message)
	if (IsInAlphabet(NormalizeChar(c))) {
	  c = kReversedTabulaRecta[Hash(password.Next(), NormalizeChar(c))];
	}
  return message;
}
