///////////////////////////////////////////////////////////////////////
// EditorEngine.hpp
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
#include "EditorEngine.h"
#include <stdio.h>

EditorEngine::EditorEngine() {
  Tile::setTexture("include/Test_Tiles1.png");
  map.resize(100, 100);
  textureMap.resize((int)Tile::getTextureSize().x / Tile::nSize,
                    (int)Tile::getTextureSize().y / Tile::nSize);

  for (int i = 0; i < textureMap.size(); i++) {
    for (int j = 0; j < textureMap[i].size(); j++) {
      textureMap[i][j].setTile(j * textureMap.size() + i);
    }
  }
  textureMap.redraw();

  toolboxWindow.create(sf::VideoMode(
                                     std::min(Tile::nSize
                                              * (int)Tile::getTextureSize().x
                                              / (Tile::nSize + 1),
                                              Tile::nSize * (275 / Tile::nSize)),
                                     std::min(Tile::nSize
                                              * (int)Tile::getTextureSize().y
                                              / (Tile::nSize + 1),
                                              Tile::nSize * (275 / Tile::nSize))
                                     ), "Toolbox");
  mainWindow.create(sf::VideoMode(600, 600), "Map");

  nCurrentTile = 0;
}

int EditorEngine::mainLoop() {
  while (mainWindow.isOpen() && toolboxWindow.isOpen()) {
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case (sf::Keyboard::Up):
            map.move(0, -1, mainWindow);
            break;

          case (sf::Keyboard::Down):
            map.move(0, 1, mainWindow);
            break;

          case (sf::Keyboard::Right):
            map.move(1, 0, mainWindow);
            break;

          case (sf::Keyboard::Left):
            map.move(-1, 0, mainWindow);
            break;

          case (sf::Keyboard::S):
            map.save("include/map.map");
            break;

          case (sf::Keyboard::A):
            map.save("include/map.map", true);
            break;

          case (sf::Keyboard::L):
            map.load("include/map.map");
            break;
        } // switch
      }
      else if (event.type == sf::Event::Closed) {
        mainWindow.close();
      }
      else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          int x =
            (int)(event.mouseButton.x / Tile::nSize) + map.getLocation().x;
          int y =
            (int)(event.mouseButton.y / Tile::nSize) + map.getLocation().y;

          if ((x < map.size()) && (x >= 0) && (y < map[x].size())
              && (y >= 0))
          {
            map[x][y].setTile(nCurrentTile);
            map.redraw();
          }
        }
      }
      else if (event.type == sf::Event::LostFocus) {
        listen = false;
      }
      else if (event.type == sf::Event::GainedFocus) {
        listen = true;
      }
      else if (event.type == sf::Event::Resized) {
        mainWindow.setView(sf::View(sf::FloatRect(0.f, 0.f,
                                                  static_cast <float> (
                                                                       mainWindow
                                                                         .
                                                                         getSize()
                                                                         .x),
                                                  static_cast <float> (
                                                                       mainWindow
                                                                         .
                                                                         getSize()
                                                                         .y))));
      }
      else if (event.type == sf::Event::MouseWheelMoved) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
         ||sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
          map.move(-1*event.mouseWheel.delta, 0, mainWindow);
        else
          map.move(0, -1*event.mouseWheel.delta, mainWindow);
      }
    }

    while (toolboxWindow.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case (sf::Keyboard::Up):
            textureMap.move(0, -1, toolboxWindow);
            break;

          case (sf::Keyboard::Down):
            textureMap.move(0, 1, toolboxWindow);
            break;

          case (sf::Keyboard::Right):
            textureMap.move(1, 0, toolboxWindow);
            break;

          case (sf::Keyboard::Left):
            textureMap.move(-1, 0, toolboxWindow);
            break;

          case (sf::Keyboard::S):
            map.save("include/map.map");
            break;

          case (sf::Keyboard::A):
            map.save("include/map.map", true);
            break;

          case (sf::Keyboard::L):
            map.load("include/map.map");
            break;
        } // switch
      }
      else if (event.type == sf::Event::Closed) {
        toolboxWindow.close();
      }
      else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          int x =
            (int)(event.mouseButton.x / Tile::nSize)
            + textureMap.getLocation().x;
          int y =
            (int)(event.mouseButton.y / Tile::nSize)
            + textureMap.getLocation().y;

          if ((x < textureMap.size()) && (x >= 0)
              && (y < textureMap[x].size()) && (y >= 0))
          {
            nCurrentTile = (y * textureMap.size()) + (x);
          }
        }
      }
      else if (event.type == sf::Event::LostFocus) {
        listen = false;
      }
      else if (event.type == sf::Event::GainedFocus) {
        listen = true;
      }
      else if (event.type == sf::Event::Resized) {
        toolboxWindow.setView(sf::View(sf::FloatRect(0.f, 0.f,
                                                     static_cast <float> (
                                                                          toolboxWindow
                                                                            .
                                                                            getSize()
                                                                            .x),
                                                     static_cast <float> (
                                                                          toolboxWindow
                                                                            .
                                                                            getSize()
                                                                            .y))));
      }
      else if (event.type == sf::Event::MouseWheelMoved) {
        textureMap.move(event.mouseWheel.x, event.mouseWheel.y, toolboxWindow);
      }
    }

    update();

    mainWindow.clear();
    toolboxWindow.clear();

    draw();

    mainWindow.display();
    toolboxWindow.display();
  }

  return 0;
} // mainLoop

void EditorEngine::draw() {
  toolboxWindow.draw(textureMap);
  mainWindow.draw(map);
} // draw

void EditorEngine::update() {
  //Not needed
} // update

