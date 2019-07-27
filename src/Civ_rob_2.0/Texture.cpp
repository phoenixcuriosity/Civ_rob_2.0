/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.15
	file version : 1.8

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

#include "Texture.h"
#include "civ_lib.h"
#include "IHM.h"

///////////////////////////// Texture //////////////////////////////


/* *********************************************************
 *				START Texture::STATIC					   *
 ********************************************************* */


/*
 * NAME : loadImage
 * ROLE : Allocation dynamique d'une Texture avec ses caractéristiques
 * INPUT  PARAMETERS : SDL_Renderer*& renderer : le ptr sur la variable contenant SDL_Renderer
 * INPUT  PARAMETERS : std::vector<Texture*>& tabTexture : le tableau dans lequel sera stocké la Texture (allocation dynamique)
 * INPUT  PARAMETERS : Uint8 stateScreen, Uint8 select : les variables qui décrivent les différents état de l'écran et les spécifications de la séléction
 * INPUT  PARAMETERS : std::string path : le chemin d'accès ainsi que le nom de l'image à partir du fichier (inclure le type .png , .bmp ...)
 * INPUT  PARAMETERS : std::string msg : le nom qui permettra d'identifier la Texture dans le tableau
 * INPUT  PARAMETERS : Uint8 alpha : la valeur de transparance de la Texture -> enum Transparance_Type
 * INPUT  PARAMETERS : int x, int y	: les valeurs en pixel de la future position
 * INPUT  PARAMETERS : unsigned int w, unsigned int h : les valeurs de longueur et de largeur permettant de changer la définition de l'image originale sinon mettre NULL
 * INPUT  PARAMETERS : Uint16 angle : enum Rotation_Type
 * INPUT  PARAMETERS : Uint8 cnt : le type de centrage -> enum Center_Type
 * OUTPUT PARAMETERS : Allocation dynamique d'une Texture dans le tableau correspondant
 * RETURNED VALUE    : void
 */
void Texture::loadImage(	SDL_Renderer*& renderer,
							std::vector<Texture*>& tabTexture,
							Uint8 stateScreen,
							Uint8 select,
							std::string path,
							std::string msg,
							Transparance_Type alpha,
							int x,
							int y,
							unsigned int w,
							unsigned int h,
							Rotation_Type angle,
							Center_Type cnt
						)
{


	int xt = 0, yt = 0, wt = 0, ht = 0;
	if (x != -1 && y != -1)
		xt = x, yt = y;

	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (w == 0 && h == 0)
	{
		wt = loadedSurface->w;
		ht = loadedSurface->h;
	}
	else
	{
		wt = w;
		ht = h;
	}

	if (loadedSurface != nullptr)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != nullptr)
		{
			if (alpha != nonTransparent)
			{
				if (SDL_SetTextureAlphaMod(newTexture, alpha) != 0)
					IHM::logSDLError(std::cout, "alpha : ");
			}
			centrage(xt, yt, wt, ht, cnt);
			tabTexture.push_back(new Texture(renderer, newTexture, msg, stateScreen, select, xt, yt, wt, ht, alpha, angle, cnt));
		}
		else
			IHM::logfileconsole("[ERROR]___: ___________ERROR : loadImage : cannot create Texture from : " + path);
		SDL_FreeSurface(loadedSurface);
	}
	else
		IHM::logfileconsole("[ERROR]___:___________ERROR : loadImage : path or image are corrupt : " + path);
}


/*
 * NAME : centrage
 * ROLE : Permet de centrer la Texture selon enum Center_Type
 * INPUT  PARAMETERS : int& xc, int& yc : positions demandées
 * INPUT  PARAMETERS : int iW, int iH : largeur et hauteur de la Texture
 * INPUT  PARAMETERS : Uint8 cnt : type de centrage : par défaut nocenter
 * OUTPUT PARAMETERS : Permet de centrer la Texture
 * RETURNED VALUE    : void
 */
void Texture::centrage(	int& xc,
						int& yc,
						int iW,
						int iH,
						Center_Type cnt
					)
{
	switch (cnt)
	{
	case nocenter:
		break;
	case center_x:
		xc -= (iW / 2);
		break;
	case center_y:
		yc -= (iH / 2);
		break;
	case center:
		xc -= (iW / 2);
		yc -= (iH / 2);
		break;
	}
}


