#include <iostream>
#include <fstream>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Game.h"

Game::Game(const std::string& configuration)
{
	init(configuration);
}

void Game::init(const std::string& filepath)
{

	std::ifstream fs(filepath);
	std::string current_line;

	while (fs >> current_line)
	{
		if (current_line == "Window")
		{
			int window_width;
			int window_height;
			int framerate_limit;
			int fullscreen_mode;

			fs >> window_width >> window_height >> framerate_limit
				>> fullscreen_mode;

			m_window_configuration.W = window_width;
			m_window_configuration.H = window_height;
			m_window_configuration.FL = framerate_limit;
			m_window_configuration.FS = fullscreen_mode;

			m_render_window.setFramerateLimit(m_window_configuration.FL);

			if (m_window_configuration.FS == 1)
			{
				m_render_window.create(
					sf::VideoMode(
						m_window_configuration.W,
						m_window_configuration.H
					),
					"Geometry Wars",
					sf::Style::Fullscreen
				);
			}
			else
			{
				m_render_window.create(
					sf::VideoMode(
						m_window_configuration.W,
						m_window_configuration.H
					),
					"Geometry Wars",
					sf::Style::Default
				);
			}

			std::cout << "Window configuration read" << std::endl;
		}
		else if (current_line == "Font")
		{
			std::string font_file_path;
			int font_size;
			int font_colour_red;
			int font_colour_green;
			int font_colour_blue;

			fs >> font_file_path >> font_size >> font_colour_red
				>> font_colour_green >> font_colour_blue;

			if (!m_font.loadFromFile(font_file_path))
			{
				std::cerr << "Error: Could not load font" << std::endl;
				exit(1);
			}

			m_text.setFont(m_font);
			m_text.setCharacterSize(font_size);
			m_text.setFillColor(sf::Color(
				font_colour_red, font_colour_green, font_colour_blue
			));

			std::cout << "Font configuration read" << std::endl;
		}
		else if (current_line == "Player")
		{
			int shape_radius;
			int collision_radius;
			float speed;
			int fill_colour_red;
			int fill_colour_green;
			int fill_colour_blue;
			int outline_colour_red;
			int outline_colour_green;
			int outline_colour_blue;
			int outline_thickness;
			int vertice_count;

			fs >> shape_radius >> collision_radius >> speed >> fill_colour_red
				>> fill_colour_green >> fill_colour_blue >> outline_colour_red
				>> outline_colour_green >> outline_colour_blue
				>> outline_thickness >> vertice_count;

			m_player_configuration = {
				shape_radius, collision_radius, fill_colour_red,
				fill_colour_green, fill_colour_blue, outline_colour_red,
				outline_colour_green, outline_colour_blue, outline_thickness,
				vertice_count, speed
			};

			std::cout << "Player configuration read" << std::endl;
		}
		else if (current_line == "Enemy")
		{
			int shape_radius;
			int collision_radius;
			float speed_min;
			float speed_max;
			int outline_colour_red;
			int outline_colour_green;
			int outline_colour_blue;
			int outline_thickness;
			int vertice_count_min;
			int vertice_count_max;
			int lifespan;
			int spawn_interval;

			fs >> shape_radius >> collision_radius >> speed_min >> speed_max
				>> outline_colour_red >> outline_colour_green
				>> outline_colour_blue >> outline_thickness
				>> vertice_count_min >> vertice_count_max >> lifespan
				>> spawn_interval;

			m_enemy_configuration = {
				shape_radius, collision_radius, outline_colour_red,
				outline_colour_green, outline_colour_blue, outline_thickness,
				vertice_count_min, vertice_count_max, lifespan, spawn_interval, 
				speed_min, speed_max
			};

			gui = GUI(spawn_interval);

			std::cout << "Enemy configuration read" << std::endl;
		}
		else if (current_line == "Bullet")
		{
			int shape_radius;
			int collision_radius;
			float speed;
			int fill_colour_red;
			int fill_colour_green;
			int fill_colour_blue;
			int outline_colour_red;
			int outline_colour_green;
			int outline_colour_blue;
			int outline_thickness;
			int vertice_count;
			int lifespan;

			fs >> shape_radius >> collision_radius >> speed >> fill_colour_red
				>> fill_colour_green >> fill_colour_blue >> outline_colour_red
				>> outline_colour_green >> outline_colour_blue
				>> outline_thickness >> vertice_count >> lifespan;

			std::cout << "Bullet configuration read" << std::endl;
		}
		else
		{
			std::cout << "Error: Line type not recognised" << std::endl;
		}
	}

	ImGui::SFML::Init(m_render_window);

	ImGui::GetStyle().ScaleAllSizes(2.0f);
	ImGui::GetIO().FontGlobalScale = 2.0f;

	spawnPlayer();
}

