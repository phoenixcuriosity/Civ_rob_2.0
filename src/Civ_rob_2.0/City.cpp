/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.19
	file version : 1.11

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

#include "City.h"
#include "IHM.h"
#include "LoadConfig.h"
#include "GamePlay.h"

/* *********************************************************
 *					START City::STATIC					   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : createCity																   */
/* ROLE : Création d'une City à partir d'un settler sur la carte					   */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::createCity
(
	Sysinfo& sysinfo
)
{
	if (sysinfo.var.s_player.unitNameToMove.compare("settler") == 0)
	{
		/* ---------------------------------------------------------------------- */
		/* 1° : Recherche du nom de la nouvelle Citie 							  */
		/*    : Recherche dans le tableau global des noms de Citie				  */
		/*  : En fonction du nombre de Citie déjà crées et de MAX_CITY_PER_PLAYER */
		/* ---------------------------------------------------------------------- */

		std::string name(sysinfo.var.s_player.tabCitieName
			[
				(unsigned int)
				(
					((unsigned int)sysinfo.var.s_player.selectplayer * (double)MAX_CITY_PER_PLAYER)
					+ sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
						->GETtabCity().size()
				)
			]);

		/* ---------------------------------------------------------------------- */
		/* 2° : Recherche du position de la nouvelle Citie = position settler 	  */
		/* ---------------------------------------------------------------------- */

		unsigned int x(sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
						->GETtheUnit(sysinfo.var.s_player.selectunit)
							->GETx());
		unsigned int y(sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
						->GETtheUnit(sysinfo.var.s_player.selectunit)
							->GETy());

		/* ---------------------------------------------------------------------- */
		/* 3° : Recherche de la tile ou se trouve le settler 					  */
		/* ---------------------------------------------------------------------- */

		unsigned int middletileX(0), middletileY(0);
		searchMiddleTile(sysinfo.map.maps, x, y, &middletileX, &middletileY);

		std::vector<Tile> tabtile;
		tabtile.resize(INIT_SIZE_VIEW * INIT_SIZE_VIEW);

		/* ---------------------------------------------------------------------- */
		/* 4° : Remplisage tableau de tile Citie			 					  */
		/* ---------------------------------------------------------------------- */

		fillCitieTiles
					(
						sysinfo.screen,
						middletileX,
						middletileY,
						sysinfo.var.s_player.selectplayer,
						sysinfo.map,
						tabtile
					);

		/* ---------------------------------------------------------------------- */
		/* 5° : Création d'un ptr et passage au tableau de Citie du joueur		  */
		/*    : Destruction ptr de l'Unit										  */
		/*    : Aucune Unit n'est séléctionnée et aucune Unit à bouger	 		  */
		/* ---------------------------------------------------------------------- */

		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
			->addCity(name, x, y, tabtile);

		sysinfo.tabplayer[sysinfo.var.s_player.selectplayer]
			->deleteUnit(sysinfo.var.s_player.selectunit);
		sysinfo.var.s_player.selectunit = NO_UNIT_SELECTED;
		sysinfo.var.s_player.unitNameToMove = EMPTY_STRING;
	}
	else
	{
		/* N/A */
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : searchMiddleTile															   */
/* ROLE : Recherche les indices de la Tile centrale de la Citie						   */
/* INPUT : const MatriceTile& maps : Matrice de la map								   */
/* INPUT : unsigned int x :	index en x de la Citie 									   */
/* INPUT : unsigned int y :	index en y de la Citie 									   */
/* OUTPUT : unsigned int* middletileX : index en tileSize de x						   */
/* OUTPUT : unsigned int* middletileX : index en tileSize de y						   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::searchMiddleTile
(
	const MatriceTile& maps,
	unsigned int x,
	unsigned int y,
	unsigned int* middletileX,
	unsigned int* middletileY
)
{
	for (unsigned int i(0); i < maps.size(); i++)
	{
		for (unsigned int j(0); j < maps.size(); j++)
		{
			if  (
					maps[i][j].tile_x == x
					&&
					maps[i][j].tile_y == y
				)
			{
				*middletileX = i;
				*middletileY = j;
				return;
			}
			else
			{
				/* N/A */
			}
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : fillCitieTiles															   */
/* ROLE : Rempli le tableau de la Citie avec le point centrale la middletileXY		   */
/* ROLE : et de largeur et hauteur totale INIT_SIZE_VIEW							   */
/* INPUT : const Screen& screen	: taille en x et y de l'écran						   */
/* INPUT : unsigned int middletileX : index en tileSize de x de la Citie			   */
/* INPUT : unsigned int middletileY : index en tileSize de y de la Citie			   */
/* INPUT : unsigned int selectplayer : index d'appartenance							   */
/* INPUT/OUTPUT : Map& map : structure de la Map									   */
/* OUTPUT : std::vector<Tile>& tabtile : tableau à remplir de la Citie				   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::fillCitieTiles
(
	const Screen& screen,
	unsigned int middletileX,
	unsigned int middletileY,
	unsigned int selectplayer,
	Map& map,
	std::vector<Tile>& tabtile
)
{
	unsigned int k(0);
	for (int o(-(int)ceil(INIT_SIZE_VIEW / 2)); o <= (int)ceil(INIT_SIZE_VIEW / 2); o++)
	{
		for (int p(-(int)ceil(INIT_SIZE_VIEW / 2)); p <= (int)ceil(INIT_SIZE_VIEW / 2); p++)
		{
			if (initSizeInfluenceCondition(o, p))
			{
				map.maps[(unsigned int)((double)middletileX + o)]
						[(unsigned int)((double)middletileY + p)]
						.appartenance = selectplayer;
			}
			else
			{
				/* N/A */
			}

			/* ---------------------------------------------------------------------- */
			/* Remplissage du tableau de Tile								 		  */
			/* ---------------------------------------------------------------------- */
			tabtile[k] = map.maps
							[(unsigned int)((double)middletileX + o)]
							[(unsigned int)((double)middletileY + p)];
			tabtile[k].tile_x = (screen.screenWidth / 2) - (-o * map.tileSize);
			tabtile[k].tile_y = (screen.screenHeight / 2) - (-p * map.tileSize);
			k++;
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initSizeInfluenceCondition												   */
/* ROLE : Conditions des cases de la ville à l'intérieur de zone d'influence		   */
/* INPUT : int o :	index en x														   */
/* INPUT : int p :	index en y														   */
/* RETURNED VALUE : bool : false -> invalid / true -> valid							   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool City::initSizeInfluenceCondition
(
	int o,
	int p
)
{
	if	(
			o > -(int16_t)INIT_SIZE_INFLUENCE
			&&
			o < INIT_SIZE_INFLUENCE
			&&
			p > -(int16_t)INIT_SIZE_INFLUENCE
			&&
			p < INIT_SIZE_INFLUENCE
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : searchCityTile															   */
/* ROLE : Recherche la case de la City et renvoie vers cityMap						   */
/* INPUT : const std::vector<Player*>& : Vecteur de joueurs							   */
/* INPUT/OUTPUT : Var& : Structure Var												   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::searchCityTile
(
	const std::vector<Player*>& tabplayer,
	Var& var
)
{
	
	for (unsigned int i(0); i < tabplayer[var.s_player.selectplayer]->GETtabCity().size(); i++)
	{
		if	(
				tabplayer[var.s_player.selectplayer]
					->GETtheCity(i)
						->testPos
							(var.mouse.GETmouse_xNormalized(), var.mouse.GETmouse_yNormalized())
			)
		{
			var.s_player.selectCitie = i;
			var.statescreen = State_Type::STATEcitiemap;
			var.select = Select_Type::selectnothing;
			return;
		}
		else
		{
			/* N/A */
		}
	}
}


