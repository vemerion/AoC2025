#include <iostream>
#include <string>
#include <vector>
#include <print>

using Num = unsigned long long;

using Bank = std::vector<unsigned>;
using Banks = std::vector<Bank>;

using Cache = std::vector<Num>;

Num joltage(Cache& cache, const Bank& bank, size_t index, size_t left, Num value) {
  if (cache[left] < value) {
    cache[left] = value;
  }

  if (left == 0) {
    return value;
  } else if (index >= bank.size()) {
    return 0;
  } else if (value < cache[left]) {
    return 0;
  }

  return std::max(joltage(cache, bank, index + 1, left, value), joltage(cache, bank, index + 1, left - 1, value * 10 + bank[index]));
}

Num joltage(const Banks& banks, size_t count) {
  Num sum{};
  for (const auto& bank : banks) {
    Cache cache(count + 1, 0);
    sum += joltage(cache, bank, 0, count, 0);
  }
  return sum;
}

Banks parse() {
  Banks result{};
  std::string line{};
  while (std::getline(std::cin, line)) {
    Bank bank{};
    for (char c : line) {
      bank.push_back(c - '0');
    }
    result.push_back(std::move(bank));
  }
  return result;
}

int main() {
  Banks banks = parse();
  std::println("Part 1 result = {}", joltage(banks, 2));
  std::println("Part 2 result = {}", joltage(banks, 12));
  return 0;
}
