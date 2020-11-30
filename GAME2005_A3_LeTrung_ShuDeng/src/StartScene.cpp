#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE_01);
	}
	else if(EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("GAME2005_A3", "Consolas", 80, blue, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pAuthorLabel1 = new Label("by Trung Le (Kyle) - 101264698", "Consolas", 20, blue, glm::vec2(400.0f, 90.0f));
	m_pAuthorLabel1->setParent(this);
	addChild(m_pAuthorLabel1);
	m_pAuthorLabel2 = new Label("and Shu Deng - 101260645", "Consolas", 20, blue, glm::vec2(400.0f, 130.0f));
	m_pAuthorLabel2->setParent(this);
	addChild(m_pAuthorLabel2);


	m_pInstructionsLabel = new Label("Press 1 for Part 1", "Consolas", 40, blue, glm::vec2(400.0f, 180.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);
	m_pInstructionsLabel2 = new Label("Press 2 for Part 2", "Consolas", 40, blue, glm::vec2(400.0f, 240.0f));
	m_pInstructionsLabel2->setParent(this);
	addChild(m_pInstructionsLabel2);


	m_pShip = new Ship();
	m_pShip->getTransform()->position = glm::vec2(400.0f, 300.0f); 
	addChild(m_pShip); 

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 500.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE_01);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	
}