/* *********************************************************
 *					END City::STATIC					   *
 ********************************************************* */


 
/* *********************************************************
 *					START City::METHODS					   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : City																		   */
/* ROLE : Constructeur complet														   */
/* INPUT : const std::string &	: name de la Citie									   */
/* INPUT : unsigned int x : index en x												   */
/* INPUT : unsigned int y : index en y												   */
/* INPUT : Tile tile[] : tableau de tile de la Citie								   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
City::City
(
	const std::string& name,
	unsigned int x,
	unsigned int y,
	std::vector<Tile>& tiles
)
	: _image("citie.png"),
_name(name), _x(x), _y(y), _tile(tiles),
_influenceLevel(1),_nbpop(1), _atq(0), _def(0), _emotion(0), _nbstructurebuild(0),
_foodStock(0), _foodBalance(tiles[(unsigned int)ceil((INIT_SIZE_VIEW*INIT_SIZE_VIEW) / 2)].food)
{
	_citizens.push_back(new Citizen(tiles[(unsigned int)ceil((INIT_SIZE_VIEW * INIT_SIZE_VIEW) / 2)]));

	LoadConfig::logfileconsole("[INFO]___: Create Citie: " + _name + " Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : ~City																		   */
/* ROLE : Destructeur																   */
/* INPUT : void																		   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
City::~City()
{
	for (const auto& n : _citizens)
	{
		if (nullptr != n)
		{
			delete n;
		}
		else
		{
			/* TODO Throw error */
		}
	}
	LoadConfig::logfileconsole("[INFO]___: Destroy Citie: " + _name + " Success");
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : foodNextTurn																   */
/* ROLE : Calcul et application du niveau de Food pour le prochain tour				   */
/* INPUT : void																		   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::foodNextTurn()
{
	double foodLimitPerLevelCurrent(15 + ((double)_nbpop - 1) * 6 + pow((_nbpop - 1), 1.8));
	double foodLimitPerLevelMinusOne(15 + ((double)_nbpop - 1 - 1) * 6 + pow((_nbpop - 1 - 1), 1.8));
	double sommeFoodCitizen(0);
	bool change(false);

	_foodStock += _foodBalance ;
	
	if (0 > _foodStock)
	{
		/* ---------------------------------------------------------------------- */
		/* TODO gestion prioritaire de suppression de Citizen					  */
		/* ---------------------------------------------------------------------- */
		_nbpop--;
		if (nullptr != _citizens[_citizens.size() - 1])
		{
			delete _citizens[_citizens.size() - 1];
		}
		else
		{
			/* TODO Throw error */
		}
		_citizens.pop_back();
		_foodStock = foodLimitPerLevelMinusOne;
		change = true;
	}
	else if (_foodStock >= foodLimitPerLevelCurrent)
	{
		_nbpop++;
		
		_citizens.push_back(new Citizen(_tile, _citizens));
		_foodStock -= foodLimitPerLevelCurrent;
		change = true;
	}
	else
	{
		/* ---------------------------------------------------------------------- */
		/* Entre 0 et foodLimitPerLevelCurrent									  */
		/* ---------------------------------------------------------------------- */
		/* N/A */
	}

	if (change)
	{
		for (unsigned int i(0); i < _citizens.size(); i++)
			sommeFoodCitizen += _citizens[i]->GETfood();
		_foodBalance = sommeFoodCitizen - (2 * ((double)_nbpop - 1));
	}
	else
	{
		/* N/A */
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : testPos																	   */
/* ROLE : Retourne si la position est valide										   */
/* INPUT : unsigned int x : position de la souris en x								   */
/* INPUT : unsigned int y : position de la souris en y								   */
/* RETURNED VALUE : bool : false : invalid / true : valid							   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
bool City::testPos
(
	unsigned int mouse_x,
	unsigned int mouse_y
)
{
	if	(
			_x == mouse_x
			&&
			_y == mouse_y
		)
	{
		return true;
	}	
	return false;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : computeEmotion															   */
/* ROLE : Calcul sur une echelle de 0 à 100 le bonheur de la Citie					   */
/* INPUT : void																		   */
/* INTERNAL OUTPUT : _emotion : bonheur de la Citie									   */
/* RETURNED VALUE : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::computeEmotion()
{
	double result(0);

	/* ---------------------------------------------------------------------- */
	/* Result limit : -inf / inf											  */
	/* ---------------------------------------------------------------------- */
	for (unsigned int nbCitizen(0); nbCitizen < _citizens.size(); nbCitizen++)
	{
		result += (int)_citizens[nbCitizen]->GEThappiness();
	}

	/* ---------------------------------------------------------------------- */
	/* Result limit : -2.0 / 2.0											  */
	/* ---------------------------------------------------------------------- */
	result /= _citizens.size();

	/* ---------------------------------------------------------------------- */
	/* Result limit : -100.0 / 100.0										  */
	/* ---------------------------------------------------------------------- */
	result *= 50.0;

	/* ---------------------------------------------------------------------- */
	/* Result limit : 0.0 / 200.0											  */
	/* ---------------------------------------------------------------------- */
	result += 100.0;

	/* ---------------------------------------------------------------------- */
	/* Result limit : 0.0 / 100.0											  */
	/* ---------------------------------------------------------------------- */
	result /= 2.0;

	_emotion = (unsigned int)result;
}

