/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.8

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

#include "sdl.h"

using namespace std;


void initfile(sysinfo& information){
	ofstream log(information.file.log);
	if (log){}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << information.file.log;
}



void logfileconsole(const std::string &msg){
	const std::string logtxt = "bin/log/log.txt";
	ofstream log(logtxt, ios::app);

	//std::time_t result = std::time(nullptr);
	//<< std::asctime(std::localtime(&result))

	if (log){
		cout << endl  << msg;
		log << endl << msg;
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}

void logSDLError(std::ostream &os, const std::string &msg){
	const std::string logtxt = "bin/log/log.txt";
	ofstream log(logtxt, ios::app);
	if (log){
		os << msg << " error: " << SDL_GetError() << std::endl;
		log << msg << " error: " << SDL_GetError() << std::endl;
	}
	else
		cout << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt << endl;
}

void initsdl(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font* font[]){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		cout << endl << "SDL could not initialize! SDL_Error: " << SDL_GetError();
	else{
		window = SDL_CreateWindow("Civ_rob_2",
			0, 0,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			 SDL_WINDOW_OPENGL);

		//	SDL_WINDOW_FULLSCREEN_DESKTOP or SDL_WINDOW_FULLSCREEN
		if (window == nullptr) {
			logSDLError(cout, "CreateWindow");
			SDL_Quit();
		}
		else
			logfileconsole("CreateWindow Success");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		//| SDL_RENDERER_PRESENTVSYNC
		if (renderer == nullptr) {
			logSDLError(cout, "CreateRenderer");
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
		else
			logfileconsole("CreateRenderer Success");

		if (TTF_Init() != 0) {
			logSDLError(std::cout, "TTF_Init");
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
		else
			logfileconsole("TTF_Init Success");


		const std::string fontFile = "arial.ttf";

		for (unsigned int i = 1; i < 80; i++)
			font[i] = TTF_OpenFont(fontFile.c_str(), i);

		logfileconsole("SDL_Init Success");
	}
}



SDL_Texture* renderText(SDL_Renderer*& renderer, const std::string &message, SDL_Color color, TTF_Font* font){
	
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr)
		logfileconsole("___________ERROR : renderText nullptr for : " + message);
	SDL_FreeSurface(surf);
	return texture;
}

SDL_Texture* renderTextShaded(SDL_Renderer*& renderer, const std::string &message, SDL_Color color, SDL_Color colorback, TTF_Font* font){

	SDL_Surface *surf = TTF_RenderText_Shaded(font, message.c_str(), color, colorback);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr)
		logfileconsole("___________ERROR : renderTextShaded nullptr for : " + message);
	SDL_FreeSurface(surf);
	return texture;
}

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