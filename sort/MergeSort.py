#!/usr/bin/python3

'''
MergeSort.py
by Xiaoguang Zhu
'''

#############################################

def merge(left, right):
	merged = []
	l = 0; r = 0
	while l < len(left) and r < len(right):
		if left[l] <= right[r]:
			merged.append(left[l])
			l += 1
		else:
			merged.append(right[r])
			r += 1
	merged.extend(left[l:])
	merged.extend(right[r:])
	return merged

def merge_sort(list):
	if len(list) < 2:
		return list
	else:
		middle = len(list) // 2
		left = merge_sort(list[:middle])
		right = merge_sort(list[middle:])
		return merge(left, right)

############################################

array = []
print("Enter at least two numbers to start merge-sorting.")
print("(You can end inputing anytime by entering nonnumeric)")

# get numbers
while True:
	try:
		array.append(float(input(">> ")))
	except ValueError:	# exit inputing
		break

print("\nThe array you've entered was:", array)
print("\nNow sorting...")

print("\nAll done! Now the moment of truth!")
print(merge_sort(array))