/* *********************************************************
 *				END Texture::STATIC						   *
 ********************************************************* */




/* *********************************************************
 *				START Texture::METHODS					   *
 ********************************************************* */


Texture::Texture(	SDL_Renderer*& renderer,
					SDL_Texture* image,
					std::string msg,
					Uint8 stateScreen,
					Uint8 select,
					unsigned int x,
					unsigned int y,
					int w,
					int h,
					Transparance_Type alpha,
					Rotation_Type angle,
					Center_Type center
				)
	: _renderer(renderer),
	_texture(image), _dst(rectangle(x, y, w, h)), _name(msg),
	_stateScreen(stateScreen), _select(select), _alpha(alpha), _angle(angle), _center(center)
{
}
Texture::~Texture()
{
	if (_renderer != nullptr)
		_renderer = nullptr;

	if (_texture != nullptr) 
	{
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
}


/*
 * NAME : rectangle
 * ROLE : Création d'un SDL_Rect à partir des positions x, y et des longueur et hauteur
 * INPUT  PARAMETERS : int xc, int yc, int w, int h : positions du rectangle
 * OUTPUT PARAMETERS : Destruction des allocations dynamique du programme
 * RETURNED VALUE    : SDL_Rect : Rectangle
 */
SDL_Rect Texture::rectangle(int x, int y, int w, int h)
{
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
	return rectangle;
}


/* *********************************************************
 *				END Texture::METHODS					   *
 ********************************************************* */



/* *********************************************************
 *			START Texture::METHODS::Affichage			   *
 ********************************************************* */



/*
 * NAME : render
 * ROLE : Permet de rendre la Texture au coordonnées voulues
 * INPUT  PARAMETERS : int = -1, int = -1 : coordonnées optionnelles
 * OUTPUT PARAMETERS : rendre la Texture
 * RETURNED VALUE    : void
 */
void Texture::render(int x, int y)
{
	if (x != -1 && y != -1)
	{
		_dst.x = x;
		_dst.y = y;
	}
	if (_angle == 0)
		SDL_RenderCopy(_renderer, _texture, NULL, &_dst);
	else
		SDL_RenderCopyEx(_renderer, _texture, NULL, &_dst, _angle, NULL, SDL_FLIP_NONE);
}


/*
 * NAME : renderTextureTestStates
 * ROLE : Test les attributs _stateScreen et _select qui correspondent
 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
 * OUTPUT PARAMETERS : Destruction des allocations dynamique du programme
 * RETURNED VALUE    : void
 */
bool Texture::renderTextureTestStates(Uint8 stateScreen, Uint8 select, int x, int y)
{
	if (_stateScreen == stateScreen && _select == select)
	{
		render(x, y);
		return true;
	}
	return false;
}

/* *********************************************************
 *			END Texture::METHODS::Affichage				   *
 ********************************************************* */









//--- Texte ----------------------------------------------------------------------------------------------------------------------------------------

/* *********************************************************
 *				START Texte::STATIC						   *
 ********************************************************* */


/*
 * NAME : createSDL_TextureFromTexte
 * ROLE : Permet de créer un ptr sur une SDL_Texture
 * ROLE : pour par la suite créer un objet Texte
 * INPUT  PARAMETERS : SDL_Renderer*& renderer : le ptr sur la variable contenant SDL_Renderer
 * INPUT  PARAMETERS : Uint8 type : enum Texte_Type
 * INPUT  PARAMETERS : std::string message : Texte
 * INPUT  PARAMETERS : SDL_Color color : couleur du Texte
 * INPUT  PARAMETERS : SDL_Color colorback : couleur du fond du Texte
 * INPUT  PARAMETERS : TTF_Font* font : Taille de la font utilisée
 * OUTPUT PARAMETERS : Permet de créer un ptr sur une SDL_Texture
 * RETURNED VALUE    : SDL_Texture*
 */
SDL_Texture* Texte::createSDL_TextureFromTexte(	SDL_Renderer*& renderer,
												Texte_Type type,
												std::string message,
												SDL_Color color,
												SDL_Color colorback,
												TTF_Font* font
											   )
{
	SDL_Surface *surf = nullptr;

	if (type == blended)
		surf = TTF_RenderText_Blended(font, message.c_str(), color);
	else if (type == shaded)
		surf = TTF_RenderText_Shaded(font, message.c_str(), color, colorback);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr)
		IHM::logfileconsole("[ERROR]___:___________ERROR : renderTextShaded nullptr for : " + message);
	SDL_FreeSurface(surf);

	return texture;
}


