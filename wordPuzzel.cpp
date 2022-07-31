#include <iostream>
#include <fstream>
using namespace std;
void menu()
{
	std::cout << "\tPress [1] for new game\n"
		<< "\tPress [2] for resume game\n"
		<< "\tPress [3] for level selection\n"
		<< "\tPress [4] for high scores\n"
		<< "\tPress [0] for exit\n";
}
void converter(char* word);
char* grow(char* array, int size, char character)
{
	char* other = new char[size + 1];
	for (int i = 0; i < size; i++)
		other[i] = array[i];
	other[size - 1] = character;
	delete[] array;
	array = NULL;
	return other;
}
int lengthFinder(char* array)
{
	int length = 0;
	for (int i = {}; array[i] != '\0'; i++, length++);
	return length;
}
void readBoard(std::ifstream& in, char** array, int rowSize, int& colSize)
{
	char ch;
	for (int i = 0; !in.eof(); i++)
	{
		colSize = 1;
		array[i] = new char[colSize];
		for (int j = 0; in.get(ch); j++)
		{
			if (ch == '\n')
				break;
			array[i] = grow(array[i], colSize, ch);
			colSize++;
		}
	}
	colSize--;
}
void forwardRowCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores);
void backwardRowCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores);
void forwardColumnCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores);
void backwardColumnCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores);
void forwardDiagonalCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores);
void backwardDiagonalCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores);
void reverseForwardDiagonalCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores);
void reverseBackwardDiagonalCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores);
bool verify(char* word);
void readWord(char* word, int& length, bool& furtherCheck)
{
	std::cout << "\n\tEnter guessed word ..? ";
	std::cin >> word;
	length = lengthFinder(word);
	bool available = verify(word);
	if (available)
	{
		converter(word);
		furtherCheck = true;
	}
}
bool verify(char* word)
{
	int length = lengthFinder(word);
	std::ifstream in("dictionary.txt");
	char* dWord = new char[50];
	while (in >> dWord)
	{
		int dlength = lengthFinder(dWord);

		if (length == dlength)
		{
			int count = 0;
			for (int i = 0; i < length; i++)
				if (word[i] == dWord[i])
					count++;
			if (count == length)
			{
				return true;
			}
			else
				continue;
		}
		else
			continue;
	}
	return false;
}
void saveRecord(int scores)
{
	std::ifstream in("highScores.txt");
	int n[6], count = 0;
	for (int i = 0; in >> n[i]; i++)
		count++;
	n[5] = scores;
	if (count >= 5)
	{
		int temp, ptr;
		for (int i = 1; i < 6; i++)
		{
			temp = n[i];
			ptr = i - 1;
			while (temp > n[ptr] && ptr != -1)
			{
				n[ptr + 1] = n[ptr];
				ptr--;
			}
			n[ptr + 1] = temp;
		}
	}

	in.close();
	std::ofstream out("highScores.txt", std::ios::app);
	if (count >= 5)
	{
		out.close();
		std::ofstream fout("highScores.txt");
		for (int i = 0; i < 5; i++)
			fout << n[i] << " ";
		fout.close();
	}
	else
		out << scores << " ";
	out.close();
}
void printBoard(char** arr, int rowSize, int columnSize);
int main()
{
	std::ifstream in("hardboard.txt");
	int rowSize = 15, columnSize = 0, scores = 0, choice = 0;
	char** array = new char* [rowSize], * name = new char[50];
	readBoard(in, array, rowSize, columnSize);
	bool asked = false;
	do
	{
		bool notFound = true, furtherCheck = false;
		system("cls");
		menu();
		if (!asked)
		{
			std::cout << "\tEnter Name : ";
			std::cin.getline(name, 50);
			asked = true;
		}
		std::cout << "\tEnter choice ..? ";
		std::cin >> choice;
		char* word = new char[20];
		int length = 0;
		if (choice == 1)
		{
			printBoard(array, rowSize, columnSize);
			readWord(word, length, furtherCheck);
			if (!furtherCheck)
				goto notAvailable;
				forwardRowCheck(array, rowSize, columnSize, word, length, notFound, scores);
				forwardColumnCheck(array, rowSize, columnSize, word, length, notFound, scores);
		}
		else if (choice == 2)
		{
			printBoard(array, rowSize, columnSize);
			readWord(word, length, furtherCheck);
			if (!furtherCheck)
				goto notAvailable;
			forwardRowCheck(array, rowSize, columnSize, word, length, notFound, scores);
			backwardRowCheck(array, rowSize, columnSize, word, length, notFound, scores);
			forwardColumnCheck(array, rowSize, columnSize, word, length, notFound, scores);
			backwardColumnCheck(array, rowSize, columnSize, word, length, notFound, scores);
		}
		else if (choice == 3)
		{
			std::cout << "\t\tPresse [1] for easy lever\n"
				<< "\t\tPresse [2] for intermediate lever\n"
				<< "\t\tPresse [3] for hard lever\n";
			std::cout << "\tChoice : ";
			std::cin >> choice;
			if (choice == 1)
			{
				printBoard(array, rowSize, columnSize);
				readWord(word, length, furtherCheck);
				if (!furtherCheck)
					goto notAvailable;
					forwardRowCheck(array, rowSize, columnSize, word, length, notFound, scores);
				forwardColumnCheck(array, rowSize, columnSize, word, length, notFound, scores);
			}
			else if (choice == 2)
			{
				printBoard(array, rowSize, columnSize);
				readWord(word, length, furtherCheck);
				if (!furtherCheck)
					goto notAvailable;
					forwardRowCheck(array, rowSize, columnSize, word, length, notFound, scores);
				backwardRowCheck(array, rowSize, columnSize, word, length, notFound, scores);
				forwardColumnCheck(array, rowSize, columnSize, word, length, notFound, scores);
				backwardColumnCheck(array, rowSize, columnSize, word, length, notFound, scores);
			}
			else if (choice == 3)
			{
				printBoard(array, rowSize, columnSize);
				readWord(word, length, furtherCheck);
				if (!furtherCheck)
					goto notAvailable;
				forwardRowCheck(array, rowSize, columnSize, word, length, notFound, scores);
				backwardRowCheck(array, rowSize, columnSize, word, length, notFound, scores);
				forwardColumnCheck(array, rowSize, columnSize, word, length, notFound, scores);
				backwardColumnCheck(array, rowSize, columnSize, word, length, notFound, scores);
				reverseForwardDiagonalCheck(array, rowSize, columnSize, word, length, notFound, scores);
				reverseBackwardDiagonalCheck(array, rowSize, columnSize, word, length, notFound, scores);
				backwardDiagonalCheck(array, rowSize, columnSize, word, length, notFound, scores);
			}
		}
		else if (choice == 4)
		{
			std::ifstream fin("highScores.txt");
			if (!fin)
			{
				std::cout << "\tYou have not played yet\n";
				goto again;
			}
			for (int i = 0; fin >> scores; i++)
			{
				if (i > 5)
					break;
				std::cout << "\t" << scores << "\n";
			}
			fin.close();
		}
		if (notFound && choice != 0 && choice != 4)
			std::cout << "\tNo word match\n";
		else if (choice == 0)
			break;
	notAvailable:
		if (!furtherCheck)
			std::cout << "\tThe word you entered, not found\n";
	again:
		std::cout << "\tPress 1 for play again OR press 0 for exit : ";
		std::cin >> choice;
		std::cin.ignore();
		if (choice == 0)
		{
			if (scores > 0)
				saveRecord(scores);
		}
	} while (choice != 0);
	std::cout << "\tExit successful!\n";
	return 0;
}
void printBoard(char** arr, int rowSize, int columnSize)
{
	for (int i = 0; i < rowSize; i++)
	{
		std::cout << "\t   ";
		for (int j = 0; j < columnSize; j++)
		{
			char capital = arr[i][j] - 32;
			std::cout << capital << " ";
		}
		std::cout << std::endl;
	}
}
void forwardRowCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores)
{
	bool fFound = true;
	for (int i = 0; i < rowSize; i++)
	{
		int count, j;
		for (j = 0, count = 0; j <= columnSize; j++)
		{
			if (count == length)
			{
				scores += 10;
				scores += 10;
				notFound = false;
				if (fFound)
					std::cout << "\t\t\t    Forward Row Wise    \n";
				fFound = false;
				std::cout << "\t\t\t   Starts at [" << i + 1 << ", " << j - count + 1 << "]\n";
				std::cout << "\t\t\t      Ends at [" << i + 1 << ", " << j << "]\n";
				count = 0;
			}
			if (j == columnSize)
				break;
			if (array[i][j] == word[count])
				count++;
			else
				count = 0;
			if (array[i][j + 1] != word[count] && count < length)
				count = 0;
		}
	}
}
void backwardRowCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores)
{
	bool rFound = true;
	for (int i = 0; i < rowSize; i++)
	{
		int count, j;
		for (j = columnSize - 1, count = 0; j >= 0; j--)
		{
			if (count == length)
			{
				scores += 10;
				if (rFound)
					std::cout << "\t\t\t\    Backward Row Wise    \n";
				rFound = false;
				std::cout << "\t\t\t   Starts at [" << i + 1 << ", " << j + count + 1 << "]\n";
				std::cout << "\t\t\t   Ends at [" << i + 1 << ", " << j + 2 << "]\n";
				count = 0;
			}
			if (array[i][j] == word[count])
				count++;
			else
				count = 0;
			if (array[i][j - 1] != word[count] && count < length)
				count = 0;
		}
	}
}
void forwardColumnCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores)
{

	bool fFound = true;
	for (int i = 0; i < columnSize; i++)
	{
		int count, j;
		for (j = 0, count = 0; j <= rowSize; j++)
		{
			if (count == length)
			{
				notFound = false;
				scores += 10;
				if (fFound)
					std::cout << "\t\t\t   Forward Column Wise   \n";
				fFound = false;
				std::cout << "\t\t\t  Starts at [" << j - count + 1 << ", " << i + 1 << "]\n";
				std::cout << "\t\t\t  Ends at [" << j << ", " << i + 1 << "]\n";
				count = 0;
			}				if (j == rowSize)
				break;
			if (array[j][i] == word[count])
			{
				count++;
				if ((count + 1 <= length && j + 1 < rowSize) && array[j + 1][i] != word[count])
					count = 0;
			}
			else
				count = 0;
		}
	}
}
void backwardColumnCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores)
{
	bool rFound = true;
	for (int i = 0; i < columnSize; i++)
	{
		int count, j;
		for (j = rowSize - 1, count = 0; j >= -1; j--)
		{
			notFound = false;
			if (count == length)
			{
				scores += 10;
				if (rFound)
					std::cout << "\t\t\t   Backward Column Wise  \n";
				rFound = false;
				std::cout << "\t\t\t   Starts at [" << j + count + 1 << ", " << i + 1 << "]\n";
				std::cout << "\t\t\t   Ends at [" << j + 2 << ", " << i + 1 << "]\n";
				count = 0;
			}
			if (j < 0)
				break;
			if (array[j][i] == word[count])
			{
				count++;
				if ((count + 1 <= length && j - 1 >= 0) && array[j - 1][i] != word[count])
					count = 0;
			}
			else
				count = 0;
		}
	}
}
void forwardDiagonalCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores)
{
	bool fFound = true;
	for (int i = 0; i < columnSize; i++)
	{
		int count, j, k = i;
		for (j = 0, count = 0; j <= rowSize; j++, k++)
		{
			if (count == length)
			{
				notFound = false;
				scores += 10;
				if (fFound)
					std::cout << "\t\t\t  Forward diagonal Wise  \n";
				fFound = false;
				std::cout << "\t\t\t   Starts at [" << j - count + 1 << ", " << i + 1 + (j - count) << "]\n";
				std::cout << "\t\t\t   Ends at [" << j << ", " << k << "]\n";
				count = 0;
			}
			if (j == rowSize)
				break;
			if (array[j][k] == word[count])
			{
				count++;
				if ((count + 1 <= length && j + 1 < rowSize) && array[j + 1][k + 1] != word[count])
					count = 0;
			}
			else
				count = 0;
		}
	}
	for (int i = 1; i < columnSize; i++)
	{
		int count, j, k = i;
		for (j = 0, count = 0; j <= rowSize; j++, k++)
		{
			if (count == length)
			{
				notFound = false;
				scores += 10;
				if (fFound)
					std::cout << "\t\t\t  Forward diagonal Wise  \n";
				fFound = false;
				std::cout << "\t\t\t   Starts at \033[1m[" << k - count + 1 << ", " << j - count + 1 << "]\n";
				std::cout << "\t\t\t   Ends at [" << k << ", " << j << "]\n";
				count = 0;
			}
			if (k == rowSize)
				break;
			if (array[k][j] == word[count])
			{
				count++;
				if ((count + 1 <= length && j + i + 1 < rowSize) && array[k + 1][j + 1] != word[count])
					count = 0;
			}
			else
				count = 0;
		}
	}
}
void backwardDiagonalCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores)
{
	bool bFound = true;
	for (int i = columnSize - 1; i >= 0; i--)
	{
		int count, j, k = i;
		for (j = rowSize - 1, count = 0; j >= 0; j--, k--)
		{
			if (count == length)
			{
				notFound = false;
				scores += 10;
				if (bFound)
					std::cout << "\t\t\t Backward diagonal Wise  \n";
				bFound = false;
				std::cout << "\t\t\t   Starts at [" << j + count + 1 << ", " << k + count + 1 << "]\n";
				std::cout << "\t\t\t   Ends at [" << j + 2 << ", " << k + 2 << "]\n";
				count = 0;
			}
			if (array[j][k] == word[count])
			{
				count++;
				if ((count + 1 <= length && j - 1 >= 0) && array[j - 1][k - 1] != word[count])
					count = 0;
			}
			else
				count = 0;
		}
	}

	for (int i = columnSize - 2; i >= 0; i--)
	{
		int count, j, k = i;
		for (j = rowSize - 1, count = 0; j >= 0; j--, k--)
		{
			if (count == length)
			{
				notFound = false;
				scores += 10;
				if (bFound)
					std::cout << "\t\t\tBackward diagonal Wise  \n";
				bFound = false;
				std::cout << "\t\t\t   Starts at [" << k + count + 1 << ", " << j + count + 1 << "]\n";
				std::cout << "\t\t\t   Ends at [" << k + 2 << ", " << j + 2 << "]\n";
				count = 0;
			}
			if (k < 0)
				break;
			if (array[k][j] == word[count])
			{
				count++;
				if (k - 1 < 0)
					continue;
				if ((count + 1 <= length && j - i - 1 >= 0) && (count != length && array[k - 1][j - 1] != word[count]))
					count = 0;
			}
			else
				count = 0;
		}
	}
}
void reverseForwardDiagonalCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores)
{
	bool fFound = true;
	int starts, ends;
	for (int i = 0; i < columnSize; i++)
	{
		bool oneMore = false;
		int count, j, k = i;
		for (j = rowSize - 1, count = 0; j >= 0; j--, k++)
		{
			if (count == length)
			{
				notFound = false;
				scores += 10;
				if (fFound)
					std::cout << "\t\t\t  Reverse Forward diagonal Wise  \n";
				fFound = false;
				if (!oneMore)
				{
					starts = j + count + 1;
					ends = j + 2;
				}
				else
				{
					starts = j + count;
					ends = j + 1;
				}
				std::cout << "\t\t\t   Starts at [" << starts << ", " << k - count + 1 << "]\n";
				std::cout << "\t\t\t   Ends at [" << ends << ", " << k << "]\n";
				count = 0;
			}
			if (j == rowSize)
				break;
			if (array[j][k] == word[count])
			{
				count++;
				if ((count + 1 <= length && j - 1 >= 0) && array[j - 1][k + 1] != word[count])
					count = 0;
			}
			else
				count = 0;
			if (j - 1 < 0 && !oneMore)
			{
				oneMore = true;
				j++;
			}
		}
	}
	for (int i = columnSize - 2; i >= 0; i--)
	{
		int count, j, k = i;
		for (j = 0, count = 0; j < rowSize; j++, k--)
		{
			if (count == length)
			{
				notFound = false;
				scores += 10;
				if (fFound)
					std::cout << "\t\t\t  Reverse Forward diagonal Wise  \n";
				fFound = false;
				std::cout << "\t\t\t   Starts at \033[1m[" << k + count + 1 << ", " << j - count + 1 << "]\n";
				std::cout << "\t\t\t   Ends at [" << k + 2 << ", " << j << "]\n";
				count = 0;
			}
			if (k < 0)
				break;
			if (array[k][j] == word[count])
			{
				count++;
				if (k - 1 < 0)
					continue;
				if ((count + 1 <= length && j + i + 1 < rowSize) && array[k - 1][j + 1] != word[count])
					count = 0;
			}
			else
				count = 0;
		}
	}
}
void reverseBackwardDiagonalCheck(char** array, int rowSize, int columnSize, char* word, int length, bool& notFound, int& scores)
{
	bool bFound = true;
	//int starts, ends;
	for (int i = 1; i < columnSize; i++)
	{
		bool oneMore = false;
		int count, j, k = i;
		for (j = rowSize - 1, count = 0; j >= 0; j--, k++)
		{
			notFound = false;
			if (count == length)
			{
				scores += 10;
				if (bFound)
					std::cout << "\t\t\t  Reverse Backward diagonal Wise \n";
				bFound = false;
				std::cout << "\t\t\t  Starts at [" << k - count + 1 << ", " << j + count + 1 << "]\n";
				std::cout << "\t\t\t   Ends at [" << k << ", " << j + 2 << "]\n";
				count = 0;
			}
			if (k == rowSize)
				break;
			if (array[k][j] == word[count])
			{
				count++;
				if (k + 1 == rowSize)
					continue;
				if ((count + 1 <= length && j >= 0) && array[k + 1][j - 1] != word[count])
					count = 0;
			}
			else
				count = 0;
		}
	}
	for (int i = columnSize - 1; i >= 0; i--)
	{
		bool oneMore = false;
		int count, j, k = i;
		for (j = 0, count = 0; j < rowSize; j++, k--)
		{
			if (count == length)
			{
				notFound = false;
				scores += 10;
				if (bFound)
					std::cout << "\t\t\t  Reverse Backward diagonal Wise  \n";
				bFound = false;
				std::cout << "\t\t\t   Starts at [" << j - count + 1 << ", " << k + count + 1 << "]\n";
				std::cout << "\t\t\t   Ends at [" << j << ", " << k + 2 << "]\n";
				count = 0;
			}
			if (j == rowSize)
				break;
			if (array[j][k] == word[count])
			{
				count++;
				if (k - 1 < 0)
					continue;
				if ((count + 1 <= length && j < rowSize) && array[j + 1][k - 1] != word[count])
					count = 0;
			}
			else
				count = 0;
		}
	}
}
void converter(char* word)
{
	int length = lengthFinder(word);
	for (int i = 0; i < length; i++)
		if (word[i] >= 'A' && word[i] <= 'Z')
			word[i] += 32;
}