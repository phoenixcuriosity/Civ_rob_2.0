/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.18
	file version : 1.8

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

#include "GamePlay.h"
#include "IHM.h"
#include "SaveReload.h"
#include "KeyboardMouse.h"
#include "LoadConfig.h"

/* *********************************************************
 *			START GamePlay::STATIC::NEW-GAME			   *
 ********************************************************* */

 
/*
* NAME : newGame
* ROLE : Initialisation de la nouvelle partie
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Noms des joueurs, groundGen, positions des settlers
* RETURNED VALUE    : void
*/
void GamePlay::newGame(Sysinfo& sysinfo)
{
	LoadConfig::logfileconsole("[INFO]___: Newgame Start");
	sysinfo.var.statescreen = STATEscreennewgame;

	// création d'une sauvegarde concernant la nouvelle partie
	SaveReload::createSave(sysinfo);

	// Fond noir
	SDL_RenderClear(sysinfo.screen.renderer);

	/* *********************************************************
	 *						Nb player ?						   *
	 ********************************************************* */

	// Première demande au joueur : Le nombre de joueurs ?
	sysinfo.allTextes.newGame["Press Return or kpad_Enter to valid selection"]->render();
	sysinfo.allTextes.newGame["How many player(s) (max 9):"]->render();
	SDL_RenderPresent(sysinfo.screen.renderer);

	sysinfo.var.cinState = cinScreenNewGameNbPlayer;
	sysinfo.var.waitEvent = true;

	unsigned int space(32);

	sysinfo.var.tempX = sysinfo.screen.screenWidth / 2;
	sysinfo.var.tempY = 164;

	// Le joueur doit rentrer une valeur entre 1 et 9, par défaut 1
	KeyboardMouse::eventSDL(sysinfo);

	/* *********************************************************
	 *					Name of player ?					   *
	 ********************************************************* */

	sysinfo.var.tempY += space;
	sysinfo.var.cinState = cinScreenNewGameNamePlayer;
	// Deuxième demande au joueur : Le nom des joueurs
	for (unsigned int i(0); i < sysinfo.var.nbPlayer; i++)
	{
		sysinfo.var.waitEvent = true;

		Texte::writeTexte
		(sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			blended,
			"Name of player nb:" + std::to_string(i),
			{ 255, 0, 0, 255 },
			NoColor,
			24, 
			sysinfo.screen.screenWidth / 2,
			sysinfo.var.tempY,
			no_angle, center_x);

		SDL_RenderPresent(sysinfo.screen.renderer);

		sysinfo.var.tempY += space;

		// valeur par défaut avec incrémentation en fonction du nombre de joueur : noName 
		KeyboardMouse::eventSDL(sysinfo);

		sysinfo.var.s_player.tabPlayerName.push_back(sysinfo.var.tempPlayerName);
		sysinfo.var.tempPlayerName = "";
		sysinfo.tabplayer.push_back(new Player(sysinfo.var.s_player.tabPlayerName[i]));
		sysinfo.var.tempY += space;
	}

	/* *********************************************************
	 *					Map Generation						   *
	 ********************************************************* */
	
	groundGen(sysinfo);
	newGameSettlerSpawn(sysinfo);

	/* *********************************************************
	 *							Save						   *
	 ********************************************************* */

	/*** Sauvegarde des paramètres appliqués et de la génération de la map ***/
	SaveReload::saveMaps(sysinfo);
	SaveReload::savePlayer(sysinfo);

	/* *********************************************************
	 *					 Button Creation					   *
	 ********************************************************* */
	
	// Création des boutons pour séléctionner les joueurs
	int initspacename(200), spacename(24);
	sysinfo.var.statescreen = STATEmainmap;
	sysinfo.var.cinState = cinMainMap;
	for (unsigned int i(0); i < sysinfo.tabplayer.size(); i++)
	{
		ButtonTexte::createButtonTexte
		(	sysinfo.screen.renderer,
			sysinfo.allTextures.font,
			sysinfo.var.statescreen,
			sysinfo.var.select,
			sysinfo.allButton.player,
			shaded,
			sysinfo.var.s_player.tabPlayerName[i],
			{ 127, 255, 127, 255 },
			{ 64, 64, 64, 255 },
			16,
			0,
			initspacename += spacename,
			nonTransparent,
			no_angle);
	}

	
	sysinfo.screen.enableFPS = true;
	sysinfo.screen.fpsTimer.start();

	/* ### Don't put code below here ### */

	LoadConfig::logfileconsole("[INFO]___: Newgame End");
}

