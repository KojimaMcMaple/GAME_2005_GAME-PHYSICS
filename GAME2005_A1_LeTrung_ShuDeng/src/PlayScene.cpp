#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();

	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}	
	
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	angle_label->setText("Angle = " + std::to_string(m_pProjectile->GetThrowAngle()));
	velocity_x_label->setText("Velo X = " + std::to_string(m_pProjectile->getRigidBody()->velocity.x));
	velocity_y_label->setText("Velo Y = " + std::to_string(m_pProjectile->getRigidBody()->velocity.y));

	if (CollisionManager::AABBCheck(m_pProjectile, m_pTarget))
	{
		m_pProjectile->Stop();
	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
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
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
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
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
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
	
	// Target Sprite
	m_pTarget = new Target(glm::vec2(target_range + m_pPlayer->getTransform()->position.x, m_pPlayer->getTransform()->position.y));
	addChild(m_pTarget);

	// Projectile Sprite
	m_pProjectile = new Projectile(m_pPlayer->getTransform()->position);
	addChild(m_pProjectile);

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(100.0f, 550.0f);
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
	m_pNextButton->getTransform()->position = glm::vec2(700.0f, 550.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		TheGame::Instance()->changeSceneState(END_SCENE);
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
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);
	addChild(m_pInstructionsLabel);

	angle_label = new Label("Angle = ", "Consolas", 20, color);
	angle_label->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 50.0f);
	addChild(angle_label);

	velocity_x_label = new Label("Velo X = ", "Consolas", 20, color);
	velocity_x_label->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 75.0f);
	addChild(velocity_x_label);

	velocity_y_label = new Label("Velo Y = ", "Consolas", 20, color);
	velocity_y_label->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 100.0f);
	addChild(velocity_y_label);
}

void PlayScene::UpdateTargetRange(float new_range)
{
	target_range = new_range;
	m_pTarget->getTransform()->position.x = new_range;
}

void PlayScene::UpdateThrowVelo(float new_velo)
{
	throw_velocity = new_velo;
}

void PlayScene::StartSimulation() {
	/*m_pProjectile->SetInitialVelocity(95.0f);
	m_pProjectile->SetThrowAngle(15.89f);*/
	m_pProjectile->getTransform()->position = m_pPlayer->getTransform()->position;
	m_pProjectile->StartThrow(throw_velocity, m_pTarget->getTransform()->position.x);
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Simulation Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	static float target_range_slider[1] = { target_range };
	if (ImGui::SliderFloat("Target Range", target_range_slider, 50.0f, 800.0f)) {
		UpdateTargetRange(target_range_slider[0]);
	}

	static float throw_velocity_slider[1] = { throw_velocity };
	if (ImGui::SliderFloat("Throw Velo", throw_velocity_slider, 0.0f, 100.0f)) {
		UpdateThrowVelo(throw_velocity_slider[0]);
	}

	if(ImGui::Button("Start Simulation"))
	{
		std::cout << "Start Simulation Pressed" << std::endl;
		StartSimulation();
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
