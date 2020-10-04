#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
}

void PlayScene::update()
{
	updateDisplayList();

	float distance_player_enemy = m_pPlayer->GetDistance(m_pEnemy);
	if (distance_player_enemy > (m_pPlayer->getWidth() / 2 + m_pEnemy->getWidth() / 2)) {
		m_pDistanceLabel->setText("Distance = " + std::to_string(distance_player_enemy));
	}
	else {
		m_pDistanceLabel->setText("HIT!!!");
	}
	
	float player_magnitude = Util::magnitude(m_pPlayer->getRigidBody()->velocity);
	m_pMagnitudeLabel->setText("Velo Magnitude = " + std::to_string(player_magnitude));
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pPlayer->moveLeft();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pPlayer->moveRight();
	}
	else {
		m_pPlayer->StopMovingX();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		m_pPlayer->moveUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		m_pPlayer->moveDown();
	}
	else {
		m_pPlayer->StopMovingY();
	}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	
	// Enemy Sprite
	m_pEnemy = new Enemy();
	addChild(m_pEnemy);

	// Labels
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pDistanceLabel = new Label("Distance", "Consolas", 40, blue, glm::vec2(400.0f, 40.0f));
	m_pDistanceLabel->setParent(this);
	addChild(m_pDistanceLabel);
	m_pMagnitudeLabel = new Label("VeloMag", "Consolas", 40, blue, glm::vec2(400.0f, 80.0f));
	m_pMagnitudeLabel->setParent(this);
	addChild(m_pMagnitudeLabel);
}