/* *********************************************************
 *					END City::METHODS					   *
 ********************************************************* */

 
 
/* *********************************************************
 *				START City::METHODS::Affichage			   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : afficher																	   */
/* ROLE : Affichage de la City (Texture et nom)										   */
/* INPUT : truct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::afficher
(
	Sysinfo& sysinfo
)
{
	unsigned int x(_x - sysinfo.map.screenOffsetXIndexMin * sysinfo.map.tileSize);
	unsigned int y(_y - sysinfo.map.screenOffsetYIndexMin * sysinfo.map.tileSize);

	sysinfo.allTextures.citieMap[_image]->render(x, y);

	sysinfo.allTextes.mainMap[_name]->render(x + sysinfo.map.tileSize / 2, y + sysinfo.map.tileSize);

	sysinfo.allTextes.number[std::to_string((unsigned int)floor(_nbpop))]
		->render(x + sysinfo.map.tileSize / 2 - 20, y + sysinfo.map.tileSize - 6);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : affichercitiemap															   */
/* ROLE : Affichage des cases qui compose le secteur de la City						   */
/* INPUT : truct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void City::affichercitiemap
(
	Sysinfo& sysinfo
)
{

	/* Affichage des cases qui compose le secteur de la City */
	for (unsigned int i(0); (i < (INIT_SIZE_VIEW * INIT_SIZE_VIEW)); i++) 
	{
		switch (_tile[i].tile_ground)
		{
		case Ground_Type::grass:
			sysinfo.allTextures.ground["grass.bmp"]->render(_tile[i].tile_x, _tile[i].tile_y);
			break;
		case Ground_Type::water:
			sysinfo.allTextures.ground["water.bmp"]->render(_tile[i].tile_x, _tile[i].tile_y);
			break;
		default:
			/* N/A */
			break;
		}

		if (GroundSpec_Type::nothing < _tile[i].tile_spec)
		{
			sysinfo.allTextures.groundSpec[_tile[i].tile_stringspec]
				->render(_tile[i].tile_x, _tile[i].tile_y);
		}
		else
		{
			/* N/A */
		}

		if (NO_APPARTENANCE < _tile[i].appartenance)
		{
			sysinfo.allTextures.colorapptile["ColorPlayertile" + std::to_string(_tile[i].appartenance) + ".bmp"]
				->render(_tile[i].tile_x, _tile[i].tile_y);
		}
		else
		{
			/* N/A */
		}

		for (unsigned int nbCitizen(0); nbCitizen < _citizens.size(); nbCitizen++)
		{
			if (_citizens[nbCitizen]->GETtileOccupied() == i && _citizens[nbCitizen]->GETplace())
			{
				_citizens[nbCitizen]->afficher(sysinfo.allTextures.citieMap, _tile[i].tile_x, _tile[i].tile_y);
			}
			else
			{
				/* N/A */
			}
		}
	}

	/* Affichage food */
	unsigned int renderFoodX(24), renderFoodY(sysinfo.map.tileSize), offSetRenderX(0), offSetRenderY(0);
	if (_foodStock > 0)
	{
		for (double nbfood(0); nbfood < _foodStock; nbfood++)
		{
			if (((unsigned int)nbfood % 10) == 0)
			{
				offSetRenderY++;
				offSetRenderX = 0;
			}
			else
			{
				/* N/A */
			}

			sysinfo.allTextures.citieMap["food.png"]
				->render(1400 + (offSetRenderX * renderFoodX), 500 + (offSetRenderY * renderFoodY));

			offSetRenderX++;
		}
	}
	else
	{
		/* N/A */
	}
}

/* *********************************************************
 *				END City::METHODS::Affichage			   *
 ********************************************************* */








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
_tileOccupied((unsigned int)ceil((INIT_SIZE_VIEW*INIT_SIZE_VIEW) / 2)),
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
_tileOccupied((unsigned int)ceil((INIT_SIZE_VIEW*INIT_SIZE_VIEW) / 2)),
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
	std::unordered_map<std::string,Texture*>& citieMap,
	unsigned int x,
	unsigned int y
)
{
	switch (_happiness)
	{
	case Emotion_Type::ecstatic:
		citieMap["Adore.png"]->render(x, y);
		break;
	case Emotion_Type::happy:
		citieMap["Laugh.png"]->render(x, y);
		break;
	case Emotion_Type::neutre:
		citieMap["Cool.png"]->render(x, y);
		break;
	case Emotion_Type::sad:
		citieMap["Cry.png"]->render(x, y);
		break;
	case Emotion_Type::angry:
		citieMap["Furious.png"]->render(x, y);
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
*	End Of File City.cpp
*/