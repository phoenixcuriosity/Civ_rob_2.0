/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.17
	file version : 1.16

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

#include "IHM.h"
#include "GamePlay.h"
#include "SaveReload.h"
#include "LoadConfig.h"
#include "End.h"


/* *********************************************************
 *					Variable Globale					   *
 ********************************************************* */

static std::ofstream logger;
static Sysinfo* ptrSysinfo;

void IHM::initPtrSysinfo(Sysinfo& sysinfo)
{
	ptrSysinfo = &sysinfo;
	End::initPtrSysinfoLogger(sysinfo, logger);
}

/* *********************************************************
 *				START INITIALISATION					   *
 ********************************************************* */


/*
* NAME : initTile
* ROLE : Initialisation des cases de la map en fonction de sa taille
* INPUT  PARAMETERS : struct Map& : données générale de la map : taille
* OUTPUT PARAMETERS : Initialisation de map.screen et map.maps
* RETURNED VALUE    : void
*/
void IHM::initTile(Map& map)
{
	Tile blankTile;
	std::vector<Tile> blank;
	for (unsigned int i(0); i < map.mapSize / map.tileSize; i++)
	{
		map.maps.push_back(blank);
		for (unsigned int j(0); j < map.mapSize / map.tileSize; j++) 
		{
			map.maps[i].push_back(blankTile);
		}
	}
}

/*
* NAME : initFile
* ROLE : Initialisation des fichiers : log
* INPUT  PARAMETERS : struct File& : nom des fichiers
* OUTPUT PARAMETERS : Initialisation de log.txt
* RETURNED VALUE    : void
*/
void IHM::initFile(File& file)
{
	logger.open(file.log, std::ofstream::out | std::ofstream::trunc);
	if (!logger.is_open())
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		/* N/A */
	}
}


/*
* NAME : logfileconsole
* ROLE : Transmission du message sur la console et dans le fichier log.txt
* INPUT  PARAMETERS : const std::string msg : message
* OUTPUT PARAMETERS : message dans la console et le log.txt
* RETURNED VALUE    : void
*/
void IHM::logfileconsole(const std::string msg)
{
	time_t now(time(0));
	struct tm  tstruct;
	char  buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%F %X", &tstruct);

	std::cout << std::endl << buf << "      " << msg;
	logger << std::endl << buf << "      " << msg;
}


/*
* NAME : logSDLError
* ROLE : SDL erreur
* INPUT  PARAMETERS : std::ostream &os, const std::string &msg
* OUTPUT PARAMETERS : message d'erreur dans la console
* RETURNED VALUE    : void
*/
void IHM::logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
	logger << msg << " error: " << SDL_GetError() << std::endl;
}





/*
* NAME : initSDL
* ROLE : Initialisation de la SDL fenetre et renderer ainsi que le tableau de police de font
* INPUT  PARAMETERS : SDL_Window*& : pointeur sur la fenetre de la SDL
* INPUT  PARAMETERS : SDL_Renderer*& : pointeur sur le Renderer de la SDL
* INPUT  PARAMETERS : TTF_Font*[] : pointeur sur le tableau de police de font
* OUTPUT PARAMETERS : message dans la console et le log.txt
* RETURNED VALUE    : bool : true = pas de d'erreur lors de l'initialisation de la SDL
*/
bool IHM::initSDL(Screen& screen, TTF_Font* font[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << std::endl << "SDL could not initialize! SDL_Error: " << SDL_GetError();
		return false;
	}
	else
	{
		

		screen.window = SDL_CreateWindow("Civ_Rob_2.0",
			0, 0,
			screen.screenWidth, screen.screenHeight,
			SDL_WINDOW_OPENGL);

		//	SDL_WINDOW_FULLSCREEN_DESKTOP or SDL_WINDOW_FULLSCREEN
		if (screen.window == nullptr)
		{
			logSDLError(std::cout, "CreateWindow");
			SDL_Quit();
			return false;
		}
		else
		{
			logfileconsole("CreateWindow Success");
		}
			
		screen.renderer = SDL_CreateRenderer(screen.window, -1, SDL_RENDERER_ACCELERATED);
		//| SDL_RENDERER_PRESENTVSYNC
		if (screen.renderer == nullptr)
		{
			logSDLError(std::cout, "CreateRenderer");
			SDL_DestroyWindow(screen.window);
			SDL_Quit();
			return false;
		}
		else
		{
			logfileconsole("[INFO]___: CreateRenderer Success");
		}	

		if (TTF_Init() != 0)
		{
			logSDLError(std::cout, "TTF_Init");
			SDL_DestroyRenderer(screen.renderer);
			SDL_DestroyWindow(screen.window);
			SDL_Quit();
			return false;
		}
		else
		{
			logfileconsole("[INFO]___: TTF_Init Success");
		}

		for (Uint8 i(1); i < MAX_FONT; i++)
		{
			font[i] = TTF_OpenFont(fontFile.c_str(), i);
		}	

		logfileconsole("[INFO]___: SDL_Init Success");
		return true;
	}
}

