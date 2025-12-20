#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <print>
#include <sstream>
#include <list>
#include <set>

using Devices = std::map<std::string, std::set<std::string>>;

using Num = unsigned long long;

Devices parse() {
  Devices result{};
  std::string line{};
  while (std::getline(std::cin, line)) {
    std::istringstream stream{std::move(line)};
    std::string name{};
    std::string connection{};
    stream >> name;
    name = name.substr(0, name.size() - 1);
    while (stream >> connection) {
      result[name].insert(std::move(connection));
    }
  }
  return result;
}

Num paths(const Devices& devices, const std::string& from, const std::string& to, Num start) {
  std::set<std::string> processing{devices.at(from).begin(), devices.at(from).end()};
  std::map<std::string, Num> counts{{from, start}};

  while (!processing.empty()) {
    std::set<std::string> nexts{};
    for (const auto& device : processing) {
      const auto prev = counts[device];
      Num current{};
      for (const auto& [name, connections] : devices) {
        if (connections.contains(device)) {
          current += counts[name];
        }
      }
      if (prev != current) {
        counts[device] = current;
        if (const auto found = devices.find(device); found != devices.end()) {
          for (const auto& connection : found->second) {
            nexts.insert(connection);
          }
        }
      }
    }
    processing = std::move(nexts);
  }

  return counts[to];
}

Num part1(const Devices& devices) {
  return paths(devices, "you", "out", 1);
}

Num part2(const Devices& devices) {
  return paths(devices, "dac", "out", paths(devices, "fft", "dac", paths(devices, "svr", "fft", 1)));
}

int main() {
  const auto devices = parse();
  std::println("Part 1 result = {}", part1(devices));
  std::println("Part 2 result = {}", part2(devices));

  return 0;
}
