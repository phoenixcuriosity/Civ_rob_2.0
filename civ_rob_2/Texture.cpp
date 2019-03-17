/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.14
	file version : 1.4

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
/* TEXTURE :: STATIC */
void Texture::loadImage(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture, Uint8 stateScreen, Uint8 select,
	std::string path, std::string msg, Uint8 alpha, int x, int y, unsigned int w, unsigned int h, Uint16 angle, Uint8 cnt)
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
			IHM::logfileconsole("___________ERROR : loadImage : cannot create Texture from : " + path);
		SDL_FreeSurface(loadedSurface);
	}
	else
		IHM::logfileconsole("___________ERROR : loadImage : path or image are corrupt : " + path);
}
void Texture::centrage(int& xc, int& yc, int iW, int iH, Uint8 cnt)
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

/* TEXTURE :: METHODES */
Texture::Texture(SDL_Renderer*& renderer,
	SDL_Texture* image, std::string msg, Uint8 stateScreen, Uint8 select,
	unsigned int x, unsigned int y, int w, int h, Uint8 alpha, Uint16 angle, Uint8 center)
	: _renderer(renderer),
	_texture(image), _dst(rectangle(x, y, w, h)), _name(msg),
	_stateScreen(stateScreen), _select(select), _alpha(alpha), _angle(angle), _center(center)
{
}
Texture::~Texture()
{
	if (_renderer != nullptr)
		_renderer = nullptr;

	if (_texture != nullptr) {
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
}
SDL_Rect Texture::rectangle(int x, int y, int w, int h)
{
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
	return rectangle;
}
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
bool Texture::renderTextureTestStates(Uint8 stateScreen, Uint8 select, int x, int y)
{
	if (_stateScreen == stateScreen && _select == select)
	{
		render(x, y);
		return true;
	}
	return false;
}
bool Texture::renderTextureTestString(std::string msg, int xc, int yc)
{
	if (_name.compare(msg) == 0)
	{
		render(xc, yc);
		return true;
	}
	return false;
}
bool Texture::renderTextureTestStringAndStates(std::string msg, Uint8 stateScreen, int xc, int yc)
{
	if (_name.compare(msg) == 0 && _stateScreen == stateScreen)
	{
		render(xc, yc);
		return true;
	}
	return false;
}



///////////////////////////// Texte //////////////////////////////
/* Texte :: STATIC */
SDL_Texture* Texte::createSDL_TextureFromTexte(SDL_Renderer*& renderer, Uint8 type, std::string message, SDL_Color color, SDL_Color colorback, TTF_Font* font)
{
	SDL_Surface *surf = nullptr;

	if (type == blended)
		surf = TTF_RenderText_Blended(font, message.c_str(), color);
	else if (type == shaded)
		surf = TTF_RenderText_Shaded(font, message.c_str(), color, colorback);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr)
		IHM::logfileconsole("___________ERROR : renderTextShaded nullptr for : " + message);
	SDL_FreeSurface(surf);

	return texture;
}
void Texte::loadTexte(SDL_Renderer*& renderer, TTF_Font* font[],
	Uint8 stateScreen, Uint8 select, std::vector<Texte*>& tabTexte, Uint8 type, std::string msg,
	SDL_Color color, SDL_Color backcolor, Uint8 size, int x, int y, Uint8 alpha, Uint16 angle, Uint8 cnt)
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
void Texte::writeTexte(SDL_Renderer*& renderer, TTF_Font* font[], Uint8 type, std::string msg,
	SDL_Color color, SDL_Color backcolor, Uint8 size, unsigned int x, unsigned int y, Uint16 angle, Uint8 cnt)
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


