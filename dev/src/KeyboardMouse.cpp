/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.15
	file version : 1.6

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

#include "KeyboardMouse.h"
#include "civ_lib.h"
#include "IHM.h"
#include "SaveReload.h"
#include "GamePlay.h"
#include "HashTable.h"


/* *********************************************************
 *			START KeyboardMouse::STATIC::CIN			   *
 ********************************************************* */
 

/*
* NAME : cinDigit
* ROLE : Recherche d'un digit rentré par le joueur
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : unsigned int& digit : le digit a retourner
* INPUT  PARAMETERS : unsigned int x : coordonnée en x pour l'affichage du digit
* INPUT  PARAMETERS : unsigned int y : coordonnée en y pour l'affichage du digit
* OUTPUT PARAMETERS : le digit
* RETURNED VALUE    : void
*/
void KeyboardMouse::cinDigit(Sysinfo& sysinfo, unsigned int& digit, unsigned int x, unsigned int y)
{
	bool continuer = true;
	SDL_Event event;
	int SDL_EnableUNICODE(1);

	while (continuer)
	{
		SDL_WaitEvent(&event); // attente d'un événement (clavier, souris)
		switch (event.type) // test sur le type d'événement
		{
		case SDL_QUIT:	// permet de quitter le jeu
			SDL_Quit();
			break;
		case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				if (digit == 0)
					digit = 1;
				continuer = false;
				break;
			case SDLK_RETURN:
				if (digit == 0)
					digit = 1;
				continuer = false;
				break;
			case SDLK_KP_ENTER:
				if (digit == 0)
					digit = 1;
				continuer = false;
				break;
			case SDLK_1:
				digit = 1;
				break;
			case SDLK_2:
				digit = 2;
				break;
			case SDLK_3:
				digit = 3;
				break;
			case SDLK_4:
				digit = 4;
				break;
			case SDLK_5:
				digit = 5;
				break;
			case SDLK_6:
				digit = 6;
				break;
			case SDLK_7:
				digit = 7;
				break;
			case SDLK_8:
				digit = 8;
				break;
			case SDLK_9:
				digit = 9;
				break;
			case SDLK_KP_1:
				digit = 1;
				break;
			case SDLK_KP_2:
				digit = 2;
				break;
			case SDLK_KP_3:
				digit = 3;
				break;
			case SDLK_KP_4:
				digit = 4;
				break;
			case SDLK_KP_5:
				digit = 5;
				break;
			case SDLK_KP_6:
				digit = 6;
				break;
			case SDLK_KP_7:
				digit = 7;
				break;
			case SDLK_KP_8:
				digit = 8;
				break;
			case SDLK_KP_9:
				digit = 9;
				break;
			}
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
				shaded, "Number of player(s)" + std::to_string(digit), { 255, 127, 127, 255 }, { 64, 64, 64, 255 }, 24, x, y, no_angle, center_x);
			SDL_RenderPresent(sysinfo.screen.renderer);
			break;
		}
	}
}

