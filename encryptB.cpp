#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using std::string;
using std::endl;
using std::cin;
using std::cout;
using std::cerr;
using std::vector;
using std::pair;
using std::ifstream;
using std::ofstream;



// removeUnique removes duplicate letters 
string removeUnique(string input)
{
	//
	int counter[26] = {0};
	int occur[26] = {0};
	string newString;

	// Count the characters
	for(int i = 0; i < input.size(); i++)
	{
	 counter[(tolower(input[i]) - 97)]++;
	}

	for(int i = 0; i < input.size(); i++)
	{
		// Make sure the count is above one, and we have already encountered the character
		if(counter[(tolower(input[i]) - 97)] > 1 && occur[(tolower(input[i]) - 97)] > 0)
		{
			// Don't copy over the character 
		}
		else
		{
			occur[(tolower(input[i]) - 97)]++;
			newString += input[i];
		}
	}
	newString = newString.substr(0,10);
	return newString;
}


//Get the unique keys from input
void getKey(string &key1)
{
	int SUCCESS = 0;
	cout << "Please enter first key: ";
	cin >> key1;

	while(SUCCESS != 1)
	{
		key1 = removeUnique(key1);

		if(key1.size() == 10)
		{
			SUCCESS = 1;
		}
		else
		{
			cout << "Please enter first key with unique letters: ";
			cin >> key1;
		}

	}

	cout << "KEY: " << key1 << endl;
}

vector<pair<char, int> > makePairs(string key)
{
	vector<pair<char, int> > keyMap;
	for(int i = 0; i < key.size(); i++)
	{
		pair<char, int> a(key[i], i);
		keyMap.push_back(a);
	}

	sort(keyMap.begin(), keyMap.end());


	cout << "KEY: " << key << endl;
	
	for(int i = 0; i < keyMap.size(); i++)
	{
		cout << keyMap[i].first << " " << keyMap[i].second << endl;
	}
	return keyMap;


}
vector<vector<char> > readFile(const char *filename)
{

	int line = 0, cols = 10, row = 0;
	vector<vector<char> > matrix;
	vector<char> r;
	ifstream input(filename);
	if(!input)
	{
		cout << "Error could not open file: " << filename << endl;
		return matrix;
	}
	char c; 
	int count = 0;
	while (input.get(c))
	{
		if(!isspace(c) && c != '.' && c != ',' && c != '!')
		{
		//cout << "PUSHING BACK " << c << "COUNT = " << count << endl;
			r.push_back(c);
			count++;
		}
		if(c == '.')
		{
			r.push_back('x');
			r.push_back('x');
			count += 2;

		}
		
		if(count > 9)
		{
			//cout << "PUSHING BACK R!!! " << endl;
			matrix.push_back(r);
			r.clear();
			count = 0;
		} 
	}

	if(r.size() != 0)
	{
		matrix.push_back(r);

	}

	row = matrix.size(); 
	cout << "ROW = " << row << "COL = " << matrix[0].size() << endl;
	while(matrix[row-1].size() < 10)
	{
		matrix[row-1].push_back('x');
	}

	input.close();

	//test matrix values


	return matrix;

}

void consumeCol(vector<vector<char> > &matrix, int col, string &cipher)
{
	for(int j = 0; j < 1; j++)
	{
		for(int i = 0; i < matrix.size(); i++)
		{
			cipher += matrix[i][col];
		}
	}
}

string encrypt(vector<vector<char> > &matrix, vector<pair<char, int> > keyMap)
{
	string cipher; 
	int counter = 0;

	for(int i = 0; i < 10; i++)
	{
		consumeCol(matrix, keyMap[i].second, cipher);	

	}

	//Restructure matrix
	for(int i = 0; i < matrix.size(); i++)
	{
		for(int j = 0; j < 10; j++)
		{
			matrix[i][j] = cipher[counter];
			counter++;
		}
	}


	return cipher;

}
void printString(string cipher)
{
	ofstream output("Cameron-ONeal-encrypted-str.txt");
	output << cipher;
}
int main()
{
	int counter[26];
	string filename;
	vector<vector<char> > matrix;
	vector<pair<char, int> > keyMap1, keyMap2; //key pairs with the letter and index
	
	string key1, key2;
	getKey(key1);
	getKey(key2);

	keyMap1 = makePairs(key1);
	keyMap2 = makePairs(key2);

	cout << "Please enter file name: ";
	cin >> filename;
	matrix = readFile(filename.c_str());

	for(int i = 0; i < matrix.size(); i++)
	{
		for(int j = 0; j < 10; j++)
			cout << matrix[i][j];

		cout << endl;
	}

	string msg = encrypt(matrix, keyMap1);
	cout << "MSG = " << msg << endl;

	cout << "MATRIX 1" << msg << endl;
	for(int i = 0; i < matrix.size(); i++)
	{
		for(int j = 0; j < 10; j++)
			cout << matrix[i][j];

		cout << endl;
	}

	string cipher = encrypt(matrix, keyMap2);
	cout << "MSG = " << cipher << endl;

	for(int i = 0; i < matrix.size(); i++)
	{
		for(int j = 0; j < 10; j++)
			cout << matrix[i][j];

		cout << endl;
	}

	printString(cipher);
	return 0;



}