/*
* NAME : groundGen
* ROLE : Génération du sol et des spec de la map
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Génération du sol et des spec de la map
* RETURNED VALUE    : void
*/
void GamePlay::groundGen(Sysinfo& sysinfo)
{
	LoadConfig::logfileconsole("[INFO]___: Groundgen Start");
	
	for (Uint8 i(0); i < sysinfo.map.mapSize / sysinfo.map.tileSize; i++)
	{
		for (Uint8 j(0); j < sysinfo.map.mapSize / sysinfo.map.tileSize; j++)
		{
			
			sysinfo.map.maps[i][j].indexX = i + (Uint8)((sysinfo.screen.screenWidth / 10) / sysinfo.map.tileSize);
			sysinfo.map.maps[i][j].indexY = j;
			sysinfo.map.maps[i][j].tile_x = sysinfo.map.tileSize * i + (sysinfo.screen.screenWidth / 10);
			sysinfo.map.maps[i][j].tile_y = sysinfo.map.tileSize * j;
			

			/* *********************************************************
			 *			bord de la map (MAP_BORDER_ZERO)			   *
			 ********************************************************* */

			if (   (i == MAP_BORDER_ZERO)
				|| (i == (sysinfo.map.mapSize / sysinfo.map.tileSize) - (MAP_BORDER_ZERO + 1))
				|| (j == MAP_BORDER_ZERO)
				|| (j == (sysinfo.map.mapSize / sysinfo.map.tileSize) - (MAP_BORDER_ZERO + 1))
				)
			{
				tileAffectation
				(sysinfo.map.maps[i][j],
					deepwater,
					(std::string)"deepwater.bmp",
					specnothing,
					(std::string)"specnothing",
					0,
					0,
					0);
			}
					
			/* *********************************************************
			 *	  bord de la map (MAP_BORDER_MIN to MAP_BORDER_MAX)    *
			 ********************************************************* */

			else if (mapBordersConditions(sysinfo.map, i, j))
			{
				mapBorders(sysinfo.map.maps[i][j]);
			}

			/* *********************************************************
			 *					reste de la map						   *
			 ********************************************************* */
			else
			{
				mapIntern(sysinfo.map.maps, i, j);
			}
		}
	}
	LoadConfig::logfileconsole("[INFO]___: Groundgen End");
}

/*
* NAME : mapBordersConditions
* ROLE : Boucle For de conditions
* ROLE : Nombre de conditions = (MAP_BORDER_MAX - MAP_BORDER_MIN) * 2
* INPUT  PARAMETERS : Map& map : structure de la MAP
* INPUT  PARAMETERS : unsigned int i : index en X
* INPUT  PARAMETERS : unsigned int j : index en Y
* OUTPUT PARAMETERS : Validations des conditions ou non
* RETURNED VALUE    : bool : valid = true / not valid = false
*/
bool GamePlay::mapBordersConditions(Map& map, unsigned int i, unsigned int j)
{
	for (unsigned int index(MAP_BORDER_MIN); index < MAP_BORDER_MAX; index++)
	{
		if (
				(i == index)
			||  (i == (map.mapSize / map.tileSize) - (index + 1))
			||  (j == index)
			||  (j == (map.mapSize / map.tileSize) - (index + 1))
			)
		{
			return true;
		}
	}
	return false;
}

