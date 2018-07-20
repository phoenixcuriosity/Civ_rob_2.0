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

	Buttons :
	Cette classe est la représentation d'un objet Buttons qui est heritié de la classe mère Texture

	Un Buttons est défini par une image et une imageOn qui sont contenu dans SDL_Texture* de la classe mère et celle-ci 
	Cet objet hérite de tous les attributs de la classe Texture
	_x et _y représente forcément le coin haut gauche de la texture du boutons
	_size représente la taille de la police d'écriture
	_txtcolor représente la couleur de l'écriture
	_backcolor représente la couleur du fond du bouton
	_on représente l'état du bouton l'image est normal ou On
	

	searchButton permet de chercher le bouton en fonction de son nom ainsi que de l'ecran et de la position x,y
	renderButton permet d'afficher le bouton avec l'aide de la fonction de la SDL2.0.6 SDL_RenderCopy
	resetOnStatescreen permet de reset l'image si l'on n'est plus sur la bonne séléction ou sur le bon écran
	resetOnPlayer permet de reset l'image si le joueur séléctionner n'est plus le meme
	changeOn permet de changer entre l'imageOn et l'image

*/

#ifndef Buttons_H
#define Buttons_H

#include "Texture.h"


class Buttons : public Texture {
public:
	Buttons() {};
	Buttons(SDL_Texture*, const std::string&, unsigned int, unsigned int, int, int, int, int,
		SDL_Texture*, int, int, int, SDL_Color, SDL_Color, bool = false);
	~Buttons();


	virtual unsigned int testcolor(SDL_Color, SDL_Color) const;
	virtual unsigned int searchButton(std::string& msg, unsigned int, signed int, signed int);

	virtual void resetOnStatescreen(unsigned int, unsigned int);
	virtual void resetOnPlayer(unsigned int, std::vector<std::string> );
	virtual bool renderButton(SDL_Renderer*&, unsigned int);
	virtual bool renderButtonTestString(SDL_Renderer*&, unsigned int, std::string& msg, int newx = -1, int newy = -1, int center = 0);

	virtual void changeOn();

	virtual SDL_Texture* GETimageOn() const;
	virtual int GETx() const;
	virtual int GETy() const;
	virtual int GETsize() const;
	virtual SDL_Color GETtxtcolor() const;
	virtual SDL_Color GETbackcolor() const;
	virtual bool GETon() const;

	virtual void SETon(bool);

private:
	SDL_Texture* _imageOn;
	int _x;
	int _y;
	int _size;
	SDL_Color _txtcolor;
	SDL_Color _backcolor;
	bool _on;

};


#endif // !Buttons_H