/* *********************************************************
 *					END INITIALISATION					   *
 ********************************************************* */




/* *********************************************************
 *					START IN-GAME						   *
 ********************************************************* */



/*
* NAME : eventSDL
* ROLE : Recherche infini des évenements d'entré de type SDL_event : souris, clavier
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : évenements d'entré utilisateur
* RETURNED VALUE    : void
*/
void IHM::eventSDL(Sysinfo& sysinfo)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:	// permet de quitter le jeu
			sysinfo.var.continuer = 0;
			break;
		case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
			switch (event.key.keysym.sym)
			{
			case SDLK_F5:
				GamePlay::groundGen(sysinfo);
				break;
			case SDLK_F6:
				End::deletePlayer(sysinfo.tabplayer, "player");
				for (unsigned int i(0); i < 4; i++)
				{
					sysinfo.tabplayer.push_back(new Player("NoName" + std::to_string(i)));
				}
				GamePlay::newGameSettlerSpawn(sysinfo);
				break;
			case SDLK_ESCAPE:
				sysinfo.var.continuer = 0;
				break;
			case SDLK_UP:
				if (sysinfo.map.screenOffsetYIndexMin > 0)
				{
					sysinfo.map.screenOffsetYIndexMin--;
					sysinfo.map.screenOffsetYIndexMax--;
				}
				else
				{
					/* N/A */
				}
				break;
			case SDLK_LEFT:
				if (sysinfo.map.screenOffsetXIndexMin > 0)
				{
					sysinfo.map.screenOffsetXIndexMin--;
					sysinfo.map.screenOffsetXIndexMax--;
				}
				else
				{
					/* N/A */
				}
				break;
			case SDLK_DOWN:
				if (sysinfo.map.screenOffsetYIndexMax < sysinfo.map.maps[0].size())
				{
					sysinfo.map.screenOffsetYIndexMin++;
					sysinfo.map.screenOffsetYIndexMax++;
				}
				else
				{
					/* N/A */
				}
				break;
			case SDLK_RIGHT:
				if (sysinfo.map.screenOffsetXIndexMax < sysinfo.map.maps.size())
				{
					sysinfo.map.screenOffsetXIndexMin++;
					sysinfo.map.screenOffsetXIndexMax++;
				}
				else
				{
					/* N/A */
				}
				break;
			case SDLK_SPACE:
				GamePlay::nextTurn(sysinfo);
				break;
			case SDLK_b:
				KeyboardMouse::keySDLK_b(sysinfo);
				break;
			case SDLK_i:
				KeyboardMouse::keySDLK_i(sysinfo);
				break;
			case SDLK_KP_1:
				KeyboardMouse::keySDLK_KP_1(sysinfo);
				break;
			case SDLK_KP_2:
				KeyboardMouse::keySDLK_KP_2(sysinfo);
				break;
			case SDLK_KP_3:
				KeyboardMouse::keySDLK_KP_3(sysinfo);
				break;
			case SDLK_KP_4:
				KeyboardMouse::keySDLK_KP_4(sysinfo);
				break;
			case SDLK_KP_5:
				KeyboardMouse::keySDLK_KP_5(sysinfo);
				break;
			case SDLK_KP_6:
				KeyboardMouse::keySDLK_KP_6(sysinfo);
				break;
			case SDLK_KP_7:
				KeyboardMouse::keySDLK_KP_7(sysinfo);
				break;
			case SDLK_KP_8:
				KeyboardMouse::keySDLK_KP_8(sysinfo);
				break;
			case SDLK_KP_9:
				KeyboardMouse::keySDLK_KP_9(sysinfo);
				break;
			default:
				/* N/A */
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN: // test sur le type d'événement click souris (enfoncé)
			KeyboardMouse::mouse(sysinfo, event);
			break;
		case SDL_MOUSEWHEEL:
			KeyboardMouse::wheel(sysinfo, event.wheel.y);
			break;
		default:
			/* N/A */
			break;
		}

	}
}