/*
* NAME : mapBordersConditions
* ROLE : Affectation des caractéristiques de la case en fonction ...
* ROLE : ... de la fonction rand, dans la bordure de la map entre ...
* ROLE : ... MAP_BORDER_MIN et MAP_BORDER_MAX
* INPUT  PARAMETERS : Tile& tile : tile à affecter
* OUTPUT PARAMETERS : Affectation des caractéristiques
* RETURNED VALUE    : void
*/
void GamePlay::mapBorders(Tile& tile)
{
	unsigned int randomspecwaterborder
	((rand() % MAP_GEN_RANDOM_RANGE_SPEC_WATER_BORDER) + MAP_GEN_RANDOM_OFFSET_SPEC_WATER_BORDER);
	switch (randomspecwaterborder) {
	case 1:
		tileAffectation
		(	tile,
			water, (std::string)"water.bmp",
			fish,
			(std::string)"fish.bmp",
			3,
			2,
			1);
		break;
	case 2:
		tileAffectation
		(	tile,
			water,
			(std::string)"water.bmp",
			petroleum,
			(std::string)"petroleum.bmp",
			1,
			3,
			4);
		break;
	default:
		/* N/A */
		break;
	}
	if (randomspecwaterborder > 2)
	{
		tileAffectation
		(tile,
			water,
			(std::string)"water.bmp",
			specnothing,
			(std::string)"specnothing",
			1,
			1,
			1);
	}
}

/*
* NAME : mapIntern
* ROLE : Affectation des caractéristiques de la case en fonction ...
* ROLE : ... de la fonction rand, dans le reste de la map
* ROLE : Si la case est de type water alors création de 2 autres ...
* ROLE : ... cases de type water pour obtenir une forme en L
* INPUT  PARAMETERS : std::vector<std::vector<Tile>>& maps : matrice de la map
* INPUT  PARAMETERS : unsigned int i : index en X
* INPUT  PARAMETERS : unsigned int j : index en Y
* OUTPUT PARAMETERS : Affectation des caractéristiques
* RETURNED VALUE    : void
*/
void GamePlay::mapIntern(std::vector<std::vector<Tile>>& maps, unsigned int i, unsigned int j)
{
	unsigned int	randomground(0),
					randomspecgrass(0),
					randomspecwater(0),
					randomspecwater1(0),
					randomspecwater2(0);

	randomground = rand() % MAP_GEN_RANDOM_RANGE_GROUND + MAP_GEN_RANDOM_OFFSET_GROUND;
	if (randomground < 92)
	{
		maps[i][j].tile_ground = grass;
		maps[i][j].tile_stringground = "grass.bmp";
		randomspecgrass =
			rand() % MAP_GEN_RANDOM_RANGE_SPEC_GRASS + MAP_GEN_RANDOM_OFFSET_SPEC_GRASS;
		switch (randomspecgrass)
		{
		case 1:
			maps[i][j].tile_spec = coal;
			maps[i][j].tile_stringspec = "coal.png";
			break;
		case 2:
			maps[i][j].tile_spec = copper;
			maps[i][j].tile_stringspec = "copper.png";
			break;
		case 3:
			maps[i][j].tile_spec = iron;
			maps[i][j].tile_stringspec = "iron.png";
			break;
		case 4:
			maps[i][j].tile_spec = tree;
			maps[i][j].tile_stringspec = "tree1.bmp";
			break;
		case 5:
			maps[i][j].tile_spec = stone;
			maps[i][j].tile_stringspec = "stone.png";
			break;
		case 6:
			maps[i][j].tile_spec = uranium;
			maps[i][j].tile_stringspec = "uranium.png";
			break;
		case 7:
			maps[i][j].tile_spec = horse;
			maps[i][j].tile_stringspec = "horse.bmp";
			break;
		default:
			/* N/A */
			break;
		}
		if (randomspecgrass > 7 && randomspecgrass <= 32)
		{ // plus de chance d'avoir des arbres
			maps[i][j].tile_spec = tree;
			maps[i][j].tile_stringspec = "tree1.bmp";
			maps[i][j].food = 1;
			maps[i][j].work = 2;
			maps[i][j].gold = 1;
		}
		else if (randomspecgrass > 32)
		{
			maps[i][j].tile_spec = specnothing;
			maps[i][j].tile_stringspec = "specnothing";
			maps[i][j].food = 2;
			maps[i][j].work = 1;
			maps[i][j].gold = 1;
		}
		else if (randomspecgrass <= 7)
		{
			maps[i][j].food = 1;
			maps[i][j].work = 2;
			maps[i][j].gold = 3;
		}
		else
		{
			/* N/A */
		}
	}
	else
	{

		/* *********************************************************
		 *		génération de l'eau -> forme en L (3 cases)		   *
		 ********************************************************* */

		/* 1er case */

		if (i > 2 && j > 2)
		{
			randomspecwater =
				rand() % MAP_GEN_RANDOM_RANGE_SPEC_WATER + MAP_GEN_RANDOM_OFFSET_SPEC_WATER;
			switch (randomspecwater)
			{
			case 1:
				tileAffectation
				(	maps[i][j],
					water,
					(std::string)"water.bmp",
					fish,
					(std::string)"fish.bmp",
					3,
					2,
					1);
				break;
			case 2:
				tileAffectation
				(	maps[i][j],
					water,
					(std::string)"water.bmp",
					petroleum,
					(std::string)"petroleum.bmp",
					1,
					3,
					4);
				break;
			default:
				/* N/A */
				break;
			}
			if (randomspecwater > 2)
				tileAffectation
				(	maps[i][j],
					water,
					(std::string)"water.bmp",
					specnothing,
					(std::string)"specnothing",
					1,
					1,
					1);
		}
		else
		{
			/* N/A */
		}

		/* 2ème case */

		if (maps[i - 1][j].tile_ground != deepwater)
		{
			randomspecwater1 =
				rand() % MAP_GEN_RANDOM_RANGE_SPEC_WATER1 + MAP_GEN_RANDOM_OFFSET_SPEC_WATER1;
			switch (randomspecwater1)
			{
			case 1:
				tileAffectation
				(	maps[i - 1][j],
					water,
					(std::string)"water.bmp",
					fish,
					(std::string)"fish.bmp",
					3,
					2,
					1);
				break;
			case 2:
				tileAffectation
				(	maps[i - 1][j],
					water,
					(std::string)"water.bmp",
					petroleum,
					(std::string)"petroleum.bmp",
					1,
					3,
					4);
				break;
			default:
				/* N/A */
				break;
			}
			if (randomspecwater1 > 2)
				tileAffectation
				(	maps[i - 1][j],
					water,
					(std::string)"water.bmp",
					specnothing,
					(std::string)"specnothing",
					1,
					1,
					1);
		}
		else
		{
			/* N/A */
		}

		/* 3ème case */

		if (maps[i - 1][j - 1].tile_ground != deepwater)
		{
			randomspecwater2 =
				rand() % MAP_GEN_RANDOM_RANGE_SPEC_WATER2 + MAP_GEN_RANDOM_OFFSET_SPEC_WATER2;
			switch (randomspecwater2)
			{
			case 1:
				tileAffectation
				(	maps[i - 1][j - 1],
					water,
					(std::string)"water.bmp",
					fish,
					(std::string)"fish.bmp",
					3,
					2,
					1);
				break;
			case 2:
				tileAffectation
				(	maps[i - 1][j - 1],
					water,
					(std::string)"water.bmp",
					petroleum,
					(std::string)"petroleum.bmp",
					1,
					3,
					4);
				break;
			default:
				/* N/A */
				break;
			}
			if (randomspecwater2 > 2)
				tileAffectation
				(	maps[i - 1][j - 1],
					water,
					(std::string)"water.bmp",
					specnothing,
					(std::string)"specnothing",
					1,
					1,
					1);
		}
		else
		{
			/* N/A */
		}
	}
}

