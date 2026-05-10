#include "Config/ConfigManager.h"
#include <iostream>
#include <fstream>
#include "Config/ConfigTypes.h"
#include <array>

ConfigManager::ConfigManager()
{
}

ConfigManager::~ConfigManager()
{
}

void ConfigManager::ReadConfigFile(const std::string& filename)
{
	std::string line;
	std::ifstream fin(filename);
	std::string currentKey;
	std::array<std::string, 10> configBuffer;
	int bufferIndex = 0;
	
	while (fin >> line)
	{
		printf("Checking value %s \n",line.c_str());

		if (KeyMap.count(line)!=0)
		{
			printf("Value is a valid  key\n");

			if (currentKey != "")//We have a previous key buffered, flush it!
			{
				printf("Flushing config values\n");
				PushConfigValues(KeyMap.at(currentKey), configBuffer);
				configBuffer.fill("");
				bufferIndex = 0;
			}

			currentKey = line;
		}
		else {
			if (currentKey != "")
			{
				configBuffer[bufferIndex] = line;
				bufferIndex++;
			}
		}
	}

	// EOF reached flush last block
	if (currentKey != "")
	{
		PushConfigValues(KeyMap.at(currentKey), configBuffer);
	}
}

void ConfigManager::PushConfigValues(EConfigType key, const std::array<std::string, 10>& configBuffer)
{
	ConfigCircle tempConf;
	ConfigRectangle tempConfRect;
	switch (key)
	{
		case EConfigType::Window:
			windowConfig.width = std::stoi(configBuffer[0]);
			windowConfig.height = std::stoi(configBuffer[1]);
			break;
		case EConfigType::Font:
			fontConfig.path = configBuffer[0];
			fontConfig.size = std::stoi(configBuffer[1]);
			fontConfig.r = std::stoi(configBuffer[2]);
			fontConfig.g = std::stoi(configBuffer[3]);
			fontConfig.b = std::stoi(configBuffer[4]);
			break;
		case EConfigType::Circle:
			tempConf.name = configBuffer[0];
			tempConf.xpos = std::stoi(configBuffer[1]);
			tempConf.ypos = std::stoi(configBuffer[2]);
			tempConf.xspeed = std::stoi(configBuffer[3]);
			tempConf.yspeed = std::stoi(configBuffer[4]);
			tempConf.r = std::stoi(configBuffer[5]);
			tempConf.g = std::stoi(configBuffer[6]);
			tempConf.b = std::stoi(configBuffer[7]);
			tempConf.radius = std::stoi(configBuffer[8]);
			circleConfigs.push_back(tempConf);
			break;
		case EConfigType::Rectangle:
			tempConfRect.name = configBuffer[0];
			tempConfRect.xpos = std::stoi(configBuffer[1]);
			tempConfRect.ypos = std::stoi(configBuffer[2]);
			tempConfRect.xspeed = std::stoi(configBuffer[3]);
			tempConfRect.yspeed = std::stoi(configBuffer[4]);
			tempConfRect.r = std::stoi(configBuffer[5]);
			tempConfRect.g = std::stoi(configBuffer[6]);
			tempConfRect.b = std::stoi(configBuffer[7]);
			tempConfRect.width = std::stoi(configBuffer[8]);
			tempConfRect.height = std::stoi(configBuffer[9]);
			rectangleConfigs.push_back(tempConfRect);
			break;
	}
}

ConfigWindowSize& ConfigManager::GetWindowConfig()
{
	return windowConfig;
}

ConfigFont& ConfigManager::GetFontConfig()
{
	return fontConfig;
}

ConfigCircle& ConfigManager::GetCircleConfig(int index)
{
	return circleConfigs.at(index);
}

ConfigRectangle& ConfigManager::GetRectangleConfig(int index)
{
	return rectangleConfigs.at(index);
}

int ConfigManager::GetCircleConfigLength()
{
	return circleConfigs.size();
}

int ConfigManager::GetRectangleConfigLength()
{
	return rectangleConfigs.size();
}
