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

#include "Buttons.h"
#include "createButton.h"

using namespace std;



Buttons::Buttons(SDL_Texture* image, const string& msg, unsigned int statescreen, unsigned int select, int xc, int yc, int w, int h,
	SDL_Texture* imageOn, int x, int y, int size, SDL_Color txtcolor, SDL_Color backcolor, bool on)
	: Texture(image, msg, statescreen, select, xc, yc, w, h),
	_imageOn(imageOn), _x(x), _y(y), _size(size), _txtcolor(txtcolor), _backcolor(backcolor), _on(on)
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

unsigned int Buttons::searchButton(string& msg, unsigned int statescreen, signed int x, signed int y) {
	if (statescreen == this->GETstatescreen()) {
		if (x >= this->GETxc() - this->GETw() / 2 && x <= this->GETxc() + this->GETw() / 2) {
			if (y >= this->GETy() - this->GETh() / 2 && y <= this->GETyc() + this->GETh() / 2) {
				if (this->GETname().compare(msg) == 0)
					return 1;
			}
		}
	}
	return 0;
}




void Buttons::resetOnStatescreen(unsigned int select, unsigned int selectnothing) {
	if (this->GETselect() != select && this->GETselect() != selectnothing)
		_on = false;
}

void Buttons::resetOnPlayer(unsigned int selectplayer, std::vector<std::string> tabPlayerName) {
	for(unsigned int i = 0; i < tabPlayerName.size(); i++){
		if (i != selectplayer && this->GETname().compare(tabPlayerName[i]) == 0)
			_on = false;
	}
}

bool Buttons::renderButton(SDL_Renderer*& renderer, unsigned int statescreen) {
	if (this->GETstatescreen() == statescreen) {
		this->SETdstx(_x);
		this->SETdsty(_y);
		if (_on)
			SDL_RenderCopy(renderer, _imageOn, NULL, &this->GETdst());
		else
			SDL_RenderCopy(renderer, this->GETtexture(), NULL, &this->GETdst());
		return true;
	}
	return false;
}

bool Buttons::renderButtonTestString(SDL_Renderer*& renderer, unsigned int statescreen, std::string& msg, int newx, int newy, int center) {
	if (this->GETstatescreen() == statescreen && this->GETname().compare(msg) == 0) {
		if (newx != -1 && newy != -1) {
			_x = newx;
			_y = newy;
			int xc = this->GETxc();
			int yc = this->GETyc();
			int w = this->GETw();
			int h = this->GETh();
			searchcenter(_x, _y, xc, yc, w, h, center);
			this->SETxc(xc);
			this->SETyc(yc);
			this->SETw(w);
			this->SETh(h);
		}
		this->SETdstx(_x);
		this->SETdsty(_y);
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

int Buttons::GETx() const {
	return _x;
}
int Buttons::GETy() const {
	return _y;
}
int Buttons::GETsize() const {
	return _size;
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


