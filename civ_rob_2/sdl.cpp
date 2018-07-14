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

#include "sdl.h"

using namespace std;


void initfile(sysinfo& information){
	ofstream log(information.file.log);
	if (log){}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << information.file.log;

	ofstream savemaps(information.file.Savemaps, ios::app);
	if (savemaps){}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << information.file.Savemaps;

	ofstream SavePlayer(information.file.SavePlayer, ios::app);
	if (SavePlayer){}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << information.file.SavePlayer;
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