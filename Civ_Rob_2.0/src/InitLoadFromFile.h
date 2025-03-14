/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2024 (robin.sauter@orange.fr)

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

#ifndef InitLoadFromFile_H
#define InitLoadFromFile_H

#include "LIB.h"

#include "Unit.h"

class InitLoadFromFile
{
private:

	using VectUnitTemplate = std::vector<Unit::Template>;

public:

	static void loadMainMapConfig(MainMap& mainMap);

	static void initFromFile(VectUnitTemplate& vectUnitTemplate, VectCityName& vectCityName);

private:

	static void loadUnitAndSpec(VectUnitTemplate& vectUnitTemplate);

	static void loadCitiesNames(VectCityName& vectCityName);

};

#endif /* InitLoadFromFile_H */