// since the player will be referred to a lot, here is a method to retrieve
// where the player is stored
std::shared_ptr<Entity> Game::player()
{
	auto& players = m_entities.getEntities("player");

	//assert(players.size() == 1);

	return players.front();
}

void Game::run()
{
	// add pause functionality
	// - some systems should function whilst paused (i.e., rendering)
	// - some systems should not function whilst paused (e.g., movement, input)
	// - current frame should not increment whilst paused

	while (m_is_running)
	{
		m_entities.update();

		ImGui::SFML::Update(m_render_window, m_delta_clock.restart());

		if (!m_is_paused)
		{
			if (gui.spawning) systemEnemySpawner();
			if (gui.movement) systemMovement();
			if (gui.collision) systemCollision();
			if (gui.lifespan) systemLifespan();

			m_current_frame++;
		}

		systemInput();
		if (gui.gui) systemGUI();
		systemRender();
	}
}

void Game::setPaused(bool paused)
{
	// pause or unpause the game
	// - lifespan should not deplete whilst the game is paused
	// - entities may still rotate whilst the game is paused if you would like
	m_is_paused = paused;
}

void Game::spawnPlayer()
{
	auto entity = m_entities.addEntity("player");

	entity->add<CTransform>(
		Vec2f(m_render_window.getSize().x / 2, m_render_window.getSize().y / 2),
		Vec2f(0.0f, 0.0f),
		0.0f
	);

	entity->add<CShape>(
		m_player_configuration.SR, m_player_configuration.V,
		sf::Color(m_player_configuration.FR, m_player_configuration.FG, m_player_configuration.FB),
		sf::Color(m_player_configuration.OR, m_player_configuration.OG, m_player_configuration.OB),
		m_player_configuration.OT
	);

	entity->add<CInput>();
}

void Game::spawnEnemyLarge()
{
	// make sure enemy is spawned property with the enemy configuration variables
	// enemy must be spawned at a random position (using configuration variables)
	// enemy must be spawned completely within the bounds of the window

	/* configuration
		- shape radius
		- collision radius
		- min speed
		- max speed
		- outline red
		- outline green
		- outline blue
		- outline thickness
		- min vertices
		- max vertices
		- lifespan small
		- spawn interval
	*/

	auto entity = m_entities.addEntity("enemy");

	int min_vertices = m_enemy_configuration.VMIN;
	int max_vertices = m_enemy_configuration.VMAX;

	int vertices = min_vertices + (rand() % (1 + max_vertices - min_vertices));

	int fill_red = 0 + (rand() % (1 + 255 - 0));
	int fill_green = 0 + (rand() % (1 + 255 - 0));
	int fill_blue = 0 + (rand() % (1 + 255 - 0));

	int outline_red = 0 + (rand() % (1 + 255 - 0));
	int outline_green = 0 + (rand() % (1 + 255 - 0));
	int outline_blue = 0 + (rand() % (1 + 255 - 0));

	entity->add<CShape>(
		m_enemy_configuration.SR, vertices,
		sf::Color(fill_red, fill_green, fill_blue),
		sf::Color(outline_red, outline_green, outline_blue),
		m_enemy_configuration.OT
	);

	int radius = entity->get<CShape>().circle.getRadius();

	int min_position_x = radius;
	int max_position_x =
		m_window_configuration.W - radius;

	int min_position_y = radius;
	int max_position_y =
		m_window_configuration.H - radius;

	int position_x = min_position_x + (rand() % (1 + max_position_x - min_position_x));
	int position_y = min_position_y + (rand() % (1 + max_position_y - min_position_y));

	int min_velocity = m_enemy_configuration.SMIN;
	int max_velocity = m_enemy_configuration.SMAX;

	int velocity_x = min_velocity + (rand() % (1 + max_velocity - min_velocity));
	int velocity_y = min_velocity + (rand() % (1 + max_velocity - min_velocity));

	entity->add<CTransform>(
		Vec2f(position_x, position_y),
		Vec2f(velocity_x, velocity_y),
		0.0f
	);

	entity->add<CScore>(10);


	entity->add<CCollision>(m_enemy_configuration.CR);

	m_last_enemy_spawn_time = m_current_frame;
}