/*
* NAME : titleScreen
* ROLE : Desciption de la fenetre "titleScreen"
* ROLE : fonctionnement selon l'état : enum State_Type = STATEtitleScreen
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Ouverture de la fenetre "titleScreen"
* RETURNED VALUE    : void
*/
void IHM::titleScreen(Sysinfo& sysinfo)
{
	logfileconsole("[INFO]___: [START] : titleScreen");

	/* title screen init */
	sysinfo.var.statescreen = STATEtitleScreen;
	sysinfo.var.select = selectnothing;

	// applique une surface de la taille de l'écran de couleur noir
	SDL_RenderClear(sysinfo.screen.renderer);


	for (const auto& n : sysinfo.allTextures.titleScreen)
	{
		n.second->renderTextureTestStates(sysinfo.var.statescreen, sysinfo.var.select);
	}

	for (const auto& n : sysinfo.allTextes.titleScreen)
	{
		n.second->renderTextureTestStates(sysinfo.var.statescreen, sysinfo.var.select);
	}

	for (const auto& n : sysinfo.allButton.titleScreen)
	{
		n.second->renderButtonTexte(sysinfo.var.statescreen);
	}

	/* ### Don't put code below here ### */

	SDL_RenderPresent(sysinfo.screen.renderer);
	logfileconsole("[INFO]___: [END] : titleScreen");
}


/*
 * NAME : reloadScreen
 * ROLE : Desciption de la fenetre "reloadScreen"
 * ROLE : fonctionnement selon l'état : enum State_Type = STATEreload
 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
 * OUTPUT PARAMETERS : Ouverture de la fenetre "reloadScreen"
 * RETURNED VALUE    : void
 */
void IHM::reloadScreen(Sysinfo& sysinfo)
{
	logfileconsole("[INFO]___: [START] : reloadScreen");
	sysinfo.var.statescreen = STATEreload;
	SDL_RenderClear(sysinfo.screen.renderer);

	for (const auto& n : sysinfo.allButton.reload)
	{
		n.second->renderButtonTexte(sysinfo.var.statescreen);
	}

	/* ### Don't put code below here ### */

	SDL_RenderPresent(sysinfo.screen.renderer);
	logfileconsole("[INFO]___: [END] : reloadScreen");
}


/*
 * NAME : alwaysrender
 * ROLE : Tous les 1/SCREEN_REFRESH_RATE cette fonction permet ...
 * ROLE : ... la désciption de la fenetre "STATEmainmap" ou "STATEcitiemap"
 * ROLE : fonctionnement selon l'état : enum State_Type = STATEmainmap ou STATEcitiemap
 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
 * OUTPUT PARAMETERS : Ouverture de la fenetre "STATEmainmap" ou "STATEcitiemap"
 * RETURNED VALUE    : void
 */
