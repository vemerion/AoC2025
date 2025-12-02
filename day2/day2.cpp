#include <iostream>
#include <string>
#include <print>
#include <vector>
#include <flat_set>
#include <numeric>

using Num = unsigned long long;

Num append(Num n, Num m) {
  return std::stoull(std::to_string(n) + std::to_string(m));
}

struct Range {
  Num first{};
  Num last{};

  Num invalid(bool part1) const {
    std::flat_set<Num> invalid{};
    for (Num i = 1; append(i, i) <= last; i++) {
      auto num = append(i, i);
      if (num >= first) {
        invalid.insert(num);
      }
      if (!part1) {
        num = append(num, i);
        for (; num <= last; num = append(num, i)) {
          if (num >= first) {
            invalid.insert(num);
          }
        }
      }
    }
    return std::accumulate(invalid.begin(), invalid.end(), Num{});
  }
};

using Ranges = std::vector<Range>;

Ranges parse() {
  Ranges ranges{};
  Range range{};
  char unused{};
  while (std::cin >> range.first >> unused >> range.last) {
    ranges.push_back(range);
    std::cin.ignore();
  }
  return ranges;
}

Num invalid(const Ranges& ranges, bool part1) {
  return std::accumulate(ranges.begin(), ranges.end(), Num{}, [part1](const auto a, const auto& b) { return a + b.invalid(part1); });
}

int main() {
  const auto ranges = parse();
  std::println("Part 1 result = {}", invalid(ranges, true));
  std::println("Part 2 result = {}", invalid(ranges, false));
  return 0;
}
