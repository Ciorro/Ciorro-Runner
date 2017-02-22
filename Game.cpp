#include "Game.h"

Game::Game()
{
}

void Game::init(RenderWindow * win, Font * font, std::string mapName, int lvlNumber, bool isEndless)
{
	this->isEndless = isEndless;
	cursorTex.loadFromFile("res/images/cursor.png");
	cursor.setTexture(cursorTex);

	mapPath = mapName;
	this->font = font;
	this->win = win;
	this->lvlNumber = lvlNumber;

	map = new Map(isEndless);
	if ((isEndless)?!map->load("res/maps/presets/setup.crs"):!map->load(mapName))
	{
		MessageBoxW(NULL, L"An error has occurred.", L"Error", MB_ICONERROR);
		exit(0);
	}
	
	this->win->setVerticalSyncEnabled(true);
	slowTex.loadFromFile("res/images/vignetting.png");
	slowmotion.setTexture(slowTex);
	slowmotion.setColor(Color::Transparent);
	//loading slowmos' info background
	numberOfSlowmoTex.loadFromFile("res/images/numberofslowmo.png");
	numberOfSlowmoBg.setTexture(numberOfSlowmoTex);
	numberOfSlowmoBg.setPosition(138, 5);

	numberOfCoinsTex.loadFromFile("res/images/numberofcoins.png");
	numberOfCoinsBg.setTexture(numberOfCoinsTex);
	numberOfCoinsBg.setPosition(5, 0);

	slowmoInfo.setFont(*font);
	slowmoInfo.setCharacterSize(25);
	slowmoInfo.setPosition(90+132, 17);
	slowmoInfo.setColor(Color::Black);

	coinsInfo.setFont(*font);
	coinsInfo.setCharacterSize(25);
	coinsInfo.setColor(Color::Black);

	lenFromStart.setFont(*font);
	lenFromStart.setColor(Color::Blue);
	lenFromStart.setCharacterSize(25);
	lenFromStart.setPosition(0, 40);

	pause = false;
	teleportMode = false;
	view.setCenter(1680 / 2, 1050 / 2);
	view.setSize(1680, 1050);
	win->setView(view);
	
	gameState = Continues;
	fpsCounter.setFont(*font);
	fpsCounter.setColor(Color::Blue);

	teleportTimeProgress.create(0, 1040, 1680, 20, 3000);
	teleportTimeProgress.setFillColor(Color(247, 50, 32));
	teleportTimeProgress.setBorderColor(Color::Transparent);
	teleportTimeProgress.setAnimation(false);
	
	gameResult = false;

	SettingsManager::loadKeys();
	//loading assets TODO progressbar
}

void Game::handleEvents()
{
	while (win->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			delete map;
			win->close();
			exit(0);
		}
		if (event.type == Event::KeyReleased && event.key.code == Keyboard::G && SettingsManager::godMode==false)
		{
			SettingsManager::godMode = true;
		}
		else if (event.type == Event::KeyReleased && event.key.code == Keyboard::G && SettingsManager::godMode == true)
		{
			SettingsManager::godMode = false;
		}
		if (((event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) || (SettingsManager::isJoystickConnected() && Joystick::isButtonPressed(SettingsManager::joystickId,7))) && pause==false)
		{
			win->setView(win->getDefaultView());
			pauseMenu = new Pause(win, font);
			map->music.pause();
			//win->setMouseCursorVisible(true);
			pause = true;
		//	printf("pause");
		}
		else if(((event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) || (SettingsManager::isJoystickConnected() && Joystick::isButtonPressed(SettingsManager::joystickId, 1))) && pause==true)
		{
			win->setView(view);
			map->music.play();
			delete pauseMenu;
			//win->setMouseCursorVisible(false);
			pause = false;
		}
		if (pause)
		{
			cursor.setPosition(Mouse::getPosition(*win).x, Mouse::getPosition(*win).y);
			if (pauseMenu->handle(&event))
			{
				gameState = Aborted;
			}
		}
		if (((event.type == Event::KeyReleased && event.key.code == (Keyboard::Key)SettingsManager::slowmotionKey) || 
			(Joystick::isButtonPressed(SettingsManager::joystickId,2))) && 
			teleportMode == false && map->teleportsQuantity > 0)
		{
			teleportMode = true;
			map->teleportsQuantity--;
			teleportTime.restart();
		}
		else if (teleportMode == true)
		{
			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Num1:
					map->player.teleport(Vector2i(420, 262));
					teleportMode = false;
					break;
				case Keyboard::Num2:
					map->player.teleport(Vector2i(420*3, 262));
					teleportMode = false;
					break;
				case Keyboard::Num3:
					map->player.teleport(Vector2i(420, 262*3));
					teleportMode = false;
				case Keyboard::Num4:
					map->player.teleport(Vector2i(420*3, 262*3));
					teleportMode = false;
					break;
				}
			}
			if (SettingsManager::isJoystickConnected())
			{
				if (Joystick::isButtonPressed(SettingsManager::joystickId, 4))
				{
					map->player.teleport(Vector2i(420, 262));
					teleportMode = false;
				}
				else if (Joystick::isButtonPressed(SettingsManager::joystickId, 5))
				{
					map->player.teleport(Vector2i(420 * 3, 262));
					teleportMode = false;
				}
				else if (Joystick::getAxisPosition(SettingsManager::joystickId,Joystick::Axis::Z)>50)
				{
					map->player.teleport(Vector2i(420, 262 * 3));
					teleportMode = false;
				}
				else if (Joystick::getAxisPosition(SettingsManager::joystickId, Joystick::Axis::Z)<-50)
				{
					map->player.teleport(Vector2i(420 * 3, 262 * 3));
					teleportMode = false;
				}
			}
		}
		if (SettingsManager::godMode)
		{
			//zoom in godmode
			if (event.type == Event::MouseWheelMoved)
			{
				if (event.mouseWheel.delta > 0)
				{
					view.zoom(0.98);
				}
				else if (event.mouseWheel.delta < 0)
				{
					view.zoom(1.02);
				}
			}
			//some features in godmode goes here
			win->setView(view);
		}
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::F2)
		{
			makeScreenshot();
		}

	}
}