/*
 * NAME : loadTexte
 * ROLE : création et ajout d'un objet Texte dans le tableau de Texte choisi
 * INPUT  PARAMETERS : SDL_Renderer*& renderer : le ptr sur la variable contenant SDL_Renderer
 * INPUT  PARAMETERS : TTF_Font* font[] : tableau de police de la font
 * INPUT  PARAMETERS : Uint8 stateScreen, Uint8 select : les variables qui décrivent les différents état de l'écran et les spécifications de la séléction
 * INPUT  PARAMETERS : std::vector<Texte*>& tabTexte : tableau de Texte* ou sera rangé le nouveau Texte
 * INPUT  PARAMETERS : Uint8 type : enum Texte_Type
 * INPUT  PARAMETERS : std::string msg : Le Texte dans le tableau
 * INPUT  PARAMETERS : SDL_Color color : couleur du Texte
 * INPUT  PARAMETERS : SDL_Color colorback : couleur du fond du Texte
 * INPUT  PARAMETERS : Uint8 : la taille du Texte
 * INPUT  PARAMETERS : int x, int y	: les valeurs en pixel de la future position
 * INPUT  PARAMETERS : Uint8 alpha : la valeur de transparance de la Texture -> enum Transparance_Type
 * INPUT  PARAMETERS : Uint16 angle : enum Rotation_Type
 * INPUT  PARAMETERS : Uint8 cnt : enum Center_Type
 * OUTPUT PARAMETERS : création et ajout d'un objet Texte
 * RETURNED VALUE    : void
 */
void Texte::loadTexte(	SDL_Renderer*& renderer,
						TTF_Font* font[],
						Uint8 stateScreen,
						Uint8 select,
						std::vector<Texte*>& tabTexte,
						Texte_Type type,
						std::string msg,
						SDL_Color color,
						SDL_Color backcolor,
						Uint8 size,
						int x,
						int y,
						Transparance_Type alpha,
						Rotation_Type angle,
						Center_Type cnt
					)
{

	SDL_Texture *image = createSDL_TextureFromTexte(renderer, type, msg, color, backcolor, font[size]);
	if (alpha != nonTransparent)
		SDL_SetTextureAlphaMod(image, alpha);
	int xc = x, yc = y, iW = 0, iH = 0;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);
	tabTexte.push_back(new Texte(renderer, font, image, msg, stateScreen, select, xc, yc, iW, iH,
		type, color, backcolor, size, alpha, angle, cnt));
}


/*
 * NAME : writeTexte
 * ROLE : créer un ptr sur SDL_Texture temporaire pour afficher le texte à l'écran
 * ROLE : le ptr et la SDL_Texture sont détruit après l'affichage
 * INPUT  PARAMETERS : SDL_Renderer*& renderer : le ptr sur la variable contenant SDL_Renderer
 * INPUT  PARAMETERS : TTF_Font* font[] : tableau de police de la font
 * INPUT  PARAMETERS : Uint8 type : enum Texte_Type
 * INPUT  PARAMETERS : std::string msg : Le Texte dans le tableau
 * INPUT  PARAMETERS : SDL_Color color : couleur du Texte
 * INPUT  PARAMETERS : SDL_Color colorback : couleur du fond du Texte
 * INPUT  PARAMETERS : Uint8 : la taille du Texte
 * INPUT  PARAMETERS : int x, int y	: les valeurs en pixel de la future position
 * INPUT  PARAMETERS : Uint8 alpha : la valeur de transparance de la Texture -> enum Transparance_Type
 * INPUT  PARAMETERS : Uint16 angle : enum Rotation_Type
 * INPUT  PARAMETERS : Uint8 cnt : enum Center_Type
 * OUTPUT PARAMETERS : créer un ptr sur SDL_Texture temporaire pour afficher le texte à l'écran
 * RETURNED VALUE    : void
 */
