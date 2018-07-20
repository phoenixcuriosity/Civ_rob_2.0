/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.6

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

#include "nextTurn.h"

using namespace std;

void nextTurn(sysinfo& information, vector<Player*>& tabplayer) {
	for (unsigned int i = 0; i < tabplayer.size(); i++) {
		for (unsigned int j = 0; j < tabplayer[i]->GETtabunit().size(); j++) {
			tabplayer[i]->GETtheunit(j)->RESETmovement();
			tabplayer[i]->GETtheunit(j)->heal(information.maps.tiles, i);
		}
		for (unsigned int j = 0; j < tabplayer[i]->GETtabcities().size(); j++) {
			tabplayer[i]->GETthecitie(j)->foodNextTurn();
		}
	}
	information.variable.nbturn++;
}