/* Texte :: METHODES */
Texte::Texte(SDL_Renderer*& renderer, TTF_Font* font[],
	SDL_Texture* image, std::string msg, Uint8 stateScreen, Uint8 select, int x, int y, int w, int h,
	Uint8 type, SDL_Color txtcolor, SDL_Color backcolor, Uint8 size, Uint8 alpha, Uint16 angle, Uint8 center) :
	Texture(renderer, image, msg, stateScreen, select, x, y, w, h, alpha, angle, center),
	_type(type), _txtcolor(txtcolor), _backcolor(backcolor),
	_size(size)
{
	for (unsigned int i = 0; i < MAX_FONT; i++)
		_font[i] = font[i];
}
Texte::~Texte()
{
	for (unsigned int i = 0; i < MAX_FONT; i++)
		_font[i] = nullptr;
}

void Texte::SETname(std::string msg)
{
	if (this->GETname().compare(msg) != 0)
	{
		this->Texture::SETname(msg);
		this->SETtexture(createSDL_TextureFromTexte(this->GETrenderer(), _type, this->GETname(), _txtcolor, _backcolor, _font[_size]));
		resizeTexte();
	}
}
void Texte::SETtype(Uint8 type)
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
bool Texte::isSameColor(SDL_Color color1, SDL_Color color2) const
{
	if (color1.a != color2.a || color1.b != color2.b || color1.g != color2.g || color1.r != color2.r)
		return false;
	else
		return true;
}
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




///////////////////////////// ButtonImage //////////////////////////////
/* ButtonImage :: STATIC */
void ButtonImage::createButtonImage(SDL_Renderer*& renderer, std::vector<ButtonImage*>& tabButtonImage, Uint8 stateScreen, Uint8 select,
	std::string path, std::string msg, Uint8 alpha, int x, int y, unsigned int w, unsigned int h, Uint16 angle, Uint8 cnt)
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
			IHM::logfileconsole("___________ERROR : createButtonImage : cannot create Texture from : " + path);
		SDL_FreeSurface(loadedSurface);
		SDL_FreeSurface(loadedSurfaceOn);
	}
	else
		IHM::logfileconsole("___________ERROR : createButtonImage : path or image are corrupt : " + path);


	IHM::logfileconsole("Create ButtonImage n:" + std::to_string(tabButtonImage.size() - 1) + " msg = " + msg + " Success");
}

/* ButtonImage :: METHODES */
ButtonImage::ButtonImage(SDL_Renderer*& renderer,
	SDL_Texture* image, const std::string& msg, Uint8 stateScreen, Uint8 select, int x, int y, int w, int h,
	Uint8 alpha, Uint16 angle, SDL_Texture* imageOn, Uint8 center)
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
unsigned int ButtonImage::searchButtonImage(std::string msg, Uint8 stateScreen, signed int x, signed int y)
{
	if (stateScreen == this->GETstateScreen())
	{
		if (x >= this->GETdstx() && x <= this->GETdstx() + this->GETdstw())
		{
			if (y >= this->GETdsty() && y <= this->GETdsty() + this->GETdsth())
			{
				if (this->GETname().compare(msg) == 0)
					return 1;
			}
		}
	}
	return 0;
}
unsigned int ButtonImage::searchButtonImageName(std::string& msg, Uint8 stateScreen)
{
	if (stateScreen == this->GETstateScreen())
	{
		if (this->GETname().compare(msg) == 0)
			return 1;
	}
	return 0;
}
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
bool ButtonImage::renderButtonImageTestString(Uint8 stateScreen, std::string& msg, int newx, int newy, Uint8 cnt)
{
	if (this->GETstateScreen() == stateScreen && this->GETname().compare(msg) == 0)
	{
		if (newx != -1 && newy != -1)
		{
			centrage(newx, newy, this->GETdstw(), this->GETdsth(), cnt);
			this->SETdstx(newx);
			this->SETdstx(newx);
		}
		if (_on)
			SDL_RenderCopy(this->GETrenderer(), _imageOn, NULL, &this->GETdst());
		else
			SDL_RenderCopy(this->GETrenderer(), this->GETtexture(), NULL, &this->GETdst());
		return true;
	}
	return false;
}
void ButtonImage::changeOn()
{
	_on = !_on;
}
SDL_Texture* ButtonImage::GETimageOn() const
{
	return _imageOn;
}
bool ButtonImage::GETon() const
{
	return _on;
}
void ButtonImage::SETname(std::string msg)
{
	if (this->GETname().compare(msg) != 0)
	{
		IHM::logfileconsole("___ERROR : ButtonTexte::SETname() : Le nom d'un bouton ne peut pas changer après initialisation");
	}
}
void ButtonImage::SETon(bool state)
{
	_on = state;
}
void ButtonImage::SETalpha(Uint8 alpha)
{
	this->SETalpha(alpha);
	if (SDL_SetTextureAlphaMod(this->GETtextureNonConst(), this->GETalpha()) != 0)
		IHM::logSDLError(std::cout, "alpha : ");
	if (SDL_SetTextureAlphaMod(_imageOn, this->GETalpha()) != 0)
		IHM::logSDLError(std::cout, "alpha : ");
}