void Game::spawnEnemySmall(std::shared_ptr<Entity> entity)
{
	// - spawn small enemies at the location of the parameter entity
	// - the number of enemies should be equal to the number of vertices of the
	// parameter entity
	// - fill colour of emeies should be the same as the parameter entity
	// - size of enemies should be half the size of the parameter entity
	// - score of each enemy should be double the score of the parameter entity
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2f& target)
{
	// spawn a bullet at a given entity to a target location
	// bullet speed is given as a scalar speed
	// use formula in notes to set the velocity
}

void Game::spawnSpecialAbility(std::shared_ptr<Entity> entity)
{
	// implement your custom special ability
}

void Game::systemMovement()
{
	// implement all entity movement
	// the CInput component of m_player should be read to determine whether the
	// player is moving

	
	// sample movement speed update

	auto& input = player()->get<CInput>();
	auto& transform = player()->get<CTransform>();

	if (input.is_up_pressed)
	{
		transform.velocity.y -=
			(m_player_configuration.S / m_window_configuration.FL);
	}
	if (input.is_right_pressed)
	{
		transform.velocity.x +=
			(m_player_configuration.S / m_window_configuration.FL);
	}
	if (input.is_down_pressed)
	{
		transform.velocity.y +=
			(m_player_configuration.S / m_window_configuration.FL);
	}
	if (input.is_left_pressed)
	{
		transform.velocity.x -=
			(m_player_configuration.S / m_window_configuration.FL);
	}

	transform.position += transform.velocity;
	transform.velocity = { 0.0, 0.0 };
}

void Game::systemLifespan()
{
	// implement all lifespan functionality
	// - for all entities
	//     - if entity has not lifespan component, skip it
	//     - if lifespan component has lifespan_remaining greater than 0, subtract
	//     1 from it
	//     - if entity has lifespan component and is alive
	//         - modify its alpha channel appropriately
	//     - if entity has a lifespan component and lifespan_remaining is less
	//     than 0, destroy it

	for (auto& entity : m_entities.getEntities())
	{
		auto& lifespan = entity->get<CLifespan>();

		if (!lifespan.exists) continue;

		if (lifespan.lifespan_remaining >= 0)
		{
			lifespan.lifespan_remaining -= 1;
		}
		
		if (entity->getIsActive())
		{
			// modify alpha channel
		}

		if (lifespan.lifespan_remaining < 0)
		{
			
		}
	}
}

void Game::systemCollision()
{
	// implement all proper collisons between entities
	// use collision radius, not shape radius

	for (auto& bullet : m_entities.getEntities("bullet"))
	{
		for (auto& enemy : m_entities.getEntities("enemy-large"))
		{
			// use transforms and collision radii to detect whether a 
			// collision occurs
		}

		for (auto& enemy : m_entities.getEntities("enemy-small"))
		{
			// use transforms and collision radii to detect whether a
			// collision occurs
		}
	}

	for (auto& enemy : m_entities.getEntities("enemy-large"))
	{
		// check for collision against player
	}

	for (auto& enemy : m_entities.getEntities("enemy-smal"))
	{
		// check for collision against player
	}
}

void Game::systemEnemySpawner()
{
	// implement enemy spawner
	// check when the last time an enemy was spawned
	if (
		m_current_frame - m_last_enemy_spawn_time
		>= m_enemy_configuration.SI * 1000
	)
	{
		spawnEnemyLarge();
	}
}

