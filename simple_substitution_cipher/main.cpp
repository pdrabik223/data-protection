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
  std::cout << ToString(from_shift(3));

  auto cipher = from_shift(  22);

  auto message = load_file(Path("lorem_ipsum.txt"));
  message = encode(message, cipher);


  std::cout << calculate_average_shift(FromText(message), FromEnglishLanguage());

  return 0;
}
