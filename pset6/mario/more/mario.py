from cs50 import get_int

h = 0
while h < 1 or h > 8:
    #prompt user for height
    h = get_int("Height:")
    
# print pyramid
for r in range(h):
    print(' ' * (h-r-1) + '#' * (r+1) + '  ' + '#' * (r+1))