void Texte::writeTexte(	SDL_Renderer*& renderer,
						TTF_Font* font[],
						Texte_Type type,
						std::string msg,
						SDL_Color color,
						SDL_Color backcolor,
						Uint8 size,
						unsigned int x,
						unsigned int y,
						Rotation_Type angle,
						Center_Type cnt
					)
{

	SDL_Texture *image = createSDL_TextureFromTexte(renderer, type, msg, color, backcolor, font[size]);

	int xc = x, yc = y, iW = 0, iH = 0;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);

	SDL_Rect dst;
	dst.x = xc;
	dst.y = yc;
	dst.w = iW;
	dst.h = iH;

	if (angle == 0)
		SDL_RenderCopy(renderer, image, NULL, &dst);
	else
		SDL_RenderCopyEx(renderer, image, NULL, &dst, angle, NULL, SDL_FLIP_NONE);

	SDL_DestroyTexture(image);
}


/* *********************************************************
 *					END Texte::STATIC					   *
 ********************************************************* */



/* *********************************************************
 *				START Texte::METHODS					   *
 ********************************************************* */


Texte::Texte(	SDL_Renderer*& renderer,
				TTF_Font* font[],
				SDL_Texture* image,
				std::string msg,
				Uint8 stateScreen,
				Uint8 select,
				int x,
				int y,
				int w,
				int h,
				Texte_Type type,
				SDL_Color txtcolor,
				SDL_Color backcolor,
				Uint8 size,
				Transparance_Type alpha,
				Rotation_Type angle,
				Center_Type center
			) :
	Texture(renderer, image, msg, stateScreen, select, x, y, w, h, alpha, angle, center),
	_type(type), _txtcolor(txtcolor), _backcolor(backcolor),
	_size(size), _font()
{
	for (unsigned int i = 0; i < MAX_FONT; i++)
		_font[i] = font[i];
}
Texte::~Texte()
{
	for (unsigned int i = 0; i < MAX_FONT; i++)
		_font[i] = nullptr;
}



/*
 * NAME : isSameColor
 * ROLE : Comparaison de 2 couleurs SDL_Color
 * INPUT  PARAMETERS : SDL_Color, SDL_Color: couleur à comparer
 * OUTPUT PARAMETERS : Destruction des allocations dynamique du programme
 * RETURNED VALUE    : bool : false = pas les meme/ true = meme couleur
 */
bool Texte::isSameColor(SDL_Color color1, SDL_Color color2) const
{
	if (color1.a != color2.a || color1.b != color2.b || color1.g != color2.g || color1.r != color2.r)
		return false;
	else
		return true;
}


/*
 * NAME : resizeTexte
 * ROLE : recentre le Texte lors de changement de taille du texte
 * INPUT  PARAMETERS : void
 * OUTPUT PARAMETERS : recentre le Texte lors de changement de taille du texte
 * RETURNED VALUE    : void
 */
void Texte::resizeTexte()
{
	int xc = 0, yc = 0, iW = 0, iH = 0;

	switch (this->GETcenter())
	{
	case nocenter:
		xc = this->GETdstx();
		yc = this->GETdsty();
		break;
	case center_x:
		xc = this->GETdstx() + this->GETdstw() / 2;
		yc = this->GETdsty();
		break;
	case center_y:
		xc = this->GETdstx();
		yc = this->GETdsty() + this->GETdsth() / 2;
		break;
	case center:
		xc = this->GETdstx() + this->GETdstw() / 2;
		yc = this->GETdsty() + this->GETdsth() / 2;
		break;
	}

	SDL_QueryTexture(this->GETtextureNonConst(), NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, this->GETcenter());
	this->SETdstx(xc); this->SETdsty(yc); this->SETdstw(iW); this->SETdsth(iH);
}

/* *********************************************************
 *				END Texte::METHODS						   *
 ********************************************************* */




/* *********************************************************
 *			START Texte::METHODES::GET/SET				   *
 ********************************************************* */

