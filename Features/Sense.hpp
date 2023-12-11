#pragma once
#include <iostream>
#include <vector>
#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Core/GlowMode.hpp"
#include "../Core/Camera.hpp"

#include "../Features/Aimbot.hpp"

#include "../Overlay/Overlay.hpp"
#include "../Overlay/Renderer.hpp"

#include "../Utils/Memory.hpp"
#include "../Utils/Color.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/HitboxType.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// Geometry
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI / 180.f) )

struct Sense {
    // Glow
    bool GlowEnabled = true;
    float GlowMaxDistance = 200;

    // Item Glow
    std::vector<GlowMode>* StoredGlowMode = new std::vector<GlowMode>;
    bool ItemGlow = true;

    // Health and Armor, etc...
    bool DrawSeer = true;
    bool VisibleOnly = true;
    float SeerMaxDistance = 200;

    bool DrawTracers = true; // Unused
    bool DrawDistance = true; // Unused
    bool ShowSpectators = false;

    bool DrawFOVCircle = true;
    float GameFOV = 120;

    
    Camera* GameCamera;
    LocalPlayer* Myself;
    std::vector<Player*>* Players;
    std::chrono::milliseconds LastUpdateTime;
    int TotalSpectators = 0;
    std::vector<std::string> Spectators;

    Sense(std::vector<Player*>* Players, Camera* GameCamera) {
        this->Players = Players;
        this->GameCamera = GameCamera;
    }

