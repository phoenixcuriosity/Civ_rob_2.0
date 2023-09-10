/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.0.0
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

#include "ColorRGBA8.h"

using namespace R2D;


void ColorRGBA8C::initializeRGBA8Map()
{
	m_colorRGBA8Map.emplace("WHITE", COLOR_WHITE);
	m_colorRGBA8Map.emplace("BLACK", COLOR_BLACK);
	m_colorRGBA8Map.emplace("LIGHT_GREY", COLOR_LIGHT_GREY);
	m_colorRGBA8Map.emplace("GREY", COLOR_GREY);
	m_colorRGBA8Map.emplace("GREY", COLOR_DARK_GREY);
	m_colorRGBA8Map.emplace("RED", COLOR_RED);
	m_colorRGBA8Map.emplace("GREEN", COLOR_GREEN);
	m_colorRGBA8Map.emplace("BLUE", COLOR_BLUE);
	m_colorRGBA8Map.emplace("GOLD", COLOR_GOLD);
	m_colorRGBA8Map.emplace("WHITE_T50", COLOR_WHITE_T50);
	m_colorRGBA8Map.emplace("WHITE_T25", COLOR_WHITE_T25);
}

ColorRGBA8& ColorRGBA8C::getRGBA8Color
(
	const std::string colorName
)
{
	auto it{ m_colorRGBA8Map.find(colorName) };

	if (it == m_colorRGBA8Map.end())
	{
		return m_colorRGBA8Map["WHITE"];
	}
	return it->second;
}