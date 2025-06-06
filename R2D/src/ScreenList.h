/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Civ_rob_2.0

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef ScreenList_H
#define ScreenList_H

#include "API_fwd.h"

namespace R2D
{

class ScreenList
{
public:
	using IGameScreenPtr = std::shared_ptr<IGameScreen>;
	using IGameScreenPtrVector = std::vector<std::shared_ptr<IGameScreen>>;
public:
	ScreenList(IMainGame* game) : m_game(game), m_currentScreenIndex(R2D::SCREEN_INDEX::INIT) {};
	~ScreenList() { destroy(); };

	IGameScreenPtr moveNext();
	IGameScreenPtr movePrevious();

	void setScreen(int nextScreen);
	void addScreen(IGameScreenPtr newScreen);

	void destroy();

	IGameScreenPtr getCurrent();

protected:
	IMainGame* m_game;
	IGameScreenPtrVector m_screens;
	int m_currentScreenIndex;
};

}

#endif // !ScreenList_H

