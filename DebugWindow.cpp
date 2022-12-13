#include "DebugWindow.h"
#include  <fstream>
#include <iostream>
#include  <string>

DebugWindow::DebugWindow() :AUIScreen("DEBUG_WINDOW")
{
    open = true;
}

DebugWindow::~DebugWindow()
{
}

void DebugWindow::print(const std::string str, std::ostream& output)
{
	std::string strs = "\n";
	std::string newString = "\n";
	newString = str + strs;
	//str = str + strs;

	//log.AddLog(str.c_str());
	log.AddLog(newString.c_str());
}

void DebugWindow::drawUI()
{
	

	// For the demo: add a debug button _BEFORE_ the normal log window contents
	// We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
	// Most of the contents of the window will be added by the log.Draw() call.
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
	ImGui::Begin("Debug Window", &open);
	//IMGUI_DEMO_MARKER("Examples/Log");
	if (ImGui::SmallButton("[Debug] Add 5 entries"))
	{
		print("bad", std::cout);

		/*static int counter = 0;
		const char* categories[3] = { "info", "warn", "error" };
		const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
		for (int n = 0; n < 5; n++)
		{
			const char* category = categories[counter % IM_ARRAYSIZE(categories)];
			const char* word = words[counter % IM_ARRAYSIZE(words)];
			log.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
				ImGui::GetFrameCount(), category, ImGui::GetTime(), word);
			counter++;
		}*/
	}
	ImGui::End();

	// Actually call in the regular Log helper (which will Begin() into the same window as we just did)
	log.Draw("Debug Window", &open);
}
