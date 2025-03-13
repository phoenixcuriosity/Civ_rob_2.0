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

#include "Screen.h"

#include "ResourceManager.h"

bool 
R2D::CScreen
::init(const int width, const int height)
{
	if (!m_isInitialized)
	{
		m_camera.init(width, height);
		m_camera.SETposition(glm::vec2(width / 2, height / 2));
		m_cameraHUD.init(width, height);
		m_cameraHUD.SETposition(glm::vec2(width / 2, height / 2));

		m_spriteBatchHUDDynamic.init();
		m_spriteBatchHUDStatic.init();

		m_gui.init(ResourceManager::getFile(e_Files::GUIPath)->getPath());
	}

	initAll();
	return true;
}

bool 
R2D::CScreen
::end()
{
	m_gui.destroy();
	return true;
}

void 
R2D::CScreen
::initAll()
{
	doInitOptimizeTexture();
	initUI();
	initHUDText();
}

void 
R2D::CScreen
::initUI()
{
	if (!m_isInitialized)
	{
		m_gui.loadScheme(GUI_SCHEME_A);
		m_gui.loadScheme(GUI_SCHEME_B);

		m_gui.setFont(GUI_FONT);

		m_gui.setMouseCursor(GUI_MOUSE_CURSOR);
		m_gui.showMouseCursor();

		/* HIDE normal mouse cursor */
		SDL_ShowCursor(0);

		m_isInitialized = true;
	}
	
	doInitUI();
}

void 
R2D::CScreen
::initHUDText()
{
	m_spriteBatchHUDStatic.begin();

	doInitHUDText();

	m_spriteBatchHUDStatic.end();
}

void 
R2D::CScreen
::drawAll()
{
	m_camera.update();
	m_cameraHUD.update();

	/* line for CEGUI because CEGUI doesn't do it, do not remove  */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Back */
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	R2D::ResourceManager::getGLSLProgram().use();
	/* use GL_TEXTURE0 for 1 pipe; use GL_TEXTURE1/2/3 for multiple */
	glActiveTexture(GL_TEXTURE0);

	const GLint textureLocation
		= R2D::ResourceManager::getGLSLProgram().getUnitformLocation(GLSL_SAMPLER);
	glUniform1i(textureLocation, 0);

	/* --- camera --- */
	/* GL - get parameter P */
	const GLint pLocation
		= R2D::ResourceManager::getGLSLProgram().getUnitformLocation(GLSL_SAMPLER_UNIFORM);

	/* Copy camera matrix */
	glm::mat4 cameraMatrix = m_camera.GETcameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_spriteBatchHUDDynamic.begin();

	doDrawAll();

	/* Copy camera matrix */
	glm::mat4 cameraMatrixHUD = m_cameraHUD.GETcameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrixHUD[0][0]));

	m_spriteBatchHUDDynamic.end();

	m_spriteBatchHUDStatic.renderBatch();
	m_spriteBatchHUDDynamic.renderBatch();

	/* --- GL unbind --- */
	glBindTexture(GL_TEXTURE_2D, 0);
	R2D::ResourceManager::getGLSLProgram().unuse();

	/* --- Draw UI --- */
	m_gui.draw();
}

void 
R2D::CScreen
::updateInputManager(SDL_Event& ev, InputManager& resourceManager)
{
	m_gui.onSDLEvent(ev, resourceManager);
}
