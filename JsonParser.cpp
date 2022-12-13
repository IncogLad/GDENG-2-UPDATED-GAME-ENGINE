#include "JsonParser.h"

#include  <iostream>
#include  <json/value.h>
#include  <json/json.h>
#include  <fstream>
#include  <string>

#include "GameObjectManager.h"
#include "UISystem.h"

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

void JsonParser::ShowExampleAppLog(bool* p_open)
{
	static ExampleAppLog log;

	// For the demo: add a debug button _BEFORE_ the normal log window contents
	// We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
	// Most of the contents of the window will be added by the log.Draw() call.
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
	ImGui::Begin("Example: Log", p_open);
	//IMGUI_DEMO_MARKER("Examples/Log");
	if (ImGui::SmallButton("[Debug] Add 5 entries"))
	{
		static int counter = 0;
		const char* categories[3] = { "info", "warn", "error" };
		const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
		for (int n = 0; n < 5; n++)
		{
			const char* category = categories[counter % IM_ARRAYSIZE(categories)];
			const char* word = words[counter % IM_ARRAYSIZE(words)];
			log.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
				ImGui::GetFrameCount(), category, ImGui::GetTime(), word);
			counter++;
		}
	}
	ImGui::End();

	// Actually call in the regular Log helper (which will Begin() into the same window as we just did)
	log.Draw("Example: Log", p_open);
}


void JsonParser::saveScene()
{
	static ExampleAppLog my_log;
	  my_log.AddLog("Hello %d world\n", 123);
	  my_log.Draw("title");

	  bool* p_open = 0;

	  static ExampleAppLog log;

	  // For the demo: add a debug button _BEFORE_ the normal log window contents
	  // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
	  // Most of the contents of the window will be added by the log.Draw() call.
	  ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
	  ImGui::Begin("Example: Log", p_open);
	  //IMGUI_DEMO_MARKER("Examples/Log");
	  if (ImGui::SmallButton("[Debug] Add 5 entries"))
	  {
		  static int counter = 0;
		  const char* categories[3] = { "info", "warn", "error" };
		  const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
		  for (int n = 0; n < 5; n++)
		  {
			  const char* category = categories[counter % IM_ARRAYSIZE(categories)];
			  const char* word = words[counter % IM_ARRAYSIZE(words)];
			  log.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
				  ImGui::GetFrameCount(), category, ImGui::GetTime(), word);
			  counter++;
		  }
	  }
	  ImGui::End();

	  // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
	  log.Draw("Example: Log", p_open);

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
			result["position"] = data;
			data["x"] = game_object->getLocalRotation().m_x;//get position data
			data["y"] = game_object->getLocalRotation().m_y;//get position data
			data["z"] = game_object->getLocalRotation().m_z;//get position data
			result["rotation"] = data;
			data["x"] = game_object->getLocalScale().m_x;//get position data
			data["y"] = game_object->getLocalScale().m_y;//get position data
			data["z"] = game_object->getLocalScale().m_z;
			result["scale"] = data;
			if (!game_object->getComponentsOfType(AComponent::Physics).empty())
			{
				result["rigidBody"] = true;
			}
			else
			{
				result["rigidBody"] = false;
			}
			event["cubes"][latestCubeCount] = result;
			latestCubeCount++;
		}
		if (game_object->getTag() == "plane")
		{
			result["name"] = game_object->getName();
			data["x"] = game_object->getLocalPosition().m_x;//get position data
			data["y"] = game_object->getLocalPosition().m_y;//get position data
			data["z"] = game_object->getLocalPosition().m_z;//get position data
			result["position"] = data;
			data["x"] = game_object->getLocalRotation().m_x;//get position data
			data["y"] = game_object->getLocalRotation().m_y;//get position data
			data["z"] = game_object->getLocalRotation().m_z;//get position data
			result["rotation"] = data;
			data["x"] = game_object->getLocalScale().m_x;//get position data
			data["y"] = game_object->getLocalScale().m_y;//get position data
			data["z"] = game_object->getLocalScale().m_z;
			result["scale"] = data;
			if (!game_object->getComponentsOfType(AComponent::Physics).empty())
			{
				result["rigidBody"] = true;
			}
			else
			{
				result["rigidBody"] = false;
			}
			event["planes"][latestPlaneCount] = result;
			latestPlaneCount++;
		}
		if (game_object->getTag() == "sphere")
		{
			result["name"] = game_object->getName();
			data["x"] = game_object->getLocalPosition().m_x;//get position data
			data["y"] = game_object->getLocalPosition().m_y;//get position data
			data["z"] = game_object->getLocalPosition().m_z;//get position data
			result["position"] = data;
			data["x"] = game_object->getLocalRotation().m_x;//get position data
			data["y"] = game_object->getLocalRotation().m_y;//get position data
			data["z"] = game_object->getLocalRotation().m_z;//get position data
			result["rotation"] = data;
			data["x"] = game_object->getLocalScale().m_x;//get position data
			data["y"] = game_object->getLocalScale().m_y;//get position data
			data["z"] = game_object->getLocalScale().m_z;
			result["scale"] = data;
			if (!game_object->getComponentsOfType(AComponent::Physics).empty())
			{
				result["rigidBody"] = true;
			}
			else
			{
				result["rigidBody"] = false;
			}
			event["spheres"][latestSphereCount] = result;
			latestSphereCount++;
		}
		if (game_object->getTag() == "capsule")
		{
			result["name"] = game_object->getName();
			data["x"] = game_object->getLocalPosition().m_x;//get position data
			data["y"] = game_object->getLocalPosition().m_y;//get position data
			data["z"] = game_object->getLocalPosition().m_z;//get position data
			result["position"] = data;
			data["x"] = game_object->getLocalRotation().m_x;//get position data
			data["y"] = game_object->getLocalRotation().m_y;//get position data
			data["z"] = game_object->getLocalRotation().m_z;//get position data
			result["rotation"] = data;
			data["x"] = game_object->getLocalScale().m_x;//get position data
			data["y"] = game_object->getLocalScale().m_y;//get position data
			data["z"] = game_object->getLocalScale().m_z;
			result["scale"] = data;
			if (!game_object->getComponentsOfType(AComponent::Physics).empty())
			{
				result["rigidBody"] = true;
			}
			else
			{
				result["rigidBody"] = false;
			}
			
			event["capsules"][latestCapsuleCount] = result;
			latestCapsuleCount++;
		}
	}

	Json::StreamWriterBuilder builder;
	const std::string json_file = Json::writeString(builder, event);

	//std::string test = "test";
	UISystem::getInstance()->UpdateDebugWindow(json_file);

	//std::cout << json_file << std::endl;


	std::ofstream myfile;
	//filepath
	myfile.open("ParseThis.level");
	//writing it to file
	myfile << json_file;
	myfile.close();

}


