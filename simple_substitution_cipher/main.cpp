//
// Created by piotr on 04/03/2022.
//

#include <string>
#include <iostream>
#include "substitution_cipher.h"
#include "statistical_attack.h"
std::string Path(const std::string &file) {
  return std::string("../simple_substitution_cipher/" + file);
}

int main() {
//  std::cout << ToString(from_shift(3));
  int counter = 0;
//  for (int i = 0; i < 36; i++) {
  auto cipher = from_shift(0);

  auto message = load_file(Path("lorem_ipsum.txt"));
  message = encode(message, cipher);
calculate_average_shift(FromText(message),FromEnglishLanguage());
//	std::cout << i << " -> " << prediction << "\n";
//	if (i == prediction) counter++;
//  }
  std::cout << "counter:\t" << counter << "\n";
  std::cout << "correctness:\t" << counter / 36.0;

  return 0;
}