/*
* NAME : tileAffectation
* ROLE : Affectation des caractéristiques à une case
* INPUT  PARAMETERS : Tile& tile, : la case à affecter
* INPUT  PARAMETERS : Uint8 tile_ground, std::string tile_stringground,
* INPUT  PARAMETERS : Uint8 tile_spec, std::string tile_stringspec,
* INPUT  PARAMETERS : int8_t food, int8_t work, int8_t gold
* OUTPUT PARAMETERS : Affectation
* RETURNED VALUE    : void
*/
void GamePlay::tileAffectation(	Tile& tile,
								Uint8 tile_ground, 
								std::string tile_stringground,
								Uint8 tile_spec,
								std::string tile_stringspec,
								int8_t food,
								int8_t work,
								int8_t gold)
{
	tile.tile_ground = tile_ground;
	tile.tile_stringground = tile_stringground;
	tile.tile_spec = tile_spec;
	tile.tile_stringspec = tile_stringspec;
	tile.food = food;
	tile.work = work;
	tile.gold = gold;
}

/*
* NAME : newGameSettlerSpawn
* ROLE : Création des position pour les settlers de chaque joueurs
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : position pour les settlers de chaque joueurs
* RETURNED VALUE    : void
*/
void GamePlay::newGameSettlerSpawn(Sysinfo& sysinfo)
{
	/*
		association des vecteurs de position (x,y) avec les settlers de départ
	*/
	unsigned int selectunit(0);
	for (unsigned int p(0); p < sysinfo.var.s_player.tabUnit_Struct.size(); p++)
	{
		if (sysinfo.var.s_player.tabUnit_Struct[p].name.compare("settler") == 0)
		{
			selectunit = p;
			break;
		}
		else
		{
			/* N/A */
		}
	}

	std::vector<randomPos> tabRandom;
	for (unsigned int i(0); i < sysinfo.tabplayer.size(); i++)
	{
		try
		{
			makeRandomPosTab(sysinfo, tabRandom);
		}
		catch (const std::string& msg)
		{
			randomPos RandomPOS;
			makeRandomPos(RandomPOS, sysinfo.map.maps, sysinfo.map.toolBarSize, sysinfo.map.tileSize);
			tabRandom.push_back(RandomPOS);
			LoadConfig::logfileconsole(msg);
			throw("[ERROR]___: [Catch]___: makeRandomPosTab, Too many Iterations : No Critical Error -> Continue");
		}
		sysinfo.tabplayer[i]->addUnit
		(	"settler",
			tabRandom[i].x,
			tabRandom[i].y,
			sysinfo.var.s_player.tabUnit_Struct[selectunit].life,
			sysinfo.var.s_player.tabUnit_Struct[selectunit].atq,
			sysinfo.var.s_player.tabUnit_Struct[selectunit].def,
			sysinfo.var.s_player.tabUnit_Struct[selectunit].movement,
			sysinfo.var.s_player.tabUnit_Struct[selectunit].level);
	}
}