void Texte::SETname(std::string msg)
{
	if (this->GETname().compare(msg) != 0)
	{
		this->Texture::SETname(msg);
		this->SETtexture(createSDL_TextureFromTexte(this->GETrenderer(), _type, this->GETname(), _txtcolor, _backcolor, _font[_size]));
		resizeTexte();
	}
}
void Texte::SETtype(Texte_Type type)
{
	if (type != _type)
	{
		_type = type;
		this->SETtexture(createSDL_TextureFromTexte(this->GETrenderer(), _type, this->GETname(), _txtcolor, _backcolor, _font[_size]));
	}
}
void Texte::SETsize(Uint8 size)
{
	if (size != _size)
	{
		_size = size;
		this->SETtexture(createSDL_TextureFromTexte(this->GETrenderer(), _type, this->GETname(), _txtcolor, _backcolor, _font[_size]));
		resizeTexte();
	}
}
void Texte::SETtxtcolor(SDL_Color txtcolor)
{
	if (!isSameColor(txtcolor, _txtcolor))
	{
		_txtcolor = txtcolor;
		this->SETtexture(createSDL_TextureFromTexte(this->GETrenderer(), _type, this->GETname(), _txtcolor, _backcolor, _font[_size]));
	}
}
void Texte::SETbackcolor(SDL_Color backcolor)
{
	if (!isSameColor(backcolor, _backcolor))
	{
		_backcolor = backcolor;
		this->SETtexture(createSDL_TextureFromTexte(this->GETrenderer(), _type, this->GETname(), _txtcolor, _backcolor, _font[_size]));
	}
}


/* *********************************************************
 *				END Texte::METHODES::GET/SET			   *
 ********************************************************* */





 //--- ButtonImage ---------------------------------------------------------------------------------------------------------------------------------------

/* *********************************************************
 *				START ButtonImage::STATIC				   *
 ********************************************************* */



/*
 * NAME : createButtonImage
 * ROLE : création et ajout d'un objet ButtonTexte dans le tableau de ButtonTexte choisi
 * INPUT  PARAMETERS : SDL_Renderer*& renderer : le ptr sur la variable contenant SDL_Renderer
 * INPUT  PARAMETERS : std::vector<ButtonImage*>& : le tableau dans lequel sera stocké la ButtonImage (allocation dynamique)
 * INPUT  PARAMETERS : Uint8 stateScreen, Uint8 select : les variables qui décrivent les différents état de l'écran et les spécifications de la séléction
 * INPUT  PARAMETERS : std::string path : le chemin d'accès ainsi que le nom de l'image à partir du fichier (inclure le type .png , .bmp ...)
 * INPUT  PARAMETERS : std::string msg : le nom qui permettra d'identifier la Texture dans le tableau
 * INPUT  PARAMETERS : Uint8 alpha : la valeur de transparance de la Texture -> enum Transparance_Type
 * INPUT  PARAMETERS : int x, int y	: les valeurs en pixel de la future position
 * INPUT  PARAMETERS : unsigned int w, unsigned int h : les valeurs de longueur et de largeur permettant de changer la définition de l'image originale sinon mettre NULL
 * INPUT  PARAMETERS : Uint16 angle : enum Rotation_Type
 * INPUT  PARAMETERS : Uint8 cnt : le type de centrage -> enum Center_Type
 * OUTPUT PARAMETERS : création et ajout d'un objet ButtonTexte
 * RETURNED VALUE    : void
 */
