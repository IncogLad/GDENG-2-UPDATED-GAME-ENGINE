#include "JsonParser.h"

#include  <iostream>
#include  <json/value.h>
#include  <json/json.h>
#include  <fstream>
#include  <string>

using namespace  std;


JsonParser* JsonParser::sharedInstance = nullptr;

JsonParser::JsonParser()
{
}

JsonParser::~JsonParser()
{
}

void JsonParser::initialize()
{
	sharedInstance = new JsonParser();

	Json::Value event;
	//Json::Value& coords = event["cubes"];

	Json::Value result;
	Json::Value data;

	result["name"] = "cube1";
	data["x"] = 20;//get position data
	data["y"] = 30;//get position data
	data["z"] = 30;//get position data
	result["Position"] = data;
	data["x"] = 0;//get rotation data
	data["y"] = 0;//get rotation data
	data["z"] = 0;//get rotation data
	result["Rotation"] = data;
	data["x"] = 5;//get scale data
	data["y"] = 5;//get scale data
	data["z"] = 5;//get scale data
	result["Scale"] = data;
	event["cubes"][0] = result;


	result["name"] = "cube2";
	data["x"] = 20;//get position data
	data["y"] = 30;//get position data
	data["z"] = 30;//get position data
	result["Position"] = data;
	data["x"] = 0;//get rotation data
	data["y"] = 0;//get rotation data
	data["z"] = 0;//get rotation data
	result["Rotation"] = data;
	data["x"] = 5;//get scale data
	data["y"] = 5;//get scale data
	data["z"] = 5;//get scale data
	result["Scale"] = data;

	event["cubes"][1] = result;


	result["name"] = "cube3";

	data["x"] = 20;//get position data
	data["y"] = 30;//get position data
	data["z"] = 30;//get position data
	result["Position"] = data;
	data["x"] = 0;//get rotation data
	data["y"] = 0;//get rotation data
	data["z"] = 0;//get rotation data
	result["Rotation"] = data;
	data["x"] = 5;//get scale data
	data["y"] = 5;//get scale data
	data["z"] = 5;//get scale data
	result["Scale"] = data;

	event["cubes"][2] = result;

	//loop for spheres
	result["name"] = "sphere1";

	data["x"] = 20;//get position data
	data["y"] = 30;//get position data
	data["z"] = 30;//get position data
	result["Position"] = data;
	data["x"] = 0;//get rotation data
	data["y"] = 0;//get rotation data
	data["z"] = 0;//get rotation data
	result["Rotation"] = data;
	data["x"] = 5;//get scale data
	data["y"] = 5;//get scale data
	data["z"] = 5;//get scale data
	result["Scale"] = data;


	event["spheres"][0] = result;

	//loop for capsule
	result["name"] = "capsule1";

	data["x"] = 20;//get position data
	data["y"] = 30;//get position data
	data["z"] = 30;//get position data
	result["Position"] = data;
	data["x"] = 0;//get rotation data
	data["y"] = 0;//get rotation data
	data["z"] = 0;//get rotation data
	result["Rotation"] = data;
	data["x"] = 5;//get scale data
	data["y"] = 5;//get scale data
	data["z"] = 5;//get scale data
	result["Scale"] = data;


	event["capsules"][0] = result;

	//loop for planes
	result["name"] = "planes1";

	data["x"] = 20;//get position data
	data["y"] = 30;//get position data
	data["z"] = 30;//get position data
	result["Position"] = data;
	data["x"] = 0;//get rotation data
	data["y"] = 0;//get rotation data
	data["z"] = 0;//get rotation data
	result["Rotation"] = data;
	data["x"] = 5;//get scale data
	data["y"] = 5;//get scale data
	data["z"] = 5;//get scale data
	result["Scale"] = data;


	event["planes"][0] = result;




	Json::StreamWriterBuilder builder;
	const std::string json_file = Json::writeString(builder, event);
	std::cout << json_file << std::endl;


	std::ofstream myfile;
	//filepath
	myfile.open("example.txt");
	//writing it to file
	myfile << json_file;

	//myfile << "Writing this to a file.\n";



	myfile.close();
}