void Game::systemGUI()
{
	// create the imgui interface...

	ImGui::Begin("Geometry Wars");

	if (ImGui::BeginTabBar("Geometry Wars Tab"))
	{
		if (ImGui::BeginTabItem("System"))
		{
			ImGui::Checkbox("Movement", &gui.movement);
			ImGui::Checkbox("Lifespan", &gui.lifespan);
			ImGui::Checkbox("Collision", &gui.collision);
			ImGui::Checkbox("Spawning", &gui.spawning);

			// implement: spawn rate slider
			ImGui::SliderInt(
				"Spawn",
				&gui.spawn_interval,
				10, 150
			);

			m_enemy_configuration.SI = gui.spawn_interval;

			if (ImGui::Button("Manual Spawn"))
			{
				spawnEnemyLarge();
			}

			ImGui::Checkbox("GUI", &gui.gui);
			ImGui::Checkbox("Rendering", &gui.rendering);

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Entity"))
		{
			ImGui::Text("Tab 2");
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();
}

void Game::systemRender()
{
	m_render_window.clear();

	if (gui.rendering)
	{

		for (auto& entity : m_entities.getEntities())
		{
			// modify code bellow to draw all entities, not just the player
			// loop over all entities to achieve this

			// determine entity type

			if (entity == player())
			{
				// update position
				player()->get<CShape>()
					.circle.setPosition(player()->get<CTransform>().position);

				// update transform rotation
				player()->get<CTransform>().angle +=
					(1.0f / m_window_configuration.FL);
				// update shape rotation using transform rotation
				player()->get<CShape>()
					.circle.setRotation(player()->get<CTransform>().angle);

				// draw player sf::CircleShape
				m_render_window.draw(player()->get<CShape>().circle);
			}
			else {

			}


			if (entity->getTag() == "enemy")
			{

			}
			else if (entity->getTag() == "bullet")
			{

			}
		}
	}

	// draw ui last
	ImGui::SFML::Render(m_render_window);

	m_render_window.display();
}

void Game::systemInput()
{
	// handle user input
	// only set player's input component variables
	// do not implement player's movement logic here
	// movement system will be reading variables that are modified in this function

	sf::Event event;

	while (m_render_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

		// change state to determine whether window will be closed later
		if (event.type == sf::Event::Closed) m_is_running = false;

		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
				case sf::Keyboard::W:
					player()->get<CInput>().is_up_pressed = true;
					break;
				case sf::Keyboard::D:
					player()->get<CInput>().is_right_pressed = true;
					break;
				case sf::Keyboard::S:
					player()->get<CInput>().is_down_pressed = true;
					break;
				case sf::Keyboard::A:
					player()->get<CInput>().is_left_pressed = true;
					break;
				case sf::Keyboard::Escape:
					m_is_running = false;
					break;
				default: break;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
				case sf::Keyboard::W:
					player()->get<CInput>().is_up_pressed = false;
					break;
				case sf::Keyboard::D:
					player()->get<CInput>().is_right_pressed = false;
					break;
				case sf::Keyboard::S:
					player()->get<CInput>().is_down_pressed = false;
					break;
				case sf::Keyboard::A:
					player()->get<CInput>().is_left_pressed = false;
					break;
				case sf::Keyboard::P:
					setPaused(!m_is_paused);
					break;
				default:
					break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			// ignore mouse events if the mouse is clicking on the imgui window
			if (ImGui::GetIO().WantCaptureMouse) continue;

			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "Left: (" << event.mouseButton.x << ", "
					<< event.mouseButton.y << ")" << std::endl;

				// use mouse position (along with player position) to determine
				// trajectory of the bullet
				// and then spawn the bullet
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "Right: (" << event.mouseButton.x << ", "
					<< event.mouseButton.y << ")" << std::endl;
				spawnEnemyLarge();

				// use mouse position (along with player position) to determine
				// trajectory of the bullet
				// and then spawn the bullet
			}
		}
	}
}
