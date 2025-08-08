#pragma once

#ifndef GAME_H
#define GAME_H

#include <string>

#include "SFML/Graphics.hpp"

#include "EntityManager.h"

//#include "Component.h"
//#include "CCollision.hpp"
//#include "CInput.hpp"
//#include "CLifespan.hpp"
//#include "CScore.hpp"
//#include "CShape.hpp"
//#include "CSpecialAbility.hpp"
//#include "CTransform.hpp"

struct PlayerConfiguration
{
	int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S;
};

struct EnemyConfiguration
{
	int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX;
};

struct BulletConfiguration
{
	int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S;
};

class Game
{
	sf::RenderWindow m_render_window;
	sf::Font m_font;
	sf::Text m_text;

	EntityManager m_entities;

	PlayerConfiguration m_player_configuration;
	EnemyConfiguration m_enemy_configuration;
	BulletConfiguration m_bullet_configuration;

	sf::Clock m_delta_clock;

	int m_score = 0;
	int m_current_frame = 0;
	int m_last_enemy_spawn_time = 0;
	bool m_is_running = true;
	bool m_is_paused = false;

	void init(const std::string&);
	void setPaused(bool);

	void systemMovement();
	void systemInput();
	void systemLifespan();
	void systemRender();
	void systemGUI();
	void systemEnemySpawner();
	void systemCollision();

	void spawnPlayer();
	void spawnEnemyLarge();
	void spawnEnemySmall(std::shared_ptr<Entity>);
	void spawnBullet(std::shared_ptr<Entity>, const Vec2f&);
	void spawnSpecialAbility(std::shared_ptr<Entity>);

	std::shared_ptr<Entity> player();

public:
	// constructor
	Game(const std::string&);

	// getter

	// setter

	// overload

	// other
	void run();
};

#endif