void Game::makeScreenshot()
{
	Image window = win->capture();
	int filename = 1;
	bool opened = false;
	do
	{
		std::ifstream screenNameFinder("res/screenshots/" + std::to_string(filename) + ".png");
		if (screenNameFinder.is_open())
		{
			opened = true;
			screenNameFinder.close();
			filename++;
		}
		else
			opened = false;
	} while (opened);
	window.saveToFile("res/screenshots/" + std::to_string(filename) + ".png");
}

void Game::render()
{
	win->clear(Color(137,249,255));
	win->draw(*map);
	if (map->isSlowMotionAvailable && !isEndless)
	{
		win->draw(numberOfSlowmoBg);
		win->draw(slowmoInfo);
	}
	if (map->getTotalNumberOfCoins() > 0 && !isEndless)
	{
		win->draw(numberOfCoinsBg);
		win->draw(coinsInfo);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		win->draw(lenFromStart);
	}
	win->draw(slowmotion);
	
	if (teleportMode)
	{
		win->draw(teleportTimeProgress);
	}
	if (pause)
	{
		win->draw(*pauseMenu);
		win->draw(cursor);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		win->draw(fpsCounter);
	}
	win->display();
}

bool Game::run()
{
	fpsClock.restart();
	Clock framerate;

	//time from last game update
	float time = 0;

	while (gameState == Continues)
	{
		handleEvents();
		//*****UPDATING GAME*****

		fps++;
		//showing fps
		if (fpsClock.getElapsedTime().asSeconds() > 1)
		{
			fpsCounter.setString("Fps: " + std::to_string(fps));
			fps = 0;
			fpsClock.restart();
		}
		//add elapsed time from last game update
		time += framerate.getElapsedTime().asMilliseconds();
		
		if (time > 14)
		{	
			if (!pause)
			{
				if (teleportMode == false && map->gameSpeed < -12)
				{
					map->gameSpeed = -12;
				}
				if (map->gameSpeed > -12 && teleportMode == false)
				{
					slowmotion.setColor(Color(255, 255, 255, slowmotion.getColor().a - 4));
					map->gameSpeed -= 0.1;
				}
				else if (map->gameSpeed < -7 && teleportMode == true)
				{
					slowmotion.setColor(Color(255, 255, 255, slowmotion.getColor().a + 4));
					map->gameSpeed += 0.1;
				}
				if (teleportMode)
				{
					teleportTimeProgress.setValue((int)teleportTime.getElapsedTime().asMilliseconds());
					if (teleportTime.getElapsedTime().asSeconds() > 3)
					{
						teleportMode = false;
					}
				}
				map->update();
				lenFromStart.setString(std::to_string((int)map->lenFromStart)+"m");
				if (isEndless)
				{
					map->player.say(lenFromStart.getString());
				}
				slowmoInfo.setString(std::to_string(map->teleportsQuantity));
				coinsInfo.setString(std::to_string(map->getNumberOfCoins()) + "/" + std::to_string(map->getTotalNumberOfCoins()));
				coinsInfo.setPosition(69 - coinsInfo.getGlobalBounds().width / 2, 25);
			}
			render();

			
			framerate.restart();
			time -= 14;
		}
		//***********************

		if (map->player.getState()==Player::STATE::IS_DEAD)
		{
			gameState = Ended;
		}
		if (map->player.getState() == Player::STATE::IS_DONE)
		{
			gameState = Won;
		}
	}

	if (gameState == Ended)
	{
		gameResult = false;
		gameOverScreen();
	}
	else if (gameState == Won)
	{
		winScreen();
		gameResult = true;
	}
	else if (gameState == Aborted)
	{
		gameResult = false;
		printf("deleting...");
	}
	return gameResult;
}

