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

#include "loadUnitAndSpec.h"

using namespace std;

void loadUnitAndSpec(sysinfo& information){
	ifstream UNIT("bin/UNIT.txt");
	if (UNIT){
		string destroy;
		tabUnitAndSpec currentUnit;

		UNIT >> destroy;
		UNIT >> information.variable.unitNameMaxToCreate;

		for (unsigned int i = 0; i < information.variable.unitNameMaxToCreate; i++) {
			UNIT >> destroy;
			UNIT >> currentUnit.name;

			UNIT >> destroy;
			UNIT >> currentUnit.life;

			UNIT >> destroy;
			UNIT >> currentUnit.atq;

			UNIT >> destroy;
			UNIT >> currentUnit.def;

			UNIT >> destroy;
			UNIT >> currentUnit.movement;

			UNIT >> destroy;
			UNIT >> currentUnit.level;
			information.variable.s_tabUnitAndSpec.push_back(currentUnit);
		}
		
	}
	else
		logfileconsole("ERREUR: Impossible d'ouvrir le fichier bin/UNIT.txt");
}