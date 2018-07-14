/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.6

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Civ_rob_2

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

#include "keySDLK.h"

#include "unit.h"
#include "citie.h"

using namespace std;


void keySDLK_b(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.ecran.statescreen == STATEmainmap && information.variable.select == selectmove)
		createcitie(information, tabplayer);
}

void keySDLK_KP_1(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.ecran.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, -tileSize, tileSize);
}
void keySDLK_KP_2(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.ecran.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, 0, tileSize);
}
void keySDLK_KP_3(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.ecran.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, tileSize, tileSize);
}
void keySDLK_KP_4(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.ecran.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, -tileSize, 0);
}
void keySDLK_KP_5(sysinfo& information, vector<Player*>& tabplayer) {
	
}
void keySDLK_KP_6(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.ecran.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, tileSize, 0);
}
void keySDLK_KP_7(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.ecran.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, -tileSize, -tileSize);
}
void keySDLK_KP_8(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.ecran.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, 0, -tileSize);
}
void keySDLK_KP_9(sysinfo& information, vector<Player*>& tabplayer) {
	if (information.ecran.statescreen == STATEmainmap && information.variable.select == selectmove)
		tryToMove(information, tabplayer, tileSize, -tileSize);	
}