void ButtonImage::createButtonImage(	SDL_Renderer*& renderer,
										std::vector<ButtonImage*>& tabButtonImage,
										Uint8 stateScreen,
										Uint8 select,
										std::string path,
										std::string msg,
										Transparance_Type alpha,
										int x,
										int y,
										unsigned int w,
										unsigned int h,
										Rotation_Type angle,
										Center_Type cnt
									)
{

	int xt = 0, yt = 0, wt = 0, ht = 0;
	if (x != -1 && y != -1)
		xt = x, yt = y;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	std::size_t found = path.find('.');
	if (found != std::string::npos)
		path.insert(found, "On");
	SDL_Surface* loadedSurfaceOn = IMG_Load(path.c_str());
	if (w == 0 && h == 0)
	{
		wt = loadedSurface->w;
		ht = loadedSurface->h;
	}
	else
	{
		wt = w;
		ht = h;
	}

	if (loadedSurface != nullptr && loadedSurfaceOn != nullptr)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		SDL_SetColorKey(loadedSurfaceOn, SDL_TRUE, SDL_MapRGB(loadedSurfaceOn->format, 0, 0xFF, 0xFF));
		SDL_Texture *image = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		SDL_Texture *imageOn = SDL_CreateTextureFromSurface(renderer, loadedSurfaceOn);
		if (image != nullptr && imageOn != nullptr)
		{
			if (alpha != nonTransparent)
			{
				SDL_SetTextureAlphaMod(image, alpha);
				SDL_SetTextureAlphaMod(imageOn, alpha);
			}
			centrage(xt, yt, wt, ht, cnt);
			tabButtonImage.push_back(new ButtonImage(renderer, image, msg, stateScreen, select, xt, yt, wt, ht, alpha, angle, imageOn, cnt));
		}
		else
			IHM::logfileconsole("[ERROR]___:___________ERROR : createButtonImage : cannot create Texture from : " + path);
		SDL_FreeSurface(loadedSurface);
		SDL_FreeSurface(loadedSurfaceOn);
	}
	else
		IHM::logfileconsole("[ERROR]___:___________ERROR : createButtonImage : path or image are corrupt : " + path);


	IHM::logfileconsole("Create ButtonImage n:" + std::to_string(tabButtonImage.size() - 1) + " msg = " + msg + " Success");
}

/* *********************************************************
 *				END ButtonImage::STATIC					   *
 ********************************************************* */



/* *********************************************************
 *				START ButtonImage::METHODES				   *
 ********************************************************* */


ButtonImage::ButtonImage(	SDL_Renderer*& renderer,
							SDL_Texture* image,
							const std::string& msg,
							Uint8 stateScreen,
							Uint8 select,
							int x,
							int y,
							int w,
							int h,
							Transparance_Type alpha,
							Rotation_Type angle,
							SDL_Texture* imageOn,
							Center_Type center
						)
	: Texture(renderer, image, msg, stateScreen, select, x, y, w, h, alpha, angle, center),
	_imageOn(imageOn), _on(false)
{

}
ButtonImage::~ButtonImage()
{
	if (_imageOn != nullptr)
	{
		SDL_DestroyTexture(_imageOn);
		_imageOn = nullptr;
	}
}


/*
 * NAME : searchButtonImage
 * ROLE : Recherche si les coordonnées en entrée sont celles du bouton
 * INPUT  PARAMETERS : Uint8 stateScreen : enum State_Type
 * INPUT  PARAMETERS : signed int x, signed int y : coordonnées souris
 * OUTPUT PARAMETERS : Validation ou non du bouton
 * RETURNED VALUE    : bool : false = pas valide / true = valide
 */
bool ButtonImage::searchButtonImage(Uint8 stateScreen, signed int x, signed int y)
{
	if (stateScreen == this->GETstateScreen())
	{
		if (x >= this->GETdstx() && x <= this->GETdstx() + this->GETdstw())
		{
			if (y >= this->GETdsty() && y <= this->GETdsty() + this->GETdsth())
			{
				return true;
			}
		}
	}
	return false;
}



/*
 * NAME : renderButtonImage
 * ROLE : Affiche le bouton si le contexte est valide
 * INPUT  PARAMETERS : Uint8 stateScreen :  enum State_Type
 * OUTPUT PARAMETERS : Affiche le bouton
 * RETURNED VALUE    : bool : false = non affiché / true = affichage
 */
bool ButtonImage::renderButtonImage(Uint8 stateScreen)
{
	if (this->GETstateScreen() == stateScreen)
	{
		if (this->GETangle() == 0)
		{
			if (_on)
				SDL_RenderCopy(this->GETrenderer(), _imageOn, NULL, &this->GETdst());
			else
				SDL_RenderCopy(this->GETrenderer(), this->GETtexture(), NULL, &this->GETdst());
			return true;
		}
		else
		{
			if (_on)
				SDL_RenderCopyEx(this->GETrenderer(), _imageOn, NULL, &this->GETdst(), this->GETangle(), NULL, SDL_FLIP_NONE);
			else
				SDL_RenderCopyEx(this->GETrenderer(), this->GETtexture(), NULL, &this->GETdst(), this->GETangle(), NULL, SDL_FLIP_NONE);
			return true;
		}

	}
	return false;
}