/*
* NAME : makeRandomPosTab
* ROLE : Créér autant de vecteur de position (x,y) que de joueur initial
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : std::vector<randomPos>& : vecteurs de positions
* OUTPUT PARAMETERS : std::vector<randomPos>& : vecteurs de positions
* RETURNED VALUE    : void
*/
void GamePlay::makeRandomPosTab(Sysinfo& sysinfo, std::vector<randomPos>& tabRandom)
{
	/*
		créér autant de vecteur de position (x,y) que de joueur initial
	*/
	randomPos RandomPOS;
	bool continuer(true);
	unsigned int nbConditionCheck(0);
	unsigned int iteration(0);

	while (continuer)
	{
		iteration++;
		if (iteration > MAX_RANDOM_POS_ITERATION)
		{
			throw("[ERROR]___: makeRandomPosTab, Too many Iterations");
		}
		else
		{
			/* N/A */
		}

		makeRandomPos(RandomPOS, sysinfo.map.maps, sysinfo.map.toolBarSize, sysinfo.map.tileSize);
		if (conditionground(sysinfo, RandomPOS))
		{
			if (tabRandom.size() > 1)
			{
				nbConditionCheck = 0;
				for (unsigned int i = 0; i < tabRandom.size(); i++)
				{
					if (conditionspace(RandomPOS, tabRandom, sysinfo.map.tileSize, i))
					{
						nbConditionCheck++;
						if (nbConditionCheck == tabRandom.size())
						{
							continuer = false;
							break;
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
			}
			else
				continuer = false;
		}
		else
		{
			/* N/A */
		}
	}
	tabRandom.push_back(RandomPOS);
}

/*
* NAME : makeRandomPos
* ROLE : créér un vecteur de position (x,y) aléatoire respectant la taille de l'écran
* INPUT  PARAMETERS : randomPos& RandomPOS : couple de positions
* INPUT  PARAMETERS : unsigned int toolBarSize: taille de la barre d'outil
* INPUT  PARAMETERS : unsigned int tileSize
* OUTPUT PARAMETERS : un vecteur de position
* RETURNED VALUE    : void
*/
void GamePlay::makeRandomPos(	randomPos& RandomPOS,
								std::vector<std::vector<Tile>> maps,
								unsigned int toolBarSize,
								unsigned int tileSize)
{
	/*
		créér un vecteur de position (x,y) aléatoire respectant la taille de l'écran
	*/
	int x((rand() % ((unsigned int)(maps.size() * tileSize) - (unsigned int)(toolBarSize * tileSize))) + (toolBarSize * tileSize));
	int y((rand() % (maps[0].size() * tileSize)));
	RandomPOS.x = (int)ceil(x / tileSize) * tileSize;
	RandomPOS.y = (int)ceil(y / tileSize) * tileSize;
}

/*
* NAME : conditionspace
* ROLE : condition pour valider les coordonnées crées:
* ROLE : - etre en dehors d'un carré d'influence (ici tileSize * 8) d'une autre entitée
* INPUT  PARAMETERS : randomPos& RandomPOS : couple de positions
* INPUT  PARAMETERS : std::vector<randomPos>& : vecteurs de positions
* INPUT  PARAMETERS : unsigned int tileSize
* INPUT  PARAMETERS : couple de positions courant
* OUTPUT PARAMETERS : validation des positions
* RETURNED VALUE    : true -> condition de position validée / false -> non valide
*/
bool GamePlay::conditionspace(	randomPos& RandomPOS,
								std::vector<randomPos>& tabRandom,
								unsigned int tileSize,
								unsigned int i)
{
	/*
		condition pour valider les coordonnées crées:
					- etre en dehors d'un carré d'influence (ici tileSize * 8) d'une autre entitée
	*/
	int spaceBetweenSettler(tileSize * 16);

	if (RandomPOS.x < (tabRandom[i].x - spaceBetweenSettler)
		|| RandomPOS.x >(tabRandom[i].x + spaceBetweenSettler)
		|| RandomPOS.y < (tabRandom[i].y - spaceBetweenSettler)
		|| RandomPOS.y >(tabRandom[i].y + spaceBetweenSettler))
		return true;
	else
		return false;
}

/*
* NAME : conditionground
* ROLE : condition pour valider les coordonnées crées:
* ROLE : - etre sur une tile possédant la caractéristique d'etre du sol
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* INPUT  PARAMETERS : std::vector<randomPos>& : vecteurs de positions
* OUTPUT PARAMETERS : validation des positions
* RETURNED VALUE    : true -> condition de position validée / false -> non valide
*/
bool GamePlay::conditionground(Sysinfo& sysinfo, randomPos& RandomPOS)
{
	/*
		condition pour valider les coordonnées crées:
			- etre sur une tile possédant la caractéristique d'etre du sol
	*/
	for (unsigned int i(0); i < sysinfo.map.maps.size(); i++) 
	{
		for (unsigned int j(0); j < sysinfo.map.maps[i].size(); j++) 
		{
			if (sysinfo.map.maps[i][j].tile_x == RandomPOS.x && sysinfo.map.maps[i][j].tile_y == RandomPOS.y) 
			{
				if (sysinfo.map.maps[i][j].tile_ground == grass)
					return true;
				return false;
			}
			else
			{
				/* N/A */
			}
		}
	}
	return false;
}

/* *********************************************************
 *			 END GamePlay::STATIC::NEW-GAME				   *
 ********************************************************* */


 
 
/* *********************************************************
 *			 START GamePlay::STATIC::NextTurn			   *
 ********************************************************* */


/*
* NAME : nextTurn
* ROLE : Action à réaliser lors du passage à un nouveau tour 
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : passage à un nouveau tour 
* RETURNED VALUE    : void
*/
void GamePlay::nextTurn(Sysinfo& sysinfo)
{
	for (unsigned int i(0); i < sysinfo.tabplayer.size(); i++) 
	{
		for (unsigned int j(0); j < sysinfo.tabplayer[i]->GETtabUnit().size(); j++) 
		{
			sysinfo.tabplayer[i]->GETtheUnit(j)->RESETmovement();
			sysinfo.tabplayer[i]->GETtheUnit(j)->heal(sysinfo.map.maps, i);
		}
		for (unsigned int j(0); j < sysinfo.tabplayer[i]->GETtabCity().size(); j++)
		{
			sysinfo.tabplayer[i]->GETtheCity(j)->foodNextTurn();
		}
	}
	sysinfo.var.nbturn++;
}


/* *********************************************************
 *				END GamePlay::STATIC::NextTurn			   *
 ********************************************************* */

/*
*	End Of File : GamePlay.cpp
*/
