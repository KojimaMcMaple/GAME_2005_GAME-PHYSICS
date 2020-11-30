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


	switch (m_pBall->getShape())
	{
	case Projectile::ProjectileShape::SQUARE:
		if (CollisionManager::circleAABBCheck(m_pBall, m_pPlayerBrick))
		{
			solveBrickCollision();
		}
		else
		{
			solveBoundaryCollision();
		}
		break;
	case Projectile::ProjectileShape::CIRCLE:
		if (CollisionManager::circleAABBCheck(m_pBall, m_pPlayerBrick))
		{
			solveBrickCollision();
		}
		else
		{
			solveBoundaryCollision();
		}
		break;
	case Projectile::ProjectileShape::TRIANGLE:
		if (CollisionManager::circleAABBCheck(m_pBall, m_pPlayerBrick))
		{
			solveBrickCollision();
		}
		else
		{
			solveBoundaryCollision();
		}
		break;
	default:
		break;
	}	

	updateDisplayList();

	velocity_x_label->setText("Velo X = " + std::to_string(m_pBall->getRigidBody()->velocity.x));
	velocity_y_label->setText("Velo Y = " + std::to_string(m_pBall->getRigidBody()->velocity.y));
}

void PlayScene::solveBoundaryCollision()
{
	glm::vec2 topLeft = m_pBall->getTransform()->position;
	if (CollisionManager::lineRectCheck(glm::vec2(0, 0), glm::vec2(800, 0), topLeft, m_pBall->getWidth(), m_pBall->getHeight()))		
	{
		//top boundary		
		m_pBall->getTransform()->position += glm::vec2(((0 - m_pBall->getTransform()->position.y) / m_pBall->getRigidBody()->velocity.y) * m_pBall->getRigidBody()->velocity.x,
			(0 - m_pBall->getTransform()->position.y));  //repositioning along velocity direction
		m_pBall->getRigidBody()->velocity.x *= m_dampingFactorTangent;
		m_pBall->getRigidBody()->velocity.y *= -m_dampingFactorNormal;
	}
	else if (CollisionManager::lineRectCheck(glm::vec2(0, 600), glm::vec2(800, 600), topLeft, m_pBall->getWidth(), m_pBall->getHeight()))
	{
		//bottom boundary
		m_pBall->getTransform()->position += glm::vec2(((600 - m_pBall->getTransform()->position.y - m_pBall->getHeight()) / m_pBall->getRigidBody()->velocity.y) * m_pBall->getRigidBody()->velocity.x,
			(600 - m_pBall->getTransform()->position.y - m_pBall->getHeight()));
		m_pBall->getRigidBody()->velocity.x *= m_dampingFactorTangent;
		m_pBall->getRigidBody()->velocity.y *= -m_dampingFactorNormal;
	}
	else if (CollisionManager::lineRectCheck(glm::vec2(0, 0), glm::vec2(0, 600), topLeft, m_pBall->getWidth(), m_pBall->getHeight()))
	{
		//left boundary
		m_pBall->getTransform()->position += glm::vec2((0 - m_pBall->getTransform()->position.x), 
			((0 - m_pBall->getTransform()->position.x) / m_pBall->getRigidBody()->velocity.x) * m_pBall->getRigidBody()->velocity.y);
		m_pBall->getRigidBody()->velocity.x *= -m_dampingFactorNormal;
		m_pBall->getRigidBody()->velocity.y *= m_dampingFactorTangent;
	}
	else if (CollisionManager::lineRectCheck(glm::vec2(800, 0), glm::vec2(800, 600), topLeft, m_pBall->getWidth(), m_pBall->getHeight()))
	{
		//right boundary
		m_pBall->getTransform()->position += glm::vec2((800 - m_pBall->getTransform()->position.x - m_pBall->getWidth()),
			((800 - m_pBall->getTransform()->position.x - m_pBall->getWidth()) / m_pBall->getRigidBody()->velocity.x) * m_pBall->getRigidBody()->velocity.y);
		m_pBall->getRigidBody()->velocity.x *= -m_dampingFactorNormal;
		m_pBall->getRigidBody()->velocity.y *= m_dampingFactorTangent;
	}
}

