#!/usr/bin/python3

'''
BubbleSort.py
by Xiaoguang Zhu
'''

array = []
print("Enter at least two numbers to start bubble-sorting.")
print("(You can end inputing anytime by entering nonnumeric)")

# get numbers
while True:
	try:
		array.append(float(input(">> ")))
	except ValueError:	# exit inputing
		break

print("\nThe array you've entered was:"); print(array)
print("\nNow sorting...")

# sorting
for x in range(len(array)-1, 0, -1):
	for y in range(x):
		if array[y] > array[y+1]:
			array[y], array[y+1] = array[y+1], array[y]
			print(array)

# output
print("\nAll done! Now the moment of truth!")
print(array)
