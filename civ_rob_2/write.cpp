/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.7

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Civ_rob_2

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

#include "write.h"
#include "sdl.h"

using namespace std;


void loadImage(sysinfo& information, unsigned int& index, const std::string &path, const std::string &msg, Uint8 alpha, int x, int y, int cnt) {
	
	
	int iW = 0, iH = 0, xc = 0, yc = 0;
	if (x != -1 && y != -1)
		xc = x, yc = y;

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != NULL) {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(information.ecran.renderer, loadedSurface);
		if (newTexture != NULL) {
			if (alpha != (Uint8)255) {
				if (SDL_SetTextureAlphaMod(newTexture, alpha) != 0)
					logSDLError(cout, "alpha : ");
			}
			centrage(xc, yc, loadedSurface->w, loadedSurface->h, cnt);
			information.allTextures.tabTexture.push_back(new Texture(newTexture, msg, information.ecran.statescreen, information.variable.select, xc, yc, loadedSurface->w, loadedSurface->h));
			index++;
		}
		else
			logfileconsole("___________ERROR : loadImage : cannot create Texture from : " + path);
		SDL_FreeSurface(loadedSurface);
	}
	else
		logfileconsole("___________ERROR : loadImage : path or image are corrupt : " + path);
}

void loadwritetxt(sysinfo& information, const std::string &msg, SDL_Color color, int size, unsigned int x, unsigned int y, int cnt) {
	SDL_Texture *image = renderText(information.ecran.renderer, msg, color, information.allTextures.font[size]);
	int xc = x, yc = y, iW = 0, iH = 0;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);
	information.allTextures.tabTexture.push_back(new Texture(image, msg, information.ecran.statescreen, information.variable.select, xc, yc, iW, iH));
}
void loadwritetxtshaded(sysinfo& information, const std::string &msg, SDL_Color color, SDL_Color backcolor, int size, unsigned int x, unsigned int y, int cnt) {
	SDL_Texture *image = renderTextShaded(information.ecran.renderer, msg, color, backcolor, information.allTextures.font[size]);
	int xc = x, yc = y, iW = 0, iH = 0;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);
	information.allTextures.tabTexture.push_back(new Texture(image, msg, information.ecran.statescreen, information.variable.select, xc, yc, iW, iH));
}



void writetxt(sysinfo& information, const std::string &msg, SDL_Color color, int size, unsigned int x, unsigned int y, int cnt) {
	SDL_Texture *image = renderText(information.ecran.renderer, msg, color, information.allTextures.font[size]);
	loadAndWriteImage(information.ecran.renderer, image, x, y, cnt);
	SDL_DestroyTexture(image);
}

void writetxtshaded(sysinfo& information, const std::string &msg, SDL_Color color, SDL_Color backcolor, int size, unsigned int x, unsigned int y, int cnt) {
	SDL_Texture *image = renderTextShaded(information.ecran.renderer, msg, color, backcolor, information.allTextures.font[size]);
	loadAndWriteImage(information.ecran.renderer, image, x, y, cnt);
	SDL_DestroyTexture(image);
}

void loadAndWriteImage(SDL_Renderer*& renderer, SDL_Texture *image, unsigned int x, unsigned int y, int cnt) {
	int xc = x, yc = y, iW = 0, iH = 0;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);

	SDL_Rect dst;
	dst.x = xc;
	dst.y = yc;
	dst.w = iW;
	dst.h = iH;
	SDL_RenderCopy(renderer, image, NULL, &dst);
}


void centrage(int& xc, int& yc, int iW, int iH, int cnt) {
	switch (cnt) {
	case nocenter:
		break;
	case center_x:
		xc = xc - (iW / 2);
		break;
	case center_y:
		yc = yc - (iH / 2);
		break;
	case center:
		xc = xc - (iW / 2);
		yc = yc - (iH / 2);
		break;
	}
}