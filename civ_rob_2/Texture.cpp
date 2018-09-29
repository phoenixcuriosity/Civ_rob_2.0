/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.12

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
SDL_Texture* Texture::renderText(SDL_Renderer*& renderer, unsigned int type, const std::string &message, SDL_Color color, SDL_Color colorback, TTF_Font* font) {
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
void Texture::loadImage(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture, unsigned int statescreen, unsigned int select,
	const std::string &path, const std::string &msg, Uint8 alpha, int x, int y, unsigned int w, unsigned int h, int cnt) {


	int xt = 0, yt = 0, wt = 0, ht = 0;
	if (x != -1 && y != -1)
		xt = x, yt = y;

	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (w == 0 && h == 0) {
		wt = loadedSurface->w;
		ht = loadedSurface->h;
	}
	else {
		wt = w;
		ht = h;
	}

	if (loadedSurface != nullptr) {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != nullptr) {
			if (alpha != (Uint8)255) {
				if (SDL_SetTextureAlphaMod(newTexture, alpha) != 0)
					IHM::logSDLError(std::cout, "alpha : ");
			}
			centrage(xt, yt, wt, ht, cnt);
			tabTexture.push_back(new Texture(newTexture, msg, statescreen, select, xt, yt, wt, ht));
		}
		else
			IHM::logfileconsole("___________ERROR : loadImage : cannot create Texture from : " + path);
		SDL_FreeSurface(loadedSurface);
	}
	else
		IHM::logfileconsole("___________ERROR : loadImage : path or image are corrupt : " + path);
}
void Texture::loadwritetxt(sysinfo& information, std::vector<Texture*>& tabTexture, unsigned int type, const std::string &msg,
	SDL_Color color, SDL_Color backcolor, unsigned int size, int x, int y, int cnt) {
	SDL_Texture *image = renderText(information.ecran.renderer, type, msg, color, backcolor, information.allTextures.font[size]);
	int xc = x, yc = y, iW = 0, iH = 0;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);
	tabTexture.push_back(new Texture(image, msg, information.variable.statescreen, information.variable.select, xc, yc, iW, iH));
}
void Texture::writetxt(sysinfo& information, unsigned int type, const std::string &msg, SDL_Color color, SDL_Color backcolor, unsigned int size, unsigned int x, unsigned int y, int cnt) {
	SDL_Texture *image = renderText(information.ecran.renderer, type, msg, color, backcolor, information.allTextures.font[size]);
	loadAndWriteImage(information.ecran.renderer, image, x, y, cnt);
	SDL_DestroyTexture(image);
}
void Texture::loadAndWriteImage(SDL_Renderer*& renderer, SDL_Texture *image, unsigned int x, unsigned int y, int cnt) {
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
void Texture::centrage(int& xc, int& yc, int iW, int iH, int cnt) {
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

/* TEXTURE :: METHODES */
Texture::Texture(SDL_Texture* image, const std::string& msg,
	unsigned int statescreen, unsigned int select,
	unsigned int x, unsigned int y, int w, int h)
	: _texture(image), _dst(rectangle(x, y, w, h)), _name(msg),
	_statescreen(statescreen), _select(select)
{
}
Texture::~Texture() {
	if (_texture != nullptr) {
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
}
SDL_Rect Texture::rectangle(int x, int y, int w, int h) {
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
	return rectangle;
}
void Texture::render(SDL_Renderer*& renderer, int x, int y) {
	if (x != -1 && y != -1) {
		_dst.x = x;
		_dst.y = y;
	}
	SDL_RenderCopy(renderer, _texture, NULL, &_dst);
}
void Texture::renderTextureTestStates(SDL_Renderer*& renderer, unsigned int statescreen, int x, int y) {
	if (_statescreen == statescreen)
		render(renderer, x, y);
}
void Texture::renderTextureTestStatesAngle(SDL_Renderer*& renderer, unsigned int statescreen, int x, int y, unsigned int angle) {
	if (_statescreen == statescreen) {
		if (x != -1 && y != -1) {
			_dst.x = x;
			_dst.y = y;
		}
		SDL_RenderCopyEx(renderer, _texture, NULL, &_dst, angle, NULL, SDL_FLIP_NONE);
	}
}
bool Texture::renderTextureTestString(SDL_Renderer*& renderer, const std::string& msg, int xc, int yc) {
	if (_name.compare(msg) == 0) {
		render(renderer, xc, yc);
		return true;
	}
	return false;
}
bool Texture::renderTextureTestStringAndStates(SDL_Renderer*& renderer, const std::string& msg, unsigned int statescreen, int xc, int yc) {
	if (_name.compare(msg) == 0 && _statescreen == statescreen) {
		render(renderer, xc, yc);
		return true;
	}
	return false;
}
bool Texture::TextureTestString(const std::string& msg) {
	if (_name.compare(msg) == 0)
		return true;
	return false;
}
void Texture::changeAlpha(Uint8 alpha) {
	if (SDL_SetTextureAlphaMod(_texture, alpha) != 0)
		IHM::logSDLError(std::cout, "alpha : ");
}
void Texture::changeTextureMsg(sysinfo& information, unsigned int type, const std::string &msg,
	SDL_Color color, SDL_Color backcolor, unsigned int size, unsigned int x, unsigned int y, int cnt) {
	_name = msg;
	_texture = renderText(information.ecran.renderer, type, msg, color, backcolor, information.allTextures.font[size]);
	int xc = x, yc = y, iW = 0, iH = 0;
	SDL_QueryTexture(_texture, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);
	_dst.x = xc; _dst.y = yc; _dst.w = iW; _dst.h = iH;
}
SDL_Texture* Texture::GETtexture() const {
	return _texture;
}
SDL_Rect Texture::GETdst()const {
	return _dst;
}
int Texture::GETdstx()const {
	return _dst.x;
}
int Texture::GETdsty()const {
	return _dst.y;
}
int Texture::GETdstw()const {
	return _dst.w;
}
int Texture::GETdsth()const {
	return _dst.h;
}
std::string Texture::GETname() const {
	return _name;
}
unsigned int Texture::GETstatescreen() const {
	return _statescreen;
}
unsigned int Texture::GETselect() const {
	return _select;
}
void Texture::SETdstx(int x) {
	_dst.x = x;
}
void Texture::SETdsty(int y) {
	_dst.y = y;
}
void Texture::SETdstw(int w) {
	_dst.w = w;
}
void Texture::SETdsth(int h) {
	_dst.h = h;
}





///////////////////////////// Button //////////////////////////////
/* BUTTONS :: STATIC */
void Buttons::createbutton(sysinfo& information, std::vector<Buttons*>& tabbutton, unsigned int type, const std::string& msg, SDL_Color color, SDL_Color backcolor, unsigned int size, int x, int y, int cnt) {
	int iW = 0, iH = 0;
	unsigned int i = 0;

	SDL_Texture *image = nullptr;
	SDL_Texture *imageOn = nullptr;

	if (tabbutton.size() > 0) {
		i++;
	}
	for (i; i <= tabbutton.size(); i++) {
		if (i == tabbutton.size()) {
			image = renderText(information.ecran.renderer, type, msg, color, backcolor, information.allTextures.font[size]);
			imageOn = renderText(information.ecran.renderer, type, msg, color, { 64,128,64,255 }, information.allTextures.font[size]);
			SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
			centrage(x, y, iW, iH, cnt);
			tabbutton.push_back(new Buttons(image, msg, information.variable.statescreen, information.variable.select, x, y, iW, iH, imageOn, color, backcolor));

			IHM::logfileconsole("Create Button n:" + std::to_string(i) + " msg = " + tabbutton[i]->GETname() + " Success");
			break;
		}
	}
}


/* BUTTONS :: METHODES */
Buttons::Buttons(SDL_Texture* image, const std::string& msg, unsigned int statescreen, unsigned int select, int x, int y, int w, int h,
	SDL_Texture* imageOn, SDL_Color txtcolor, SDL_Color backcolor, bool on)
	: Texture(image, msg, statescreen, select, x, y, w, h),
	_imageOn(imageOn), _txtcolor(txtcolor), _backcolor(backcolor), _on(on)
{

}
Buttons::~Buttons() {
	if (_imageOn != nullptr) {
		SDL_DestroyTexture(_imageOn);
		_imageOn = nullptr;
	}
}
unsigned int Buttons::testcolor(SDL_Color txt, SDL_Color back) const {
	if (_txtcolor.a != txt.a || _txtcolor.b != txt.b || _txtcolor.g != txt.g || _txtcolor.r != txt.r ||
		_backcolor.a != back.a || _backcolor.b != back.b || _backcolor.g != back.g || _backcolor.r != back.r)
		return 1;
	else
		return 0;
}
unsigned int Buttons::searchButton(std::string msg, unsigned int statescreen, signed int x, signed int y) {
	if (statescreen == this->GETstatescreen()) {
		if (x >= this->GETdstx() && x <= this->GETdstx() + this->GETdstw()) {
			if (y >= this->GETdsty() && y <= this->GETdsty() + this->GETdsth()) {
				if (this->GETname().compare(msg) == 0)
					return 1;
			}
		}
	}
	return 0;
}
unsigned int Buttons::searchButtonName(std::string& msg, unsigned int statescreen) {
	if (statescreen == this->GETstatescreen()) {
		if (this->GETname().compare(msg) == 0)
			return 1;
	}
	return 0;
}
void Buttons::resetOnStatescreen(unsigned int select, unsigned int selectnothing) {
	if (this->GETselect() != select && this->GETselect() != selectnothing)
		_on = false;
}
void Buttons::resetOnPlayer(unsigned int selectplayer, std::vector<std::string> tabPlayerName) {
	for (unsigned int i = 0; i < tabPlayerName.size(); i++) {
		if (i != selectplayer && this->GETname().compare(tabPlayerName[i]) == 0)
			_on = false;
	}
}
bool Buttons::renderButton(SDL_Renderer*& renderer, unsigned int statescreen) {
	if (this->GETstatescreen() == statescreen) {
		if (_on)
			SDL_RenderCopy(renderer, _imageOn, NULL, &this->GETdst());
		else
			SDL_RenderCopy(renderer, this->GETtexture(), NULL, &this->GETdst());
		return true;
	}
	return false;
}
bool Buttons::renderButtonTestString(SDL_Renderer*& renderer, unsigned int statescreen, std::string& msg, int newx, int newy, int cnt) {
	if (this->GETstatescreen() == statescreen && this->GETname().compare(msg) == 0) {
		if (newx != -1 && newy != -1) {
			centrage(newx, newy, this->GETdstw(), this->GETdsth(), cnt);
			this->SETdstx(newx);
			this->SETdstx(newx);
		}
		if (_on)
			SDL_RenderCopy(renderer, _imageOn, NULL, &this->GETdst());
		else
			SDL_RenderCopy(renderer, this->GETtexture(), NULL, &this->GETdst());
		return true;
	}
	return false;
}
void Buttons::changeOn() {
	_on = !_on;
}
SDL_Texture* Buttons::GETimageOn() const {
	return _imageOn;
}
SDL_Color Buttons::GETtxtcolor() const {
	return _txtcolor;
}
SDL_Color Buttons::GETbackcolor() const {
	return _backcolor;
}
bool Buttons::GETon() const {
	return _on;
}
void Buttons::SETon(bool state) {
	_on = state;
}
