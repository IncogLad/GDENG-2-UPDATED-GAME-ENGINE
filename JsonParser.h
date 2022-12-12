#pragma once
#include <json/json.h>

class JsonParser
{
public:
	JsonParser();
	~JsonParser();


	static void initialize();
	static JsonParser* getInstance();
	static void destroy();
	
	 void saveScene();
	 void loadScene();

private:
	static JsonParser* sharedInstance;

	


};