void Game::gameOverScreen()
{
	map->music.stop();
	SoundBuffer deathSoundBuffer;
	deathSoundBuffer.loadFromFile("res/sounds/death.wav");
	Sound deathSound(deathSoundBuffer);
	deathSound.setVolume(SettingsManager::loadSoundsVolume());
	deathSound.play();

	win->setView(win->getDefaultView());
	Texture bgTex;
	bgTex.loadFromImage(Image(win->capture()));
	Sprite bg(bgTex);
	Texture controlsTex;
	controlsTex.loadFromFile("res/images/controls.png");
	Sprite controls(controlsTex);
	controls.setPosition(0, win->getSize().y - 35);

	Button restart(win->getSize().x / 2 - 100, 1200, Text("", *font, 20), font, "res/images/restartbutton.png");
	Button menu(win->getSize().x / 2 - 100, 1260, Text("", *font, 20), font, "res/images/backtomenubutton.png");

	std::vector <std::string> texts =
	{
		"Mad","LOSER","Seriously?","Pffff...","Better luck next time?",
		"Not a surprise","Is it a bird? Is it a plane? No it's a complete failure",
		"Ouch","Why won't you just give up","Your the best - around. Nothing's ever gonna' keep you down",
		"Keep trying", "Let's pretend this never happened", "I can't look at this"
	};
	Text header("Game over!", *font, 70);
	Text splashText("", *font, 20);
	splashText.setString(texts[rand() % texts.size()]); 

	RectangleShape dark(Vector2f(win->getSize().x, win->getSize().y));
	dark.setFillColor(Color(0, 0, 0, 160));
	dark.setPosition(0, 780);
	int speed = 39;
	int choose = 0;

	while (choose==0)
	{
		Event event;
		while (win->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				win->close();
				exit(0);
			}
			if (restart.isMouseOn(win))
			{
				if (restart.click(&event, win))
				{
					choose = 1;
				}
			}
			if (menu.isMouseOn(win))
			{
				if (menu.click(&event, win))
				{
					choose = 2;
				}
			}
			if (SettingsManager::isJoystickConnected())
			{
				if (Joystick::isButtonPressed(SettingsManager::joystickId, 0))
				{
					choose = 1;
				}
				else if (Joystick::isButtonPressed(SettingsManager::joystickId, 1))
				{
					choose = 2;
				}
			}
		}
		cursor.setPosition(Mouse::getPosition(*win).x, Mouse::getPosition(*win).y);
		if (speed > 0)
		{
			dark.move(0, -speed);
			restart.setPosition(win->getSize().x / 2 - 100, dark.getPosition().y + 550);
			menu.setPosition(win->getSize().x / 2 - 100, dark.getPosition().y + 610);
			header.setPosition(win->getSize().x / 2 - header.getGlobalBounds().width/2, dark.getPosition().y + 10);
			splashText.setPosition(win->getSize().x / 2 - splashText.getGlobalBounds().width / 2, dark.getPosition().y + 85);
			speed--;
		}
		if (dark.getPosition().y <= -1050)
			dark.setPosition(0, 1050);

		win->clear();
		win->draw(bg);
		win->draw(dark);
		win->draw(restart);
		win->draw(menu);
		win->draw(header);
		win->draw(splashText);
		//win->draw(controls);
		win->draw(cursor);
		win->display();
	}
	delete map;
	if (choose == 1)
	{
		win->setMouseCursorVisible(false);
		init(win, font, mapPath, lvlNumber, isEndless);
		std::cout << "Initialized" << std::endl;
		run();
	}
}