void JsonParser::loadScene()
{

	//ifstream file("example.txt");
	//ifstream file("FromUnity.level");
	ifstream file("FromUnreal.level");

	Json::Value actualJson;
	Json::Reader reader;
	reader.parse(file, actualJson);

	

	for (int i = 0; i < actualJson["cubes"].size(); i++)
	{
		Json::FastWriter fastWriter;
		
		std::string name = fastWriter.write(actualJson["cubes"][i]["name"]);

		float xPosition = actualJson["cubes"][i]["position"]["x"].asFloat();
		float yPosition = actualJson["cubes"][i]["position"]["y"].asFloat();
		float zPosition = actualJson["cubes"][i]["position"]["z"].asFloat();

		float xScale = actualJson["cubes"][i]["scale"]["x"].asFloat();
		float yScale = actualJson["cubes"][i]["scale"]["y"].asFloat();
		float zScale = actualJson["cubes"][i]["scale"]["z"].asFloat();

		float xRotation = actualJson["cubes"][i]["rotation"]["x"].asFloat();
		float yRotation = actualJson["cubes"][i]["rotation"]["y"].asFloat();
		float zRotation = actualJson["cubes"][i]["rotation"]["z"].asFloat();

		Vector3D position = Vector3D(xPosition, yPosition, zPosition);
		Vector3D scale = Vector3D(xScale, yScale, zScale);
		Vector3D rotation = Vector3D(xRotation, yRotation, zRotation);

		bool isRigidBody = actualJson["cubes"][i]["rigidBody"].asBool();

		GameObjectManager::getInstance()->initializeCubeOnLoad(name, 0, position, scale, rotation, isRigidBody);
	}

	for (int i = 0; i < actualJson["planes"].size(); i++)
	{
		Json::FastWriter fastWriter;

		std::string name = fastWriter.write(actualJson["planes"][i]["name"]);

		float xPosition = actualJson["planes"][i]["position"]["x"].asFloat();
		float yPosition = actualJson["planes"][i]["position"]["y"].asFloat();
		float zPosition = actualJson["planes"][i]["position"]["z"].asFloat();

		float xScale = actualJson["planes"][i]["scale"]["x"].asFloat();
		float yScale = actualJson["planes"][i]["scale"]["y"].asFloat();
		float zScale = actualJson["planes"][i]["scale"]["z"].asFloat();

		float xRotation = actualJson["planes"][i]["rotation"]["x"].asFloat();
		float yRotation = actualJson["planes"][i]["rotation"]["y"].asFloat();
		float zRotation = actualJson["planes"][i]["rotation"]["z"].asFloat();

		Vector3D position = Vector3D(xPosition, yPosition, zPosition);
		Vector3D scale = Vector3D(xScale, yScale, zScale);
		Vector3D rotation = Vector3D(xRotation, yRotation, zRotation);

		bool isRigidBody = actualJson["planes"][i]["rigidBody"].asBool();

		GameObjectManager::getInstance()->initializeCubeOnLoad(name, 1, position, scale, rotation, isRigidBody);
	}
	for (int i = 0; i < actualJson["capsules"].size(); i++)
	{
		Json::FastWriter fastWriter;

		std::string name = fastWriter.write(actualJson["capsules"][i]["name"]);

		float xPosition = actualJson["capsules"][i]["position"]["x"].asFloat();
		float yPosition = actualJson["capsules"][i]["position"]["y"].asFloat();
		float zPosition = actualJson["capsules"][i]["position"]["z"].asFloat();

		float xScale = actualJson["capsules"][i]["scale"]["x"].asFloat();
		float yScale = actualJson["capsules"][i]["scale"]["y"].asFloat();
		float zScale = actualJson["capsules"][i]["scale"]["z"].asFloat();

		float xRotation = actualJson["capsules"][i]["rotation"]["x"].asFloat();
		float yRotation = actualJson["capsules"][i]["rotation"]["y"].asFloat();
		float zRotation = actualJson["capsules"][i]["rotation"]["z"].asFloat();

		Vector3D position = Vector3D(xPosition, yPosition, zPosition);
		Vector3D scale = Vector3D(xScale, yScale, zScale);
		Vector3D rotation = Vector3D(xRotation, yRotation, zRotation);

		bool isRigidBody = actualJson["capsules"][i]["rigidBody"].asBool();

		GameObjectManager::getInstance()->initializeCapsuleOnLoad(name, position, scale, rotation, isRigidBody);
	}

	for (int i = 0; i < actualJson["spheres"].size(); i++)
	{
		Json::FastWriter fastWriter;

		std::string name = fastWriter.write(actualJson["spheres"][i]["name"]);

		float xPosition = actualJson["spheres"][i]["position"]["x"].asFloat();
		float yPosition = actualJson["spheres"][i]["position"]["y"].asFloat();
		float zPosition = actualJson["spheres"][i]["position"]["z"].asFloat();

		float xScale = actualJson["spheres"][i]["scale"]["x"].asFloat();
		float yScale = actualJson["spheres"][i]["scale"]["y"].asFloat();
		float zScale = actualJson["spheres"][i]["scale"]["z"].asFloat();

		float xRotation = actualJson["spheres"][i]["rotation"]["x"].asFloat();
		float yRotation = actualJson["spheres"][i]["rotation"]["y"].asFloat();
		float zRotation = actualJson["spheres"][i]["rotation"]["z"].asFloat();

		Vector3D position = Vector3D(xPosition, yPosition, zPosition);
		Vector3D scale = Vector3D(xScale, yScale, zScale);
		Vector3D rotation = Vector3D(xRotation, yRotation, zRotation);

		bool isRigidBody = actualJson["spheres"][i]["rigidBody"].asBool();

		GameObjectManager::getInstance()->initializeSphereOnLoad(name, position, scale, rotation, isRigidBody);
	}
	
}

void JsonParser::print(const std::string str, std::ostream& output)
{
	output << str;


	
}

