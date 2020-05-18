/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.20.4.5
	file version : 1.1

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

#include "Citizen.h"

#include "City.h"
#include "LoadConfig.h"
#include "GamePlay.h"

/* *********************************************************
 *					START Citizen::STATIC				   *
 ********************************************************* */

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : placeCitizen																   */
/* ROLE : Placement d'un Citizen en fonction des cases occupées de la City			   */
/* INPUT : std::vector<Tile> : carte de la City										   */
/* INPUT : std::vector<Citizen> : tableau de Citizen								   */
/* INPUT : int& _food, int& _work, int& _gold : spec de la case						   */
/* RETURNED VALUE    : unsigned int : la place allouée								   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
unsigned int Citizen::placeCitizen
(
	std::vector<Tile>& tile,
	std::vector<Citizen*>& citizens,
	int& _food,
	int& _work,
	int& _gold
)
{
	unsigned int condition((unsigned int)citizens.size());
	unsigned int checkcondition(0);
	unsigned int place(0);
	bool continuer(true);

	std::vector<unsigned int> tabpos;
	for (unsigned int j(0); j < condition; j++)
	{
		tabpos.push_back(citizens[j]->GETtileOccupied());
	}


	for (unsigned int i(0); (i < INIT_SIZE_VIEW * INIT_SIZE_VIEW) && (true == continuer); i++)
	{
		checkcondition = 0;
		for (unsigned int p(0); (p < condition) && (true == continuer); p++)
		{
			if (i != tabpos[p])
			{
				checkcondition++;
			}
			else
			{
				/* N/A */
			}

			if (checkcondition == condition)
			{
				place = i;
				continuer = false;
			}
			else
			{
				/* N/A */
			}
		}
	}

	_food = tile[place].food;
	_work = tile[place].work;
	_gold = tile[place].gold;
	return place;
}


/* *********************************************************
 *					END Citizen::STATIC					   *
 ********************************************************* */



 /* *********************************************************
  *					START Citizen::METHODS				   *
  ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Citizen																	   */
/* ROLE : Constructeur par défaut													   */
/* INPUT : void																		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Citizen::Citizen()
	:
	_tileOccupied((unsigned int)ceil((INIT_SIZE_VIEW* INIT_SIZE_VIEW) / 2)),
	_happiness(Emotion_Type::neutre),
	_food(2),
	_work(1),
	_gold(1),
	_revolt(0),
	_religion(Religion_Type::catholic),
	_place(false)
{
	LoadConfig::logfileconsole("[INFO]___: Create Citizen par défaut Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Citizen																	   */
/* ROLE : Constructeur par une Tile													   */
/* INPUT : Tile tile : tile centrale de la Citie									   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Citizen::Citizen
(
	Tile tile
)
	:
	_tileOccupied((unsigned int)ceil((INIT_SIZE_VIEW* INIT_SIZE_VIEW) / 2)),
	_happiness(Emotion_Type::neutre),
	_food(tile.food),
	_work(tile.work),
	_gold(tile.gold),
	_revolt(0),
	_religion(Religion_Type::catholic),
	_place(true)
{
	LoadConfig::logfileconsole("[INFO]___: Create Citizen Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Citizen																	   */
/* ROLE : Constructeur par une Tile													   */
/* INPUT : std::vector<Tile>& tile : tableau de Tile de la Citie					   */
/* INPUT : std::vector<Citizen*>& citizens : tableau de Citizens					   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Citizen::Citizen
(
	std::vector<Tile>& tile,
	std::vector<Citizen*>& citizens
)
	:
	_tileOccupied(placeCitizen(tile, citizens, _food, _work, _gold)),
	_happiness(Emotion_Type::neutre),
	_revolt(0),
	_religion(Religion_Type::catholic),
	_place(true)
{
	LoadConfig::logfileconsole("[INFO]___: Create Citizen Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : ~Citizen																	   */
/* ROLE : Destructeur																   */
/* INPUT : void																		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Citizen::~Citizen()
{
	LoadConfig::logfileconsole("[INFO]___: Kill Citizen Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : placeCitizenWithMouse														   */
/* ROLE : TODO																		   */
/* INPUT : void 																	   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Citizen::placeCitizenWithMouse()
{
	/* TODO */
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : afficher																	   */
/* ROLE : affichage du citizen sur la case de la citie map							   */
/* INPUT : std::unordered_map<std::string,Texture*>& : tableau de Texture de la Citie  */
/* INPUT : unsigned int x : index en x du Citizen									   */
/* INPUT : unsigned int y : index en y du Citizen									   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void Citizen::afficher
(
	std::unordered_map<std::string, Texture*>& citieMap,
	unsigned int x,
	unsigned int y
)
{
	switch (_happiness)
	{
	case Emotion_Type::ecstatic:
		citieMap["Adore.png"]->render((int)x, (int)y);
		break;
	case Emotion_Type::happy:
		citieMap["Laugh.png"]->render((int)x, (int)y);
		break;
	case Emotion_Type::neutre:
		citieMap["Cool.png"]->render((int)x, (int)y);
		break;
	case Emotion_Type::sad:
		citieMap["Cry.png"]->render((int)x, (int)y);
		break;
	case Emotion_Type::angry:
		citieMap["Furious.png"]->render((int)x, (int)y);
		break;
	default:
		/* TODO ERROR */
		break;
	}
}

/* *********************************************************
 *					END Citizen::METHODS				   *
 ********************************************************* */

/*
 *	End Of File : Citizen.cpp
 */