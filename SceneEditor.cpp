#include "SceneEditor.h"

#include "imgui/imgui.h"

SceneEditor::SceneEditor() : AUIScreen("SCENE_EDITOR")
{
}

SceneEditor::~SceneEditor()
{
}

void SceneEditor::drawUI()
{
    ImGui::Begin("Scene Editor");
    for (String object : ObjectList)
    {
        const char* cc = object.c_str();
        ImGui::Button(cc);
    }
    ImGui::End();
}
