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

#ifndef GUI_H
#define GUI_H

#include "API_fwd.h"

#include <glm/glm.hpp>
#include <SDL/SDL.h>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

namespace R2D
{

	namespace GUI_MOUSE
	{
		/* SDL : Define the number of mouse click ONE */
		const int ONE_CLICK = 1;

		/* SDL : Define the number of mouse clicks TWO */
		const int TWO_CLICKS = 2;

		/* SDL : Define if the wheel scroll up */
		const int MOUSE_SCROLL_UP = 1;

		/* SDL : Define if the wheel scroll down */
		const int MOUSE_SCROLL_DOWN = -1;
	}

	class GUI
	{
	public:
		GUI();
		~GUI();

		void init(const std::string& filePath);
		void destroy();

		void draw();
		void update();

		void setMouseCursor(const std::string& imageFile);
		void showMouseCursor();
		void hideMouseCursor();

		void onSDLEvent(SDL_Event& ev, InputManager& inputManager);

		void loadScheme(const std::string& shemeFile);
		void setFont(const std::string& fontFile);

		CEGUI::Window* createWidget
		(
			const std::string& type,
			const glm::vec4& destRectPerc,
			const glm::vec4& destRectPix,
			const std::string& name = ""
		);

		static void setWidgetDestRect
		(
			CEGUI::Window* window,
			const glm::vec4& destRectPerc,
			const glm::vec4& destRectPix
		);

		static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; };
		const CEGUI::GUIContext* getContext() { return m_context; };

		CEGUI::MouseButton SDLButtonToCEGUI(Uint8 sdlButton);

	private:
		Uint32 m_lasTime = 0;

		static CEGUI::OpenGL3Renderer* m_renderer;
		CEGUI::GUIContext* m_context = nullptr;
		CEGUI::Window* m_root = nullptr;
	};

}

#endif // !GUI_H



