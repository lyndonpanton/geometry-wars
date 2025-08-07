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
    // TODO: read in configuration file, use the premade PlayerConfiguration,
    // EnemyConfiguration, and BulletConfiguration variables

    // TODO: modify this to use parameters read from the configuration file
    m_render_window.create(sf::VideoMode(1280, 720), "Geometry Wars");
    m_render_window.setFramerateLimit(60);

    ImGui::SFML::Init(m_render_window);

    // scaling for appearance
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;

    spawnPlayer();
}

// since the player will be referred to a lot, we will need a method to retrieve
// where the player variable is stored
std::shared_ptr<Entity> Game::player()
{
    auto& players = m_entities.getEntities("player");

    // assert(players.size() == 1);

    return players.front();
}

void Game::run()
{
    // TODO: add pause functionality
    //     - some systems should function whilst paused (i.e., rendering)
    //     - some systems should not function whilst paused (e.g., movement,
    //     input)
    //     - current frame should not increment whilst paused

    while (m_is_running)
    {
        m_entities.update();

        ImGui::SFML::Update(m_render_window, m_delta_clock.restart());

        systemEnemySpawner();
        systemMovement();
        systemCollision();
        systemInput();
        systemGUI();
        systemRender();

        m_current_frame++;
    }
}

void Game::setPaused(bool paused)
{
    // TODO: pause or unpause the game
    //     - lifespan should not deplete whilst the game is paused
    //     - entities may still rotate whilst the game is paused if you would
    //     like
}

