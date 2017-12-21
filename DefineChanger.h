#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <fstream>
#include <regex>

const std::string keyDefine = "#define";
char* buffer=new char[10];

void changeDefine(char* inputFile, char* outputFile)
{
	std::string inputLine, outputLine, firstWord, key, value, word;

	std::list<std::vector <std::string> > table;

	std::ifstream ifs(inputFile);
	if (!ifs.is_open())
	{
		std::cout << "ERROR: changeDefine: Input file open error: " << strerror_s(buffer, 10, errno);
		std::getchar();
		return;
	}

	std::ofstream ofs(outputFile);
	if (!ofs.is_open())
	{
		std::cout << "ERROR: changeDefine: Output file open error: " << strerror_s(buffer, 10, errno);
		std::getchar();
		return;
	}

	while (std::getline(ifs, inputLine))
	{
		outputLine = inputLine;
		std::istringstream iss(inputLine);
		iss >> firstWord;

		if (firstWord == keyDefine)	//add to table
		{
			int nOfWords = 0;
			while (iss >> word)
			{
				if (nOfWords == 0)
					key = word;
				if (nOfWords == 1)
					value = word;
				nOfWords += 1;
			}
			if (nOfWords > 2)
			{
				std::cout << "ERROR: changeDefine: Define has wrong format: " << strerror_s(buffer, 10,errno);
				std::getchar();
				return;
			}
			for (auto &pair : table)
				if (pair[1] == key)
					pair[1] = value;

			std::vector<std::string> newPair;
			newPair.push_back(key);
			newPair.push_back(value);

			table.push_back(newPair);
		}
		else //check if in table and write line to file
		{
			//std::string currentWord = firstWord;
			//do
			//{
			for (auto &pair : table) {
				//if (pair[0] == currentWord)
				size_t index;
				int index1 = 0;
				while ((index = outputLine.find(pair[0], index1)) != string::npos) {
					if (index == 0 &&
						!((outputLine[index + pair[0].length()] <= 'z' && outputLine[index + pair[0].length()] >= 'a')
							|| (outputLine[index + pair[0].length()] <= 'Z' && outputLine[index + pair[0].length()] >= 'A')))
						outputLine.replace(index, pair[0].length(), pair[1]);
					if (index > 0 &&
						!((outputLine[index + pair[0].length()] <= 'z' && outputLine[index + pair[0].length()] >= 'a')
							|| (outputLine[index + pair[0].length()] <= 'Z' && outputLine[index + pair[0].length()] >= 'A'))
						&&
						!((outputLine[index - 1] <= 'z' && outputLine[index - 1] >= 'a')
							|| (outputLine[index - 1] <= 'Z' && outputLine[index - 1] >= 'A')))
						outputLine.replace(index, pair[0].length(), pair[1]);
					index1 = index + 1;
				}
			}
			//					outputLine = std::regex_replace(outputLine, std::regex(pair[0]), pair[1]);
			//currentWord = pair[1];
			//ofs << currentWord << " ";

			//} while (iss >> currentWord);

			ofs << outputLine << " \r\n"; // outputLine <<
		}
	}
	ifs.close();
	ofs.close();
}