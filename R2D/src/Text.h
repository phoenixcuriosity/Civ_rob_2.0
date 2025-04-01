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

#ifndef Text_H
#define Text_H

#include "API_fwd.h"

#include "ColorRGBA8.h"
#include "Window.h"


namespace R2D
{

/// For text justification
enum class Justification
{
	LEFT, MIDDLE, RIGHT
};


struct Text_t
{
	std::string text;
	double x;
	double y;
	float size;
	float alpha;
	R2D::ColorRGBA8 color;
	R2D::Justification justification;
};

struct Text_json
{
	std::string text;
	double x;
	double y;
	float size;
	float alpha;
	std::string color;
	std::string justification;
};

class Text
{
public:
	
	Text() {};
	~Text() {};

public:

	static void getTextFromFile
	(
		const e_Files name,
		MapTexts& mapTexts
	);

	static void displayTextFromFile
	(
		const MapTexts& mapTexts,
		const Window& window,
		SpriteBatch& spriteBatchHUDStatic
	);
};

}

#endif // !Text_H