///////////////////////////// ButtonTexte //////////////////////////////
/* ButtonTexteS :: STATIC */
void ButtonTexte::createButtonTexte(SDL_Renderer*& renderer, TTF_Font* font[], Uint8 stateScreen, Uint8 select,
	std::vector<ButtonTexte*>& tabButtonTexte, Uint8 type, std::string msg,
	SDL_Color color, SDL_Color backcolor, Uint8 size, int x, int y, Uint8 alpha, Uint16 angle, Uint8 cnt)
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
	centrage(x, y, iW, iH, cnt);
	tabButtonTexte.push_back(new ButtonTexte(renderer, font, image, msg, stateScreen, select, x, y, iW, iH,
		type, color, backcolor, size, alpha, angle, imageOn, cnt));

	IHM::logfileconsole("Create ButtonTexte n:" + std::to_string(tabButtonTexte.size() - 1) + " msg = " + msg + " Success");
}


/* ButtonTexteS :: METHODES */
ButtonTexte::ButtonTexte(SDL_Renderer *renderer, TTF_Font *font[], SDL_Texture* image, std::string msg, Uint8 stateScreen, Uint8 select, int x, int y, int w, int h,
	Uint8 type, SDL_Color txtcolor, SDL_Color backcolor, Uint8 size, Uint8 alpha, Uint16 angle, SDL_Texture* imageOn, Uint8 center)
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
bool ButtonTexte::searchButtonTexte(std::string msg, Uint8 stateScreen, signed int x, signed int y)
{
	if (stateScreen == this->GETstateScreen())
	{
		if (x >= this->GETdstx() && x <= this->GETdstx() + this->GETdstw())
		{
			if (y >= this->GETdsty() && y <= this->GETdsty() + this->GETdsth())
			{
				if (this->GETname().compare(msg) == 0)
					return true;
			}
		}
	}
	return false;
}
bool ButtonTexte::searchButtonTexteName(std::string msg, Uint8 stateScreen)
{
	if (stateScreen == this->GETstateScreen())
	{
		if (this->GETname().compare(msg) == 0)
			return true;
	}
	return false;
}
void ButtonTexte::resetOnstateScreen(Uint8 select, unsigned int selectnothing)
{
	if (this->GETselect() != select && this->GETselect() != selectnothing)
		_on = false;
}
void ButtonTexte::resetOnPlayer(unsigned int selectplayer, std::vector<std::string> tabPlayerName)
{
	for (unsigned int i = 0; i < tabPlayerName.size(); i++)
	{
		if (i != selectplayer && this->GETname().compare(tabPlayerName[i]) == 0)
			_on = false;
	}
}
bool ButtonTexte::renderButtonTexte(Uint8 stateScreen)
{
	if (this->GETstateScreen() == stateScreen)
	{
		if (_on)
			SDL_RenderCopy(this->GETrenderer(), _imageOn, NULL, &this->GETdst());
		else
			SDL_RenderCopy(this->GETrenderer(), this->GETtexture(), NULL, &this->GETdst());
		return true;
	}
	return false;
}
bool ButtonTexte::renderButtonTexteTestString(Uint8 stateScreen, std::string msg, int newx, int newy, Uint8 cnt)
{
	if (this->GETstateScreen() == stateScreen && this->GETname().compare(msg) == 0)
	{
		if (newx != -1 && newy != -1)
		{
			centrage(newx, newy, this->GETdstw(), this->GETdsth(), cnt);
			this->SETdstx(newx);
			this->SETdstx(newx);
		}
		if (_on)
			SDL_RenderCopy(this->GETrenderer(), _imageOn, NULL, &this->GETdst());
		else
			SDL_RenderCopy(this->GETrenderer(), this->GETtexture(), NULL, &this->GETdst());
		return true;
	}
	return false;
}
void ButtonTexte::changeOn()
{
	_on = !_on;
}
SDL_Texture* ButtonTexte::GETimageOn() const
{
	return _imageOn;
}
bool ButtonTexte::GETon() const
{
	return _on;
}
void ButtonTexte::SETname(std::string msg)
{
	if (this->GETname().compare(msg) != 0)
	{
		IHM::logfileconsole("___ERROR : ButtonTexte::SETname() : Le nom d'un bouton ne peut pas changer après initialisation");
	}
}
void ButtonTexte::SETon(bool state)
{
	_on = state;
}
void ButtonTexte::SETalpha(Uint8 alpha)
{
	this->SETalpha(alpha);
	if (SDL_SetTextureAlphaMod(this->GETtextureNonConst(), this->GETalpha()) != 0)
		IHM::logSDLError(std::cout, "alpha : ");
	if (SDL_SetTextureAlphaMod(_imageOn, this->GETalpha()) != 0)
		IHM::logSDLError(std::cout, "alpha : ");
}



