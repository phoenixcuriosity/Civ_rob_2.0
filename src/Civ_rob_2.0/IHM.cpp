/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.22.1.0
	file version : 1.31

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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "IHM.h"

#include "LoadConfig.h"
#include "End.h"
#include "civ_lib.h"
#include "Utility.h"

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

/* *********************************************************
 *					START IN-GAME						   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : titleScreen																   */
/* ROLE : Desciption de la fenetre "titleScreen"									   */
/* ROLE : fonctionnement selon l'�tat : enum State_Type = STATEtitleScreen			   */
/* INPUT  : struct Sysinfo& : structure globale du programme						   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void IHM::titleScreen
(
	Sysinfo& sysinfo
)
{
	LoadConfig::logfileconsole("[INFO]___: [START] : titleScreen");

	/* title screen init */
	sysinfo.var.statescreen = State_Type::STATEtitleScreen;
	sysinfo.var.select = Select_Type::selectnothing;

	// applique une surface de la taille de l'�cran de couleur noir
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
	LoadConfig::logfileconsole("[INFO]___: [END] : titleScreen");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : refreshNbPlayerTxt														   */
/* ROLE : Maj du nombre de joueurs lors de la saisie								   */
/* INPUT/OUTPUT : SDL_Renderer*& : Ptr sur le SDL_Renderer							   */
/* INPUT/OUTPUT : TTF_Font* font[] : ptr sur tableau de font						   */
/* INPUT : const Var& var : structure globale pour les variables					   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void IHM::refreshNbPlayerTxt
(
	SDL_Renderer*& renderer,
	TTF_Font* font[],
	const Var& var
)
{
	Texte::writeTexte(renderer, font, Index_staticIndexVectorTextes::NB_PLAYER,
		Texte_Type::shaded, "Number of player(s)" + std::to_string(var.nbPlayer),
		{ 255, 127, 127, 255 }, { 64, 64, 64, 255 }, 24,
		var.tempX, var.tempY, nonTransparent, no_angle, Center_Type::center_x);

	SDL_RenderPresent(renderer);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : refreshNamePlayerTxt														   */
/* ROLE : Maj du noms du joueur lors de la saisie									   */
/* INPUT/OUTPUT : SDL_Renderer*& : Ptr sur le SDL_Renderer							   */
/* INPUT/OUTPUT : TTF_Font* font[] : ptr sur tableau de font						   */
/* INPUT : const Var& var : structure globale pour les variables					   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void IHM::refreshNamePlayerTxt
(
	SDL_Renderer*& renderer,
	TTF_Font* font[],
	const Var& var
)
{
	if (!var.tempPlayerName.empty())
	{
		Texte::writeTexte(renderer, font, Index_staticIndexVectorTextes::PLAYER_NAME,
			Texte_Type::shaded, var.tempPlayerName, { 255, 127, 127, 255 }, { 64, 64, 64, 255 },
			24, var.tempX + 12, var.tempY, nonTransparent, no_angle, Center_Type::center_x);
	}
	else
	{
		Texte::writeTexte(renderer, font, Index_staticIndexVectorTextes::PLAYER_NAME,
			Texte_Type::shaded, "_", { 255, 127, 127, 255 }, { 64, 64, 64, 255 },
			24, var.tempX + 12, var.tempY, nonTransparent, no_angle, Center_Type::center_x);
	}
	SDL_RenderPresent(renderer);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : reloadScreen																   */