void PlayScene::solveBrickCollision()
{
	glm::vec2 ballCenter = m_pBall->getTransform()->position + glm::vec2(m_pBall->getWidth() * 0.5f, m_pBall->getHeight() * 0.5f);
	glm::vec2 brickStartPos = m_pPlayerBrick->getTransform()->position;
	glm::vec2 brickCenter = m_pPlayerBrick->getTransform()->position + glm::vec2(m_pPlayerBrick->getWidth() * 0.5f, m_pPlayerBrick->getHeight() * 0.5f);

	if (ballCenter.y > brickStartPos.y && ballCenter.y < brickStartPos.y + m_pPlayerBrick->getHeight())
	{
		if (ballCenter.x < brickCenter.x)
		{
			m_pBall->getTransform()->position += glm::vec2((brickStartPos.x - m_pBall->getTransform()->position.x - m_pBall->getWidth()),
				((brickStartPos.x - m_pBall->getTransform()->position.x - m_pBall->getWidth()) / m_pBall->getRigidBody()->velocity.x) * m_pBall->getRigidBody()->velocity.y);
		}
		else
		{
			m_pBall->getTransform()->position += glm::vec2((brickStartPos.x + m_pPlayerBrick->getWidth() - m_pBall->getTransform()->position.x),
				((brickStartPos.x + m_pPlayerBrick->getWidth() - m_pBall->getTransform()->position.x) / m_pBall->getRigidBody()->velocity.x) * m_pBall->getRigidBody()->velocity.y);
		}
		solveBrickCollisionX();
	}
	else if (ballCenter.x > brickStartPos.x && ballCenter.x < brickStartPos.x + m_pPlayerBrick->getWidth())
	{
		if (ballCenter.y < brickCenter.y)
		{
			m_pBall->getTransform()->position += glm::vec2(((brickStartPos.y - m_pBall->getTransform()->position.y - m_pBall->getHeight()) / m_pBall->getRigidBody()->velocity.y) * m_pBall->getRigidBody()->velocity.x,
				(brickStartPos.y - m_pBall->getTransform()->position.y - m_pBall->getHeight()));
		}
		else
		{
			m_pBall->getTransform()->position += glm::vec2(((brickStartPos.y + m_pPlayerBrick->getHeight() - m_pBall->getTransform()->position.y) / m_pBall->getRigidBody()->velocity.y) * m_pBall->getRigidBody()->velocity.x,
				(brickStartPos.y + m_pPlayerBrick->getHeight() - m_pBall->getTransform()->position.y));
		}
		solveBrickCollisionY();
	}
	else
	{
		glm::vec2 collisionPoint;
		if (ballCenter.x < brickCenter.x && ballCenter.y < brickCenter.y)
		{
			collisionPoint = brickStartPos;
		}
		else if (ballCenter.x < brickCenter.x && ballCenter.y > brickCenter.y)
		{
			collisionPoint = brickStartPos + glm::vec2(0, m_pPlayerBrick->getHeight());
		}
		else if (ballCenter.x > brickCenter.x && ballCenter.y < brickCenter.y)
		{
			collisionPoint = brickStartPos + glm::vec2(m_pPlayerBrick->getWidth(), 0);
		}
		else if (ballCenter.x > brickCenter.x && ballCenter.y > brickCenter.y)
		{
			collisionPoint = glm::vec2(m_pPlayerBrick->getWidth(), m_pPlayerBrick->getHeight());
		}
		m_pBall->getTransform()->position = collisionPoint + m_pBall->getWidth() * 0.5f * glm::normalize(-m_pBall->getRigidBody()->velocity);
		solveBrickCollisionX();
		solveBrickCollisionY();
	}
}

void PlayScene::solveBrickCollisionY()
{
	if (m_pBall->getRigidBody()->velocity.y * m_pPlayerBrick->getRigidBody()->velocity.y < 0) //collision with different directions
	{
		m_pBall->getRigidBody()->velocity.y = m_pPlayerBrick->getRigidBody()->velocity.y - m_pBall->getRigidBody()->velocity.y;
	}
	else //collision with same direction
	{
		if (abs(m_pPlayerBrick->getRigidBody()->velocity.y) > abs(m_pBall->getRigidBody()->velocity.y)) //brick is faster
		{
			m_pBall->getRigidBody()->velocity.y += m_pPlayerBrick->getRigidBody()->velocity.y;
		}
		else //ball is faster
		{
			m_pBall->getRigidBody()->velocity.y *= -1;
		}
	}
}

void PlayScene::solveBrickCollisionX()
{
	if (m_pBall->getRigidBody()->velocity.x * m_pPlayerBrick->getRigidBody()->velocity.x < 0) //collision with different directions
	{
		m_pBall->getRigidBody()->velocity.x = m_pPlayerBrick->getRigidBody()->velocity.x - m_pBall->getRigidBody()->velocity.x;
	}
	else //collision with same direction
	{
		if (abs(m_pPlayerBrick->getRigidBody()->velocity.x) > abs(m_pBall->getRigidBody()->velocity.x)) //brick is faster
		{
			m_pBall->getRigidBody()->velocity.x += m_pPlayerBrick->getRigidBody()->velocity.x;
		}
		else //ball is faster
		{
			m_pBall->getRigidBody()->velocity.x *= -1;
		}
	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE_01);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

	m_pPlayerBrick->getTransform()->position = EventManager::Instance().getMousePosition() - glm::vec2(m_pPlayerBrick->getWidth() * 0.5f, m_pPlayerBrick->getHeight() * 0.5f);
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	// BKG TEXTURE
	bkg_texture = new Background();
	addChild(bkg_texture);	

	m_pPlayerBrick = new Brick();
	addChild(m_pPlayerBrick);

	m_pBall = new Projectile(glm::vec2(400, 300), 200);
	addChild(m_pBall);

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(100.0f, 550.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE_01);
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


	velocity_x_label = new Label("Velo X = ", "Consolas", 20, color);
	velocity_x_label->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.75f, 75.0f);
	addChild(velocity_x_label);

	velocity_y_label = new Label("Velo Y = ", "Consolas", 20, color);
	velocity_y_label->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.75f, 100.0f);
	addChild(velocity_y_label);

	/*acceleration_x_label = new Label("Acce X = ", "Consolas", 20, color);
	acceleration_x_label->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.75f, 125.0f);
	addChild(acceleration_x_label);

	acceleration_y_label = new Label("Acce Y = ", "Consolas", 20, color);
	acceleration_y_label->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.75f, 150.0f);
	addChild(acceleration_y_label);*/
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Simulation Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Circle"))
	{
		m_pBall->changeShape(Projectile::ProjectileShape::CIRCLE);
	}
	ImGui::SameLine();
	if (ImGui::Button("Square"))
	{
		m_pBall->changeShape(Projectile::ProjectileShape::SQUARE);
	}
	ImGui::SameLine();
	if (ImGui::Button("Triangle"))
	{
		m_pBall->changeShape(Projectile::ProjectileShape::TRIANGLE);
	}

	//ImGui::Separator();

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