    void RenderUI() {
        if (ImGui::BeginTabItem("Sense", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
            // Glow //
            ImGui::Checkbox("Glow##ESP", &GlowEnabled);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Toggle Glowing");
            ImGui::SameLine();
            ImGui::Checkbox("Item Glow", &ItemGlow);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("You will have Loba's ability to see rare items");
            ImGui::SliderFloat("Max Distance", &GlowMaxDistance, 0, 1000, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Only those in range will glow");

            ImGui::Separator();

            // Drawings
            ImGui::Checkbox("Draw Health and Armor##ESP", &DrawSeer);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Draw Health Bar and Armor");
            ImGui::Checkbox("Visible Only##ESP", &VisibleOnly);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Only draw those who are visible");
            ImGui::SliderFloat("Draw Distance", &SeerMaxDistance, 0, 1000, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Only draw those in range.");

            ImGui::Separator();

            ImGui::Checkbox("Draw FOV Circle", &DrawFOVCircle);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Draw FOV Circle");
            ImGui::SliderFloat("Game's FOV", &GameFOV, 70, 120, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Your current FOV in Settings");

            ImGui::Separator();

            ImGui::Checkbox("Show Spectators", &ShowSpectators);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Show spectators");

            ImGui::EndTabItem();
        }
    }
    
    bool Save() {
        try {
            Config::Glow::Enabled = GlowEnabled;
            Config::Glow::ItemGlow = ItemGlow;
            Config::Glow::MaxDistance = GlowMaxDistance;
            Config::Glow::DrawSeer = DrawSeer;
            Config::Glow::SeerMaxDistance = SeerMaxDistance;
            Config::Glow::VisibleOnly = VisibleOnly;
            Config::Glow::DrawFOVCircle = DrawFOVCircle;
            Config::Glow::GameFOV = GameFOV;
            //Config::Glow::VisibleColor = VisibleColor;
            return true;
        } catch (...) {
            return false;
        }
    }



    void Initialize() {
        for (int placebo = 0; placebo < 31; placebo++) {
            const GlowMode Ehh = { 135, 132, 35, 127 };
            StoredGlowMode->push_back(Ehh);
        }

        const GlowMode FirstStyle = { 135, 135, 128, 64 };
        const GlowMode SecondStyle = { 135, 135, 160, 64 };
        const GlowMode ThirdStyle = { 135, 135, 255, 64 };
        const GlowMode FourthStyle = { 135, 135, 32, 64 };

        StoredGlowMode->push_back(FirstStyle);
        StoredGlowMode->push_back(SecondStyle);
        StoredGlowMode->push_back(ThirdStyle);
        StoredGlowMode->push_back(FourthStyle);
    }

    void RenderDrawings(ImDrawList* Canvas, Aimbot* AimAssistState, LocalPlayer* Myself, Overlay OverlayWindow) {
        if (!Myself->IsCombatReady()) return;
        if (DrawFOVCircle) {
            int ScreenWidth;
            int ScreenHeight;
            float FOV = std::min(AimAssistState->FOV, AimAssistState->FOV * (AimAssistState->GetFOVScale() * AimAssistState->ZoomScale));
            OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);
            float Radius = tanf(DEG2RAD(FOV) / 2) / tanf(DEG2RAD(GameFOV) / 2) * ScreenWidth;
            Renderer::DrawCircle(Canvas, Vector2D(ScreenWidth / 2, ScreenHeight / 2), Radius, 20, ImColor(255, 255, 255), 2);
        }

        if (ShowSpectators) {
            ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(ImVec2(0.0f, Center.y), ImGuiCond_Once, ImVec2(0.02f, 0.5f));
            ImGui::SetNextWindowBgAlpha(0.3f);
            ImGui::Begin("Spectators", nullptr, ImGuiWindowFlags_AlwaysAutoResize | 
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoSavedSettings | 
                ImGuiWindowFlags_NoMove | 
                ImGuiWindowFlags_NoInputs | 
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoScrollbar);

            std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
            if (Now >= LastUpdateTime + std::chrono::milliseconds(1500)) {
                int TempTotalSpectators = 0;
                std::vector<std::string> TempSpectators;

                for (int i = 0; i < Players->size(); i++) {
                    Player* p = Players->at(i);
                    if (p->BasePointer == Myself->BasePointer) continue;
                    if (p->GetViewYaw() == Myself->ViewYaw && p->IsDead) {
                        TempTotalSpectators++;
                        TempSpectators.push_back(p->GetPlayerName());
                    }
                }

                TotalSpectators = TempTotalSpectators;
                Spectators = TempSpectators;
                LastUpdateTime = Now;
            }
            ImGui::Text("Spectators: ");
            ImGui::SameLine(); ImGui::TextColored(TotalSpectators > 0 ? ImVec4(1, 0.343, 0.475, 1) : ImVec4(0.4, 1, 0.343, 1), "%d", TotalSpectators);
            if (static_cast<int>(Spectators.size()) > 0) {
                ImGui::Separator();
                for (int i = 0; i < static_cast<int>(Spectators.size()); i++) {
                    ImGui::TextColored(ImVec4(1, 0.343, 0.475, 1), "> %s", Spectators.at(i).c_str());
                }
            }
            ImGui::End();
        }

        // Draw Seer on locked target
        if (AimAssistState->TargetSelected && AimAssistState->CurrentTarget) {
            Vector2D headScreenPosition;
            GameCamera->WorldToScreen(AimAssistState->CurrentTarget->GetBonePosition(HitboxType::Head), headScreenPosition);
            if (headScreenPosition.IsZeroVector())
                return;

            Renderer::DrawSeer(Canvas, headScreenPosition.x, headScreenPosition.y - 35, AimAssistState->CurrentTarget->Shield, AimAssistState->CurrentTarget->MaxShield, AimAssistState->CurrentTarget->Health);
            return;
        }

        // Draw Seer on everyone
        for (int i = 0; i < Players->size(); i++) {
            Player* p = Players->at(i);
            if (!p->IsCombatReady() || !p->IsVisible || !p->IsHostile || p->DistanceToLocalPlayer > (Conversion::ToGameUnits(SeerMaxDistance)) || Myself->BasePointer == p->BasePointer) continue;

            if (DrawSeer) {
                Vector2D headScreenPosition;
                GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), headScreenPosition);
                if (headScreenPosition.IsZeroVector())
                    continue;

                Renderer::DrawSeer(Canvas, headScreenPosition.x, headScreenPosition.y - 35, p->Shield, p->MaxShield, p->Health);
            }
        }
    }

    void SetGlowState(long HighlightSettingsPointer, long HighlightSize, int HighlightID, GlowMode NewGlowMode) {
        const GlowMode oldGlowMode = Memory::Read<GlowMode>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 4);
        if (NewGlowMode != oldGlowMode)
            Memory::Write<GlowMode>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 4, NewGlowMode);
    }

    void SetColorState(long HighlightSettingsPointer, long HighlightSize, int HighlightID, Color NewColor) {
        const Color oldColor = Memory::Read<Color>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 8);
        if (oldColor != NewColor)
            Memory::Write<Color>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 8, NewColor);
    }

    void SetGlow(Player* Target, int GlowEnabled, int GlowThroughWall, int HighlightID) {
        if (Target->GlowEnable != GlowEnabled) Memory::Write<int>(Target->BasePointer + OFF_GLOW_ENABLE, GlowEnabled);
        if (Target->GlowThroughWall != GlowThroughWall) {
            Memory::Write<int>(Target->BasePointer + OFF_GLOW_THROUGH_WALL, GlowThroughWall);
            Memory::Write<int>(Target->BasePointer + OFF_GLOW_FIX, 2);
        }
        if (Target->HighlightID != HighlightID) Memory::Write<int>(Target->BasePointer + OFF_GLOW_HIGHLIGHT_ID + 1, HighlightID);
    }

    void Update() {
        const long HighlightSettingsPointer = Memory::Read<long>(OFF_REGION + OFF_GLOW_HIGHLIGHTS);
        const long HighlightSize = 0x28;

        // Item Glow //
        if (ItemGlow) {
            for (int highlightId = 31; highlightId < 35; highlightId++) {
                const GlowMode newGlowMode = { 137, 138, 35, 127 };
                SetGlowState(HighlightSettingsPointer, HighlightSize, highlightId, newGlowMode);
            }
        } else {
            for (int highlightId = 31; highlightId < 35; highlightId++) {
                const GlowMode newGlowMode = StoredGlowMode->at(highlightId);
                SetGlowState(HighlightSettingsPointer, HighlightSize, highlightId, newGlowMode);
            }
        }
        
        Color::ImGuiColorToColor(VisibleColorTemp, &VisibleColor);
        Color::ImGuiColorToColor(InvisibleColorTemp, &InvisibleColor);
        Color::ImGuiColorToColor(LockedOnColorTemp, &LockedOnColor);

        // Player Glow //
        // -> Visible
        SetGlowState(HighlightSettingsPointer, HighlightSize, 0, VisibleMode);
        SetColorState(HighlightSettingsPointer, HighlightSize, 0, VisibleColor);

        // -> Invisible
        SetGlowState(HighlightSettingsPointer, HighlightSize, 1, InvisibleMode);
        SetColorState(HighlightSettingsPointer, HighlightSize, 1, InvisibleColor);

        // -> Knocked
        SetGlowState(HighlightSettingsPointer, HighlightSize, 90, KnockedMode);
        SetColorState(HighlightSettingsPointer, HighlightSize, 90, KnockedColor);

        // -> Disabled
        const GlowMode DisabledMode = { 0, 0, 0, 0 };
        const Color DisabledColor = { 1, 1, 1 };
        SetGlowState(HighlightSettingsPointer, HighlightSize, 91, DisabledMode);
        SetColorState(HighlightSettingsPointer, HighlightSize, 91, DisabledColor);

        // -> Locked On
        SetGlowState(HighlightSettingsPointer, HighlightSize, 92, LockedOnMode);
        SetColorState(HighlightSettingsPointer, HighlightSize, 92, LockedOnColor);


        for (int i = 0; i < Players->size(); i++) {
            Player* Target = Players->at(i);
            if (!Target->IsValid()) continue;
            if (!Target->IsHostile) continue;

            if (GlowEnabled) {
                if (Target->IsLockedOn) {
                    SetGlow(Target, 1, 2, 92);
                    continue;
                }

                if (Target->DistanceToLocalPlayer < Conversion::ToGameUnits(GlowMaxDistance)) {
                    if (Target->IsKnocked) {
                        SetGlow(Target, 1, 2, 90);
                        continue;
                    }

                    int Highlight = 1;
                    if (Target->IsVisible){
                        Highlight = 0;
                    }
                    else {
                        Highlight = 1;
                    }
                    SetGlow(Target, 1, 2, Highlight);
                    continue;
                }
            }

            SetGlow(Target, 0, 0, 91);
        }
    }
};