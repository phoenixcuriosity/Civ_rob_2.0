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
	ScreenList(IMainGame* game);
	~ScreenList();

	std::shared_ptr<IGameScreen> moveNext();
	std::shared_ptr<IGameScreen> movePrevious();

	void setScreen(int nextScreen);
	void addScreen(std::shared_ptr<IGameScreen> newScreen);

	void destroy();

	std::shared_ptr<IGameScreen> getCurrent();

protected:
	IMainGame* m_game;
	std::vector< std::shared_ptr<IGameScreen>> m_screens;
	int m_currentScreenIndex;
};

}

#endif // !ScreenList_H

