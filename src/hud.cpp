#include "hud.h"
#include "simulation.h"
#include "universe.h"

#include "imgui.h"
#include <random>

CelestialBody* Hud::selectedBody;

void Hud::render() {
	ImGuiWindowFlags winFlags = 0;
	winFlags |= ImGuiWindowFlags_NoResize;
	winFlags |= ImGuiWindowFlags_NoCollapse;
	winFlags |= ImGuiWindowFlags_AlwaysAutoResize;

	// Body settings window
	ImGui::Begin("Body Setttings", nullptr, winFlags);
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
	} else {
		ImGui::Text("No body selected");
		ImGui::Text("Select one by clicking");
	}
	ImGui::End();

	// Simulation settings window
	ImGui::Begin("Simulation Settings", nullptr, winFlags);
	ImGui::Checkbox("Paused (Space)", &Simulation::paused);
	ImGui::SliderInt("Simulation speed", &Simulation::TPS, 1, 1000, "%d steps/second");
	ImGui::SliderFloat("Gravitational strength", &Universe::G, 0, 0.001, "%.5f");
	if(ImGui::Button("Add body")) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution distr(0, 255);
		BodyManager::add(CelestialBody(Vec2d(500 - Camera::offsetX, 500 - Camera::offsetY), 100, 10, sf::Color(distr(gen), distr(gen), distr(gen))));
	}
	if(ImGui::Button("Reset")) {
		BodyManager::resetBodies();
	}
	ImGui::End();

	// Help Window
	ImGui::Begin("Help", nullptr, ImGuiWindowFlags_NoResize);
	ImGui::TextWrapped("GravSim is a simple 2D newtonian gravitation simulation.\nTo select a body, you need to click it.\n\nKeyboard shortcuts:\n- Space: pause / unpause the simulation\n- Arrow Keys: Move the camera");
	ImGui::End();
}
