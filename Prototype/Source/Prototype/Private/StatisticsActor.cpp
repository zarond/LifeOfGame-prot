// Fill out your copyright notice in the Description page of Project Settings.


#include "StatisticsActor.h"
#include <fstream>
#include <time.h>
#include <ctime>

// Sets default values
AStatisticsActor::AStatisticsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStatisticsActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStatisticsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStatisticsActor::StartTimer() {
	duration = clock();
}

void AStatisticsActor::StopTimer() {
	duration = clock() - duration;
}

std::string MsToString(unsigned int duration) {
	std::string str = "";
	int time;
	
	time = duration / 3600000;
	str += std::to_string(time) + "h ";
	
	duration -= time * 3600000;
	time = duration / 60000;
	str += std::to_string(time) + "min ";
	
	duration -= time * 60000;
	time = duration / 1000;
	str += std::to_string(time) + "sec ";
	
	return str;
}

std::string ULFCreateString(std::string description, std::string value, const int len) {
	std::string str = "|";
	int num;

	num = (len - description.length()) / 2;
	str += std::string(num, ' ') + description;
	num = len - num;
	str += std::string(num, ' ') + "|";
	
	num = (len - value.length()) / 2;
	str += std::string(num, ' ') + value;
	num = len - num;
	str += std::string(num, ' ') + "|";

	return str;
}

void AStatisticsActor::UpdateLastFile() const {
	const int len = 50;
	const int numOfHyphen = len * 2 + 3;
	char tmpbuf1[16], tmpbuf2[16];
	_strtime_s(tmpbuf1, 16);
	_strdate_s(tmpbuf2, 16);

	std::ofstream outFile(fileNameLast, std::ios_base::trunc | std::ios_base::binary);

	if (!outFile) {
		printf(std::string("Can't open file «" + fileNameLast + "»!").c_str());
		return;
	}

	outFile << std::string(numOfHyphen, '-') << std::endl; //----...----, where number of '-' is numOfHyphen
	outFile << ULFCreateString("Player by", playerName, len) << std::endl;
	outFile << std::string(numOfHyphen, '-') << std::endl;
	outFile << ULFCreateString("Walkthrough completed at", std::string(tmpbuf2) + std::string(", ") + std::string(tmpbuf1), len) << std::endl;
	outFile << std::string(numOfHyphen, '-') << std::endl;
	outFile << ULFCreateString("Duration of walkthrough is", MsToString(duration), len) << std::endl;
	outFile << std::string(numOfHyphen, '-') << std::endl;
	outFile << std::endl;
	outFile << std::string(numOfHyphen, '-') << std::endl;
	outFile << ULFCreateString("Killed enemies:", std::to_string(killedNPC), len) << std::endl;
	outFile << std::string(numOfHyphen, '-') << std::endl;
	outFile << ULFCreateString("Inflicted damage (points):", std::to_string(inflictedDamagePoints), len) << std::endl;
	outFile << std::string(numOfHyphen, '-') << std::endl;
	outFile << ULFCreateString("Received damage (points):", std::to_string(receivedDamagePoints), len) << std::endl;
	outFile << std::string(numOfHyphen, '-') << std::endl;
	outFile << ULFCreateString("Got into Lava (times):", std::to_string(gotIntoLavaTimes), len) << std::endl;
	outFile << std::string(numOfHyphen, '-') << std::endl;

	outFile.close();
}

std::string UBFCreateString(std::string description, std::string value, std::string player, const int len) {
	std::string str = "|";
	int num;

	num = (len - description.length()) / 2;
	str += std::string(num, ' ') + description;
	num = len - num;
	str += std::string(num, ' ') + "|";

	num = (len - value.length()) / 2;
	str += std::string(num, ' ') + value;
	num = len - num;
	str += std::string(num, ' ') + "|";

	num = (len - player.length()) / 2;
	str += std::string(num, ' ') + player;
	num = len - num;
	str += std::string(num, ' ') + "|";

	return str;
}

