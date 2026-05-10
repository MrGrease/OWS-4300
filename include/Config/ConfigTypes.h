#ifndef CONFIG_TYPES_H
#define CONFIG_TYPES_H


enum EConfigType
{
	Window,
	Font,
	Circle,
	Rectangle
};

struct BaseConfig
{

};

struct ConfigWindowSize : BaseConfig {
	unsigned int width;
	unsigned int height;
};

struct ConfigFont : BaseConfig {
	std::string path;
	unsigned int size;
	uint8_t r, g, b;
};

struct ConfigCircle : BaseConfig {
	std::string name;
	float xpos, ypos;
	float xspeed, yspeed;
	uint8_t r, g, b;
	float radius;
};

struct ConfigRectangle : BaseConfig {
	std::string name;
	float xpos, ypos;
	float xspeed, yspeed;
	uint8_t r, g, b;
	float width, height;
};

#endif // CONFIG_TYPES_H