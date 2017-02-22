#include "Player.h"

void Player::draw(RenderTarget & target, RenderStates state) const
{
	if (this->state == ON_GROUND)
	{
		target.draw(player);
	}
	else
	{
		target.draw(playerOnAir);
	}
	target.draw(*particles);
	if (isSaying)
	{
		target.draw(bubbleMiddle);
		target.draw(bubbleLeft);
		target.draw(bubbleRight);
		target.draw(bubbleArrow);
		target.draw(sayText);
	}
	if (canPunchDown)
	{
		target.draw(punchDownInfo);
	}
}

void Player::move()
{
	if (Keyboard::isKeyPressed((Keyboard::Key)SettingsManager::jumpKey) || (SettingsManager::isJoystickConnected() && Joystick::isButtonPressed(SettingsManager::joystickId, 0)))
	{
		jump();
	}
	if ((Keyboard::isKeyPressed((Keyboard::Key)SettingsManager::turnLeftKey) || (SettingsManager::isJoystickConnected() && Joystick::hasAxis(SettingsManager::joystickId, Joystick::X) && Joystick::getAxisPosition(SettingsManager::joystickId, Joystick::X) < -50)) && player.getGlobalBounds().left > 0)
	{
		horizontalSpeed = (Keyboard::isKeyPressed((Keyboard::Key)SettingsManager::runKey)) ? -8 : -5;
	}
	else if ((Keyboard::isKeyPressed((Keyboard::Key)SettingsManager::turnRightKey) || (SettingsManager::isJoystickConnected() && Joystick::hasAxis(SettingsManager::joystickId, Joystick::X) && Joystick::getAxisPosition(SettingsManager::joystickId, Joystick::X) > 50)) && player.getGlobalBounds().left + player.getGlobalBounds().width < 1680)
	{
		horizontalSpeed = (Keyboard::isKeyPressed((Keyboard::Key)SettingsManager::runKey)) ? 8 : 5;
	}

	if (Keyboard::isKeyPressed((Keyboard::Key)SettingsManager::downKey) || (SettingsManager::isJoystickConnected() && Joystick::isButtonPressed(SettingsManager::joystickId, 0)))
	{
		if (state == ON_AIR && canPunchDown)
		{
			speed = 30;
			state = GOING_DOWN_FAST;
		}
	}
	if (SettingsManager::godMode)
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			teleport(Vector2i(getGlobalBounds().left, getGlobalBounds().top - 7));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			teleport(Vector2i(getGlobalBounds().left, getGlobalBounds().top + 7));
		}
	}
}

Player::Player(THEME theme)
{
	speed = 0;
	horizontalSpeed = 0;
	player.create("res/textures/player.png", 6, Vector2i(42, 71), 60);
	player.move(608, 0);
	playerOnAirTex.loadFromFile("res/textures/player.png", IntRect(336, 0, 42, 71));
	playerOnAir.setTexture(playerOnAirTex);

	chunk = nullptr;
	//particles
	particles = new ParticlesEmitter(ParticlesEmitter::LEFT);
	particles->setPower(2);
	particles->setParticleLifeTime(0.3);
	setTheme(theme);
	//bubble
	bubbleTex.loadFromFile("res/images/bubble.png");
	bubbleLeft.setTexture(bubbleTex);
	bubbleRight.setTexture(bubbleTex);
	bubbleArrow.setTexture(bubbleTex);
	bubbleMiddle.setTexture(bubbleTex);
	bubbleLeft.setTextureRect(IntRect(0, 0, 8, 39));
	bubbleRight.setTextureRect(IntRect(8, 0, 8, 39));
	bubbleArrow.setTextureRect(IntRect(0, 40, 14, 7));
	bubbleMiddle.setTextureRect(IntRect(7, 0, 1, 40));
	//end bubble
	//punch info
	punchDownInfoTexture.loadFromFile("res/images/punchDown.png");
	punchDownInfo.setTexture(punchDownInfoTexture);
	//end punch

	sayFont.loadFromFile("res/fonts/arial.ttf");
	isSaying = false;
	sayText.setFont(sayFont);
	sayText.setColor(Color::Black);
	sayText.setCharacterSize(19);

	jumpBuf.loadFromFile("res/sounds/jump.wav");
	jumpSnd.setBuffer(jumpBuf);
	jumpSnd.setVolume(SettingsManager::loadSoundsVolume());

	impactFallBuf.loadFromFile("res/sounds/impactfall.wav");
	impactFall.setBuffer(impactFallBuf);
	impactFall.setVolume(SettingsManager::loadSoundsVolume());
}

void Player::setTheme(THEME theme)
{
	this->theme = theme;
	particles->resetColors();
	switch(theme)
	{
	case COUNTRYSIDE:
		particles->addColor(Color(0, 153, 0));
		particles->addColor(Color(139, 69, 19));
		break;
	case CAVE:
		particles->addColor(Color(128, 128, 128));
		particles->addColor(Color(70, 70, 70));
		break;
	}
}