/*
* NAME : cinAlphabet
* ROLE : Recherche d'une chaine de caractères (finisant par \0) rentré par le joueur
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : std::string &name : la chaine de caractères a retourner
* INPUT  PARAMETERS : unsigned int x : coordonnée en x pour l'affichage
* INPUT  PARAMETERS : unsigned int y : coordonnée en y pour l'affichage
* OUTPUT PARAMETERS : la chaine de caractères a retourner
* RETURNED VALUE    : void
*/
void KeyboardMouse::cinAlphabet(Sysinfo& sysinfo, std::string &name, unsigned int x, unsigned int y)
{
	bool continuer = true;
	SDL_Event event;
	int SDL_EnableUNICODE(1);
	unsigned int xspace = 12;

	while (continuer)
	{
		SDL_WaitEvent(&event); // attente d'un événement (clavier, souris)
		switch (event.type) // test sur le type d'événement
		{
		case SDL_QUIT:	// permet de quitter le jeu
			SDL_Quit();
			break;
		case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				if (name.compare("") == 0)
				{
					name = "NoName" + std::to_string(sysinfo.var.s_player.nbNoNamePlayer);
					sysinfo.var.s_player.nbNoNamePlayer++;
				}
				continuer = false;
				break;
			case SDLK_BACKSPACE:
				if (name.compare("") != 0)
					name.pop_back();
				break;
			case SDLK_RETURN:
				if (name.compare("") == 0)
				{
					name = "NoName" + std::to_string(sysinfo.var.s_player.nbNoNamePlayer);
					sysinfo.var.s_player.nbNoNamePlayer++;
				}
				continuer = false;
				break;
			case SDLK_KP_ENTER:
				if (name.compare("") == 0)
				{
					name = "NoName" + std::to_string(sysinfo.var.s_player.nbNoNamePlayer);
					sysinfo.var.s_player.nbNoNamePlayer++;
				}
				continuer = false;
				break;
			case SDLK_a:
				name += 'a';
				break;
			case SDLK_b:
				name += 'b';
				break;
			case SDLK_c:
				name += 'c';
				break;
			case SDLK_d:
				name += 'd';
				break;
			case SDLK_e:
				name += 'e';
				break;
			case SDLK_f:
				name += 'f';
				break;
			case SDLK_g:
				name += 'g';
				break;
			case SDLK_h:
				name += 'h';
				break;
			case SDLK_i:
				name += 'i';
				break;
			case SDLK_j:
				name += 'j';
				break;
			case SDLK_k:
				name += 'k';
				break;
			case SDLK_l:
				name += 'l';
				break;
			case SDLK_m:
				name += 'm';
				break;
			case SDLK_n:
				name += 'n';
				break;
			case SDLK_o:
				name += 'o';
				break;
			case SDLK_p:
				name += 'p';
				break;
			case SDLK_q:
				name += 'q';
				break;
			case SDLK_r:
				name += 'r';
				break;
			case SDLK_s:
				name += 's';
				break;
			case SDLK_t:
				name += 't';
				break;
			case SDLK_u:
				name += 'u';
				break;
			case SDLK_v:
				name += 'v';
				break;
			case SDLK_w:
				name += 'w';
				break;
			case SDLK_x:
				name += 'x';
				break;
			case SDLK_y:
				name += 'y';
				break;
			case SDLK_z:
				name += 'z';
				break;
			case SDLK_1:
				name += "1";
				break;
			case SDLK_2:
				name += "2";
				break;
			case SDLK_3:
				name += "3";
				break;
			case SDLK_4:
				name += "4";
				break;
			case SDLK_5:
				name += "5";
				break;
			case SDLK_6:
				name += "6";
				break;
			case SDLK_7:
				name += "7";
				break;
			case SDLK_8:
				name += "8";
				break;
			case SDLK_9:
				name += "9";
				break;
			case SDLK_KP_1:
				name += "1";
				break;
			case SDLK_KP_2:
				name += "2";
				break;
			case SDLK_KP_3:
				name += "3";
				break;
			case SDLK_KP_4:
				name += "4";
				break;
			case SDLK_KP_5:
				name += "5";
				break;
			case SDLK_KP_6:
				name += "6";
				break;
			case SDLK_KP_7:
				name += "7";
				break;
			case SDLK_KP_8:
				name += "8";
				break;
			case SDLK_KP_9:
				name += "9";
				break;
			}
			if (name.size() > 50)
			{
				name = "par_defaut";
				IHM::logfileconsole("cinAlphabet ERROR : Name to long > 50 char");
			}
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
				shaded, name, { 255, 127, 127, 255 }, { 64, 64, 64, 255 }, 24, x + xspace, y, no_angle, center_x);
			SDL_RenderPresent(sysinfo.screen.renderer);
			break;
		}
	}
}

 
 
 /* *********************************************************
  *			END KeyboardMouse::STATIC::CIN				    *
  ********************************************************* */

 


/* *********************************************************
 *		START KeyboardMouse::STATIC::UNE TOUCHE			   *
 ********************************************************* */
 
 
