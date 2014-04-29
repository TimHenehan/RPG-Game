///////////////////////////////////////////////////////////////////////
// Map.hpp
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
#include "Map.h"

Map::Map() {
  location.x = 0;
  location.y = 0;
  resize(1, 1);
}

Map::Map(int x, int y) {
  location.x = 0;
  location.y = 0;
  resize(x, y);
}

Tile_Vec& Map::operator[] (int x) {
  return tiles[x];
} // []

locationD_t Map::getLocation() {
  return this->location;
} // getLocation

size_t Map::size() {
  return tiles.size();
} // size

void Map::redraw() {
  renderTexture.clear();
  
  for (int i = 0; i < tiles.size(); i++) {
    for (int j = 0; j < tiles[i].size(); j++) {
      renderTexture.draw(tiles[i][j]);
    }
  }
  
  renderTexture.display();
} // redraw

void Map::resize(int x, int y) {
  if ((x <= 0) || (y <= 0)) {
    return;
  }

  renderTexture.create(Tile::nSize * x, Tile::nSize * y);

  tiles.reserve(x);
  tiles.resize(x);

  for (int i = 0; i < x; ++i) {
    tiles[i].reserve(y);
    tiles[i].resize(y);

    for (int j = 0; j < y; j++) {
      tiles[i][j].setLocation(i, j);
    }
  }

  redraw();
} // resize

bool Map::move(int x, int y, sf::RenderWindow& target) {
  
  if (((location.x + x < 0) && (x != 0))
      || ((location.y + y < 0) && (y != 0))
      || ((location.x + x + (int)target.getSize().x / Tile::nSize > tiles.size()) && (x != 0))
      || ((location.y + y + (int)target.getSize().y / Tile::nSize > tiles[0].size()) && (y != 0)))
  {
    return false;
  }
  
  
  location.x += x;
  location.y += y;
  
  return true;
} // move

std::streampos Map::load(std::string filename, std::streampos pos = 0) {
  unsigned int width, height;
  int tile;

  std::ifstream data(filename.c_str(), std::ios::in | std::ios::binary);

  data.seekg(pos);

  data.read((char*)&width, sizeof(width));
  data.read((char*)&height, sizeof(height));

  resize(width, height);

  for (unsigned int i = 0; i < width; i++) {
    for (unsigned int j = 0; j < height; j++) {
      data.read((char*)&tile, sizeof(tile));
      tiles[i][j].setTile(tile);
    }
  }
  std::streampos new_pos = data.tellg();
  data.close();
  return new_pos;
} // load

void Map::save(std::string filename, bool append = false) {
  unsigned int width  = tiles.size();
  unsigned int height = tiles[0].size();
  int tile;
  std::ofstream data;

  if (append) {
    data.open(filename.c_str(),
              std::ios::out | std::ios::binary | std::ios::app);
  }
  else {
    data.open(filename.c_str(),
              std::ios::out | std::ios::binary);
  }

  data.write((char*)&width, sizeof(width));
  data.write((char*)&height, sizeof(height));

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      tile = tiles[i][j].getTile();
      data.write((char*)&tile, sizeof(tile));
    }
  }
  data.close();
} // save

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  int startI, startJ, endI, endJ;

  startI = location.x * Tile::nSize;
  startJ = location.y * Tile::nSize;
  endI   = std::min((int)tiles.size() * Tile::nSize,
                    startI
                    + ((int)target.getSize().x / Tile::nSize + 1) * Tile::nSize);
  endJ = std::min((int)tiles[0].size() * Tile::nSize,
                  startJ
                  + ((int)target.getSize().y / Tile::nSize + 1) * Tile::nSize);

  sf::IntRect rect(startI, startJ, endI, endJ);
  sf::Sprite  sprite;

  sprite.setTexture(renderTexture.getTexture());
  sprite.setTextureRect(rect);

  target.draw(sprite, states);
} // draw