void IHM::alwaysrender(Sysinfo& sysinfo)
{
	/*
	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	*/

	switch (sysinfo.var.statescreen)
	{
	case STATEmainmap:
		SDL_RenderClear(sysinfo.screen.renderer);

		/* *********************************************************
		 *					START background					   *
		 ********************************************************* */

		afficherSupertiles(sysinfo);

		// affiche la texture grise de la toolbar
		for (unsigned int i(0); i < sysinfo.map.toolBarSize; i++)
		{
			for (unsigned int j(0); j < sysinfo.screen.screenHeight / sysinfo.map.tileSize; j++)
			{
				sysinfo.allTextures.ground["toolbar.bmp"]->render(i * sysinfo.map.tileSize, j * sysinfo.map.tileSize);
			}	
		}

		/* *********************************************************
		 *					END background						   *
		 ********************************************************* */


		/* *********************************************************
		 *					START Texte							   *
		 ********************************************************* */

		for (const auto& n : sysinfo.allTextes.mainMap)
		{
			n.second->renderTextureTestStates(sysinfo.var.statescreen, sysinfo.var.select);
		}

		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
			blended, std::to_string(sysinfo.var.nbturn), { 0, 64, 255, 255 }, NoColor, 24, 80, 850, no_angle);

		/* *********************************************************
		 *					END Texte							   *		
		 ********************************************************* */


		/* *********************************************************
		 *					START Button						   *
		 ********************************************************* */

		for (const auto& n : sysinfo.allButton.mainMap)
		{
			n.second->renderButtonTexte(sysinfo.var.statescreen);
		}

		for (const auto& n : sysinfo.allButton.player)
		{
			n.second->renderButtonTexte(sysinfo.var.statescreen);
		}

		/* *********************************************************
		 *					END Button							   *
		 ********************************************************* */

		
		/* *********************************************************
		 *					START UnitInfo						   *
		 ********************************************************* */

		switch (sysinfo.var.select)
		{
		case selectcreate:
			// affiche les unités pour rendre l'unité à créer
			if (sysinfo.var.s_player.unitNameToCreate.compare("") != 0)
			{
				sysinfo.allTextures.unit[sysinfo.var.s_player.unitNameToCreate]->render(100, 432);
			}
			else
			{
				/* N/A */
			}
			break;
		case selectmove:
			if (sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
			{
				sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(sysinfo.var.s_player.selectunit)->cmpblit();
			}
			else
			{
				/* N/A */
			}
			break;
		case selectinspect:
			// affiche les stats de l'unité inspecté
			if (sysinfo.var.s_player.selectplayer != -1 && sysinfo.var.s_player.selectunit != -1)
			{
				sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheUnit(sysinfo.var.s_player.selectunit)->afficherstat(sysinfo);
			}
			else
			{
				/* N/A */
			}
			break;
		}

		/* *********************************************************
		 *					END UnitInfo						   * 
		 ********************************************************* */



		/* *********************************************************
		 *			START Affichage Unit/Citie/Player			   *
		 ********************************************************* */

		if (sysinfo.tabplayer.size() != 0)
		{
			for (unsigned int i(0); i < sysinfo.tabplayer.size(); i++) 
			{
				if (sysinfo.tabplayer[i]->GETtabUnit().size() != 0)
				{
					for (unsigned int j(0); j < sysinfo.tabplayer[i]->GETtabUnit().size(); j++)
					{
						// affiche pour chaque joueurs les unités existantes (avec les stats)
						sysinfo.tabplayer[i]->GETtheUnit(j)->afficher(sysinfo, i);
					}
				}
				else
				{
					/* N/A */
				}

				if (sysinfo.tabplayer[i]->GETtabCity().size() != 0)
				{
					for (unsigned int j(0); j < sysinfo.tabplayer[i]->GETtabCity().size(); j++)
					{
						// affiche pour chaque joueurs les cités existantes
						sysinfo.tabplayer[i]->GETtheCity(j)->afficher(sysinfo);
					}
				}
				else
				{
					/* N/A */
				}
			}
		}
		else
		{
			/* N/A */
		}

		/* *********************************************************
		 *			END Affichage Unit/Citie/Player				   *
		 ********************************************************* */


		break;
	case STATEcitiemap:

		/* *********************************************************
		 *				START Affichage citieMap				   *
		 ********************************************************* */

		if (sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabCity().size() > 0)
		{
			if (sysinfo.var.s_player.selectCitie != -1)
			{
				if (sysinfo.var.s_player.selectCitie < (int)sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabCity().size())
				{
					citiemap(sysinfo);
				}
				else
				{
					/* N/A */
				}
			}
			else
			{
				/* N/A */
			}
		}
		else
		{
			/* N/A */
		}

		/* *********************************************************
		 *				END Affichage citieMap					   *
		 ********************************************************* */


		break;
	default:
		/* N/A */
		break;
	}
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextures.font,
		blended, std::to_string(sysinfo.screen.avgFPS), { 0, 64, 255, 255 }, NoColor, 24, sysinfo.screen.screenWidth / 2, 50, no_angle, center_x);

	/* ### Don't put code below here ### */

	SDL_RenderPresent(sysinfo.screen.renderer);
	/*
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << std::endl << "temps d'execution de alwaysrender : " << std::setprecision(10) << elapsed_seconds.count();
	*/
}


/*
 * NAME : afficherSupertiles
 * ROLE : Affichage de la map (tiles, spec, appartenance) aux dimensions map.screen
 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
 * OUTPUT PARAMETERS : Affichage de la map sur la fenetre "mainMap"
 * RETURNED VALUE    : void
 */
void IHM::afficherSupertiles(Sysinfo& sysinfo)
{
	//clock_t t1, t2;
	//t1 = clock();
	
	unsigned int x(0), y(0);

	for (unsigned int m(sysinfo.map.screenOffsetXIndexMin); m < sysinfo.map.screenOffsetXIndexMax; m++)
	{
		for (unsigned int n(sysinfo.map.screenOffsetYIndexMin); n < sysinfo.map.screenOffsetYIndexMax; n++)
		{
			x = sysinfo.map.maps[m][n].tile_x - sysinfo.map.screenOffsetXIndexMin * sysinfo.map.tileSize;
			y = sysinfo.map.maps[m][n].tile_y - sysinfo.map.screenOffsetYIndexMin * sysinfo.map.tileSize;

			switch (sysinfo.map.maps[m][n].tile_ground)
			{
			case grass:
				sysinfo.allTextures.ground["grass.bmp"]->render(x, y);
				break;
			case water:
				sysinfo.allTextures.ground["water.bmp"]->render(x, y);
				break;
			case deepwater:
				sysinfo.allTextures.ground["deepwater.bmp"]->render(x, y);
				break;
			default:
				throw("afficherSupertiles : tile_ground == NoGround");
				break;
			}

			if (sysinfo.map.maps[m][n].tile_spec > 0)
			{
				sysinfo.allTextures.groundSpec[sysinfo.map.maps[m][n].tile_stringspec]->render(x, y);
			}
			else
			{
				/* N/A */
			}

			if (sysinfo.map.maps[m][n].appartenance != -1)
			{
				sysinfo.allTextures.colorapptile["ColorPlayertile" + std::to_string(sysinfo.map.maps[m][n].appartenance) + ".bmp"]->render(x, y);
			}
			else
			{
				/* N/A */
			}
		}
	}
	//t2 = clock();
	//std::cout << std::endl << "temps d'execution de alwaysrender : " + std::to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
	
}


