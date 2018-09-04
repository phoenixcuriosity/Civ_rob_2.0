/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.7

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

/*

	sdl :
	Ce module regroupe  l'initialisation des fichiers et de la fenetre créée par la librairie SDL
	Celuic-ci comprend par ordre d'apparition :
		- l'initialisation des fichiers utilisés et création du log -> initfile
		- l'enregistrement des données utiles dans le log et/ou dans le fichier erreur de la SDL -> logfileconsole et logSDLError
		- initialisation de la fenetre de jeux et création du tableau contenant une fonte -> initsdl
		- 2 fonctions permettant de créer une texture de texte avec un type différent (SDL2.0.6 : Blended et Shaded)

*/

#ifndef sdl_H
#define sdl_H

#include "civ_lib.h"

void initfile(sysinfo&);
void logfileconsole(const std::string &msg);
void logSDLError(std::ostream &os, const std::string &msg);
void initsdl(SDL_Window*&, SDL_Renderer*&, TTF_Font*[]);
SDL_Texture* renderText(SDL_Renderer*&, const std::string&, SDL_Color, TTF_Font*);
SDL_Texture* renderTextShaded(SDL_Renderer*&, const std::string&, SDL_Color, SDL_Color, TTF_Font*);

void loadImage(sysinfo&, std::vector<Texture*>& tabTexture, const std::string&, const std::string&, Uint8, int, int, int = 0);
void loadwritetxt(sysinfo&, std::vector<Texture*>& tabTexture, const std::string &msg, SDL_Color, int, unsigned int, unsigned int, int = 0);
void loadwritetxtshaded(sysinfo&, std::vector<Texture*>& tabTexture, const std::string &msg, SDL_Color, SDL_Color, int, unsigned int, unsigned int, int = 0);

void writetxt(sysinfo&, const std::string &msg, SDL_Color, int, unsigned int, unsigned int, int = 0);
void writetxtshaded(sysinfo&, const std::string &msg, SDL_Color, SDL_Color, int, unsigned int, unsigned int, int = 0);
void loadAndWriteImage(SDL_Renderer*&, SDL_Texture*, unsigned int, unsigned int, int = 0);
void centrage(int&, int&, int, int, int = 0);

#endif