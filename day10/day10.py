from scipy.optimize import linprog
import sys
import numpy

buttons = []
joltage = []

part2 = 0

for line in sys.stdin:
  buttons = []
  joltage = []
  splits = line.split(' ')
  for split in splits:
    if split[0] == '(':
      buttons.append([])
      for index in split.replace('(', '').replace(')', '').split(','):
        buttons[len(buttons) - 1].append(int(index))
    elif split[0] == '{':
      for index in split.replace('{', '').replace('}', '').split(','):
        joltage.append(int(index))
  A = []
  b = joltage
  c = [1] * len(buttons)
  bounds = [(0, None)] * len(buttons)
  integrality = [1] * len(buttons)
  for i in range(len(joltage)):
    a = [0] * len(buttons)
    for j in range(len(buttons)):
      if i in buttons[j]:
        a[j] = 1
    A.append(a)
  part2 += int(linprog(c, A_eq = numpy.array(A), b_eq = numpy.array(b), bounds = bounds, integrality = integrality).fun)
    

print(f'Part 2 result = {part2}')
