#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <print>
#include <cassert>
#include <map>
#include <sstream>
#include <numeric>

struct Machine {
  std::vector<unsigned> lights{};
  std::vector<std::vector<unsigned>> buttons{};
  std::vector<unsigned> joltage{};


  unsigned configure() const {
    std::map<std::vector<unsigned>, unsigned> cache{};
    struct Entry {
      std::vector<unsigned> light{};
      unsigned step{};
    };
    std::list<Entry> list{{std::vector<unsigned>(lights.size(), 0), 0}};

    while (!list.empty()) {
      const auto [l, s] = list.front();
      list.pop_front();
      if (l == lights) {
        return s;
      }

      if (const auto found = cache.find(l); found != cache.end() && found->second <= s) {
        continue;
      }

      cache[l] = s;

      for (const auto& button : buttons) {
        auto next = l;
        for (const auto& b : button) {
            next[b] = !next[b];
        }
        list.push_back({std::move(next), s + 1});
      }
    }

    assert(false);
  }
};

using Machines = std::vector<Machine>;

Machines parse() {
  Machines machines{};
  std::string s{};
  while (std::cin >> s) {
    if (s[0] == '[') {
      machines.push_back({});
      for (size_t i = 1; i < s.size() - 1; i++) {
        machines.back().lights.push_back(s[i] == '#');
      }
    } else if (s[0] == '(') {
      machines.back().buttons.push_back({});
      for (size_t i = 1; i < s.size() - 1; i += 2) {
        machines.back().buttons.back().push_back(s[i] - '0');
      }
    } else if (s[0] == '{') {
      std::istringstream stream{std::move(s)};
      unsigned n{};
      char unused{};
      while (stream >> unused >> n) {
        machines.back().joltage.push_back(n);
      }
    }
  }
  return machines;
}

int main() {
  const auto machines = parse();
  std::println("Part 1 result = {}", std::accumulate(machines.begin(), machines.end(), 0u, [](const auto& a, const auto& b) { return a + b.configure(); }));
  return 0;
}
