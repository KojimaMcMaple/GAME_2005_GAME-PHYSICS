#include "Player.h"
#include "TextureManager.h"

Player::Player(): m_currentAnimationState(PLAYER_IDLE_RIGHT)
{
	/*
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));
	
	// set frame width
	setWidth(53);

	// set frame height
	setHeight(58);

	getTransform()->position = glm::vec2(50.0f, 400.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);

	m_buildAnimations();
	*/

	TextureManager::Instance()->load("../Assets/textures/player_ship.png", "player_ship");

	const auto size = TextureManager::Instance()->getTextureSize("player_ship");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(400.0f, 400.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(PLAYER);
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	/*
	// draw the player according to animation state
	switch(m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	case PLAYER_IDLE_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
			x, y, 0.25f, 0, 255, true);
		break;
	case PLAYER_RUN_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
			x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}
	*/

	TextureManager::Instance()->draw("player_ship", x, y, 0, 255, true);
	
}

void Player::update()
{
	float move_direction_magnitude = Util::magnitude(move_direction);

	// ACCELERATION
	if (move_direction_magnitude > 0) {
		getRigidBody()->acceleration = Util::normalize(move_direction) * kAccelerationSpeed;
		getRigidBody()->velocity += getRigidBody()->acceleration;
	}
	// DECELERATION
	else if (Util::magnitude(getRigidBody()->velocity) > 0) {
		getRigidBody()->acceleration = Util::normalize(getRigidBody()->velocity) * kDecelerationSpeed;

		// CLAMPING
		if (getRigidBody()->velocity.x < 0) {
			getRigidBody()->velocity.x = std::min(0.0f, getRigidBody()->velocity.x + getRigidBody()->acceleration.x);
		}
		else if (getRigidBody()->velocity.x > 0) {
			getRigidBody()->velocity.x = std::max(0.0f, getRigidBody()->velocity.x + getRigidBody()->acceleration.x);
		}
		if (getRigidBody()->velocity.y < 0) {
			getRigidBody()->velocity.y = std::min(0.0f, getRigidBody()->velocity.y + getRigidBody()->acceleration.y);
		}
		else if (getRigidBody()->velocity.y > 0) {
			getRigidBody()->velocity.y = std::max(0.0f, getRigidBody()->velocity.y + getRigidBody()->acceleration.y);
		}
	}

	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * Globals::sDeltaTime;
	pos.y += getRigidBody()->velocity.y * Globals::sDeltaTime;

	getTransform()->position = pos;


}

void Player::clean()
{
}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-0"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-1"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-2"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-3"));

	setAnimation(idleAnimation);

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-0"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-1"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-2"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-3"));

	setAnimation(runAnimation);
}


void Player::moveLeft() {
	move_direction.x = -1;
}

void Player::moveRight() {
	move_direction.x = 1;
}

void Player::moveUp() {
	move_direction.y = -1;
}

void Player::moveDown() {
	move_direction.y = 1;
}

void Player::StopMovingX() {
	move_direction.x = 0;
}
void Player::StopMovingY() {
	move_direction.y = 0;
}