void Game::spawnPlayer()
{
    // TODO:
    //     - Player should be spawned at respawned in the middle of the screen
    //     - Modify this so that it uses values read in from the configuration
    //     file

    // create the player via the EntityManager, returns a
    // std::shared_ptr<Entity>
    auto entity = m_entities.addEntity("player");

    // Give the entity a transform and spawn at the given location, with the
    // given velocity, and the given angle
    entity->add<CTransform>(Vec2f(200.0f, 200.0f), Vec2f(1.0f, 1.0f), 0.0f);

    // radius = 32, 8 sides, dark grey fill colour, red outline, 4 px outline
    entity->add<CShape>
        (32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

    // allow the player to use input
    entity->add<CInput>();
}

void Game::spawnEnemyLarge()
{
    // TODO:
    //     - make sure enemy is spawned properly with the m_enemy_configuration
    //     variables
    //     - the enemy must be spawn at a random position
    //     - the enemy must be spawn completely within the bounds of the window

    // record when most recent enemy was spawned
    m_last_enemy_spawn_time = m_current_frame;
}

void Game::spawnEnemySmall(std::shared_ptr<Entity> entity)
{
    // TODO:
    //     - spawn small enemies at the location of the parameter entity
    //     - spawn a number of small enemies each to the number of vertices
    //     the parameter entity hs
    //     - fill colour of small enemies should be the same as the parameter
    //     entity
    //     - size of small enemies should be half the size of the parameter
    //     entity
    //     - score of small enemies should be double the score of the parameter
    //     entity
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2f& target)
{
    // TODO:
    //     - spawn a bullet at a given entity to a target location
    //     - bullet speed is given as a scalar speed
    //     - use formula in notes to set the velocity
}

void Game::spawnSpecialAbility(std::shared_ptr<Entity> entity)
{
    // TODO: implement your custom special ability
}

void Game::systemMovement()
{
    // TODO:
    //     - implement all entity movement
    //     - The CInput component of m_player should be read to determined
    //     whether the player is moving

    // sample movement speed update
    // a reference is needed because otherwise a copy would be made which would
    // not modify the original value
    auto& transform = player()->get<CTransform>();
    // once the vec2 class has been fully implemented, you should not need to
    // individual increment each component of the vector
    // transform.position += transform.velocity;
    transform.position.x += transform.velocity.x;
    transform.position.y += transform.velocity.y;
}

void Game::systemLifespan()
{
    // TODO: implement all lifespan functionality
    // for all entities
    //     if entity has no lifespan component, skip it
    //     if the lifespan component of entity has lifespan_remaining greater
    //     than 0, subtract 1 from lifespan_remaining
    //     if entity has a lifespan component and is alive
    //         modify its alpha channel appropriately
    //     if entity has a lifespan component and lifespan_remaining less than 0
    //         destroy entity

}

void Game::systemCollision()
{
    // TODO:
    //     - implement all proper collisions between entities
    //     - use collision radius, not shape radius

    for (auto bullet : m_entities.getEntities("bullet"))
    {
        for (auto enemy : m_entities.getEntities("enemy-large"))
        {
            // use the transforms and collision radii to detect whether a
            // collision occurs
        }

        for (auto enemy : m_entities.getEntities("enemy-small"))
        {
            // use the transforms and collision radii to detect whether a
            // collision occurs
        }
    }

    for (auto enemy : m_entities.getEntities("enemy-large"))
    {
        // check for collision against player
    }

    for (auto enemy : m_entities.getEntities("enemy-small"))
    {
        // check for collision against player
    }
}

void Game::systemEnemySpawner()
{
    // TODO: implement the enemy spawner
    //      - check when the last time an enemy was spawned
}

void Game::systemGUI()
{
    // TODO: create the imgui interface
    ImGui::Begin("Geometry Wars");

    ImGui::Text("Content...");

    ImGui::End();
}

void Game::systemRender()
{
    // TODO:
    //     - modify code below to draw all entities (not just the player)
    //     - loop over all entities to achieve this
    m_render_window.clear();

    // update the player's shape's position
    player()->get<CShape>()
        .circle.setPosition(player()->get<CTransform>().position);

    // update the player's transform's rotation
    player()->get<CTransform>().angle += 1.0f;
    // update the player's shape's rotation
    player()->get<CShape>()
        .circle.setRotation(player()->get<CTransform>().angle);

    // draw the player's sf::CircleShape
    m_render_window.draw(player()->get<CShape>().circle);

    // draw the ui last
    ImGui::SFML::Render(m_render_window);

    m_render_window.display();
}

void Game::systemInput()
{
    // TODO: handle user input
    //     - you should only be setting the player's input component variables
    //     - you should not implement player's movement logic here
    //     - movement system will be reading variables modified in this function

    sf::Event event;

    while (m_render_window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        // instead of immediately closing the window, the running state of the
        // game is modified, which will be read later
        if (event.type == sf::Event::Closed) m_is_running = false;

        if (event.type == sf::Event::KeyPressed)
        {
            // Note that you will lose marks if you update the player's position
            // (i.e., the CTransform component) in this method which is intended
            // for input handling. The movement system will handle updating the
            // player's position (i.e., CTransform component) based on the
            // the value(s) in the player's CInput component
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                // update the player's CInput component
                break;
            case sf::Keyboard::A:
                // update the player's CInput component
                break;
            case sf::Keyboard::S:
                // update the player's CInput component
                break;
            case sf::Keyboard::D:
                // update the player's CInput component
                break;
            case sf::Keyboard::P:
                // call method for modifying pause state
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
                // update the player's CInput component
                break;
            case sf::Keyboard::A:
                // update the player's CInput component
                break;
            case sf::Keyboard::S:
                // update the player's CInput component
                break;
            case sf::Keyboard::D:
                // update the player's CInput component
                break;
            case sf::Keyboard::P:
                // call method for modifying pause state
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            // ignore mouse events if an imgui element is what is being clicked
            if (ImGui::GetIO().WantCaptureMouse) continue;

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // use mouse position (along with player position) to determine
                // trajectory of the bulllet
                std::cout << "(" << event.mouseButton.x << ", "
                    << event.mouseButton.y << ")" << std::endl;
                // TODO: spawn bullet
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {
                // use mouse position (along with player position) to determine
                // trajectory of the ability (if necessary)
                std::cout << "(" << event.mouseButton.x << ", "
                    << event.mouseButton.y << ")" << std::endl;
                // TODO: use special ability
            }
        }
    }
}