/*
 * NAME : changeOn
 * ROLE : alterne l'attribut booléen _on
 * INPUT  PARAMETERS : void
 * OUTPUT PARAMETERS : alterne l'attribut booléen _on
 * RETURNED VALUE    : void
 */
void ButtonImage::changeOn()
{
	_on = !_on;
}


/* *********************************************************
 *				END ButtonImage::METHODES				   *
 ********************************************************* */





 //--- ButtonTexte ---------------------------------------------------------------------------------------------------------------------------------------

/* *********************************************************
 *				START ButtonTexte::STATIC				   *
 ********************************************************* */



/*
 * NAME : createButtonTexte
 * ROLE : création et ajout d'un objet ButtonTexte dans le tableau de ButtonTexte choisi
 * INPUT  PARAMETERS : SDL_Renderer*& renderer : le ptr sur la variable contenant SDL_Renderer
 * INPUT  PARAMETERS : TTF_Font* font[] : tableau de police de la font
 * INPUT  PARAMETERS : Uint8 stateScreen, Uint8 select : les variables qui décrivent les différents état de l'écran et les spécifications de la séléction
 * INPUT  PARAMETERS : std::vector<ButtonTexte*>& : le tableau dans lequel sera stocké la ButtonTexte (allocation dynamique)
 * INPUT  PARAMETERS : Uint8 type : enum Texte_Type
 * INPUT  PARAMETERS : std::string msg : le nom qui permettra d'identifier la Texture dans le tableau
 * INPUT  PARAMETERS : SDL_Color color : couleur du Texte
 * INPUT  PARAMETERS : SDL_Color colorback : couleur du fond du Texte
 * INPUT  PARAMETERS : Uint8 : la taille du Texte
 * INPUT  PARAMETERS : int x, int y	: les valeurs en pixel de la future position
 * INPUT  PARAMETERS : Uint8 alpha : la valeur de transparance de la Texture -> enum Transparance_Type
 * INPUT  PARAMETERS : Uint16 angle : enum Rotation_Type
 * INPUT  PARAMETERS : Uint8 cnt : le type de centrage -> enum Center_Type
 * OUTPUT PARAMETERS : création et ajout d'un objet ButtonTexte
 * RETURNED VALUE    : void
 */
void ButtonTexte::createButtonTexte(	SDL_Renderer*& renderer,
										TTF_Font* font[],
										Uint8 stateScreen,
										Uint8 select,
										std::vector<ButtonTexte*>& tabButtonTexte,
										Texte_Type type,
										std::string msg,
										SDL_Color color,
										SDL_Color backcolor,
										Uint8 size,
										int x,
										int y,
										Transparance_Type alpha,
										Rotation_Type angle,
										Center_Type centerButtonTexte
									)
{
	int iW = 0, iH = 0;

	SDL_Texture *image = nullptr;
	SDL_Texture *imageOn = nullptr;

	image = createSDL_TextureFromTexte(renderer, type, msg, color, backcolor, font[size]);
	imageOn = createSDL_TextureFromTexte(renderer, type, msg, color, { 64,128,64,255 }, font[size]);
	if (alpha != nonTransparent)
	{
		SDL_SetTextureAlphaMod(image, alpha);
		SDL_SetTextureAlphaMod(imageOn, alpha);
	}
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(x, y, iW, iH, centerButtonTexte);
	tabButtonTexte.push_back(new ButtonTexte(renderer, font, image, msg, stateScreen, select, x, y, iW, iH,
		type, color, backcolor, size, alpha, angle, imageOn, centerButtonTexte));

	IHM::logfileconsole("[INFO]___: Create ButtonTexte n:" + std::to_string(tabButtonTexte.size() - 1) + " msg = " + msg + " Success");
}

/* *********************************************************
 *				END ButtonTexte::STATIC					   *
 ********************************************************* */



/* *********************************************************
 *				START ButtonTexte::METHODS				   *
 ********************************************************* */


