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
#pragma once

#include <string>
#include <Windows.h> // DEVMODE

struct SDL_Window;

namespace R2D
{

///< Donne la fréquence de rafraichissement de l'écran en Hz
inline unsigned int getRefreshRate()
{
	DEVMODE screen;
	memset(&screen, 0, sizeof(DEVMODE));
	if (EnumDisplaySettings(NULL, 0, &screen))
	{
		return (unsigned int)screen.dmDisplayFrequency;
	}
	return 0;
}

///< fréquence de rafraichissement de l'écran en Hz
static const unsigned int SCREEN_REFRESH_RATE = getRefreshRate();

class Window
{
public:
	Window() : m_sdlWindow(nullptr), m_screenWidth(0), m_screenHeight(0) {};
	~Window();

	int create(const std::string& name,
			   const int screenWidth,
			   const int screenHeight,
			   const unsigned int currentFlags);

	void swap();

	int GETscreenWidth()const { return m_screenWidth; };
	int GETscreenHeight()const { return m_screenHeight; };

	void SETscreenWidth(int screenWidth) { m_screenWidth = screenWidth; };
	void SETscreenHeight(int screenHeight) { m_screenHeight = screenHeight; };

	double getWidthPositionScaleToWindow(const double position2Scale)const;

	double getHeightPositionScaleToWindow(const double position2Scale)const;


public:

	/* ----------------------------------------------------------------------------------- */
	/* NAME : getHorizontal																   */
	/* ROLE : Calcul de la longueur en pixels de la fenetre								   */
	/* INPUT : unsigned int tileSize : taille en pixel d'une tile 						   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	static unsigned int getHorizontal();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : getVertical																   */
	/* ROLE : Calcul de la hauteur en pixels de la fenetre								   */
	/* INPUT : unsigned int tileSize : taille en pixel d'une tile 						   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	static unsigned int getVertical();

private:

	enum Flags : unsigned int
	{
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};

	static constexpr double WINDOW_SCALE_PERCENT_MIN = 0.0;
	static constexpr double WINDOW_SCALE_PERCENT_MAX = 100.0;
	static constexpr double WINDOW_SCALE_SCREEN_WIDTH_MIN = 0.0;
	static constexpr double WINDOW_SCALE_SCREEN_HEIGHT_MIN = 0.0;

private:

	SDL_Window* m_sdlWindow;
	int m_screenWidth;
	int m_screenHeight;
};

}