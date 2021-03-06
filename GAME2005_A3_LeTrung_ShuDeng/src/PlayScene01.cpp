#include "PlayScene01.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene01::PlayScene01()
{
	PlayScene01::start();
}

PlayScene01::~PlayScene01()
= default;

void PlayScene01::draw()
{
	drawDisplayList();
	BulletPool::Instance()->Draw();

	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}	
	
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);

	SDL_RenderDrawLines(Renderer::Instance()->getRenderer(), m_points, 4);
}

void PlayScene01::update()
{
	updateDisplayList();

	BulletPool::Instance()->CheckBulletCollision(m_pPlayer);
	BulletPool::Instance()->Update();

	no_active_bullet_label->setText("Active Bullets = " + std::to_string(BulletPool::Instance()->GetSizeActiveBulletList()));
	no_inactive_bullet_label->setText("Inactive Bullets = " + std::to_string(BulletPool::Instance()->GetSizeInactiveBulletList()));
}

void PlayScene01::clean()
{
	removeAllChildren();

	BulletPool::Instance()->Clean();
}

void PlayScene01::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				m_playerFacingRight = true;
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				m_playerFacingRight = false;
			}
			else
			{
				if (m_playerFacingRight)
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				}
				else
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				}
			}
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		/*if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_playerFacingRight = false;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			m_playerFacingRight = true;
		}
		else
		{
			if (m_playerFacingRight)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			else
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}
		}*/

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
	}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void PlayScene01::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	// BKG TEXTURE
	bkg_texture = new Background();
	addChild(bkg_texture);

	//// Plane Sprite
	//m_pPlaneSprite = new Plane();
	//addChild(m_pPlaneSprite);

	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_playerFacingRight = true;
	
	// Bullet Pool
	BulletPool::Instance()->Populate();

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(100.0f, 450.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(700.0f, 450.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pNextButton->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pNextButton->setAlpha(255);
	});

	addChild(m_pNextButton);

	// LABELS
	const SDL_Color color = { 255, 255, 255, 255 };
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas", 20, color);
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 550.0f);
	addChild(m_pInstructionsLabel);

	no_active_bullet_label = new Label("Active Bullets = ", "Consolas", 20, color);
	no_active_bullet_label->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.75f, 50.0f);
	addChild(no_active_bullet_label);

	no_inactive_bullet_label = new Label("Inactive Bullets = ", "Consolas", 20, color);
	no_inactive_bullet_label->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.75f, 75.0f);
	addChild(no_inactive_bullet_label);


	// SOUNDS
	/*SoundManager::Instance().load("../Assets/audio/laser_hit.wav", "laser_hit", SOUND_SFX);*/
}

void PlayScene01::StartSimulation() 
{
	//m_pProjectile->getRigidBody()->acceleration.x = 9.8f * glm::sin(ramp_theta) * glm::cos(ramp_theta);
	//m_pProjectile->getRigidBody()->acceleration.y = 9.8f * glm::sin(ramp_theta) * glm::sin(ramp_theta);
}

void PlayScene01::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Simulation Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	//static float ramp_height_slider[1] = { ramp_height };
	//if (ImGui::SliderFloat("Ramp Height", ramp_height_slider, 0.0f, 500.0f)) {
	//	ramp_height = ramp_height_slider[0];
	//	updateRamp();
	//	m_pProjectile->reset(glm::vec2(m_points[0].x, m_points[0].y - ramp_height - m_pProjectile->getHeight()));
	//	m_touchedGround = false;
	//}

	//static float ramp_width_slider[1] = { ramp_width };
	//if (ImGui::SliderFloat("Ramp Width", ramp_width_slider, 0.0f, 500.0f)) {
	//	ramp_width = ramp_width_slider[0];
	//	updateRamp();
	//	m_pProjectile->reset(glm::vec2(m_points[0].x, m_points[0].y - ramp_height - m_pProjectile->getHeight()));
	//	m_touchedGround = false;
	//}

	if(ImGui::Button("Default Bullet Acceleration"))
	{
		BulletPool::Instance()->SetSpawnMode(0);
	}
	if(ImGui::Button("Random Bullet Acceleration"))
	{
		BulletPool::Instance()->SetSpawnMode(1);
	}

	ImGui::Separator();

	/*static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}*/

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
//
//void PlayScene01::updateRamp()
//{
//	m_points[1].x = m_points[0].x + ramp_width;
//	m_points[1].y = m_points[0].y;
//	m_points[2].x = m_points[0].x;
//	m_points[2].y = m_points[0].y - ramp_height;
//	ramp_theta = glm::atan(ramp_height / ramp_width);
//}
