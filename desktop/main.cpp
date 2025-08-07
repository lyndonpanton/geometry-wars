#include <iostream>

#include "SFML/Graphics.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

#include "Vec2.hpp"

int main(int argc, char* argv[])
{
	sf::RenderWindow render_window(sf::VideoMode(1080, 720), "Geometry Wars");
	
	ImGui::SFML::Init(render_window);
	ImGui::GetStyle().ScaleAllSizes(1.5f);
	ImGui::GetIO().FontGlobalScale = 1.5f;
	sf::Clock delta_clock;

	sf::CircleShape circle(50.0f, 32);
	circle.setFillColor(sf::Color(255, 0, 0));
	circle.setPosition(490.0f, 310.0f);

	Vec2<float> v(sf::Vector2<float>(10.0f, 20.0f));

	std::cout << v.x << ", " << v.y << std::endl;

	while (render_window.isOpen())
	{
		sf::Event event;

		while (render_window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) render_window.close();
		}

		ImGui::SFML::Update(render_window, delta_clock.restart());

		ImGui::Begin("Hello ImGui");
		ImGui::Text("This is a string");
		ImGui::End();

		render_window.clear(sf::Color(0, 255, 0));
		render_window.draw(circle);

		ImGui::SFML::Render(render_window);

		render_window.display();
	}

	ImGui::SFML::Shutdown(render_window);

	return 0;
}
