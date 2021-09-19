#include "hud.h"
#include "simulation.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream>

CelestialBody* Hud::selectedBody;
sf::Font Hud::font;

void Hud::render() {
	ImGui::Begin("Settings");

	if(selectedBody) {
		
		float color[3] = {
			(float) selectedBody->color.r / 255,
			(float) selectedBody->color.g / 255,
			(float) selectedBody->color.b / 255
		};

		ImGuiColorEditFlags flags;
		flags |= ImGuiColorEditFlags_NoInputs;
		flags |= ImGuiColorEditFlags_NoSidePreview;

		ImGui::ColorEdit3("Color", color, flags);

		selectedBody->color.r = color[0] * 255;
		selectedBody->color.g = color[1] * 255;
		selectedBody->color.b = color[2] * 255;

		ImGui::SliderFloat("Mass", &selectedBody->mass, 1, 2000000);
		ImGui::SliderInt("Radius", &selectedBody->radius, 1, 50);
		ImGui::Text("Velocity: %f pixels/step", selectedBody->vel.magnitude());
		ImGui::Checkbox("Affected by gravity", &selectedBody->affectedByGravity);
		ImGui::Checkbox("Affects others", &selectedBody->affectsOthers);
		if(ImGui::Button("Remove celestial body")) {
			BodyManager::remove(*selectedBody);
			selectedBody = nullptr;
		}
	}
	
	ImGui::End();
}
