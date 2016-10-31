#include "FlavorText.h"

FlavorText::FlavorText(string filename)
{
	file = new ifstream(filename);

	if(!*file)
	{
		cout << "FAIL WHALE!" << endl;
		exit(1);
	}

	string line;
	while(*file)
	{
		getline(*file,line);

		if(!line.empty())
			messageLines.push_back(line);
	}
	displayedMessage = messageLines[0];

}

string FlavorText::randomLine()
{
	if(messageLines.empty())
		return "I AM EMPTY";

	string newMessage;
	int num = rand() % messageLines.size();
	if(displayedMessage != (newMessage = messageLines[num]))
	{
		displayedMessage = newMessage;

		return displayedMessage;
	}
	else
	{
		return randomLine();
	}
}