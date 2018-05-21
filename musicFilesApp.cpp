#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cctype>
//using namespace System;
//using namespace System::Collections::ObjectModel;


void searcher(std::string data, std::string pname, std::string dek)
{
	dek.erase(0, 6);
	size_t pstart;
	pstart = data.find("Playlist ID"); // go to the  beginning of the playlist in the file
	while ((data.find(pname, pstart) - pstart) > 500) // loop to find correct playlist
	{
		pstart = data.find("Playlist ID", pstart);
		pstart += 12;
	}
	pstart = data.find(pname, pstart);	 // then get to the name
	size_t endOfPlay = data.find("</array>", pstart); // find the end so you can stop there
	size_t pathloc = 0; // index for where to start reading from in data file
	std::string path = ""; // for file path of the file to be copied
	std::string cpcmd = ""; // for copy command
	std::string driveLetter = ""; // drive letter to copy from
	std::string currentNum = ""; // another index pointer
	while (data.find("Track ID", pstart) != std::string::npos &&
		data.find("Track ID", pstart) < endOfPlay)
	{
		currentNum = "";
		driveLetter = "";
		path = "";
		cpcmd = " copy ";
		pstart = data.find("Track ID", pstart);
		pstart = data.find("<integer>", pstart);
		pstart += 9;
		while (data[pstart] != '<') // get track id
		{
			currentNum += data[pstart];
			pstart++;
		}
		pathloc = data.find("<key>" + currentNum);
		pathloc = data.find("localhost", pathloc);
		pathloc += 10;
		while (data[pathloc] != '/') // get drive letter
		{
			driveLetter += data[pathloc];
			pathloc++;
		}
		path += driveLetter + "\\";
		while (data[pathloc] != '<') // get file path
		{
			path += data[pathloc];
			pathloc++;
		}
		cpcmd += "\"" + path + "\"" + " " + "\"" + dek + "\""; // form command to cp file
		if (cpcmd.find("\/") != std::string::npos)
			cpcmd.replace(cpcmd.find("\/"), 1, "");
		size_t temp;
		while (cpcmd.find('/') != std::string::npos)
		{
			temp = cpcmd.find('/');
			cpcmd.replace(cpcmd.find('/'), 1, "");
			cpcmd.insert(temp, "\\");
		}
		while (cpcmd.find('%') != std::string::npos || cpcmd.find('#') != std::string::npos) // remove extra chars added by xml
		{
			size_t spot = cpcmd.find('%');
			size_t spot1 = cpcmd.find('#');
			if (spot1 != std::string::npos)
			{
				cpcmd[spot1] = '~';
				spot1++;
				while (isdigit(cpcmd[spot1]))
				{
					cpcmd[spot1] = '~';
					spot1++;
				}
				if (cpcmd[spot1] == ';')
					cpcmd[spot1] = '~';
			}
			if (spot != std::string::npos)
			{
				cpcmd[spot] = ' ';
				spot++;
				while (isdigit(cpcmd[spot]))
				{
					cpcmd[spot] = '~';
					spot++;
				}
			}
			
			while (cpcmd.find('~') != std::string::npos)
				cpcmd.replace(cpcmd.find('~'), 1, "");
		}
		system(cpcmd.c_str());
	}
}
int main()
{
	std::string data = "", answer = "", uname = "", line = "", pname = "", fd = ""; // fd is for the path of the xml 
	// dek is desktop path
	int begin = 0, end = 0; //of main file
	std::ifstream file;
	std::string dek = "mkdir C:\\Users\\";
	std::cout << "What's your username?\n";
	std::cin >> uname;
	dek += uname;
	fd += "C:\\Users\\";
	fd += uname;
	fd += "\\Music\\iTunes\\iTunes Music Library.xml";
	dek += "\\Desktop\\";
	do 
	{
		std::cout << "what's the name of the playlist that you want to do?\n";
		std::cin >> pname;
		dek += pname;
		system(dek.c_str()); // making folder on desktop to copy files to
		std::cout << "Thanks working on copying the files over to the folder I made before\n";
		file.open(fd); // trying to open itunes file
		if (!file)
		{
			std::cout << "couldn't open file";
			return 1;
		}
		while (std::getline(file, line))
		{
			data += line; // read and store data of entire file
		}
		file.close();
		size_t point = data.find("Playlist ID");
		if (data.find(pname, point) == std::string::npos)
			std::cout << "playlist not found";
		else
			searcher(data, pname, dek);
		std::cout << "would you like to make another playlist?\n";
		std::cin >> answer;
	} while (answer == "yes");
}