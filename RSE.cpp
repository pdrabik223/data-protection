//
// Created by piotr on 10/05/2022.
//


#include <cstdint>

#include <vector>
#include <iostream>

#include <cmath>
bool BruteForceIsPrime(uint64_t value) {
  double limit = sqrt(value);
  for (int i = 2; i <= limit; i++)
	if (value % i == 0) return false;
  return true;
}

std::pair<int64_t, int64_t> Calculate(int64_t a, int64_t b) {
  std::vector<int64_t> qs = {0, 0};
  std::vector<int64_t> rs = {a, b};
  std::vector<int64_t> ss = {1, 0};
  if (a < b) {
	rs = {b, a};
	ss = {0, 1};
  }

  while (true) {
	if (rs.back() == 1 and ss.back() >= 0) return {rs.back(), abs(ss.back())};
	if (rs.back() == 1 and ss.back() < 0) return {rs.back(), ss.back()};
	if (rs.back() == 0) throw std::invalid_argument("a and b are not sudo primes");

	auto q = rs.front() / rs.back();
	std::swap(qs.front(), qs.back());
	qs.back() = q;

	auto r = rs.front() - rs.back() * qs.back();
	auto s = ss.front() - ss.back() * qs.back();

	rs.front() = rs.back();
	ss.front() = ss.back();

//	if (s < 0) s += b;
	rs.back() = r;
	ss.back() = s;
  }

}
std::vector<uint8_t> Split(uint32_t value) {
  uint32_t remainder, product = 1;
  std::vector<uint8_t> binary;
  while (value != 0) {
	remainder = value % 2;
	binary.push_back(remainder);
	value /= 2;
	product *= 10;
  }
  return binary;
}

std::vector<uint64_t> ModuloPowers(uint64_t base, uint64_t binary_distribution_size, uint64_t modulo) {
  std::vector<uint64_t> modulo_powers;
  modulo_powers.push_back(base % modulo);
  modulo_powers.push_back((base * base) % modulo);
  for (int i = 2; i < binary_distribution_size; i++) {
	modulo_powers.push_back((modulo_powers[i - 1] * modulo_powers[i - 1]) % modulo);
  }
  return modulo_powers;
}
uint64_t ModuloPower(uint64_t base, uint64_t power, uint64_t modulo) {

  auto binary_distribution = Split(power);

  auto modulo_powers = ModuloPowers(base, binary_distribution.size(), modulo);
  uint64_t result = 1;
  for (int i = 0; i < binary_distribution.size(); i++)
	if (binary_distribution[i] == 1) {
	  result = (result * modulo_powers[i]) % modulo;
	}
  return result;
}
char Encrypt(char val, uint64_t pow, uint64_t mod) {
  return (char)ModuloPower((int)val, pow, mod);
}
int main() {
  srand(time(NULL));
  std::cout << "r =" << Calculate(7, 10).first << " s = " << Calculate(7, 10).second << std::endl;

  uint64_t p, q;
  p = rand() / 2;
  if (p % 2 == 0) p += 1;
  while (!BruteForceIsPrime(p))
	p += 2;

  q = rand() / 2;
  if (q % 2 == 0) q += 1;
  while (!BruteForceIsPrime(q))
	q += 2;

  std::cout << "type in prime, for example: " << p << " p:";
  std::cin >> p;
  if (!BruteForceIsPrime(p))
	throw std::invalid_argument("p must be prime");

  std::cout << "type in prime, for example: " << q << " q:";

  std::cin >> q;
  if (!BruteForceIsPrime(q))
	throw std::invalid_argument("q must be prime");

  auto n = p * q;
  auto fi = (p - 1) * (q - 1);
  uint64_t e, d;
  while (true) {
	e = 1 + rand() % fi;
	try {

	  d = Calculate(e, fi).second;

	} catch (std::invalid_argument) {
	  continue;
	}
	break;
  }
  std::string message = "Piotr Drabik";
  std::cout << "massage to cipher, for example " << message << " :";
  std::cin >> message;
  std::string encrypted_message;
  for (auto c: message) {
	encrypted_message.push_back(Encrypt(c, e, n));
  }
  std::string decrypted_message;
  for (auto c: encrypted_message) {
	decrypted_message.push_back(Encrypt(c, d, n));
  }

  std::cout << "\n";
  std::cout << "  original message: " << message << std::endl;
  std::cout << " encrypted message: " << encrypted_message << std::endl;
  std::cout << " decrypted message: " << decrypted_message << std::endl;
  /*
 * 1. get p , q: from user
 * 2. check p & q for primes
 * 3. n = p * q
 * 4. fi(n) = (p-1)(q-1)
 * 5. randomly gen e:  1 < e < fi(n) & NWD(e,fi(n)) == 1
 * 6. get d: e * d mod fi(n) = 1
 * 7. get message: from user
 * 8. convert letters to ascii
 * 9. encrypt ascii: encrypt = (message)^e mod n
 * 10. decrypt ascii: decrypt = (encrypt)^d mod n
 * 11. display
 *  note: encrypt decrypt one letter at the time or in big chunks or whatever
 */
}