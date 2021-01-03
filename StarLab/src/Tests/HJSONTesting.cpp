#include "HJSONTesting.h"

void HJSONTesting::Test()
{
	const char* file = "../../game/shaders/StarLabTesting.starlab";

	Hjson::Value val = Hjson::UnmarshalFromFile(file);

	Hjson::Value properties = val["Properties"];
	size_t propertiesSize = properties.size();

	Hjson::Type type = properties.type();

	for (int i = 0; i < propertiesSize; i++)
	{
		std::string type = properties[i]["name"].to_string();

		int j = 0;
	}

	int i = 0;
}
