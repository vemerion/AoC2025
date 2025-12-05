#include <iostream>
#include <string>
#include <vector>
#include <print>
#include <numeric>
#include <ranges>

using Num = unsigned long long;

struct Range {
  Num min{};
  Num max{};

  bool has(Num n) const {
    return min <= n && n <= max;
  }

  Num count() const {
    return max - min + 1;
  }

  bool overlap(const Range& other) const {
    return !(other.max < min || max < other.min);
  }

  Range merge(const Range& other) const {
    return {std::min(min, other.min), std::max(max, other.max)};
  }
};

using Ranges = std::vector<Range>;
using Ingredients = std::vector<Num>;

class Inventory {
  friend std::istream& operator>>(std::istream& is, Inventory& inventory);
public:
  Num part1() const {
    Num result{};
    for (const auto& ingredient : ingredients) {
      for (const auto& range : fresh) {
        if (range.has(ingredient)) {
          result++;
          break;
        }
      }
    }
    return result;
  }

  Num part2() const {
    Ranges current = fresh;
    Ranges disjoint{};
    while (!current.empty()) {
      Ranges next{};
      auto range = current[0];
      for (size_t i = 1; i < current.size(); i++) {
        if (const auto r = current[i]; range.overlap(r)) {
          range = range.merge(r);
        } else {
          next.push_back(r);
        }
      }
      if (next.size() + 1 == current.size()) { // No change
        disjoint.push_back(range);
      } else {
        next.push_back(range);
      }
      current = std::move(next);
    }

    return std::accumulate(disjoint.begin(), disjoint.end(), Num{}, [](const auto& sum, const auto& range) { return sum + range.count(); });
  }
private:
  Ranges fresh{};
  Ingredients ingredients{};
};

std::istream& operator>>(std::istream& is, Inventory& inventory) {
  std::string line{};
  bool ingredients{};
  while (std::getline(is, line)) {
    if (line.empty()) {
      ingredients = true;
    } else if (ingredients) {
      inventory.ingredients.push_back(std::stoull(line));
    } else {
      const auto split = line.find('-');
      inventory.fresh.push_back({std::stoull(line.substr(0, split)), std::stoull(line.substr(split + 1, line.size() - split))});
    }
  }
  return is;
}

int main() {
  Inventory inventory{};
  std::cin >> inventory;
  std::println("Part 1 result = {}", inventory.part1());
  std::println("Part 2 result = {}", inventory.part2());
  return 0;
}
