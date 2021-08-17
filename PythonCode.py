import re
import string
import os



## this is called for the first switch statement
def displayFreq():
	print_frequencies(
		calculate_frequencies(),
		lambda item, count: "{}: {}".format(item, count))


## calculations for the frequency when item appears
def calculate_frequencies():
	filename = ("veggies.txt")
	frequencies = {}
	with open(filename, "r") as f:
		for word in f:
			word = word.strip()
			frequencies[word] = frequencies.get(word, 0) + 1
	return frequencies

def print_frequencies(frequencies, frequency_format, file=None):
	for word in frequencies:
		print(frequency_format(word, frequencies[word]), file=file)
	
	## for option 2, this function opens veggies.txt as read only and can choose one item from list and shows its frequencies it shows
def DisplayInstance(itemSearch):
	itemSearch = itemSearch.lower()
	filename = open("veggies.txt", "r")
	count = 0
	for line in filename:
		line = line.strip()
		word = line.lower()
		if word == itemSearch:
			count += 1
	return count
	filename.close()
	## for the histogram 
def Histogram():
	with open("frequency.dat", "w") as f:
		print_frequencies(calculate_frequencies(),
			lambda item, count: "{} {}".format(item, "*" * count), f
		)
		


			
	

def printsomething():
	print("Hello from python!")

def PrintMe(v):
	print("You sent me: " + v)
	return 5;

def SquareValue(v):
	return v * 2

def MultiplicationTable(number):
	for i in range(1,11):
		print(number, 'X', i,'=', number*i)
	return 0



	
