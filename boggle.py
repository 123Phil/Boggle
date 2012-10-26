#Simple Boggle script

import random
from random import shuffle
random.seed()



def makeTrie(*Wordlist):
	root = dict()
	for Words in Wordlist:
		for word in Words:
			currentDict = root
			for letter in list(word):
				currentDict = currentDict.setdefault(letter, {})
			currentDict = currentDict.setdefault('_x', '_x')
	return root
	

def inTrie(trie, word):
	currentDict = trie
	for letter in list(word):
		if letter in currentDict:
			currentDict = currentDict[letter]
		else:
			return False
	else:
		if '_x' in currentDict:
			return True
		else:
			return False




def NumCharMatch(trie, word):
	currentDict = trie
	match = 0
	for letter in word:
		if letter in currentDict:
			match += 1
			currentDict = currentDict[letter]
	return match



def nextAdj(path, n):
	poss = []
	if path[n-1] == 0:
		poss = [1,4,5]
	elif path[n-1] == 1:
		poss = [0,2,4,5,6]
	elif path[n-1] == 2:
		poss = [1,3,5,6,7]
	elif path[n-1] == 3:
		poss = [2,6,7]
	elif path[n-1] == 4:
		poss = [0,1,5,8,9]
	elif path[n-1] == 5:
		poss = [0,1,2,4,6,8,9,10]
	elif path[n-1] == 6:
		poss = [1,2,3,5,7,9,10,11]
	elif path[n-1] == 7:
		poss = [2,3,6,10,11]
	elif path[n-1] == 8:
		poss = [4,5,9,12,13]
	elif path[n-1] == 9:
		poss = [4,5,6,8,10,12,13,14]
	elif path[n-1] == 10:
		poss = [5,6,7,8,11,13,14,15]
	elif path[n-1] == 11:
		poss = [6,7,10,14,15]
	elif path[n-1] == 12:
		poss = [8,9,13]
	elif path[n-1] == 13:
		poss = [8,9,10,12,14]
	elif path[n-1] == 14:
		poss = [9,10,11,13,15]
	elif path[n-1] == 15:
		poss = [10,11,14]

#	print n, path	
	if path[n] == poss[-1]:
		return -1
	else:
		i = 0
		while (path[n] >= poss[i] or poss[i] in path[:n]):
			i += 1
			if i == len(poss):
				return -1
		return poss[i]



class Boggle:
	letters = []
	
	def __init__(self, dice):
		self.letters = []
		dies = []
		for i in xrange(16):
			dies.append(i)
		shuffle(dies)
		for i in dies:
			self.letters.append(dice[i][random.randrange(0, 6)])

	def Pgrid(self, score):
		print " ",
		for i in xrange(16):
			if i in (4, 8, 12):
				print "\n ",
			if 'Q' == self.letters[i]:
				print 'Qu',
			else:
				print self.letters[i] + ' ',
			if 15 == i:
				print "\nCurrent score is ", score



	def oldPgrid(self, score):
		print ""
		print self.letters[:4]
		print self.letters[4:8]
		print self.letters[8:12]
		print self.letters[12:]
		print "Current score is ", score
		print ""
	
	def Solve(self, Dtrie):
		path = [0, 1, 2, -1,0,0,0,0,0,0,0,0,0,0,0,0]
		n = 3
		looping = True
		bog = self.letters[:]
		pathWord = []
		solution = []
		pWord = ""
		
		while(looping):
			pathWord = []
			i = 0
			while i < n:
				if 'Q' == bog[path[i]]:
					pathWord.append('QU')
				else:
					pathWord.append(bog[path[i]])
				i += 1
			
			pWord = "".join(pathWord)
			if inTrie(Dtrie, pWord) and pWord not in solution:
				solution.append(pWord)
#				print "Adding ", pWord
			else:
				if 'Q' in list(pWord):
					n = NumCharMatch(Dtrie, pWord) - 1
				else:
					n = NumCharMatch(Dtrie, pWord)

			#set next adjecent to path[n]
			Abool = True
			while (Abool):
				path[n] = nextAdj(path, n)
				if (-1 != path[n]):
					Abool = False
					break
				n -= 1
				if 0 == n:
					path[0] += 1
					if 16 == path[0]:
						looping = False
						break
					n += 1
					path[n] = -1
			n += 1
			path[n] = -1
		
		
		return solution
			
			

	def Custom(self):
		lString = raw_input("Enter 16 letters: ")
		self.letters = list(lString.upper())
		
	




def main():
	dice = ("AAEEGN", "ELRTTY", "AOOTTW", "ABBJOO",
	"EHRTVW", "CIMOTU", "DISTTY", "EIOSST",
	"DELRVY", "ACHOPS", "HIMNQU", "EEINSU",
	"EEGHNW", "AFFKPS", "HLNNRZ", "DEILRX")
	
	with open('dict.txt') as file:
	    Words = file.read().splitlines()
	
	Dtrie = makeTrie(Words)

	grid = Boggle(dice);
	solvedWords = grid.Solve(Dtrie)
	
	scoreCtr = 0
	grid.Pgrid(scoreCtr)
	playerWords = []
	
	#print grid, loop and ask for words
	while (True):
		guess = raw_input("Enter a word ('!' for menu): ")
		if '!' == guess:
			print " Menu:"
			print "  (M)y words"
			print "  (C)ustom board"
			print "  (S)olve"
			print "  (N)ew game"
			print "  (Q)uit"
			choice = raw_input("Please make a selection: ")
			choice = choice.upper()
			
			if 'Q' == choice:
				print "Thank you for playing!"
				exit()
			elif 'M' == choice:
				print ""
				print "Your words: ", playerWords
			elif 'S' == choice:
				print solvedWords
				maxScore = 0
				for word in solvedWords:
					maxScore += len(word) - 2
				print "Max score = ", maxScore
			elif 'N' == choice:
				grid.__init__(dice)
				solvedWords = grid.Solve(Dtrie)
				scoreCtr = 0
				playerWords = []
			elif 'C' == choice:
				grid.Custom()
				solvedWords = grid.Solve(Dtrie)
				scoreCtr = 0
				playerWords = []

		else:
			guess = guess.upper()
			if guess in solvedWords and guess not in playerWords:
				playerWords.append(guess)
				print guess, "found!"
				scoreCtr += len(guess) - 2
			else:
				print "Sorry, invalid guess"
		
		grid.Pgrid(scoreCtr)
		
		
	#delete lists and allocated memory
		


main()
