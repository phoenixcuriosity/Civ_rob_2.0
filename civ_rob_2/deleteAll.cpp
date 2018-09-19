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

#include "deleteAll.h"
#include "initAndError.h"

using namespace std;


void deleteAll(sysinfo& information, vector<Player*>& tabplayer){
	logfileconsole("*********_________ Start DeleteAll _________*********");

	for (unsigned int i = 1; i < 80; i++) 
		TTF_CloseFont(information.allTextures.font[i]);

	deleteDyTabPlayerAndTextures(information.allTextures.ground, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.groundSpec, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.unit, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.barLife, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.colorapp, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.colorappTile, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.miscTexture, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.txtecrantitre, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.txtnewgame, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.txtmainmap, "Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.txtcitiemap, "Texture");

	deleteDyTabPlayerAndTextures(information.allButton.ecrantitre, "Button");
	deleteDyTabPlayerAndTextures(information.allButton.player, "Button");
	deleteDyTabPlayerAndTextures(information.allButton.reload, "Button");
	deleteDyTabPlayerAndTextures(information.allButton.mainmap, "Button");
	deleteDyTabPlayerAndTextures(information.allButton.citie, "Button");

	deleteDyTabPlayerAndTextures(tabplayer, "player");
	SDL_DestroyRenderer(information.ecran.renderer);
	SDL_DestroyWindow(information.ecran.window);
	information.ecran.renderer = nullptr;
	information.ecran.window = nullptr;
	logfileconsole("*********_________ End DeleteAll _________*********");
}