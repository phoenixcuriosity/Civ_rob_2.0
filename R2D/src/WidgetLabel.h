/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.9.0
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

#ifndef WidgetLabel_H
#define WidgetLabel_H

#include <string>

#include <glm/glm.hpp>
#include <CEGUI/CEGUI.h>

#include "ColorRGBA8.h"

namespace R2D
{

class Window;
class SpriteBatch;
class SpriteFont;
struct ColorRGBA8;

class WidgetLabel
{
public:
	WidgetLabel() {};
	WidgetLabel(CEGUI::Window* w, const std::string& text, float scale) :
		widget(w), text(text), scale(scale) {};
	void draw(SpriteBatch& sb, SpriteFont& sf, Window& w);

	CEGUI::Window* widget = nullptr;
	std::string text = "";
	ColorRGBA8 color = COLOR_WHITE;
	float scale = 0.7f;
};

}

#endif // !WidgetLabel_H





