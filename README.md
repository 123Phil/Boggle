Boggle
======

Boggle in C++ and python


I felt like making a boggle solver, so I went at it in C++...
it ended up taking forever to solve since it looked up each possible word across the board with a linear lookup in a dictionary containing a few hundred thousand words.

So I figured I would revise it with a trie data structure so that each word lookup was basically instant.
I found a quick and easy trie in python on stackoverflow, so I decided to code the whole thing up in python.
