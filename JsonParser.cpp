#include "JsonParser.h"

#include  <iostream>
#include  <json/value.h>
#include  <json/json.h>
#include  <fstream>
#include  <string>

#include "GameObjectManager.h"

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

	
}

JsonParser* JsonParser::getInstance()
{
	return sharedInstance;
}

void JsonParser::destroy()
{
	delete sharedInstance;
}

void JsonParser::saveScene()
{
	Json::Value event;
	//Json::Value& coords = event["cubes"];

	Json::Value result;
	Json::Value data;
	int latestCubeCount = 0;
	int latestPlaneCount = 0;
	int latestSphereCount = 0;
	int latestCapsuleCount = 0;

	for (auto game_object : GameObjectManager::getInstance()->getGameObjectList())
	{
		if (game_object->getTag() == "cube")
		{
			result["name"] = game_object->getName();
			data["x"] = game_object->getLocalPosition().m_x;//get position data
			data["y"] = game_object->getLocalPosition().m_y;//get position data
			data["z"] = game_object->getLocalPosition().m_z;//get position data
			result["Position"] = data;
			data["x"] = game_object->getLocalRotation().m_x;//get position data
			data["y"] = game_object->getLocalRotation().m_y;//get position data
			data["z"] = game_object->getLocalRotation().m_z;//get position data
			result["Rotation"] = data;
			data["x"] = game_object->getLocalScale().m_x;//get position data
			data["y"] = game_object->getLocalScale().m_y;//get position data
			data["z"] = game_object->getLocalScale().m_z;
			result["Scale"] = data;
			event["cubes"][latestCubeCount] = result;
			latestCubeCount++;
		}
		if (game_object->getTag() == "plane")
		{
			result["name"] = game_object->getName();
			data["x"] = game_object->getLocalPosition().m_x;//get position data
			data["y"] = game_object->getLocalPosition().m_y;//get position data
			data["z"] = game_object->getLocalPosition().m_z;//get position data
			result["Position"] = data;
			data["x"] = game_object->getLocalRotation().m_x;//get position data
			data["y"] = game_object->getLocalRotation().m_y;//get position data
			data["z"] = game_object->getLocalRotation().m_z;//get position data
			result["Rotation"] = data;
			data["x"] = game_object->getLocalScale().m_x;//get position data
			data["y"] = game_object->getLocalScale().m_y;//get position data
			data["z"] = game_object->getLocalScale().m_z;
			result["Scale"] = data;
			event["planes"][latestPlaneCount] = result;
			latestPlaneCount++;
		}
		if (game_object->getTag() == "sphere")
		{
			result["name"] = game_object->getName();
			data["x"] = game_object->getLocalPosition().m_x;//get position data
			data["y"] = game_object->getLocalPosition().m_y;//get position data
			data["z"] = game_object->getLocalPosition().m_z;//get position data
			result["Position"] = data;
			data["x"] = game_object->getLocalRotation().m_x;//get position data
			data["y"] = game_object->getLocalRotation().m_y;//get position data
			data["z"] = game_object->getLocalRotation().m_z;//get position data
			result["Rotation"] = data;
			data["x"] = game_object->getLocalScale().m_x;//get position data
			data["y"] = game_object->getLocalScale().m_y;//get position data
			data["z"] = game_object->getLocalScale().m_z;
			result["Scale"] = data;
			event["sphere"][latestSphereCount] = result;
			latestSphereCount++;
		}
		if (game_object->getTag() == "capsule")
		{
			result["name"] = game_object->getName();
			data["x"] = game_object->getLocalPosition().m_x;//get position data
			data["y"] = game_object->getLocalPosition().m_y;//get position data
			data["z"] = game_object->getLocalPosition().m_z;//get position data
			result["Position"] = data;
			data["x"] = game_object->getLocalRotation().m_x;//get position data
			data["y"] = game_object->getLocalRotation().m_y;//get position data
			data["z"] = game_object->getLocalRotation().m_z;//get position data
			result["Rotation"] = data;
			data["x"] = game_object->getLocalScale().m_x;//get position data
			data["y"] = game_object->getLocalScale().m_y;//get position data
			data["z"] = game_object->getLocalScale().m_z;
			result["Scale"] = data;
			event["capsule"][latestCapsuleCount] = result;
			latestCapsuleCount++;
		}
	}

	Json::StreamWriterBuilder builder;
	const std::string json_file = Json::writeString(builder, event);
	std::cout << json_file << std::endl;


	std::ofstream myfile;
	//filepath
	myfile.open("example.json");
	//writing it to file
	myfile << json_file;
	myfile.close();

}