/*
* NAME : cinAlphabet
* ROLE : Recherche d'une chaine de caractères (finisant par \0) rentré par le joueur
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : std::string &name : la chaine de caractères a retourner
* INPUT  PARAMETERS : unsigned int x : coordonnée en x pour l'affichage
* INPUT  PARAMETERS : unsigned int y : coordonnée en y pour l'affichage
* OUTPUT PARAMETERS : la chaine de caractères a retourner
* RETURNED VALUE    : void
*/
void KeyboardMouse::keySDLK_b(Sysinfo& sysinfo)
{
	if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
		&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
		City::createCity(sysinfo);
}

/*
* NAME : cinAlphabet
* ROLE : Recherche d'une chaine de caractères (finisant par \0) rentré par le joueur
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : std::string &name : la chaine de caractères a retourner
* INPUT  PARAMETERS : unsigned int x : coordonnée en x pour l'affichage
* INPUT  PARAMETERS : unsigned int y : coordonnée en y pour l'affichage
* OUTPUT PARAMETERS : la chaine de caractères a retourner
* RETURNED VALUE    : void
*/
void KeyboardMouse::keySDLK_i(Sysinfo& sysinfo)
{
	if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
		&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
		Unit::irrigate(sysinfo);
}


/*
* comm 0.14e : ce commentaire est commun au 9 boutons 
* NAME : keySDLK_KP_1
* ROLE : Appel la fonction dans le contexte de l'appuie sur la touche
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Appel une fonction
* RETURNED VALUE    : void
*/
void KeyboardMouse::keySDLK_KP_1(Sysinfo& sysinfo)
{
	if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove 
		&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
		Unit::tryToMove(sysinfo, -(int)(sysinfo.map.tileSize), sysinfo.map.tileSize);
}
void KeyboardMouse::keySDLK_KP_2(Sysinfo& sysinfo)
{
	if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
		&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
		Unit::tryToMove(sysinfo, 0, sysinfo.map.tileSize);
}
void KeyboardMouse::keySDLK_KP_3(Sysinfo& sysinfo) 
{
	if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
		&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
		Unit::tryToMove(sysinfo, sysinfo.map.tileSize, sysinfo.map.tileSize);
}
void KeyboardMouse::keySDLK_KP_4(Sysinfo& sysinfo)
{
	if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
		&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
		Unit::tryToMove(sysinfo, -(int)(sysinfo.map.tileSize), 0);
}
void KeyboardMouse::keySDLK_KP_5(Sysinfo& sysinfo) 
{

}
void KeyboardMouse::keySDLK_KP_6(Sysinfo& sysinfo) 
{
	if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
		&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
		Unit::tryToMove(sysinfo, sysinfo.map.tileSize, 0);
}
void KeyboardMouse::keySDLK_KP_7(Sysinfo& sysinfo) 
{
	if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
		&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
		Unit::tryToMove(sysinfo, -(int)(sysinfo.map.tileSize), -(int)(sysinfo.map.tileSize));
}
void KeyboardMouse::keySDLK_KP_8(Sysinfo& sysinfo)
{
	if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
		&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
		Unit::tryToMove(sysinfo, 0, -(int)(sysinfo.map.tileSize));
}
void KeyboardMouse::keySDLK_KP_9(Sysinfo& sysinfo) 
{
	if (sysinfo.var.statescreen == STATEmainmap && sysinfo.var.select == selectmove
		&& sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
		Unit::tryToMove(sysinfo, sysinfo.map.tileSize, -(int)(sysinfo.map.tileSize));
}


/* *********************************************************
 *			END KeyboardMouse::STATIC::UNE TOUCHE		   *
 ********************************************************* */


 

/* *********************************************************
 *			START KeyboardMouse::STATIC::SOURIS		       *
 ********************************************************* */

 
/*
* NAME : mouse
* ROLE : Dispatch entre clique droit ou clique gauche
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : SDL_Event : l'évenement du clique
* OUTPUT PARAMETERS : choix du clique
* RETURNED VALUE    : void
*/
void KeyboardMouse::mouse(Sysinfo& sysinfo, SDL_Event event)
{
	/*

		Handle Mouse Event
		BUTTON_LEFT
		BUTTON_RIGHT

	*/

	if (event.button.button == SDL_BUTTON_LEFT)
		cliqueGauche(sysinfo, event);
	else if (event.button.button == SDL_BUTTON_RIGHT && sysinfo.var.statescreen == STATEmainmap)
		cliqueDroit(sysinfo, event);

}

/*
* NAME : cliqueGauche
* ROLE : Recherche de la zone ou le clique à lieu
* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : SDL_Event : l'évenement du clique
* OUTPUT PARAMETERS : la chaine de caractères a retourner
* RETURNED VALUE    : void
*/
void KeyboardMouse::cliqueGauche(Sysinfo& sysinfo, SDL_Event event) 
{
	// inspect citie
	if (sysinfo.var.statescreen == STATEmainmap)
	{
		if (sysinfo.var.s_player.selectplayer > -1) 
		{
			if (sysinfo.var.select == selectinspect && sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabCity().size() != 0) 
			{
				sysinfo.var.mouse.SETmouse_x((
					(unsigned int)ceil(event.button.x / sysinfo.map.tileSize) * sysinfo.map.tileSize)
					+ sysinfo.map.screenOffsetXIndexMin * sysinfo.map.tileSize);
				sysinfo.var.mouse.SETmouse_y((
					(unsigned int)ceil(event.button.y / sysinfo.map.tileSize) * sysinfo.map.tileSize)
					+ sysinfo.map.screenOffsetYIndexMin * sysinfo.map.tileSize);
				City::searchCityTile(sysinfo);
			}
		}
	}
	// recherche du bouton par comparaison de string et des positions x et y du clic

	unsigned int index = 0;

	switch (sysinfo.var.statescreen)
	{
	case STATEmainmap:

		if (sysinfo.allButton.mainMap[searchIndex("screen Titre", sysinfo.allButton.mainMap)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			SaveReload::savemaps(sysinfo);
			SaveReload::savePlayer(sysinfo);
			resetButtonOn(sysinfo);
			IHM::logfileconsole("__________________________");
			IHM::titleScreen(sysinfo);
			return;
		}
		
		if (sysinfo.allButton.mainMap[index = searchIndex("Create Unit", sysinfo.allButton.mainMap)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.mainMap[index]->changeOn();
			if (sysinfo.var.select != selectcreate)
				sysinfo.var.select = selectcreate;
			else
				sysinfo.var.select = selectnothing;

			resetButtonOn(sysinfo);
			return;
		}
		if (sysinfo.allButton.mainMap[index = searchIndex("Move Unit", sysinfo.allButton.mainMap)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.mainMap[index]->changeOn();
			if (sysinfo.var.select != selectmove)
				sysinfo.var.select = selectmove;
			else
			{
				sysinfo.var.s_player.selectunit = -1;
				sysinfo.var.select = selectnothing;
			}
			resetButtonOn(sysinfo);
			return;
		}
		if (sysinfo.allButton.mainMap[index = searchIndex("Inspect", sysinfo.allButton.mainMap)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.mainMap[index]->changeOn();
			if (sysinfo.var.select != selectinspect)
				sysinfo.var.select = selectinspect;
			else
			{
					sysinfo.var.s_player.selectunit = -1;
				sysinfo.var.select = selectnothing;
			}
			resetButtonOn(sysinfo);
			return;
		}
		if (sysinfo.allButton.mainMap[index = searchIndex("Next Turn", sysinfo.allButton.mainMap)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			GamePlay::nextTurn(sysinfo);
			resetButtonOn(sysinfo);
			return;
		}
		if (sysinfo.allButton.mainMap[index = searchIndex("Delete Unit", sysinfo.allButton.mainMap)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.mainMap[index]->SETon(!sysinfo.allButton.mainMap[index]->GETon());
			resetButtonOn(sysinfo);
			return;
		}


		for (unsigned int i = 0; i < sysinfo.allButton.playerIndex.size(); i++)
		{
			// player select
			if (sysinfo.allButton.player[index = searchIndex(sysinfo.tabplayer[i]->GETname(), sysinfo.allButton.player)]
				->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
			{
				sysinfo.allButton.player[index]->changeOn();
				if (sysinfo.var.s_player.selectplayer != (int)i)
					sysinfo.var.s_player.selectplayer = (int)i;
				else
					sysinfo.var.s_player.selectplayer = -1;
				IHM::logfileconsole("sysinfo.var.selectplayer = " + sysinfo.tabplayer[i]->GETname());
				resetButtonPlayerOn(sysinfo);
				return;
			}
		}
		
		break;
	case STATEtitleScreen:
		
		if (sysinfo.allButton.titleScreen[searchIndex("New Game", sysinfo.allButton.titleScreen)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			GamePlay::newGame(sysinfo);
			return;
		}
		if (sysinfo.allButton.titleScreen[searchIndex("Reload", sysinfo.allButton.titleScreen)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			IHM::reloadScreen(sysinfo);
			return;
		}
		if (sysinfo.allButton.titleScreen[searchIndex("Option", sysinfo.allButton.titleScreen)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			//clearSave(sysinfo);
			return;
		}
		if (sysinfo.allButton.titleScreen[searchIndex("Quit", sysinfo.allButton.titleScreen)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.var.continuer = false;
			return;
		}
		break;
	case STATEreload:

		if (sysinfo.allButton.reload[searchIndex("Back", sysinfo.allButton.reload)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y)) 
		{
			IHM::titleScreen(sysinfo);
			return;
		}
		if (sysinfo.allButton.reload[index = searchIndex("Remove all saves", sysinfo.allButton.reload)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.reload[index]->changeOn();
			SaveReload::clearSave(sysinfo);
			IHM::reloadScreen(sysinfo);
			return;
		}
		if (sysinfo.allButton.reload[searchIndex("Load", sysinfo.allButton.reload)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			SaveReload::reload(sysinfo);
			return;
		}
		if (sysinfo.allButton.reload[searchIndex("Remove", sysinfo.allButton.reload)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			SaveReload::removeSave(sysinfo);
			IHM::reloadScreen(sysinfo);
			return;
		}

		for (unsigned int j = 0; j < sysinfo.var.save.GETnbSave(); j++)
		{
			if (sysinfo.allButton.reload[index = searchIndex("Save : " + std::to_string(sysinfo.var.save.GETtabSave()[j]), sysinfo.allButton.reload)]
				->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
			{
				sysinfo.allButton.reload[index]->changeOn();
				sysinfo.var.save.SETcurrentSave(sysinfo.var.save.GETtabSave()[j]);
				sysinfo.file.SaveMaps = "save/" + std::to_string(sysinfo.var.save.GETtabSave()[j]) + "/SaveMaps.txt";
				sysinfo.file.SavePlayer = "save/" + std::to_string(sysinfo.var.save.GETtabSave()[j]) + "/SavePlayer.txt";
				IHM::reloadScreen(sysinfo);
				return;
			}
		}
		break;
	case STATEcitiemap:
		if (sysinfo.allButton.citieMap[searchIndex("Map", sysinfo.allButton.citieMap)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.var.s_player.selectCitie = -1;
			sysinfo.var.statescreen = STATEmainmap;
			sysinfo.var.select = selectnothing;
			resetButtonCitieMap(sysinfo);
			return;
		}
		if (sysinfo.allButton.citieMap[index = searchIndex("Build", sysinfo.allButton.citieMap)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.citieMap[index]->changeOn();
			if (sysinfo.var.select != selectcreate)
				sysinfo.var.select = selectcreate;
			else
				sysinfo.var.select = selectnothing;
			resetButtonCitieMap(sysinfo);
			return;
		}
		if (sysinfo.allButton.citieMap[index = searchIndex("Place Citizen", sysinfo.allButton.citieMap)]
			->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
		{
			sysinfo.allButton.citieMap[index]->changeOn();
			if (sysinfo.var.select != selectmoveCitizen)
				sysinfo.var.select = selectmoveCitizen;
			else
				sysinfo.var.select = selectnothing;
			resetButtonCitieMap(sysinfo);
			return;
		}


		if (sysinfo.var.select == selectcreate)
		{
			for (unsigned int i = 0; i < sysinfo.var.s_player.unitNameMaxToCreate; i++)
			{
				if (sysinfo.allButton.citieMap[searchIndex(sysinfo.var.s_player.tabUnit_Struct[i].name, sysinfo.allButton.citieMap)]
					->searchButtonTexte(sysinfo.var.statescreen, event.button.x, event.button.y))
				{
					sysinfo.var.s_player.toBuild = sysinfo.var.s_player.tabUnit_Struct[i].name;
					sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->addUnit(sysinfo.var.s_player.tabUnit_Struct[i].name,
						sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheCity(sysinfo.var.s_player.selectCitie)->GETx(),
						sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheCity(sysinfo.var.s_player.selectCitie)->GETy(),
						sysinfo.var.s_player.tabUnit_Struct[i].life, sysinfo.var.s_player.tabUnit_Struct[i].atq,
						sysinfo.var.s_player.tabUnit_Struct[i].def, sysinfo.var.s_player.tabUnit_Struct[i].movement,
						sysinfo.var.s_player.tabUnit_Struct[i].level);

					sysinfo.var.select = selectnothing;
					break;
				}
			}
		}
		break;
	}
}

/*
* NAME : cliqueDroit
* ROLE : Recherche de la zone ou le clique à lieu
* ROLE : En fonction de la zone touchée une action peut avoir lieu (boutons)
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : SDL_Event : l'évenement du clique
* OUTPUT PARAMETERS : la chaine de caractères a retourner
* RETURNED VALUE    : void
*/
void KeyboardMouse::cliqueDroit(Sysinfo& sysinfo, SDL_Event event)
{
	unsigned int selectunit = 0;
	sysinfo.var.mouse.SETmouse_x((unsigned int)ceil(event.button.x / sysinfo.map.tileSize) * sysinfo.map.tileSize);
	sysinfo.var.mouse.SETmouse_y((unsigned int)ceil(event.button.y / sysinfo.map.tileSize) * sysinfo.map.tileSize);
	if (sysinfo.var.s_player.selectplayer > -1)
	{
		switch (sysinfo.var.statescreen)
		{
		case STATEmainmap:
			switch (sysinfo.var.select) 
			{
			case selectcreate:
				for (unsigned int p = 0; p < sysinfo.var.s_player.unitNameMaxToCreate; p++) {
					if (sysinfo.var.s_player.unitNameToCreate.compare(sysinfo.var.s_player.tabUnit_Struct[p].name) == 0)
					{
						selectunit = p;
						break;
					}
				}
				sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->addUnit(sysinfo.var.s_player.unitNameToCreate,
					sysinfo.var.mouse.GETmouse_x(), sysinfo.var.mouse.GETmouse_y(),
					sysinfo.var.s_player.tabUnit_Struct[selectunit].life, sysinfo.var.s_player.tabUnit_Struct[selectunit].atq,
					sysinfo.var.s_player.tabUnit_Struct[selectunit].def, sysinfo.var.s_player.tabUnit_Struct[selectunit].movement,
					sysinfo.var.s_player.tabUnit_Struct[selectunit].level);
				break;
			case selectmove:
				if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabUnit().size() != 0)
				{
					Unit::searchUnitTile(sysinfo);
					IHM::logfileconsole("Unit select to move n:" + std::to_string(sysinfo.var.s_player.selectunit));
				}
				break;
			case selectinspect:
				if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabUnit().size() != 0) 
				{
					Unit::searchUnitTile(sysinfo);
					IHM::logfileconsole("Unit select to Inspect n:" + std::to_string(sysinfo.var.s_player.selectunit));
				}
				break;
			}
			break;
		}
	}
}

/*
* NAME : wheel
* ROLE : Recherche l'incrémentation ou décrémentation du contexte
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : int& wheel : l'évenement de scroll de la souris
* OUTPUT PARAMETERS : une action suivant l'incrémentation ou décrémentation du contexte
* RETURNED VALUE    : void
*/
void KeyboardMouse::wheel(Sysinfo& sysinfo, int& wheel)
{
	if (sysinfo.var.select == selectcreate)
	{
		if (wheel == 1)
		{
			if (sysinfo.var.s_player.unitToCreate > 0)
				sysinfo.var.s_player.unitToCreate--;
		}
		else if (wheel == -1) 
		{
			if (sysinfo.var.s_player.unitToCreate < sysinfo.var.s_player.unitNameMaxToCreate - 1)
				sysinfo.var.s_player.unitToCreate++;
		}
		Unit::searchUnit(sysinfo);
	}
	/*
	else if (sysinfo.var.statescreen == STATEreload)
	{
		if (wheel == 1)
		{
			if (sysinfo.var.currentSave > 0)
				sysinfo.var.currentSave--;
		}
		else if (wheel == -1)
		{
			if (sysinfo.var.currentSave < sysinfo.var.nbSave)
				sysinfo.var.currentSave++;
		}
	}
	*/
}

/*
* NAME : resetButtonOn
* ROLE : reset de l'affichage On des boutons
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : reset de l'affichage On des boutons
* RETURNED VALUE    : void
*/
void KeyboardMouse::resetButtonOn(Sysinfo& sysinfo)
{
	for (unsigned int i = 0; i < sysinfo.allButton.mainMapIndex.size(); i++)
	{
		sysinfo.allButton.mainMap[sysinfo.allButton.mainMapIndex[i]]
			->resetOnstateScreen(sysinfo.var.select, selectnothing);
		sysinfo.allButton.mainMap[sysinfo.allButton.mainMapIndex[i]]
			->resetOnPlayer(sysinfo.var.s_player.selectplayer, sysinfo.var.s_player.tabPlayerName);
	}
}

/*
* NAME : resetButtonPlayerOn
* ROLE : reset de l'affichage On des boutons player
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : reset de l'affichage On des boutons player
* RETURNED VALUE    : void
*/
void KeyboardMouse::resetButtonPlayerOn(Sysinfo& sysinfo)
{
	for (unsigned int i = 0; i < sysinfo.allButton.playerIndex.size(); i++)
	{
		sysinfo.allButton.player[sysinfo.allButton.playerIndex[i]]
			->resetOnstateScreen(sysinfo.var.select, selectnothing);
		sysinfo.allButton.player[sysinfo.allButton.playerIndex[i]]
			->resetOnPlayer(sysinfo.var.s_player.selectplayer, sysinfo.var.s_player.tabPlayerName);
	}
}

/*
* NAME : resetButtonCitieMap
* ROLE : reset de l'affichage On des boutons citieMap
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : reset de l'affichage On des boutons citieMap
* RETURNED VALUE    : void
*/
void KeyboardMouse::resetButtonCitieMap(Sysinfo& sysinfo)
{
	for (unsigned int i = 0; i < sysinfo.allButton.citieMapIndex.size(); i++)
	{
		sysinfo.allButton.citieMap[sysinfo.allButton.citieMapIndex[i]]->resetOnstateScreen(sysinfo.var.select, selectnothing);
	}
}


/* *********************************************************
 *			END KeyboardMouse::STATIC::SOURIS			   *
 ********************************************************* */

 

/* *********************************************************
 *				START KeyboardMouse::METHODS			   *
 ********************************************************* */
 

KeyboardMouse::KeyboardMouse(): _mouse_x(0), _mouse_y(0), _ywheel(0), _xwheel(0)
{
}


/* *********************************************************
 *				END KeyboardMouse::METHODS				   *
 ********************************************************* */

/*
*	End Of File : KeyboardMouse.cpp
*/