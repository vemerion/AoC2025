#include <iostream>
#include <vector>
#include <string>
#include <print>

static constexpr unsigned max = 100;

struct Rotation {
  char direction{};
  unsigned steps{};

  unsigned rotate(unsigned position) const {
    if (direction == 'R') {
      return (position + steps % max) % max;
    } else {
      return (position + (max - steps % max)) % max;
    }
  }
};

using Rotations = std::vector<Rotation>;

Rotations parse() {
  Rotations result{};
  Rotation rotation{};
  while (std::cin >> rotation.direction >> rotation.steps) {
    result.push_back(rotation);
  }

  return result;
}

unsigned count(const Rotations& rotations, bool part1) {
  unsigned result{};
  unsigned position = 50;
  for (const auto& rotation : rotations) {
    const auto prev = position;
    position = rotation.rotate(position);
    if (!part1) {
      result += rotation.steps / max;
      result += rotation.direction == 'R' ? (position < prev) : (position > prev);
    } else {
      result += position == 0;
    }
  }

  return result;
}

int main() {
  const auto rotations = parse();
  std::println("Part 1 result = {}", count(rotations, true));
  std::println("Part 2 result = {}", count(rotations, false));
  return 0;
}
