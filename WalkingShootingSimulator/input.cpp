#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#include "Engine.h"

typedef Keyboard::Key key;

inline bool pressed(key pressedKey)
{
	return Keyboard::isKeyPressed(pressedKey);
}

void Engine::input()
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			currentState = GameState::EXIT;
		}
		else if (event.type == Event::Resized)
		{
			hudResizeUpdate();
		}
	}

	static bool keyOnHold[10] = { false };
	static bool escOnHold = false;
	static bool leftMouseOnHold = false;

	// �udly
	switch (currentState)
	{
	case GameState::PLAYING:
		if (pressed(key::Escape) && !escOnHold)
		{
			window.setMouseCursorVisible(true);
			soundManager.playWalk(false);
			currentState = GameState::PAUSE;
			escOnHold = true;
			menuText.setString("1) resume\n0) menu");
		}
		else
		{
			escOnHold = false;
		}
		// POHYB HR��E
		if (pressed(key::W)) player.moveUp();
		if (pressed(key::S)) player.moveDown();
		if (pressed(key::A)) player.moveLeft();
		if (pressed(key::D)) player.moveRight();

		if (pressed(key::R) && player.getState() != Soldier::PlayerState::RELOAD)
		{
			player.reload();
			soundManager.playReload();
		}

		// st�elba
		if (Mouse::isButtonPressed(Mouse::Button::Left)
			&& player.getState() != Soldier::PlayerState::RELOAD && player.shootAvailable())
		{
			// RILFE je automatick� zbra�, ostatn� jsou poloautomaty
			if (!leftMouseOnHold || player.getWeapon() == Soldier::WeaponTypes::RIFLE)
			{
				if (player.shoot())
				{
					bullets.push_back(Bullet(player.getCenter(), mouseWorldPosition));
					soundManager.playShoot();
				}
			}
		}
		// jestli je my� dr�ena
		if (Mouse::isButtonPressed(Mouse::Button::Left))
			leftMouseOnHold = true;
		else
			leftMouseOnHold = false;

		// p�ep�n�n� zbran�
		if (pressed(key::Num1))
			player.setWeapon(Soldier::WeaponTypes::HANDGUN);
		if (pressed(key::Num2))
			player.setWeapon(Soldier::WeaponTypes::RIFLE);
		break;

	case GameState::PAUSE:
		if (pressed(key::Num1) || pressed(key::Numpad1))
		{
			if (!keyOnHold[1] && !levelFinished) 
			{ 
				currentState = GameState::PLAYING;
				window.setMouseCursorVisible(false);
			}
			keyOnHold[1] = true;
		}
		else keyOnHold[1] = false;

		if (pressed(key::Num0) || pressed(key::Numpad0))
		{
			if (!keyOnHold[0]) currentState = GameState::MENU;
			keyOnHold[0] = true;
			menuText.setString("1) play\n2) info\n0) exit");
			hudResizeUpdate();
			player.reset();
			bullets.clear();
			targets.clear();
		}
		else keyOnHold[0] = false;
		break;

	case GameState::INFO:
		if (pressed(key::Num0) || pressed(key::Numpad0))
		{
			if (!keyOnHold[0])
				currentState = GameState::MENU;
			keyOnHold[0] = true;
		}
		else
			keyOnHold[0] = false;
		break;

	case GameState::MENU:
		if (pressed(key::Num1) || pressed(key::Numpad1))
		{
			if (!keyOnHold[1]) { currentState = GameState::LEVEL_PICK; }
			keyOnHold[1] = true;
		}
		else keyOnHold[1] = false;

		if (pressed(key::Num2) || pressed(key::Numpad2))
		{
			keyOnHold[2] = true;
			currentState = GameState::INFO;
		}
		else keyOnHold[2] = false;

		if (pressed(key::Num0) || pressed(key::Numpad0))
		{
			if (!keyOnHold[0]) currentState = GameState::EXIT;
		}
		else keyOnHold[0] = false;

		break;

	case GameState::LEVEL_PICK:
		if (pressed(key::Num0) || pressed(key::Numpad0))
		{
			currentState = GameState::MENU;
			keyOnHold[0] = true;
		}
		else keyOnHold[0] = false;

		int holdIndex = 1;
		for (int i = key::Num1; i <= key::Num9; i++)
		{
			if (pressed(key(i)) || pressed(key(i + 49)))
			{
				if (!keyOnHold[holdIndex])
				{
					if (levelManager.loadMap(holdIndex - 1, player, targets))
					{
						currentState = GameState::PLAYING;
						levelTime = Time::Zero;
						levelFinished = false;
						window.setMouseCursorVisible(false);
					}
				}
			}
			else
			{
				keyOnHold[holdIndex] = false;
			}
			holdIndex++;
		}
		break;
	}
}
