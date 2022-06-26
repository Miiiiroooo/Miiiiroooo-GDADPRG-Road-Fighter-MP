#include "stdafx.h"
#include "ScoreManager.h"


// static declarations of the ScoreManager Class
ScoreManager* ScoreManager::sharedInstance = NULL;

ScoreManager* ScoreManager::getInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new ScoreManager();

	return sharedInstance;
}


// public methods of the ScoreManager Class
void ScoreManager::initialize()
{
	std::string fileContent;
	std::ifstream inFile;
	inFile.open("Media/Additional Files/KeepScore.txt");

	if (!inFile)
	{
		std::cerr << "Cannot open the KeepScore.txt file" << std::endl;
	}
	else
	{
		while (inFile >> fileContent)
		{
			if (fileContent == "Score:")
			{
				inFile >> fileContent;
				this->score = std::stoi(fileContent);
			}
			else if (fileContent == "HighScore:")
			{
				inFile >> fileContent;
				this->highScore = std::stoi(fileContent);
			}
		}
	}

	inFile.close();
}


int ScoreManager::getScore()
{
	return this->score;
}


int ScoreManager::getHighScore()
{
	return this->highScore;
}


void ScoreManager::updateScore(int score)
{
	this->score = score;
}


void ScoreManager::decideHighScore()
{
	if (score > highScore)
		highScore = score;
}


void ScoreManager::updateFile()
{
	std::ofstream outFile;
	outFile.open("Media/Additional Files/KeepScore.txt");

	if (!outFile)
	{
		std::cerr << "Cannot open the KeepScore.txt file" << std::endl;
	}
	else
	{
		// revert to the original state of the text file
		outFile << "Score:   " << std::to_string(0) << "\n";
		outFile << "HighScore:   " << highScore << "\n";
	}
	
	outFile.close();
}