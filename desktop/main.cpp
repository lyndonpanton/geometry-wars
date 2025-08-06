#include <iostream>

#include "SFML/Graphics.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

#include "Vec2.h"


int main(int argc, char* arv[])
{
	sf::RenderWindow render_window(sf::VideoMode(1080, 720), "My Window");
	sf::Clock delta_clock;

	ImGui::SFML::Init(render_window);
	ImGui::GetIO().FontGlobalScale = 1.5f;
	ImGui::GetStyle().ScaleAllSizes(1.5f);

	//Vec2f a(10.0f, 20.0f);
	//Vec2f b(50.0f, 30.0f);
	//Vec2f c = a + b;

	//std::cout << a.x << ", " << a.y << std::endl;
	//std::cout << b.x << ", " << b.y << std::endl;

	while (render_window.isOpen())
	{
		sf::Event event;
		
		while(render_window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) render_window.close();
		}

		ImGui::SFML::Update(render_window, delta_clock.restart());

		ImGui::Begin("ImGui Window");

		ImGui::Text("Hello ImGui!");

		ImGui::End();

		render_window.clear(sf::Color(0, 0, 0));

		ImGui::SFML::Render(render_window);

		render_window.display();
	}

	ImGui::SFML::Shutdown(render_window);

	return 0;
}
