#include <iostream>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Game.h"

Game::Game(const std::string& configuration)
{
	init(configuration);
}

void Game::init(const std::string& filepath)
{
	// read in configuration file, set Player, Enemy, Bullet Configuration members

	// modify the below two statements to use configuration file
	m_render_window.create(sf::VideoMode(1280, 720), "Geometry Wars");
	m_render_window.setFramerateLimit(60);

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

		systemEnemySpawner();
		systemMovement();
		systemCollision();
		systemInput();
		systemGUI();
		systemLifespan();
		systemRender();

		m_current_frame++;
	}
}

void Game::setPaused(bool paused)
{
	// pause or unpause the game
	// - lifespan should not deplete whilst the game is paused
	// - entities may still rotate whilst the game is paused if you would like
}

void Game::spawnPlayer()
{
	// player should spawn and respawn in the middle of the screen
	// modify the code bellow so that is uses the configuration file

	auto entity = m_entities.addEntity("player");

	entity->add<CTransform>(Vec2f(200.0f, 200.0f), Vec2f(1.0f, 1.0f), 0.0f);

	entity->add<CShape>(
		32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f
	);

	entity->add<CInput>();
}

void Game::spawnEnemyLarge()
{
	// make sure enemy is spawned property with the enemy configuration variables
	// enemy must be spawned at a random position (using configuration variables)
	// enemy must be spawned completely within the bounds of the window

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
	auto& transform = player()->get<CTransform>();

	transform.position += transform.velocity;
}

void Game::systemLifespan()
{
	// implement all lifespan functionality
	// - for all entities
	//     - if entity has not lifespan component, skip it
	//     - if lifespan component has lifespan_remaining greater than 0, subtract
	//     1 from it
	//     - if enitty has lifespan component and is alive
	//         - modify its alpha channel appropriately
	//     - if entity has a lifespan component and lifespan_remaining is less
	//     than 0, destroy it
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
}

void Game::systemGUI()
{
	// create the imgui interface...

	ImGui::Begin("Geometry Wars");

	ImGui::Text("Content...");

	ImGui::End();
}

void Game::systemRender()
{
	// modify code bellow to draw all entities, not just the player
	// loop over all entities to achieve this
	m_render_window.clear();

	// update position
	player()->get<CShape>()
		.circle.setPosition(player()->get<CTransform>().position);

	// update transform rotation
	player()->get<CTransform>().angle += 1.0f;
	// update shape rotation using transform rotation
	player()->get<CShape>()
		.circle.setRotation(player()->get<CTransform>().angle);

	// draw player sf::CircleShape
	m_render_window.draw(player()->get<CShape>().circle);

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
					// update player's CInput
					break;
				case sf::Keyboard::D:
					// update player's CInput
					break;
				case sf::Keyboard::S:
					// update player's CInput
					break;
				case sf::Keyboard::A:
					// update player's CInput
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
					// update player's CInput
					break;
				case sf::Keyboard::D:
					// update player's CInput
					break;
				case sf::Keyboard::S:
					// update player's CInput
					break;
				case sf::Keyboard::A:
					// update player's CInput
					break;
				case sf::Keyboard::P:
					// call method for  modifying pause state
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
				std::cout << "(" << event.mouseButton.x << ", "
					<< event.mouseButton.y << ")" << std::endl;

				// use mouse position (along with player position) to determine
				// trajectory of the bullet
				// and then spawn the bullet
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "(" << event.mouseButton.x << ", "
					<< event.mouseButton.y << ")" << std::endl;

				// use mouse position (along with player position) to determine
				// trajectory of the bullet
				// and then spawn the bullet
			}
		}
	}
}