void AStatisticsActor::UpdateBestFile() const {
	const int len = 33;
	const int numOfHyphen = len * 3 + 4;

	std::ifstream inFile(fileNameBest, std::ios_base::binary);

	if (!inFile) {
		std::ofstream outFile(fileNameBest, std::ios_base::binary);
		
		if (!outFile) {
			printf(std::string("Can't open file «" + fileNameBest + "»!").c_str());
			return;
		}

		outFile << std::string(numOfHyphen, '-') << std::endl; //----...----, where number of '-' is numOfHyphen
		outFile << UBFCreateString("Killed enemies:", std::to_string(killedNPC), playerName, len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << UBFCreateString("Inflicted damage (points):", std::to_string(inflictedDamagePoints), playerName, len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << UBFCreateString("Received damage (points):", std::to_string(receivedDamagePoints), playerName, len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << UBFCreateString("Got into Lava (times):", std::to_string(gotIntoLavaTimes), playerName, len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;

		outFile.close();
		return;
	}

	TArray<TArray<std::string>> strings = FromBestFileToStrings();
	inFile.close();

	std::ofstream outFile(fileNameBest, std::ios_base::trunc | std::ios_base::binary);

	if (!outFile) {
		printf(std::string("Can't open file «" + fileNameBest + "»!").c_str());
		return;
	}

	if (strings.Num() == 0) {
		outFile << std::string(numOfHyphen, '-') << std::endl; //----...----, where number of '-' is numOfHyphen
		outFile << UBFCreateString("Killed enemies:", std::to_string(killedNPC), playerName, len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << UBFCreateString("Inflicted damage (points):", std::to_string(inflictedDamagePoints), playerName, len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << UBFCreateString("Received damage (points):", std::to_string(receivedDamagePoints), playerName, len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << UBFCreateString("Got into Lava (times):", std::to_string(gotIntoLavaTimes), playerName, len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;

		outFile.close();
		return;
	}

	{
		outFile << std::string(numOfHyphen, '-') << std::endl; //----...----, where number of '-' is numOfHyphen

		outFile << (killedNPC > std::stoi(strings[0][1]) ?
			UBFCreateString("Killed enemies:", std::to_string(killedNPC), playerName, len) :
			UBFCreateString("Killed enemies:", strings[0][1], strings[0][2], len)) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;

		outFile << (inflictedDamagePoints > std::stoi(strings[1][1]) ?
			UBFCreateString("Inflicted damage (points):", std::to_string(inflictedDamagePoints), playerName, len) :
			UBFCreateString("Inflicted damage (points):", strings[1][1], strings[1][2], len)) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;

		outFile << (receivedDamagePoints <= std::stoi(strings[2][1]) ?
			UBFCreateString("Received damage (points):", std::to_string(receivedDamagePoints), playerName, len) :
			UBFCreateString("Received damage (points):", strings[2][1], strings[2][2], len)) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;

		outFile << (gotIntoLavaTimes <= std::stoi(strings[3][1]) ?
			UBFCreateString("Got into Lava (times):", std::to_string(gotIntoLavaTimes), playerName, len) :
			UBFCreateString("Got into Lava (times):", strings[3][1], strings[3][2], len)) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;

		outFile.close();
		return;
	}
}

void AStatisticsActor::UpdateTotalFile() const {
	const int len = 50;
	const int numOfHyphen = len * 2 + 3;

	std::ifstream inFile(fileNameTotal, std::ios_base::binary);

	if (!inFile) {
		std::ofstream outFile(fileNameTotal, std::ios_base::binary);

		if (!outFile) {
			printf(std::string("Can't open file «" + fileNameTotal + "»!").c_str());
			return;
		}


		outFile << std::string(numOfHyphen, '-') << std::endl; //----...----, where number of '-' is numOfHyphen
		outFile << ULFCreateString("Games played:", std::to_string(1), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Games won:", std::to_string(hasWon ? 1 : 0), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Killed enemies:", std::to_string(killedNPC), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Inflicted damage (points):", std::to_string(inflictedDamagePoints), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Received damage (points):", std::to_string(receivedDamagePoints), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Got into Lava (times):", std::to_string(gotIntoLavaTimes), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Games without deaths:", std::to_string(hasDied ? 0 : 1), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;

		outFile.close();
		return;
	}

	TArray<TArray<std::string>> strings = FromBestFileToStrings();
	inFile.close();

	std::ofstream outFile(fileNameBest, std::ios_base::binary);

	if (!outFile) {
		printf(std::string("Can't open file «" + fileNameTotal + "»!").c_str());
		return;
	}

	if (strings.Num() == 0) {
		outFile << std::string(numOfHyphen, '-') << std::endl; //----...----, where number of '-' is numOfHyphen
		outFile << ULFCreateString("Games played:", std::to_string(1), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Games won:", std::to_string(hasWon ? 1 : 0), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Killed enemies:", std::to_string(killedNPC), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Inflicted damage (points):", std::to_string(inflictedDamagePoints), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Received damage (points):", std::to_string(receivedDamagePoints), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Got into Lava (times):", std::to_string(gotIntoLavaTimes), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Games without deaths:", std::to_string(hasDied ? 0 : 1), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;

		outFile.close();
		return;
	}

	{
		outFile << std::string(numOfHyphen, '-') << std::endl; //----...----, where number of '-' is numOfHyphen
		outFile << ULFCreateString("Games played:", std::to_string(1 + std::stoi(strings[0][1])), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Games won:", std::to_string(hasWon ? 1 + std::stoi(strings[1][1]) : std::stoi(strings[1][1])), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Killed enemies:", std::to_string(killedNPC + std::stoi(strings[2][1])), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Inflicted damage (points):", std::to_string(inflictedDamagePoints + std::stoi(strings[3][1])), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Received damage (points):", std::to_string(receivedDamagePoints + std::stoi(strings[4][1])), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Got into Lava (times):", std::to_string(gotIntoLavaTimes + std::stoi(strings[5][1])), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;
		outFile << ULFCreateString("Games without deaths:", std::to_string(hasDied ? std::stoi(strings[6][1]) : 1 + std::stoi(strings[6][1])), len) << std::endl;
		outFile << std::string(numOfHyphen, '-') << std::endl;

		outFile.close();
		return;
	}
}

void AStatisticsActor::ClearStatisticsInFiles() const {
	remove(fileNameBest.c_str());
	remove(fileNameLast.c_str());
	remove(fileNameTotal.c_str());
}

void AStatisticsActor::ClearStatisticsOnLevel() {
	duration = 0;

	killedNPC = 0;

	inflictedDamagePoints = 0;

	receivedDamagePoints = 0;
	gotIntoLavaTimes = 0;

	hasDied = false;
}

void AStatisticsActor::IncreaseKilledNPC() {
	++killedNPC;
}

void AStatisticsActor::IncreaseInflictedDamagePoints(int points) {
	inflictedDamagePoints += points;
}

void AStatisticsActor::IncreaseReceiveDamagePoints(int points) {
	receivedDamagePoints += points;
}

void AStatisticsActor::IncreaseGotIntoLavaTimes() {
	++gotIntoLavaTimes;
}

void AStatisticsActor::YouDied() {
	hasDied = true;
}

void AStatisticsActor::YouWon() {
	hasWon = true;
}

TArray<TArray<std::string>> FromFileToStrings(std::string fileName) {
	TArray<TArray<std::string>> strings = {};
	std::string str, tmpStr;
	TArray<std::string> strs;

	const int bufSize = 128;

	std::ifstream inFile(fileName, std::ios_base::binary);

	if (!inFile) {
		printf(std::string("Can't open file «" + fileName + "»!").c_str());
		return strings;
	}

	if (inFile.eof()) return strings;

	while (!inFile.eof()) {
		std::getline(inFile, str);

		if (!inFile.eof()) std::getline(inFile, str);
		else break;

		while (str.substr(str.find("|")).length() != 1) {
			str = str.substr(str.find("|") + 1);
			tmpStr = str.substr(0, str.find("|"));
			int k = 0;
			for (int i = 0; i < tmpStr.length() / 2; ++i) {
				if (tmpStr[i] != ' ') {
					k = i; break;
				}
			}
			strs.Add(tmpStr.substr(k, tmpStr.length() - 2 * k));
		}

		strings.Add(TArray<std::string>(strs));
	}

	inFile.close();
	return strings;
}

TArray<TArray<std::string>> AStatisticsActor::FromLastFileToStrings() const {
	return FromFileToStrings(fileNameLast);
}

TArray<TArray<std::string>> AStatisticsActor::FromBestFileToStrings() const {
	return FromFileToStrings(fileNameBest);
}

TArray<TArray<std::string>> AStatisticsActor::FromTotalFileToStrings() const  {
	return FromFileToStrings(fileNameTotal);
}
