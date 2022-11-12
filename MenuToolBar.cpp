#include "MenuToolBar.h"

#include "UISystem.h"
#include "imgui/imgui.h"

MenuToolBar::MenuToolBar():AUIScreen("MENU_TOOL_BAR")
{
}

MenuToolBar::~MenuToolBar()
{
}

void MenuToolBar::drawUI()
{
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", NULL, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    else
    {
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
            ImGui::MenuItem("Padding", NULL, &opt_padding);
            ImGui::Separator();

            if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
            if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
            if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
            if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
            if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
            ImGui::Separator();

            //if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
                //*p_open = false;
            
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("About"))
        {
            if (ImGui::MenuItem("Credits"))
            {
                if (UISystem::getInstance()->uiTable["CREDITS_SCREEN"]->open == true)
                {
                    UISystem::getInstance()->uiTable["CREDITS_SCREEN"]->open = false;
                }
                else
                {
                    UISystem::getInstance()->uiTable["CREDITS_SCREEN"]->open = true;
                }
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Viewports"))
        {
            if (ImGui::MenuItem("Game View"))
            {
                if (UISystem::getInstance()->uiTable["GAME_VIEW"]->open == true)
                {
                    UISystem::getInstance()->uiTable["GAME_VIEW"]->open = false;
                }
                else
                {
                    UISystem::getInstance()->uiTable["GAME_VIEW"]->open = true;
                }
            }
            if (ImGui::MenuItem("Perspective View"))
            {
                if (UISystem::getInstance()->uiTable["PERSPECTIVE_VIEW"]->open == true)
                {
                    UISystem::getInstance()->uiTable["PERSPECTIVE_VIEW"]->open = false;
                }
                else
                {
                    UISystem::getInstance()->uiTable["PERSPECTIVE_VIEW"]->open = true;
                }
            }
            if (ImGui::MenuItem("Topdown View"))
            {
                if (UISystem::getInstance()->uiTable["TOPDOWN_VIEW"]->open == true)
                {
                    UISystem::getInstance()->uiTable["TOPDOWN_VIEW"]->open = false;
                }
                else
                {
                    UISystem::getInstance()->uiTable["TOPDOWN_VIEW"]->open = true;
                }
            }
            if (ImGui::MenuItem("Wireframe View"))
            {
                if (UISystem::getInstance()->uiTable["WIREFRAME_VIEW"]->open == true)
                {
                    UISystem::getInstance()->uiTable["WIREFRAME_VIEW"]->open = false;
                }
                else
                {
                    UISystem::getInstance()->uiTable["WIREFRAME_VIEW"]->open = true;
                }
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools"))
        {
            if (ImGui::MenuItem("Color Picker"))
            {
                if (UISystem::getInstance()->uiTable["COLOR_PICKER"]->open == true)
                {
                    UISystem::getInstance()->uiTable["COLOR_PICKER"]->open = false;
                }
                else
                {
                    UISystem::getInstance()->uiTable["COLOR_PICKER"]->open = true;
                }
            }
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();

}
