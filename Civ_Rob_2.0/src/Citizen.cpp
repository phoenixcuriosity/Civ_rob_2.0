/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.2.0
	file version : 1.4

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

#include "MainGame.h"

 /* *********************************************************
  *					START Citizen::STATIC				   *
  ********************************************************* */

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : placeCitizen																   */
/* ROLE : Placement d'un Citizen en fonction des cases occup�es de la City			   */
/* INPUT : std::vector<Tile> : carte de la City										   */
/* INPUT : std::vector<Citizen> : tableau de Citizen								   */
/* INPUT : int& _food, int& _work, int& _gold : spec de la case						   */
/* RETURNED VALUE    : unsigned int : la place allou�e								   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
unsigned int Citizen::placeCitizen
(
	VectMap& tile,
	VectCitizen& citizens,
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
		if (tile[i].appartenance == tile[citizens[0]->GETtileOccupied()].appartenance)
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
/* ROLE : Constructeur par d�faut													   */
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
	MainGame::logfileconsole("[INFO]___: Create Citizen Success");
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
	MainGame::logfileconsole("[INFO]___: Create Citizen Success");
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
	VectMap& tile,
	VectCitizen& citizens
)
	:
	_tileOccupied(placeCitizen(tile, citizens, _food, _work, _gold)),
	_happiness(Emotion_Type::neutre),
	_revolt(0),
	_religion(Religion_Type::catholic),
	_place(true)
{
	MainGame::logfileconsole("[INFO]___: Create Citizen Success");
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
	MainGame::logfileconsole("[INFO]___: Kill Citizen Success");
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

)
{

}

/* *********************************************************
 *					END Citizen::METHODS				   *
 ********************************************************* */

 /*
  *	End Of File : Citizen.cpp
  */