///////////////////////////// HashTable //////////////////////////////
/* HashTable :: STATIC */

unsigned int HashTable::hash(const std::string& name, const unsigned int length)
{
	long hash = 0;
	const unsigned int len_s = name.size();
	for (unsigned int i = 0; i < len_s; i++)
	{
		hash += (long)pow(151, len_s - (i + 1)) * name[i];
		hash = hash % length;
	}
	return (unsigned int)hash;
}
int HashTable::checkDoubleName(std::string name, std::vector<Texture*>& tabPos)
{
	if (searchIndex(name, tabPos) > 0)
	{
		std::cout << std::endl << "____WARNING:checkDoubleName(): " + name + " already found" << std::endl;
		return -1;
	}
	return 0;
}
Texture* HashTable::searchPos(std::string msg, const std::vector<Texture*>& tabPos)
{
	unsigned int nb = hash(msg, tabPos.size());

	unsigned int iteration = 0;
	while (true)
	{
		if (tabPos[nb]->GETname().compare(msg) == 0)
		{
			return tabPos[nb];
		}

		++nb %= tabPos.size();
		iteration++;

		if (iteration >= (tabPos.size() * 2))
		{
			Texture* blank = NULL;
			std::cout << std::endl << "____WARNING:SearchPos():Max Iteration: " + msg + " not found" << std::endl;
			return blank;
		}
	}
}
void HashTable::addPos(std::vector<Texture*>& tabPos, std::string msg, int x, int y)
{
	if (checkDoubleName(msg, tabPos) >= 0)
	{
		//tabPos.push_back(new Pos(msg, x, y));
		//fillTabHachage(tabPos);
	}
}
void HashTable::deletePos(std::vector<Texture*>& tabPos, std::string msg)
{
	int index = searchIndex(msg, tabPos);
	if (index < 0)
	{
		std::cout << std::endl << "____WARNING:DeletePos():Request not completed: " + msg + " not found" << std::endl;
	}
	else
	{
		delete tabPos[index];
		tabPos[index] = NULL;
		tabPos.erase(tabPos.begin() + index);
		//fillTabHachage(tabPos);
	}
}

/*
*	End Of File
*/