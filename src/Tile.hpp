///////////////////////////////////////////////////////////////////////
// Tile.hpp
// This file is part of NAME_TBD
//
// Copyright (C) 2014 - Andriy Zasypkin
//
// NAME_TBD is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// NAME_TBD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with NAME_TBD. If not, see <http://www.gnu.org/licenses/>.
///////////////////////////////////////////////////////////////////////

// Headers
#include "Tile.h"

int Tile::nSize = 30;
sf::Texture Tile::texture;

Tile::Tile() {
  this->location.x = 0;
  this->location.y = 0;
  this->nTile      = 0;
  this->rect       = sf::IntRect(0, 0, nSize, nSize);
}

Tile::Tile(int tile) {
  this->location.x = 0;
  this->location.y = 0;
  this->nTile      = tile;


  int x = nSize * (int)( tile % (texture.getSize().x / nSize) );
  int y = nSize * (int)( tile / (texture.getSize().x / nSize) );

  this->rect = sf::IntRect(0, 0, nSize, nSize);
}

Tile::Tile(int x, int y) {
  this->location.x = x;
  this->location.y = y;
  this->nTile      = 0;

  this->rect       = sf::IntRect(0, 0, nSize, nSize);
}

Tile::Tile(int x, int y, int tile) {
  this->location.x = x;
  this->location.y = y;
  this->nTile      = tile;

  x                = nSize * (int)( tile % (texture.getSize().x / nSize) );
  y                = nSize * (int)( tile / (texture.getSize().x / nSize) );

  this->rect       = sf::IntRect(x, y, nSize, nSize);
}
sf::Vector2u Tile::getTextureSize(){
  return texture.getSize();
}

locationD_t Tile::getLocation() {
  return this->location;
} // getLocation

int Tile::getTile() {
  return this->nTile;
} /* getTile */

void Tile::setLocation(int x, int y) {
  location.x = x;
  location.y = y;
} // setLocation

void Tile::setTile(int tile) {
  int x = (nSize + 1) * (int)( tile % (texture.getSize().x / nSize) );
  int y = (nSize + 1) * (int)( tile / (texture.getSize().x / nSize) );

  this->rect  = sf::IntRect(x, y, nSize, nSize);
  this->nTile = tile;
} /* setTile */

bool Tile::setTexture(std::string str) {
  return texture.loadFromFile(str);
} /* setTexture */

bool Tile::setTexture(sf::Image img) {
  return texture.loadFromImage(img);
} /* setTexture */

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::Sprite sprite;

  sprite.setTexture(this->texture);
  sprite.setTextureRect(this->rect);
  sprite.setPosition(location.x * nSize, location.y * nSize);

  target.draw(sprite, states);
} // draw

