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
	
	void update();
	

private:
	static JsonParser* sharedInstance;


};

