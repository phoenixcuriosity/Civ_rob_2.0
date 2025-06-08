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

#include "WidgetLabel.h"

#include "Window.h"
#include "SpriteFont.h"
#include "SpriteBatch.h"

#include <glm/glm.hpp>
#include <CEGUI/CEGUI.h>

void
R2D::WidgetLabel
::draw(R2D::SpriteBatch& sb, R2D::SpriteFont& sf, R2D::Window& w)
{
	if (!widget->isVisible()) return;
	glm::vec2 pos;
	pos.x = widget->getInnerRectClipper().getPosition().d_x + widget->getInnerRectClipper().getWidth() / 2.0f;
	pos.y = w.GETscreenHeight() - widget->getInnerRectClipper().getPosition().d_y;

	sf.draw(sb, text.c_str(), pos, glm::vec2(0.24f), 0.0f, color, Justification::MIDDLE);
}
