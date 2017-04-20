#include "GameEngine.h"
#include "Game.h"
#include "Cursor.h"

GameEngine::GameEngine()
{


}


GameEngine::~GameEngine()
{
	while (!games.empty()) {
		games.back()->deleteAll();
		games.pop_back();
	}
	if (exit) {
		CloseHandle(hThread);
		graphics->cleanup();
		dltPtr(graphics);
		dltPtr(gameTime);
		dltPtr(input);
		dltPtr(sound);
		dltPtr(cursor);
		dltPtr(camera);
		dltPtr(network);
	}
}

bool GameEngine::initialize(HWND hwnd)
{
	sprite = NULL;
	camera = new GameCamera(0.0f, 0.0f);
	camera->move(0.0f, 0.0f);

	network = new Network();
	network->initializeWinSock();

	if (graphics == NULL) {
		graphics = new Graphics();
		if (!graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT)) {
			MessageBox(NULL, "There was an issue initializing the graphics", NULL, NULL);
			return initialized = false;
		}

	}
	if (sound == NULL) {
		sound = new DxSound();
		if (!sound->initializeSound()) {
			MessageBox(NULL, "There was an issue initializing the Sounds", NULL, NULL);
			return initialized = false;

		}
		sound->loadSounds();
	}
	if (input == NULL) {
		input = new PlayerInput();
		// initialize device

		if (!input->initializeKeyboard(hwnd)) {
			MessageBox(NULL, "There was an issue initializing the Keyboard input", NULL, NULL);
			return initialized = false;
		}

		if (!input->initializeMouse(hwnd)) {
			MessageBox(NULL, "There was an issue initializing the Mouse input", NULL, NULL);
			return initialized = false;
		}
	}
	if (cursor == NULL) {
		cursor = new Cursor(GAME_WIDTH / 2, GAME_HEIGHT / 2, D3DXVECTOR2(1.0f, 1.0f), 11); //6 is 10 frames per second

		if (!cursor->initialize(graphics->device3d, "sprite/dankcursor.png", 1440, 95, 1, 15, true, D3DCOLOR_XRGB(255, 0, 255), 1.0f)) {
			MessageBox(NULL, "There was an issue initializing the graphics", NULL, NULL);
			return initialized = false;
		}
	}
	if (sprite == NULL) {
		HRESULT hr = D3DXCreateSprite(graphics->device3d, &sprite);
		if (FAILED(hr)) {
			MessageBox(NULL, "ERROR", "Could not create sprite", MB_ICONERROR);
			return false;
		}
	}


	//sound->playSoundtrack();

	if (gameTime == NULL) {
		gameTime = new GameTime();

		if (!gameTime->initialize(REQFPS)) {
			return initialized = false;
		}
	}
	exit = false;
	return initialized = true;
}

void GameEngine::changeState(Game * game, HWND hwnd)
{
	if (!games.empty()) {
		games.back()->deleteAll();
		games.pop_back();
	}
	games.push_back(game);
	if (!(games.back()->initializeGame(hwnd, this))) {
		MessageBox(NULL, "Game Initialize error", "Initialize error", MB_OKCANCEL);
		exit = true;
	}

}

void GameEngine::pushState(Game * game, HWND hwnd)
{
	games.push_back(game);
	if (!(games.back()->initializeGame(hwnd, this))) {
		MessageBox(NULL, "Game Initialize error", "Initialize error", MB_OKCANCEL);
		exit = true;
	}

}

void GameEngine::handleEvents()
{
	games.back()->handleEvents(this);

}

void GameEngine::popState()
{

	// cleanup the current state
	if (!games.empty()) {
		games.back()->deleteAll();
		games.pop_back();
	}
}

void GameEngine::run()
{
	games.back()->run(this);

}

LRESULT GameEngine::winProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
			break;
		case VK_BACK:
			if (ipAddress.size() != 0)
			{
				ipAddress.pop_back();
				break;
			}
			if (hostIpAddress.size() != 0)
			{
				hostIpAddress.pop_back();
				break;
			}
			break;
			//case VK_F1:
			//	input->remapKeys();//<---- underconstruction used to remap keys but needs to be switched to windows input instead of directinput

			//break;
		}
		
		// static_cast<char>(wParam);
		if (ipAddresslocked == false)
		{
			if (wParam != VK_BACK && wParam != VK_RETURN)
			{
				ipAddress += static_cast<char>(wParam);
				if (wParam == VK_OEM_PERIOD)
				{
					ipAddress.pop_back();
					ipAddress += ".";
				}

			}
			//	network->MOTD += static_cast<char>(wParam);

		}
		if (hostIpAddresslocked == false)
		{
			if (wParam != VK_BACK  && wParam != VK_RETURN)
			{
				hostIpAddress += static_cast<char>(wParam);
				if (wParam == VK_OEM_PERIOD)
				{
					hostIpAddress.pop_back();
					hostIpAddress += ".";
				}
			}
		}


		break;

	}
	this->wParam = wParam;
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
void GameEngine::setDrawingPoint(int x, int y)
{

	COORD coord; //Does not need to be define because if we right click COORD and go to definition it is already defined in another library
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);


}




