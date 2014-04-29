///////////////////////////////////////////////////////////////////////
// Tile.h
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

#ifndef __TILE_H__
#define __TILE_H__

// Headers
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

struct locationD_t {
  int x;
  int y;
};

class Tile : public sf::Drawable {
private:
  ////////////////////////////////////////////////////////////
  // The texture(image) with all the tiles in it
  ////////////////////////////////////////////////////////////
  static sf::Texture texture;

  ////////////////////////////////////////////////////////////
  // Number that represents the image of the tile object
  ////////////////////////////////////////////////////////////
  int nTile;

  ////////////////////////////////////////////////////////////
  // X and Y valuse of Tile in map
  ////////////////////////////////////////////////////////////
  locationD_t location;

  ////////////////////////////////////////////////////////////
  // A rectangle that cuts out image of tile from texture
  // used with nTile
  ////////////////////////////////////////////////////////////
  sf::IntRect rect;
public:
  ////////////////////////////////////////////////////////////
  // The Width and Height of ALL Tiles
  ////////////////////////////////////////////////////////////
  static int nSize;

  ////////////////////////////////////////////////////////////
  // Default constructor
  ////////////////////////////////////////////////////////////
  Tile();

  ////////////////////////////////////////////////////////////
  // One arg constructor
  //
  // \param (int) what to set nTile to
  ////////////////////////////////////////////////////////////
  Tile(int);

  ////////////////////////////////////////////////////////////
  // Two arg constructor
  //
  // \param (int) x - see declaration of location
  // \param (int) y - see declaration of location
  ////////////////////////////////////////////////////////////
  Tile(int, int);

  ////////////////////////////////////////////////////////////
  // Three arg constructor
  //
  // \param (int) x - see declaration of location
  // \param (int) y - see declaration of location
  // \param (int) what to set nTile to
  ////////////////////////////////////////////////////////////
  Tile(int, int, int);

  ////////////////////////////////////////////////////////////
  // Virtual destructor
  ////////////////////////////////////////////////////////////
  virtual ~Tile() {}

  ////////////////////////////////////////////////////////////
  // Get the texture size
  ////////////////////////////////////////////////////////////
  static sf::Vector2u getTextureSize();


  ////////////////////////////////////////////////////////////
  // Get the location of the current Tile in the map such that
  //    (0, 0) is the top left Tile
  //    and (size_of_map - 1, size_of_map - 1) is bottom right
  //
  // \return the location of Tile as struxt with x and y ints
  ////////////////////////////////////////////////////////////
  locationD_t getLocation();


  ////////////////////////////////////////////////////////////
  // Get the tiles number acrrding to texture
  ////////////////////////////////////////////////////////////
  int getTile();


  ////////////////////////////////////////////////////////////
  // Set location - see declaration of location
  //
  // \param (int) x location
  // \param (int) y location
  ////////////////////////////////////////////////////////////
  void setLocation(int, int);


  ////////////////////////////////////////////////////////////
  // Set nTile - see declaration of nTile
  //
  // \param (int) new value of tile
  ////////////////////////////////////////////////////////////
  void setTile(int);


  ////////////////////////////////////////////////////////////
  // Load the texture from a file
  //
  // \param (std::string) file name
  ////////////////////////////////////////////////////////////
  static bool setTexture(std::string);


  ////////////////////////////////////////////////////////////
  // Load the texture from a file
  //
  // \param (sf::Image) image to be used for texture
  ////////////////////////////////////////////////////////////
  static bool setTexture(sf::Image);


  ////////////////////////////////////////////////////////////
  // Draw the object onto the SFML RenderTarget (window)
  ////////////////////////////////////////////////////////////
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif /* __TILE_H__ */