/*
 * NAME : citiemap
 * ROLE : Affichage de la fenetre citiemap
 * ROLE : fonctionnement selon l'état : enum State_Type = STATEcitiemap
 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
 * OUTPUT PARAMETERS :  Affichage de la map sur la fenetre "citieMap"
 * RETURNED VALUE    : void
 */
void IHM::citiemap(Sysinfo& sysinfo)
{
	SDL_RenderClear(sysinfo.screen.renderer);
	
	/* *********************************************************
	 *					START Button						   *				
	 ********************************************************* */
	
	sysinfo.allButton.citieMap["Map"]->renderButtonTexte(sysinfo.var.statescreen);
	sysinfo.allButton.citieMap["Build"]->renderButtonTexte(sysinfo.var.statescreen);
	sysinfo.allButton.citieMap["Food"]->renderButtonTexte(sysinfo.var.statescreen);
	sysinfo.allButton.citieMap["Place Citizen"]->renderButtonTexte(sysinfo.var.statescreen);


	/* *********************************************************
	 *					END Button							   *
	 ********************************************************* */

	/* *********************************************************
	 *			 START select = selectcreate				   *
	 ********************************************************* */

	std::string buildName("");
	unsigned int initspace(96), space(32);
	if (sysinfo.var.select == selectcreate)
	{
		initspace = 96;
		for (unsigned int j(0); j < 10; j++)
		{
			if (sysinfo.var.s_player.unitToCreate + j < sysinfo.var.s_player.tabUnit_Struct.size())
			{
				buildName = sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].name;
			}	
			else
			{
				break;
			}		

			sysinfo.allButton.citieMap[buildName]
				->renderButtonTexte(sysinfo.var.statescreen, sysinfo.screen.screenWidth / 2, initspace += space);
			sysinfo.allTextures.unit[buildName]
				->render((sysinfo.screen.screenWidth / 2) - 50, initspace);
			sysinfo.allTextes.citieMap[
				"life:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].life) +
				"/atq:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].atq) +
				"/def:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].def) +
				"/move:" + std::to_string(sysinfo.var.s_player.tabUnit_Struct[sysinfo.var.s_player.unitToCreate + j].movement)]
				->render((sysinfo.screen.screenWidth / 2) + 200, initspace);
		}

		sysinfo.allTextes.citieMap["Scroll up or down"]->render();
		sysinfo.allTextes.citieMap["Left click to Select"]->render();
		sysinfo.allTextes.citieMap["create : "]->render();
		sysinfo.allTextes.citieMap["selectcreate"]->render();
	}
	else
	{
		/* N/A */
	}

	/* *********************************************************
	 *			 END select = selectcreate					   *
	 ********************************************************* */

	sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtheCity(sysinfo.var.s_player.selectCitie)->affichercitiemap(sysinfo);

}


/*
 * NAME : countFrame
 * ROLE : Compteur de frames durant le programme
 * ROLE : Début : à la fin de la fonction newGame(...)
 * INPUT  PARAMETERS : Screen& screen : données concernant la fenetre SDL
 * OUTPUT PARAMETERS : Incrémentation du nombre de frames comptées
 * RETURNED VALUE    : void
 */
void IHM::countFrame(Screen& screen)
{
	if (screen.enableFPS)
	{
		screen.avgFPS = (int)ceil(screen.countedFrames / (screen.fpsTimer.getTicks() / 1000.f));
		if (screen.avgFPS > 20000)
		{
			screen.avgFPS = 0;
		}	
		else
		{
			/* N/A */
		}
		++screen.countedFrames;
	}
	else
	{
		/* N/A */
	}
}


/* *********************************************************
 *						END IN-GAME						   *
 ********************************************************* */

/*
*	End Of File : IHM.cpp
*/