ButtonTexte::ButtonTexte(	SDL_Renderer* renderer,
							TTF_Font* font[],
							SDL_Texture* image,
							std::string msg,
							Uint8 stateScreen,
							Uint8 select,
							int x,
							int y,
							int w,
							int h,
							Texte_Type type,
							SDL_Color txtcolor,
							SDL_Color backcolor,
							Uint8 size,
							Transparance_Type alpha,
							Rotation_Type angle,
							SDL_Texture* imageOn,
							Center_Type center
						)
	: Texte(renderer, font, image, msg, stateScreen, select, x, y, w, h, type, txtcolor, backcolor, size, alpha, angle, center),
	_imageOn(imageOn), _on(false)
{
}
ButtonTexte::~ButtonTexte()
{
	if (_imageOn != nullptr)
	{
		SDL_DestroyTexture(_imageOn);
		_imageOn = nullptr;
	}
}


/*
 * NAME : searchButtonTexte
 * ROLE : Recherche le bouton aux coordonnées en entrée
 * INPUT  PARAMETERS : Uint8 stateScreen :  enum State_Type
 * INPUT  PARAMETERS : signed int x, signed int y : coordonnées en entrée
 * OUTPUT PARAMETERS : Validation ou non
 * RETURNED VALUE    : bool : false = non valide / true = valide
 */
bool ButtonTexte::searchButtonTexte(Uint8 stateScreen, signed int x, signed int y)
{
	if (stateScreen == this->GETstateScreen())
	{
		if (x >= this->GETdstx() && x <= this->GETdstx() + this->GETdstw())
		{
			if (y >= this->GETdsty() && y <= this->GETdsty() + this->GETdsth())
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}


/*
 * NAME : resetOnstateScreen
 * ROLE : Reset l'état _on des boutons
 * INPUT  PARAMETERS : Uint8 select, unsigned int selectnothing : enum State_Type
 * OUTPUT PARAMETERS : Reset l'état _on des boutons
 * RETURNED VALUE    : void
 */
void ButtonTexte::resetOnstateScreen(Uint8 select, unsigned int selectnothing)
{
	if (this->GETselect() != select && this->GETselect() != selectnothing)
		_on = false;
}


/*
 * NAME : resetOnPlayer
 * ROLE : Reset l'état _on des boutons
 * INPUT  PARAMETERS : unsigned int : joueur sélectionné
 * INPUT  PARAMETERS : std::vector<std::string> : tableau de nom des joueurs
 * OUTPUT PARAMETERS : Initialisation de map.screen et map.maps
 * RETURNED VALUE    : void
 */
void ButtonTexte::resetOnPlayer(unsigned int selectplayer, std::vector<std::string> tabPlayerName)
{
	for (unsigned int i = 0; i < tabPlayerName.size(); i++)
	{
		if (i != selectplayer && this->GETname().compare(tabPlayerName[i]) == 0)
			_on = false;
	}
}


/*
 * NAME : renderButtonTexte
 * ROLE : Affichage du ButtonTexte en fonction du contexte
 * INPUT  PARAMETERS : Uint8 stateScreen :  enum State_Type
 * INPUT  PARAMETERS : int x = -1, int y = -1 : positions optionnelles
 * INPUT  PARAMETERS : Uint8 center = nocenter : enum Center_Type
 * OUTPUT PARAMETERS : Initialisation de map.screen et map.maps
 * RETURNED VALUE    : bool : false = non afficher / true = affichage
 */
bool ButtonTexte::renderButtonTexte(	Uint8 stateScreen,
										int x,
										int y,
										Center_Type center
									)
{
	if (this->GETstateScreen() == stateScreen)
	{
		if (x != -1 && y != -1)
		{
			centrage(x, y, this->GETdstw(), this->GETdsth(), center);
			this->SETdstx(x);
			this->SETdsty(y);
		}

		if (_on)
			SDL_RenderCopy(this->GETrenderer(), _imageOn, NULL, &this->GETdst());
		else
			SDL_RenderCopy(this->GETrenderer(), this->GETtexture(), NULL, &this->GETdst());
		return true;
	}
	return false;
}


/*
 * NAME : changeOn
 * ROLE : alterne l'attribut booléen _on
 * INPUT  PARAMETERS : void
 * OUTPUT PARAMETERS : alterne l'attribut booléen _on
 * RETURNED VALUE    : void
 */
void ButtonTexte::changeOn()
{
	_on = !_on;
}

/* *********************************************************
 *				END ButtonTexte::METHODS				   *
 ********************************************************* */



/*
*	End Of File : Texture.cpp
*/