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

	std::string labelText = "";
	if (m_pPlayer->isColliding(m_pEnemy)) {
		labelText = "HIT";
	}
	else {
		labelText = "Distance = " + std::to_string(m_pPlayer->getDistance(m_pEnemy));
	}

	m_pDistanceLabel->setText(labelText);
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
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W)) {
		m_pPlayer->moveUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)) {
		m_pPlayer->moveDown();
	}
	else {
		m_pPlayer->stopMoving();
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

	// Label
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pDistanceLabel = new Label("Distance", "Consolas", 40, blue, glm::vec2(400.0f, 40.0f));
	m_pDistanceLabel->setParent(this);
	addChild(m_pDistanceLabel);
}
