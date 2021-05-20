#pragma once
#include <string>
#include <iostream>

using namespace std;
class LetterCode
{
public:
	LetterCode();
	inline int getIntValue(const wchar_t* letter);
	~LetterCode();

private:
	int pole_[383] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,44,0,0,0,0,0,0,0,0,0,0,0,45,46,0,0,0,0,  // 0-49
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,4,5,7,9,11,12,13,14,16,17,18,21,22,24,27,28,29,31,33,35,37,38,39,40,42,0,0,0,0,0,0,1,4,5, // 50 - 99
		7,9,11,12,13,14,16,17,18,21,22,24,27,28,29,31,33,35,37,38,39,40,42,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 100 - 149
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0, // 150 - 199
		0,10,0,0,0,15,0,0,0,0,0,25,0,0,0,0,0,0,36,0,0,41,0,0,0,2,0,3,0,0,0,0,10,0,0,0,0,15,0,0,0,0,0,25,26,0,0,0,0,0, // 200 - 249
		36,0,0,41,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 250 - 299
		0,0,0,0,0,0,0,0,0,0,0,0,0,19,19,0,0,20,20,0,0,0,0,0,0,0,0,23,23,0,0,0,0,0,0,0,0,0,0,0,30,30,0,0,0,0,0,0,0,0, // 300 - 349
		0,0,32,32,0,0,34,34,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,43,43 // 350 - 383
	};
};
LetterCode::LetterCode()
{
}

inline int LetterCode::getIntValue(const wchar_t* letter)
{
	if (*letter >= 0 && *letter <= 382)
	{
		return pole_[*letter];
	}
	return 47;
	/*
	switch (*letter)
	{
	case L'a': case L'A':
		return 1;
		
	case L'á': case L'Á':
		return 2;
		
	case L'ä':
		return 3;

	case L'b': case L'B':
		return 4;

	case L'c': case L'C':
		return 5;

	case L'č': case L'Č':
		return 6;

	case L'd': case L'D':
		return 7;

	case L'ď': case L'Ď':
		return 8;

	case L'e': case L'E':
		return 9;

	case L'é': case L'É':
		return 10;

	case L'f': case L'F':
		return 11;

	case L'g': case L'G':
		return 12;

	case L'h': case L'H':
		return 13;

	case L'i': case L'I':
		return 14;

	case L'í': case L'Í':
		return 15;

	case L'j': case L'J':
		return 16;

	case L'k': case L'K':
		return 17;

	case L'l': case L'L':
		return 18;

	case L'ĺ': case L'Ĺ':
		return 19;

	case L'ľ': case L'Ľ':
		return 20;

	case L'm': case L'M':
		return 21;

	case L'n': case L'N':
		return 22;

	case L'ň': case L'Ň':
		return 23;

	case L'o': case L'O':
		return 24;

	case L'ó': case L'Ó':
		return 25;

	case L'ô':
		return 26;

	case L'p': case L'P':
		return 27;

	case L'q': case L'Q':
		return 28;

	case L'r': case L'R':
		return 29;

	case L'ŕ': case L'Ŕ':
		return 30;

	case L's': case L'S':
		return 31;

	case L'š': case L'Š':
		return 32;

	case L't': case L'T':
		return 33;

	case L'ť': case L'Ť':
		return 34;

	case L'u': case L'U':
		return 35;

	case L'ú': case L'Ú':
		return 36;

	case L'v': case L'V':
		return 37;

	case L'w': case L'W':
		return 38;

	case L'x': case L'X':
		return 39;

	case L'y': case L'Y':
		return 40;
	
	case L'ý': case L'Ý':
		return 41;
	
	case L'z': case L'Z':
		return 42;
	
	case L'ž': case L'Ž':
		return 43;
	
	case L' ':
		return 44;
	
	default:
		return 0;
	}
	*/
}

inline LetterCode::~LetterCode()
{
}
