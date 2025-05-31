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

#include "AudioEngine.h"
#include "Camera2D.h"
#include "GUI.h"
#include "SpriteBatch.h"

namespace R2D
{

class CScreen
{
public:
	CScreen() : m_camera(), m_cameraHUD(), m_spriteBatchHUDDynamic(),
		m_spriteBatchHUDStatic(), m_gui(), m_isInitialized(false) {};

public:

	bool init(const int width, const int height);
	bool end();

public:

	void drawAll();
	void updateInputManager(SDL_Event& ev, InputManager& resourceManager);

private:

	void initAll();
	void initUI();
	void initHUDText();

	virtual void doInitOptimizeTexture() = 0;
	virtual void doInitUI() = 0;
	virtual void doInitHUDText() = 0;
	virtual void doDrawAll() = 0;

public:

	Camera2D& getCamera() { return m_camera; };

private:
	static constexpr char GUI_SCHEME_A[] = "AlfiskoSkin.scheme";
	static constexpr char GUI_SCHEME_B[] = "TaharezLook.scheme";
	static constexpr char GUI_FONT[] = "DejaVuSans-10";
	static constexpr char GUI_MOUSE_CURSOR[] = "AlfiskoSkin/MouseArrow";

	static constexpr char GLSL_SAMPLER[] = "mySampler";
	static constexpr char GLSL_SAMPLER_UNIFORM[] = "P";

protected:
	Camera2D m_camera;
	Camera2D m_cameraHUD;

	SpriteBatch m_spriteBatchHUDDynamic;
	SpriteBatch m_spriteBatchHUDStatic;

	GUI m_gui;

private:
	bool m_isInitialized;
};

}