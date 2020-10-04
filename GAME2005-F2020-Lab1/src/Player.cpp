#include "Player.h"
#include "TextureManager.h"

Player::Player()
{
	TextureManager::Instance()->load("../Assets/textures/circle.png", "circle");
	
	auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
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

	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void Player::update()
{
	const float deltaTime = 1.0f / 60.f;

	float move_direction_magnitude = Util::magnitude(move_direction);
	// ACCELERATION
	if (move_direction_magnitude > 0) {
		getRigidBody()->acceleration = Util::normalize(move_direction) * ACCELERATION;
		getRigidBody()->velocity += getRigidBody()->acceleration;
	}
	// DECELERATION
	else if (Util::magnitude(getRigidBody()->velocity) > 0) {
		getRigidBody()->acceleration = Util::normalize(getRigidBody()->velocity) * DECELERATION;

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
	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;

	getTransform()->position = pos;
}

void Player::clean()
{

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

float Player::GetDistance(GameObject* pGameObject) {
	int player_xpos = getTransform()->position.x;
	int player_ypos = getTransform()->position.y;
	int obj_xpos = pGameObject->getTransform()->position.x;
	int obj_ypos = pGameObject->getTransform()->position.y;

	return sqrt(pow((player_xpos- obj_xpos),2) + pow((player_ypos - obj_ypos), 2));
}

//float Player::GetMagnitude()
//{
//	return sqrt(pow(getRigidBody()->velocity.x, 2) + pow(getRigidBody()->velocity.y, 2));
//}
