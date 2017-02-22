#include "Map.h"

void Map::draw(RenderTarget & target, RenderStates state) const
{
	for (int i = 0; i < 2; i++)
	{
		target.draw(background[i]);
	}
	for (size_t i = 0; i < coins.size(); i++)
	{
		target.draw(*coins[i]);
	}

	target.draw(chunksSprite);
	target.draw(player);
	lights->draw(target);
	if (!isEndless)
	{
		target.draw(progress);
		target.draw(topbar);
	}
}

Map::Map(bool isEndless)
{
	this->isEndless = isEndless;
	numberOfCoins = 0;
	totalNumberOfCoins = 0;
	chunksTargetTexture.create(1680, 1050);
	chunksSprite.setTexture(chunksTargetTexture.getTexture());
}

void Map::update()
{
	//moving background
	for (int i = 0; i < 2; i++)
	{
		background[i].move(-2, 0);
		if (background[i].getPosition().x <= -1680)
			background[i].setPosition(1680, 0);
	}
	//clear chunks texture
	chunksTargetTexture.clear(Color::Transparent);
	//moving chunks
	if (Keyboard::isKeyPressed((Keyboard::Key)SettingsManager::runKey) && gameSpeed <=-12)
	{
		gameSpeed = -17;
	}
	for (size_t i = 0; i < chunks.size(); i++)
	{
		if (chunks[i]->getGlobalBounds().left > -1880)
		{
			chunks[i]->move(gameSpeed, 0);
		}
		if (chunks[i]->getGlobalBounds().intersects(SettingsManager::renderingSize))
		{
			chunks[i]->drawOnTexture(&chunksTargetTexture);
		}
		else if(i==0)
			chunks[i]->move(gameSpeed, 0);
	}
	//displaying chunks on render texture
	chunksTargetTexture.display();
	//updating coins
	for (size_t i = 0; i < coins.size(); i++)
	{
		coins[i]->update();
		coins[i]->move(gameSpeed);
		if (coins[i]->checkBounds(player.getGlobalBounds()))
		{
			coins.erase(coins.begin() + i);
			numberOfCoins++;
		}
	}
	int intersectsChunks = 0; // number of intersecting chunks
	for (size_t i = 0; i < chunks.size(); i++)
	{
		//For 1680x1050 checking collisions chunk-player
		if (chunks[i]->getGlobalBounds().intersects(SettingsManager::renderingSize))
		{
			if (chunks[i]->getGlobalBounds().intersects(player.getGlobalBounds()))
			{
				player.update(chunks[i]);


				float randomScale = (float)(rand() % 10) / 100.f + 5.f;
				lights->getLightVector()->at(0).setScale(randomScale,randomScale);
				lights->getLightVector()->at(0).setPosition(player.getGlobalBounds().left+21, player.getGlobalBounds().top + 35);

				lenFromStart = (abs(player.getGlobalBounds().left) + abs(chunks[0]->getGlobalBounds().left))/70;
				intersectsChunks++;
				playerIntersectingChunk = i;
				//**generate dynamic chunks**
				if (playerIntersectingChunk == chunks.size() - 1 && isEndless)
				{
					bool okChunk = false;
					Clock generatingTime;
					while (!okChunk) 
					{
						int randPresetNumber = rand() % endlessChunksInfo.size();
						std::string newChunkForEndlessMode[15];
						if (endlessChunksInfo[randPresetNumber].getStartingBlockLevel() == usedChunks.back().getEndingBlockLevel())
						{
							std::cout << "Added chunk ID: " << randPresetNumber << std::endl;
							endlessChunksInfo[randPresetNumber].getCode(newChunkForEndlessMode);
							usedChunks.push_back(endlessChunksInfo[randPresetNumber]);
							chunks.push_back(new Chunk(newChunkForEndlessMode));
							okChunk = true;
							chunks.back()->setPosition(chunks[chunks.size() - 2]->getGlobalBounds().left + 1680,0);
						}
						else if (generatingTime.getElapsedTime().asSeconds() > 1)
						{
							endlessChunksInfo[0].getCode(newChunkForEndlessMode);
							usedChunks.push_back(endlessChunksInfo[0]);
							chunks.push_back(new Chunk(newChunkForEndlessMode));
							okChunk = true;
							chunks.back()->setPosition(chunks[chunks.size() - 2]->getGlobalBounds().left + 1680, 0);
						}
					}
				}
				//**************************
				break;
			}
		}
	}

	if (intersectsChunks <= 0)
		player.kill();

	progress.setValue(playerIntersectingChunk);
	for (size_t i = 0; i < sayingChunks.size(); i++)
	{
		if (sayingChunks[i] == playerIntersectingChunk)
		{
			player.say(texts[i]);
		}
	}
	progress.update();
}

