/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.14
	file version : 1.0

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

#include "HashTable.h"
#include "Texture.h"

///////////////////////////// HashTable //////////////////////////////
/* HashTable :: STATIC */

unsigned int HashTable::hash(const std::string& name, const unsigned int length)
{
	long hash = 0;
	const unsigned int len_s = name.size();
	for (unsigned int i = 0; i < len_s; i++)
	{
		hash += (long)pow(151, len_s - (i + 1)) * name[i];
		hash = hash % length;
	}
	return (unsigned int)hash;
}
int HashTable::checkDoubleName(std::string name, std::vector<Texture*>& tabPos)
{
	if (searchIndex(name, tabPos) > 0)
	{
		std::cout << std::endl << "____WARNING:checkDoubleName(): " + name + " already found" << std::endl;
		return -1;
	}
	return 0;
}
Texture* HashTable::searchPos(std::string msg, std::vector<Texture*>& tabPos)
{
	unsigned int nb = hash(msg, tabPos.size());

	unsigned int iteration = 0;
	while (true)
	{
		if (tabPos[nb]->GETname().compare(msg) == 0)
		{
			return tabPos[nb];
		}

		++nb %= tabPos.size();
		iteration++;

		if (iteration >= (tabPos.size() * 2))
		{
			Texture* blank = NULL;
			std::cout << std::endl << "____WARNING:SearchPos():Max Iteration: " + msg + " not found" << std::endl;
			return blank;
		}
	}
}
void HashTable::addPos(std::vector<Texture*>& tabPos, std::string msg, int x, int y)
{
	if (checkDoubleName(msg, tabPos) >= 0)
	{
		//tabPos.push_back(new Pos(msg, x, y));
		//fillTabHachage(tabPos);
	}
}
void HashTable::deletePos(std::vector<Texture*>& tabPos, std::string msg)
{
	int index = searchIndex(msg, tabPos);
	if (index < 0)
	{
		std::cout << std::endl << "____WARNING:DeletePos():Request not completed: " + msg + " not found" << std::endl;
	}
	else
	{
		delete tabPos[index];
		tabPos[index] = NULL;
		tabPos.erase(tabPos.begin() + index);
		//fillTabHachage(tabPos);
	}
}

/*
*	End Of File
*/