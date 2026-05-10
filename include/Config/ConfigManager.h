#include <string>
#include "ConfigTypes.h"
#include <unordered_map>
class ConfigManager
{
public:
	ConfigManager();
	~ConfigManager();
	void ReadConfigFile(const std::string& filename);
	void PushConfigValues(EConfigType key, const std::array<std::string, 10>& configBuffer);
	ConfigWindowSize& GetWindowConfig();
	ConfigFont& GetFontConfig();
	ConfigCircle& GetCircleConfig(int index);
	ConfigRectangle& GetRectangleConfig(int index);
	int ConfigManager::GetCircleConfigLength();
	int ConfigManager::GetRectangleConfigLength();

private:
	const std::unordered_map<std::string, EConfigType> KeyMap = {
	    { "Window", EConfigType::Window },
		{ "Font", EConfigType::Font },
		{ "Circle", EConfigType::Circle },
		{ "Rectangle", EConfigType::Rectangle }
	};

	//Config structs
	ConfigWindowSize windowConfig;
	ConfigFont fontConfig;
	std::vector<ConfigCircle> circleConfigs;
	std::vector<ConfigRectangle> rectangleConfigs;
};