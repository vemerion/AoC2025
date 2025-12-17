#include <iostream>
#include <string>
#include <vector>
#include <print>
#include <utility>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <numeric>

struct Present {
  std::vector<std::string> shape{};

  unsigned max() const {
    return shape.size() * shape[0].size();
  }

  unsigned min() const {
    return std::accumulate(shape.begin(), shape.end(), 0u, [](const auto& a, const auto& b) { return a + std::count(b.begin(), b.end(), '#'); });
  }
};

struct Region {
  unsigned width{};
  unsigned height{};
  std::vector<unsigned> counts{};
};

using Presents = std::vector<Present>;
using Regions = std::vector<Region>;

unsigned fit(const Presents& presents, const Regions& regions) {
  unsigned result{};
  for (const auto& region : regions) {
    unsigned min{};
    unsigned max{};
    unsigned size = region.width * region.height;
    for (size_t i = 0; i < region.counts.size(); i++) {
      min += presents[i].min() * region.counts[i];
      max += presents[i].max() * region.counts[i];
    }
    if (min > size) {
      continue;
    } else if (max <= size) {
      result++;
    } else {
      assert(false);
    }
  }

  return result;
}

std::pair<Presents, Regions> parse() {
  Presents presents{};
  Regions regions{};
  std::string line{};
  Present present{};
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      presents.push_back(std::move(present));
    } else if (line[0] == '#' || line[0] == '.') {
      present.shape.push_back(std::move(line));
    } else if (line.contains('x')) {
      std::istringstream stream{std::move(line)};
      unsigned n{};
      regions.push_back({});
      stream >> regions.back().width;
      stream.ignore();
      stream >> regions.back().height;
      stream.ignore();
      while (stream >> n) {
        regions.back().counts.push_back(n);
      }
    }
  }

  return {presents, regions};
}

int main() {
  const auto [presents, regions] = parse();
  std::println("Part 1 result = {}", fit(presents, regions));
  return 0;
}
