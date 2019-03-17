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

#include "LIB.h"

#ifndef HashTable_H
#define HashTable_H


// coefficient multiplieur de taille initiale 
const unsigned int INIT_SIZE_MULTIPLIER = 5;

//--- HashTable ---------------------------------------------------------------------------------------------------------------------------------------
/*

	HashTable :
	Cette classe permet :
	*	static -> Hash

*/
class HashTable
{

public:

	static unsigned int hash(const std::string& name, const unsigned int length);

	static int checkDoubleName(std::string name, std::vector<Texture*>& tabPos);

	static Texture* searchPos(std::string msg, std::vector<Texture*>& tabPos);

	static void addPos(std::vector<Texture*>& tabPos, std::string msg, int x, int y);

	static void deletePos(std::vector<Texture*>& tabPos, std::string msg);


public:

	inline unsigned int GETnbItem()const { return _nbItem; };


public:

	inline void incrementItem() { _nbItem++; };

	inline void decrementItem() { _nbItem--; };


public:

	inline static bool assertNULL(Texture* cell)
	{
		if (cell != NULL)
		{
			return true;
		}
		return false;
	};

private:

	unsigned int _nbItem;

};

template<class T>
void fillTabHachage(T& tabPos, std::vector<unsigned int>& tabIndex)
{
	T temp;
	temp.resize(tabPos.size());
	tabIndex.clear();

	unsigned int nombreHache = 0;
	for (unsigned int i = 0; i < tabPos.size(); i++)
	{

		if (tabPos[i] != nullptr)
		{
			nombreHache = HashTable::hash(tabPos[i]->GETname(), tabPos.size());
			if (temp[nombreHache] == nullptr)
			{
				temp[nombreHache] = tabPos[i];
				tabIndex.push_back(nombreHache);
			}
			else
			{
				while (true)
				{
					++nombreHache %= temp.size();
					if (temp[nombreHache] == nullptr)
					{
						temp[nombreHache] = tabPos[i];
						tabIndex.push_back(nombreHache);
						break;
					}
				}
			}
		}
	}
	tabPos = temp;
}
template<class T>
unsigned int searchIndex(std::string msg, const T& tabPos)
{
	unsigned int nb = HashTable::hash(msg, tabPos.size());

	unsigned int iteration = 0;
	while (true)
	{
		if (tabPos[nb] != nullptr)
		{
			if (tabPos[nb]->GETname().compare(msg) == 0)
			{
				return nb;
			}
		}


		++nb %= tabPos.size();
		iteration++;

		if (iteration >= tabPos.size())
		{
			std::cout << std::endl << "____WARNING:SearchIndex():Max Iteration: " + msg + " not found" << std::endl;
			return 0;
		}
	}
}

#endif /* HashTable_H */

/*
*	End Of File
*/