void JsonParser::loadScene()
{

	ifstream file("example.json");

	Json::Value actualJson;
	Json::Reader reader;
	reader.parse(file, actualJson);

	

	for (int i = 0; i < actualJson["cubes"].size(); i++)
	{
		Json::FastWriter fastWriter;
		
		std::string name = fastWriter.write(actualJson["cubes"][i]["name"]);

		float xPosition = actualJson["cubes"][i]["Position"]["x"].asFloat();
		float yPosition = actualJson["cubes"][i]["Position"]["y"].asFloat();
		float zPosition = actualJson["cubes"][i]["Position"]["z"].asFloat();

		float xScale = actualJson["cubes"][i]["Scale"]["x"].asFloat();
		float yScale = actualJson["cubes"][i]["Scale"]["y"].asFloat();
		float zScale = actualJson["cubes"][i]["Scale"]["z"].asFloat();

		float xRotation = actualJson["cubes"][i]["Rotation"]["x"].asFloat();
		float yRotation = actualJson["cubes"][i]["Rotation"]["y"].asFloat();
		float zRotation = actualJson["cubes"][i]["Rotation"]["z"].asFloat();

		Vector3D position = Vector3D(xPosition, yPosition, zPosition);
		Vector3D scale = Vector3D(xScale, yScale, zScale);
		Vector3D rotation = Vector3D(xRotation, yRotation, zRotation);


		GameObjectManager::getInstance()->initializeCubeOnLoad(name, 0, position, scale, rotation, false);
	}

	for (int i = 0; i < actualJson["planes"].size(); i++)
	{
		Json::FastWriter fastWriter;

		std::string name = fastWriter.write(actualJson["planes"][i]["name"]);

		float xPosition = actualJson["planes"][i]["Position"]["x"].asFloat();
		float yPosition = actualJson["planes"][i]["Position"]["y"].asFloat();
		float zPosition = actualJson["planes"][i]["Position"]["z"].asFloat();

		float xScale = actualJson["planes"][i]["Scale"]["x"].asFloat();
		float yScale = actualJson["planes"][i]["Scale"]["y"].asFloat();
		float zScale = actualJson["planes"][i]["Scale"]["z"].asFloat();

		float xRotation = actualJson["planes"][i]["Rotation"]["x"].asFloat();
		float yRotation = actualJson["planes"][i]["Rotation"]["y"].asFloat();
		float zRotation = actualJson["planes"][i]["Rotation"]["z"].asFloat();

		Vector3D position = Vector3D(xPosition, yPosition, zPosition);
		Vector3D scale = Vector3D(xScale, yScale, zScale);
		Vector3D rotation = Vector3D(xRotation, yRotation, zRotation);


		GameObjectManager::getInstance()->initializeCubeOnLoad(name, 1, position, scale, rotation, false);
	}
	for (int i = 0; i < actualJson["capsule"].size(); i++)
	{
		Json::FastWriter fastWriter;

		std::string name = fastWriter.write(actualJson["capsule"][i]["name"]);

		float xPosition = actualJson["capsule"][i]["Position"]["x"].asFloat();
		float yPosition = actualJson["capsule"][i]["Position"]["y"].asFloat();
		float zPosition = actualJson["capsule"][i]["Position"]["z"].asFloat();

		float xScale = actualJson["capsule"][i]["Scale"]["x"].asFloat();
		float yScale = actualJson["capsule"][i]["Scale"]["y"].asFloat();
		float zScale = actualJson["capsule"][i]["Scale"]["z"].asFloat();

		float xRotation = actualJson["capsule"][i]["Rotation"]["x"].asFloat();
		float yRotation = actualJson["capsule"][i]["Rotation"]["y"].asFloat();
		float zRotation = actualJson["capsule"][i]["Rotation"]["z"].asFloat();

		Vector3D position = Vector3D(xPosition, yPosition, zPosition);
		Vector3D scale = Vector3D(xScale, yScale, zScale);
		Vector3D rotation = Vector3D(xRotation, yRotation, zRotation);


		GameObjectManager::getInstance()->initializeCapsuleOnLoad(name, position, scale, rotation, false);
	}

	for (int i = 0; i < actualJson["sphere"].size(); i++)
	{
		Json::FastWriter fastWriter;

		std::string name = fastWriter.write(actualJson["sphere"][i]["name"]);

		float xPosition = actualJson["sphere"][i]["Position"]["x"].asFloat();
		float yPosition = actualJson["sphere"][i]["Position"]["y"].asFloat();
		float zPosition = actualJson["sphere"][i]["Position"]["z"].asFloat();

		float xScale = actualJson["sphere"][i]["Scale"]["x"].asFloat();
		float yScale = actualJson["sphere"][i]["Scale"]["y"].asFloat();
		float zScale = actualJson["sphere"][i]["Scale"]["z"].asFloat();

		float xRotation = actualJson["sphere"][i]["Rotation"]["x"].asFloat();
		float yRotation = actualJson["sphere"][i]["Rotation"]["y"].asFloat();
		float zRotation = actualJson["sphere"][i]["Rotation"]["z"].asFloat();

		Vector3D position = Vector3D(xPosition, yPosition, zPosition);
		Vector3D scale = Vector3D(xScale, yScale, zScale);
		Vector3D rotation = Vector3D(xRotation, yRotation, zRotation);


		GameObjectManager::getInstance()->initializeSphereOnLoad(name, position, scale, rotation, false);
	}
	
}