bool Map::load(std::string path)
{
	std::cout << "Loading map from: " << path << std::endl;
	//Opening file
	std::fstream mapFile(path, std::ios::in);
	if (!mapFile.is_open())
	{
		MessageBoxW(NULL, L"Failed to load map.", L"Error", MB_ICONERROR);
		return false;
	}
	std::string currentLine;
	std::string musicPath;
	std::string blocksTexturePath;
	std::string backgroundPath;
	std::string teleportsQuantity;

	//Getting map info
	getline(mapFile, currentLine);
	getline(mapFile, teleportsQuantity);
	if (stoi(teleportsQuantity) < 0)
	{
		MessageBoxW(NULL, L"Failed to create map.", L"Error", MB_ICONERROR);
		return false;
	}
	this->teleportsQuantity = stoi(teleportsQuantity);
	if (this->teleportsQuantity > 0)
	{
		isSlowMotionAvailable = true;
	}
	else
	{
		isSlowMotionAvailable = false;
	}
	getline(mapFile, musicPath);
	getline(mapFile, blocksTexturePath);
	getline(mapFile, backgroundPath);
	Block::loadAssets(blocksTexturePath);
	width = stoi(currentLine);
	if (width % 24 != 0)
	{
		MessageBoxW(NULL, L"Failed to create map.", L"Error", MB_ICONERROR);
		return false;
	}
	if (width / 24 > 256)
	{
		std::wstring errorcode = L"Failed to create map. Map width: ";
		errorcode += std::to_wstring(width / 24);
		errorcode += L" (max 256).";
		MessageBoxW(NULL, errorcode.c_str(), L"Error", MB_ICONERROR);
		return false;
	}
	//Geting map code
	for (int i = 0; i < 15; i++)
	{
		getline(mapFile, currentLine);
		mapCode[i] = currentLine;
	}
	//Getting texts to say and its positions (in chunks)
	std::string textsToSay;
	while (getline(mapFile,textsToSay))
	{
		if (textsToSay == "END")
		{
			break;
		}
		sayingChunks.push_back(stoi(textsToSay));
		getline(mapFile, textsToSay);
		texts.push_back(textsToSay);
	}
	//Getting coins positions
	std::string coinPos;
	if (!isEndless)
	{
		while (getline(mapFile, coinPos))
		{
			int chunk, x, y;
			chunk = stoi(coinPos);
			getline(mapFile, coinPos);
			x = stoi(coinPos);
			getline(mapFile, coinPos);
			y = stoi(coinPos);
			coins.push_back(new Coin(chunk, x, y));
			totalNumberOfCoins++;
		}
	}
	mapFile.close();
	//Creating blocks
	if (!isEndless)
	{
		for (int i = 0; i < width / 24; i++)
		{
			chunks.push_back(new Chunk(mapCode));
		}
	}
	else
	{
		int i = 0;
		//loading available chunks presets
		std::cout << "Loading available chunks presets to memory..." << std::endl;
		std::ifstream loadEndlessModeChunks; 
		do
		{
			loadEndlessModeChunks.close();
			loadEndlessModeChunks.open("res/maps/presets/preset_" + std::to_string(i) + ".lvl");
			if (loadEndlessModeChunks.is_open())
			{
				endlessChunksInfo.push_back(EndlessChunkInfo("res/maps/presets/preset_" + std::to_string(i) + ".lvl"));
				std::cout << "Loading chunk " + std::to_string(i) << std::endl;
				i++;
			}
		}while(loadEndlessModeChunks.is_open());
		std::cout << "Successfully loaded "+std::to_string(i)+" chunks.\nSetting spawn chunk..." << std::endl;
		//setting first chunk
		std::string newChunkForEndlessMode[15];
		endlessChunksInfo[0].getCode(newChunkForEndlessMode);
		usedChunks.push_back(endlessChunksInfo[0]);
		chunks.push_back(new Chunk(newChunkForEndlessMode));
		std::cout << "Spawn succesfully generated!\nGenerating other near-spawn chunks..." << std::endl;
		//setting spawn chunks
		for (int i = 0; i < 10; i++)
		{
			bool okChunk = false;
			Clock generatingTime;
			while (!okChunk) {
				int randPresetNumber = rand() % endlessChunksInfo.size();
				if (endlessChunksInfo[randPresetNumber].getStartingBlockLevel() == usedChunks.back().getEndingBlockLevel())
				{
					std::string newChunkForEndlessMode[15];
					endlessChunksInfo[randPresetNumber].getCode(newChunkForEndlessMode);
					usedChunks.push_back(endlessChunksInfo[randPresetNumber]);
					chunks.push_back(new Chunk(newChunkForEndlessMode));
					okChunk = true;
					std::cout << "Chunk added! ID: " << randPresetNumber << std::endl;
				}
				else if (generatingTime.getElapsedTime().asSeconds() > 1)
				{
					endlessChunksInfo[0].getCode(newChunkForEndlessMode);
					usedChunks.push_back(endlessChunksInfo[0]);
					chunks.push_back(new Chunk(newChunkForEndlessMode));
					okChunk = true;
					chunks.back()->setPosition(chunks[chunks.size() - 2]->getGlobalBounds().left + 1680, 0);
				}
			}
		}
	}
	//Setting chunks positions
	std::cout << "Setting chunks positions...\n";
	for (size_t i = 0; i < chunks.size(); i++)
	{
		chunks[i]->setPosition(i * 1680, 0);
	}
	std::cout << "Chunks' positions set!\n";
	//loading music
	if (!music.openFromFile(musicPath))
	{
		MessageBoxW(NULL, L"Failed to load music.", L"Error", MB_ICONERROR);
		return false;
	}
	//loading background
	backgroundTex.loadFromFile(backgroundPath);
	background[0].setTexture(backgroundTex);
	background[1].setTexture(backgroundTex);
	background[0].setPosition(0, 0);
	background[1].setPosition(1680, 0);
	//loading topbar
	topbarTex.loadFromFile("res/images/topbar.png");
	topbar.setTexture(topbarTex);
	topbar.setPosition(340 - 25, 0);
	//creating progressbar
	progress.create(340, 25, 1000, 20, chunks.size()-2);
	//progress.setBorderColor(Color(255,50,50));
	//progress.setFillColor(Color(255,88,88));
	music.setLoop(true);
	music.setVolume(SettingsManager::loadMusicVolume());
	music.play();

	//particles = new ParticlesEmitter(ParticlesEmitter::LEFT);
	lights = new LightMap(Vector2f(1680,1050), "res/textures/light.png");
	lights->addLight();
	lights->getLightVector()->at(0).scale(5.5, 5.5);
	
	if (blocksTexturePath == "res/textures/countrysideblocks.png")
	{
		mapTheme = COUNTRYSIDE;
		player.setTheme(Player::COUNTRYSIDE);
		lights->setColor(Color::White);
	}
	else if (blocksTexturePath == "res/textures/caveblocks.png")
	{
		mapTheme = CAVE;
		player.setTheme(Player::CAVE);
		lights->setColor(Color(20, 20, 20));
	}
	if (!SettingsManager::godMode)
	{
		while (player.getState() != Player::ON_GROUND)
		{
			player.update(chunks[0]);
		}
	}
	

	gameSpeed = -12;
	return true;
}

int Map::getNumberOfCoins()
{
	return numberOfCoins;
}

int Map::getTotalNumberOfCoins()
{
	return totalNumberOfCoins;
}

Map::~Map()
{
	for (size_t i = 0; i < chunks.size(); i++)
	{
		delete chunks[i];
		chunks[i] = NULL;
	}

	chunks.clear();
	std::vector<Chunk*>().swap(chunks);
}
