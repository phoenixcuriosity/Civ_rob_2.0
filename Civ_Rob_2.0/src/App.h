/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.7.0
	file version : 1.5

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

#ifndef App_H
#define App_H

#include "LIB.h"

#include <fstream> // logger
#include <memory>

#include <RealEngine2D/src/IMainGame.h>

#include "GamePlayScreen.h"
#include "MainMenuScreen.h"
#include "ReloadMenuScreen.h"
#include "NewGameScreen.h"

#include "SaveReload.h"

const std::string configFilePath = "bin/filePath.xml";

struct File
{
	std::string log = "bin/log/log.txt";

	std::string readme = EMPTY_STRING;
	std::string texts = EMPTY_STRING;
	std::string mainMap = EMPTY_STRING;
	std::string buildings = EMPTY_STRING;
	std::string citiesNames = EMPTY_STRING;
	std::string units = EMPTY_STRING;
	std::string specNames = EMPTY_STRING;

	std::string saveInfo = EMPTY_STRING;

	std::string saveMaps = EMPTY_STRING;
	std::string savePlayers = EMPTY_STRING;

	std::string colorShadingVert = EMPTY_STRING;
	std::string colorShadingFrag = EMPTY_STRING;

	std::string imagesPath = EMPTY_STRING;
	std::string GUIPath = EMPTY_STRING;
};

class App : public RealEngine2D::IMainGame
{
public:
	App();
	~App();

	virtual void onInit() override;
	virtual void onExit() override;
	virtual void addScreens() override;


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initFile																	   */
	/* ROLE : Initialisation des fichiers : log											   */
	/* INPUT : struct File& : nom des fichiers											   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initFile();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initMain																	   */
	/* ROLE : Chargement des informations de la configuration du jeu					   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initMain();


	void destroy();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : exitError																	   */
	/* ROLE : Enregistre l'erreur survenue et termine le programme de façon sécurisée	   */
	/* INPUT : const std::string msg : message de l'erreur								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void exitError
	(
		const std::string& msg
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deleteAll																	   */
	/* ROLE : Destruction des allocations dynamique du programme						   */
	/* ROLE : Destruction de la fenetre et du Renderer de la SDL						   */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void deleteAll
	(
		
	);


public:

	/* *********************************************************
	 *						Logger							   *
	 ********************************************************* */

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : logfileconsole															   */
	/* ROLE : Transmission du message sur la console et dans le fichier log.txt			   */
	/* INPUT : const std::string msg : message											   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void logfileconsole
	(
		const std::string& msg
	);

private:
	MainMenuScreen* m_mainMenuScreen;
	NewGameScreen* m_newGameScreen;
	ReloadMenuScreen* m_reloadMenuScreen;
	GamePlayScreen* m_gamePlayScreen;

	File m_file;

	SaveReload m_saveReload;

	std::ofstream m_logger;
};




#endif // !App_H