void Game::winScreen()
{
	SoundBuffer winSoundBuffer;
	winSoundBuffer.loadFromFile("res/sounds/win.wav");
	Sound winSound(winSoundBuffer);
	winSound.setVolume(SettingsManager::loadSoundsVolume());
	winSound.play();

	win->setView(win->getDefaultView());
	Texture bgTex;
	bgTex.loadFromImage(Image(win->capture()));
	Sprite bg(bgTex);
	Texture controlsTex;
	controlsTex.loadFromFile("res/images/controls2.png");
	Sprite controls(controlsTex);
	controls.setPosition(0, win->getSize().y - 35);
	controls.setColor(Color::Transparent);

	Button continueGame(win->getSize().x / 2 - 100, win->getSize().y / 2+100, Text("", *font, 20), font, "res/images/continuebutton.png");
	
	Text header("Success!", *font, 50);
	header.setPosition(win->getSize().x / 2 - header.getGlobalBounds().width / 2, win->getSize().y/2 - 120);
	header.setColor(Color::Transparent);

	RectangleShape dark(Vector2f(win->getSize().x, 0));
	dark.setFillColor(Color(0, 0, 0, 160));
	dark.setPosition(0, win->getSize().y/2);
	int speed = 25;
	bool isOpen = true;
	
	while (isOpen)
	{
		Event event;
		while (win->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				win->close();
				exit(0);
			}
			if (continueGame.isMouseOn(win))
			{
				if (continueGame.click(&event, win))
				{
					isOpen = false;
				}
			}
			if (SettingsManager::isJoystickConnected())
			{
				if (Joystick::isButtonPressed(SettingsManager::joystickId, 0))
				{
					isOpen = false;
				}
			}
		}
		cursor.setPosition(Mouse::getPosition(*win).x, Mouse::getPosition(*win).y);
		win->clear();
		win->draw(bg);
		win->draw(dark);
		if (speed > 0)
		{
			dark.setSize(Vector2f(win->getSize().x, dark.getSize().y + speed));
			dark.move(0, (speed / 2)*-1);
			speed--;
		}
		else
		{
			if (header.getColor().a < 255)
			{
				header.setColor(Color(255, 255, 255, header.getColor().a + 17));
				continueGame.setColor(Color(255, 255, 255, header.getColor().a));
				controls.setColor(Color(255, 255, 255, header.getColor().a));
			}
			win->draw(header);
			win->draw(continueGame);
			//win->draw(controls);
		}
		win->draw(cursor);
		win->display();
	}
	lvlNumber++;
	std::fstream saveProgress("res/save.crsav", std::ios::out | std::ios::app);
	saveProgress << " " << std::to_string(lvlNumber);
	saveProgress.close();

	if(SettingsManager::isJoystickConnected())
		Mouse::setPosition(Vector2i(win->getSize().x / 2, win->getSize().y / 2));
}


Game::~Game()
{
	delete map;
	map = NULL;
}

void Game::Pause::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(gameBg);
	target.draw(background);
	target.draw(exitGame);
	target.draw(header);
	target.draw(tip);
}

Game::Pause::Pause(RenderWindow * win, Font *font)
{
	exitGame.create(win->getSize().x / 2 - 52.5, win->getSize().y / 2-200, 200, 40, Text("Exit", *font, 20), font, Color::White);
	
	background.setSize(Vector2f(420, 200));
	background.setFillColor(Color(0,0,0,160));
	background.setOutlineColor(Color(32,158,255));
	background.setOutlineThickness(2);
	background.setPosition(win->getSize().x / 2 - 210, win->getSize().y / 2 - 150 - 200);

	header.setString("Pause");
	header.setFont(*font);
	header.setCharacterSize(30);
	header.setPosition(win->getSize().x / 2 - header.getGlobalBounds().width / 2, win->getSize().y / 2 - 145 - 200);

	tip.setString("Press escape to continue...");
	tip.setFont(*font);
	tip.setCharacterSize(15);
	tip.setPosition(win->getSize().x / 2 - tip.getGlobalBounds().width / 2, win->getSize().y / 2 - 145 - 150);

	gameBgTex.loadFromImage(win->capture());
	gameBg.setTexture(gameBgTex);

	this->win = win;
}

bool Game::Pause::handle(Event *event)
{
	if (exitGame.isMouseOn(win))
	{
		if (exitGame.click(event, win))
		{
			return true;
		}
	}
	return false;
}

Game::Pause::~Pause()
{
}
