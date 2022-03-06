//
// Created by piotr on 23/02/2022.
//
// the task create encoder that takes letters and numbers and encodes them, leave the rest of symbols, polish letters may find they way in.
#include "substitution_cipher.h"

std::string load_file(const std::string &path)
{
  std::string file_content;
  std::fstream file;
  file.open(path, std::ios::in);
  //  file.unsetf(std::ios::skipws);
  char tmp = ' ';
  while (file >> std::noskipws >> tmp)
  {
    if (tmp >= 'a' && tmp <= 'z')
      tmp -= 32;
    file_content.push_back(tmp);
  }

  return file_content;
}
void save_file(const std::string &message, const std::string &path)
{
  std::string file_content;
  std::wfstream file;
  file.open(path, std::ios::out);
  for (auto &i : message)
    file << i;
  file.close();
}
Encoding from_shift(int32_t shift)
{
  Encoding encoding;

  for (char i = 'A'; i <= 'Z'; i++)
    encoding.push_back({i, 0});

  for (char i = '0'; i <= '9'; i++)
    encoding.push_back({i, 0});

  const size_t dict_size = encoding.size();

  while (abs(shift) >= dict_size)
  {
    if (shift > 0)
      shift -= dict_size;
    if (shift < 0)
      shift += dict_size;
  }
  uint32_t id = shift;
  for (int i = 0; i < dict_size; i++, id++)
  {
    if (id >= dict_size)
      id = 0;
    encoding[i].second = encoding[id].first;
  }
  return encoding;
}
std::string ToString(const Encoding& encoding)
{
  std::string output = "";
  for (auto i : encoding)
  {
    output.push_back(i.first);
    output.push_back('-');
    output.push_back('>');
    output.push_back(i.second);
    output.push_back('\n');
  }
  return output;
}

char encode_letter(char key, const Encoding &encoding)
{
  for (auto i : encoding)
    if (i.first == key)
      return i.second;
  return key;
}
char decode_letter(char val, const Encoding &encoding)
{
  for (auto i : encoding)
    if (i.second == val)
      return i.first;
  return val;
}

std::string encode(std::string &message, const Encoding &encoding)
{
  std::string encoded_message;
  encoded_message.reserve(message.size());
  for (auto i : message)
    encoded_message.push_back(encode_letter(i, encoding));

  return encoded_message;
}
std::string decode(const std::string &message, const Encoding &encoding)
{
  std::string decoded_message;
  decoded_message.reserve(message.size());
  for (auto i : message)
    decoded_message.push_back(decode_letter(i, encoding));

  return decoded_message;
}
