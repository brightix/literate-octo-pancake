#pragma once
class BlackBoard
{
	std::unordered_map<std::string, bool> boolData;
	std::unordered_map<std::string, float> floatData;
public:
	void setBool(std::string str, bool val) { boolData[str] = val; }
	bool getBool(std::string str) { return boolData[str]; }

	void setFloat(std::string key, float value) { floatData[key] = value; }
	float getFloat(std::string key) { return floatData[key]; }
};

