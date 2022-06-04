//
// Created by piotr on 29/03/2022.
//
#include <cmath>
#include <cstdint>
#include <iostream>
#include "test.h"
//using Int = unsigned long long;

bool BruteForceIsPrime(uint64_t value) {
  double limit = sqrt(value);
  for (int i = 2; i <= limit; i++)
	if (value % i == 0) return false;
  return true;
}

uint64_t Pow2(uint64_t val) {
  return val * val;
}

uint64_t GetS(int p, uint64_t m) {
  if (p == 0) return 4;
  return (Pow2(GetS(p - 1, m)) - 2) % m;
}

uint64_t MFromP(int p) {
  return (1ll << p) - 1;
}
bool LucasLehmerIsPrime(int p) {
  uint64_t m = MFromP(p);
  return GetS(p - 2, m) == 0;

}
char ToChar(bool val) {
  if (val) return 'y';
  else return 'n';
}
// partial specialization optimization for 64-bit numbers
int NoDigits(uint64_t x) {

  if (x >= 10000000000) {
	if (x >= 100000000000000) {
	  if (x >= 10000000000000000) {
		if (x >= 100000000000000000) {
		  if (x >= 1000000000000000000)
			return 19;
		  return 18;
		}
		return 17;
	  }
	  if (x >= 1000000000000000)
		return 16;
	  return 15;
	}
	if (x >= 1000000000000) {
	  if (x >= 10000000000000)
		return 14;
	  return 13;
	}
	if (x >= 100000000000)
	  return 12;
	return 11;
  }
  if (x >= 100000) {
	if (x >= 10000000) {
	  if (x >= 100000000) {
		if (x >= 1000000000)
		  return 10;
		return 9;
	  }
	  return 8;
	}
	if (x >= 1000000)
	  return 7;
	return 6;
  }
  if (x >= 100) {
	if (x >= 1000) {
	  if (x >= 10000)
		return 5;
	  return 4;
	}
	return 3;
  }
  if (x >= 10)
	return 2;
  return 1;
}
int main() {

  int max_p = 31;
  for (int p = 2; p <= max_p; p++) {
	if (BruteForceIsPrime(p)) {
	  uint64_t m = MFromP(p);
	  printf("p: %d\tM: %llu %*c\t%c\n",
			 p,
			 m,
			 15 - NoDigits(m),
			 ToChar(BruteForceIsPrime(m)),
			 ToChar(LucasLehmerIsPrime(p)));
	}
  }

  test test_2;
  std::cout << test_2.fun();
  return 0;
}