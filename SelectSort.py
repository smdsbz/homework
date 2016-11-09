#!usr/bin/python3

'''
SelectSort.py
by Xiaoguang Zhu
'''

#############################################

def select_sort(list):
	tmp = list
	for i in range(len(tmp)-1):
		min_index = i
		for j in range(i, len(tmp)):	# get index of min
			if tmp[j] < tmp[i]:
				min_index = j
		if min_index > i:	# swap value if needed
			tmp[i], tmp[min_index] = tmp[min_index], tmp[i]
	return tmp

############################################

array = []
print("Enter at least two numbers to start select-sorting.")
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
print(select_sort(array))
