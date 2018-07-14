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

#include "initAndError.h"

#include "button.h"
#include "sdl.h"
#include "renduecran.h"
#include "Player.h"
#include "loadUnitAndSpec.h"
#include "calculimage.h"
#include "deleteAll.h"


using namespace std;





void initAndError(){
	sysinfo information;
	vector<Player*> tabplayer;

	srand((unsigned int)time(NULL));


	try{
		initfile(information);
	}
	catch (exception const& e){
		cerr << "ERREUR : " << e.what() << endl; 
	}



	logfileconsole("________PROGRAMME START________");


	try{
		initsdl(information.ecran.window, information.ecran.renderer, information.allTextures.font);
	}
	catch (exception const& e){
		cerr << "ERREUR : " << e.what() << endl;
	}

	
	loadUnitAndSpec(information);
	calculimage(information);
	ecrantitre(information);
	button(information, tabplayer);	// fonction principale (bloquante)

	deleteAll(information, tabplayer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	logfileconsole("SDL_Quit Success");
	logfileconsole("________PROGRAMME FINISH________");
}
