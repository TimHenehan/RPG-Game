///////////////////////////////////////////////////////////////////////
// Person.h
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

#ifndef __PERSON_H__
#define __PERSON_H__


struct locationF_t {
  double x;
  double y;
};

class Person : sf::Drawable {
  protected:
    ////////////////////////////////////////////////////////////
    // The texture(image) with all the possible 
    // player images(positions) in it
    ////////////////////////////////////////////////////////////
    static sf::Texture texture;
    
    ////////////////////////////////////////////////////////////
    // Location of player relitive to map
    ////////////////////////////////////////////////////////////
    locationF_t location;
    
    ////////////////////////////////////////////////////////////
    // The state of the player
    //
    // state&3
    //   0: east (right)
    //   1: north(up)
    //   2: west (left)
    //   3: south(down)
    //
    // state&4
    //   4: midstep
    //
    // state&8
    //   0: on right foot
    //   8: on left  foot
    ////////////////////////////////////////////////////////////
    char state;
  
  public:
    ////////////////////////////////////////////////////////////
    // Default constructor
    ////////////////////////////////////////////////////////////
    Person ();
    
    ////////////////////////////////////////////////////////////
    // Move - moves the player or changes direction of
    // person if person is not facing move direction
    //
    // \param (int) x position fo move
    // \param (int) y position fo move
    ////////////////////////////////////////////////////////////
    void move(int, int);
    
    ////////////////////////////////////////////////////////////
    // Virtual destructor
    ////////////////////////////////////////////////////////////
    virtual ~Person ();
};

#endif /* __PERSON_H__ */

