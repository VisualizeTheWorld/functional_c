# Takes a binary and a function name and returns the symbols from that function as a C array.
# Takes the objdump in stdin
# The parsing is *very* brittle

from sys import argv
if len(argv) < 2:
  print("Must specify function to extract at command line!")
  exit()

fun = argv[-1]

def nop():
  return;

dump = []
binary = []

def line_to_bytes(line, b):
  line = line.split(':')[1].strip()
  while True:
    if len(line) < 2:
      break
    nextb = line[:2]
    line = line[3:]
    if ' ' in nextb or '\t' in nextb:
      break
    binary.append(nextb)

try:
  while True:
    dump.append(input())
except EOFError:
  # Do nothing
  nop()

i = 0
while True:
  if (i >= len(dump)):
    print("Err: could not find symbol %s" % fun)
    exit()
  i += 1
  if (('<' + fun + '>:') in dump[i-1]):
    break

while (len(dump[i]) > 5 and i < len(dump)):
  line_to_bytes(dump[i],binary)
  i += 1

binary = list(map(lambda s: '0x' + s,binary))
print('char foo[' + str(len(binary)) + '] = {' + ','.join(binary) + '};')