void Player::jump()
{
	if (state == ON_GROUND && !SettingsManager::godMode)
	{
		jumpSnd.play();
		speed = -15;
		state = ON_AIR;
	}
}

void Player::update(Chunk* chunk)
{
	this->chunk = chunk;
	std::vector<Block*> blocks = this->chunk->getBlocks();
	isSaying = false;
	
	if(SettingsManager::godMode==false)
		speed += 0.5;

	if (player.getGlobalBounds().left+12 < 0 || player.getGlobalBounds().left + 12 > 1680)
	{
		horizontalSpeed = 0;
	}
	if (horizontalSpeed > 0)
	{
		horizontalSpeed -= 0.5;
	}
	else if (horizontalSpeed < 0)
	{
		horizontalSpeed += 0.5;
	}
	state = ON_AIR;
	if (speed >= 30)
	{
		state = GOING_DOWN_FAST;
	}
	//speeding up animation while running
	if (Keyboard::isKeyPressed(Keyboard::LShift))
	{
		player.setFrameTime(50);
	}
	else
	{
		player.setFrameTime(60);
	}
	//-
	//searching for destroyable blocks below player
	canPunchDown = false;
	int x = player.getGlobalBounds().left;
	int y = player.getGlobalBounds().top;
	for (int i = 0; i < 15; i++)
	{
		Block *blockToMeasurement = chunk->getBlockAt(x, y);
		if (blockToMeasurement == nullptr)
		{
			break;
		}
		else
		{
			if (blockToMeasurement->isDestroyable())
			{
				canPunchDown = true;
				break;
			}
		}
		y += 70;
	}
	//-

	for (size_t i = 0; i < blocks.size(); i++)
	{
		if (player.getGlobalBounds().intersects(blocks[i]->getDeathSquare()) && (blocks[i]->isCollidable() || blocks[i]->isSpike()))
		{
			if (SettingsManager::godMode == false && state != GOING_DOWN_FAST)
			{
				kill();
			}
		}
		if (player.getGlobalBounds().intersects(blocks[i]->getGlobalBounds()) && blocks[i]->isCollidable() && state != IS_DEAD && speed >= 0)
		{
			if (state == GOING_DOWN_FAST)
			{
				impactFall.play();
				if (blocks[i]->isDestroyable())
				{
					blocks[i]->destroy();
					continue;
				}
			}
			speed = 0;
			state = ON_GROUND;
			if(!SettingsManager::godMode)
				player.move(0, ((player.getGlobalBounds().top + 60) - blocks[i]->getGlobalBounds().top)*-1);
		}
		if (player.getGlobalBounds().left>blocks[i]->getGlobalBounds().left && blocks[i]->isBlockWinning())
		{
			state = IS_DONE;
			break;
		}
	}

	if (state == ON_AIR)
	{
		playerOnAir.setPosition(player.getGlobalBounds().left, player.getGlobalBounds().top);
	}
	
	Block *particleBlock = chunk->getBlockAt(player.getGlobalBounds().left, player.getGlobalBounds().top + 80);
	if (particleBlock != nullptr && particleBlock->getId() == 0 && particleBlock->getSubId() < 3)
	{
		particles->addNewParticles();
	}
	particles->setPosition(player.getGlobalBounds().left + 20, player.getGlobalBounds().top + 60);
	particles->update();
	punchDownInfo.setPosition(player.getGlobalBounds().left-25 , player.getGlobalBounds().top - 160);

	move();
	player.move(horizontalSpeed, speed);
	playerOnAir.move(horizontalSpeed, speed);
	player.update();
}

Player::STATE Player::getState()
{
	return state;
}

void Player::kill()
{
	state = IS_DEAD;
}

void Player::say(std::string text)
{
	isSaying = true;
	sayText.setString(text);
	bubbleMiddle.scale((sayText.getGlobalBounds().width + 25) / bubbleMiddle.getGlobalBounds().width, 1);
	bubbleMiddle.setPosition(player.getGlobalBounds().left + 21 - bubbleMiddle.getGlobalBounds().width / 2, player.getGlobalBounds().top - 47);
	bubbleLeft.setPosition(bubbleMiddle.getPosition().x - 7, bubbleMiddle.getPosition().y);
	bubbleRight.setPosition(bubbleMiddle.getPosition().x + bubbleMiddle.getGlobalBounds().width, bubbleMiddle.getPosition().y);
	bubbleArrow.setPosition(player.getGlobalBounds().left + 21 - 7, bubbleMiddle.getPosition().y + 38);
	sayText.setPosition(bubbleMiddle.getPosition().x + bubbleMiddle.getGlobalBounds().width / 2 - sayText.getGlobalBounds().width / 2, player.getGlobalBounds().top - 40);
}

FloatRect Player::getGlobalBounds()
{
	return player.getGlobalBounds();
}

void Player::teleport(Vector2i mousePos)
{
	player.move(mousePos.x - player.getGlobalBounds().left, mousePos.y - player.getGlobalBounds().top);
	playerOnAir.move(mousePos.x - player.getGlobalBounds().left, mousePos.y - player.getGlobalBounds().top);
}

Player::~Player()
{
}