/* ROLE : Desciption de la fenetre "reloadScreen"									   */
/* ROLE : fonctionnement selon l'�tat : enum State_Type = STATEreload				   */
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void IHM::reloadScreen
(
	Sysinfo& sysinfo
)
{
	LoadConfig::logfileconsole("[INFO]___: [START] : reloadScreen");
	sysinfo.var.statescreen = State_Type::STATEreload;
	SDL_RenderClear(sysinfo.screen.renderer);

	for (const auto& n : sysinfo.allButton.reload)
	{
		n.second->renderButtonTexte(sysinfo.var.statescreen);
	}

	/* ### Don't put code below here ### */

	SDL_RenderPresent(sysinfo.screen.renderer);
	LoadConfig::logfileconsole("[INFO]___: [END] : reloadScreen");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : alwaysrender																   */
/* ROLE : Tous les 1/SCREEN_REFRESH_RATE cette fonction permet ...					   */
/* ROLE : ... la d�sciption de la fenetre "STATEmainmap" ou "STATEcitiemap"			   */
/* ROLE : fonctionnement selon l'�tat : enum State_Type = STATEmainmap ou STATEcitiemap*/
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void														       */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void IHM::alwaysrender
(
	Sysinfo& sysinfo
)
{
	/*
	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	*/

	switch (sysinfo.var.statescreen)
	{
	case State_Type::STATEmainMap:

		/* *********************************************************
		 *					START Affichage mainmap				   *
		 ********************************************************* */

		mainmap(sysinfo);

		/* *********************************************************
		 *					END Affichage mainmap				   *
		 ********************************************************* */

		break;
	case State_Type::STATEcityMap:

		/* *********************************************************
		 *				START Affichage citieMap				   *
		 ********************************************************* */

		if (NO_CITY_SELECTED < sysinfo.var.s_player.selectCity)
		{
			if  (
					sysinfo.var.s_player.selectCity
					<
					(int)sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]->GETtabCity().size()
				)
			{
				SDL_RenderClear(sysinfo.screen.renderer);

				sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
					->GETtheCity(sysinfo.var.s_player.selectCity)
						->afficherCityMap(sysinfo);
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

	/* ### Don't put code below here ### */

	SDL_RenderPresent(sysinfo.screen.renderer);
	/*
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << std::endl << "temps d'execution de alwaysrender : " << std::setprecision(10) << elapsed_seconds.count();
	*/
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : mainmap																	   */
/* ROLE : Affichage de la mainmap													   */
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void														       */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void IHM::mainmap
(
	Sysinfo& sysinfo
)
{
	SDL_RenderClear(sysinfo.screen.renderer);

	/* *********************************************************
	 *					START background					   *
	 ********************************************************* */

	afficherSupertiles(sysinfo);

	sysinfo.allTextures.ground["toolbar.bmp"]->render();

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

	Texte::writeTexte
	(sysinfo.screen.renderer, sysinfo.allTextures.font,Index_staticIndexVectorTextes::NB_TURN,Texte_Type::blended,
		std::to_string(sysinfo.var.nbturn), { 0, 64, 255, 255 }, NoColor,
		24, 80, 850, nonTransparent, no_angle);

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
	case Select_Type::selectcreate:
#ifdef _DEBUG_MODE
		/* ---------------------------------------------------------------------- */
		/* Affiche les unit�s pour rendre l'unit� � cr�er						  */
		/* ---------------------------------------------------------------------- */
		if (sysinfo.var.s_player.unitNameToCreate.compare(EMPTY_STRING) != IDENTICAL_STRINGS)
		{
			sysinfo.allTextures.unit[sysinfo.var.s_player.unitNameToCreate]
				->render(100, 432);
		}
#endif // DEBUG_MODE
		break;
	case Select_Type::selectmove:
		/* ---------------------------------------------------------------------- */
		/* Selectionne l'unit� � faire bouger	 								  */
		/* ---------------------------------------------------------------------- */
		if	(Utility::checkPlayerUnitSelection(sysinfo.var.s_player))
		{
			sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
				->GETtheUnit(sysinfo.var.s_player.selectunit)->cmpblit();
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


	for (unsigned int i(0); i < sysinfo.tabplayer.size(); i++)
	{
		for (unsigned int j(0); j < sysinfo.tabplayer[i]->GETtabUnit().size(); j++)
		{
			// affiche pour chaque joueurs les unit�s existantes (avec les stats)
			sysinfo.tabplayer[i]->GETtheUnit(j)->afficher
						(
							sysinfo.allTextures,
							sysinfo.map,
							i
						);

			if (sysinfo.tabplayer[i]->GETtheUnit(j)->GETshowStats())
			{
				sysinfo.tabplayer[i]->GETtheUnit(j)->afficherstat
						(
							sysinfo.map,
							sysinfo.allTextures.font,
							sysinfo.screen.renderer
						);
			}
		}
	
		for (unsigned int j(0); j < sysinfo.tabplayer[i]->GETtabCity().size(); j++)
		{
			// affiche pour chaque joueurs les cit�s existantes
			sysinfo.tabplayer[i]->GETtheCity(j)->afficher(sysinfo);
		}

		if (NO_PLAYER_SELECTED < sysinfo.var.s_player.selectplayer)
		{
			sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
				->displayGoldStats(sysinfo.screen.renderer, sysinfo.allTextures.font);
		}
	}
	

	/* *********************************************************
	 *			END Affichage Unit/Citie/Player				   *
	 ********************************************************* */
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : afficherSupertiles														   */
/* ROLE : Affichage de la map (tiles, spec, appartenance) aux dimensions map.screen	   */
/* INPUT : struct Sysinfo& : structure globale du programme						       */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void IHM::afficherSupertiles
(
	Sysinfo& sysinfo
)
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
			case Ground_Type::error:
				throw("afficherSupertiles : tile_ground == NoGround");
				break;
			case Ground_Type::grass:
				sysinfo.allTextures.ground["grass.bmp"]->render(x, y);
				break;
			case Ground_Type::water:
				sysinfo.allTextures.ground["water.bmp"]->render(x, y);
				break;
			case Ground_Type::deepwater:
				sysinfo.allTextures.ground["deepwater.bmp"]->render(x, y);
				break;
			case Ground_Type::dirt:
				/* TODO */
				break;
			case Ground_Type::sand:
				/* TODO */
				break;
			default:
				throw("afficherSupertiles : tile_ground == NoGround");
				break;
			}

			if (GroundSpec_Type::nothing < sysinfo.map.maps[m][n].tile_spec)
			{
				sysinfo.allTextures.groundSpec[sysinfo.map.maps[m][n].tile_stringspec]
					->render(x, y);
			}
			else
			{
				/* N/A */
			}

			if (NO_APPARTENANCE < sysinfo.map.maps[m][n].appartenance)
			{
				sysinfo.allTextures.colorapptile
					["ColorPlayertile" + std::to_string(sysinfo.map.maps[m][n].appartenance) + ".bmp"]
						->render(x, y);
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


/* *********************************************************
 *						END IN-GAME						   *
 ********************************************************* */

/*
*	End Of File : IHM.cpp
*/