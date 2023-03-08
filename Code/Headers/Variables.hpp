#pragma once

#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#if BUILDING_DLL
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

#include <SFML/Graphics.hpp>

#ifndef GUIC_MAX_ITEMS
#define GUIC_MAX_ITEMS 10000
#endif

#ifndef BASE_HIGH_LAYER
#define BASE_HIGH_LAYER 0
#endif

#ifndef GUIC_BASE_INTERFACE_LAYER
#define GUIC_BASE_INTERFACE_LAYER 1
#endif

#ifndef GUIC_BASE_CHAR_SIZE
#define GUIC_BASE_CHAR_SIZE 15
#endif

#ifndef GUIC_BASE_TITLE_LAYER
#define GUIC_BASE_TITLE_LAYER 6
#endif

#ifndef GUIC_BASE_CHAR_SIZE
#define GUIC_BASE_CHAR_SIZE 15
#endif

#ifndef GUIC_BASE_BUTTON_FRAMEFAT
#define GUIC_BASE_BUTTON_FRAMEFAT 4
#endif

#ifndef GUIC_BASE_BUTTON_LAYER
#define GUIC_BASE_BUTTON_LAYER 5
#endif

#ifndef GUIC_BASE_CONTAINER_LAYER
#define GUIC_BASE_CONTAINER_LAYER 0
#endif

#ifndef GUIC_MAX_LAYER
#define GUIC_MAX_LAYER 6
#endif

#ifndef GUIC_BASE_ENTER_INTERVAL
#define GUIC_BASE_ENTER_INTERVAL 5
#endif

#ifndef GUIC_MAX_LIST_ITEMS
#define GUIC_MAX_LIST_ITEMS 100
#endif

#ifndef GUIC_BASE_LIST_LAYER
#define GUIC_BASE_LIST_LAYER 2
#endif

#ifndef GUIC_BASE_LIST_TAB
#define GUIC_BASE_LIST_TAB 5
#endif

#ifndef GUIC_BASE_LIST_INTERVAL
#define GUIC_BASE_LIST_INTERVAL 5
#endif

#ifndef GUIC_BASE_CHAR_SIZE
#define GUIC_BASE_CHAR_SIZE 15
#endif

#ifndef GUIC_MAX_MLTITLE_LENGHT
#define GUIC_MAX_MLTITLE_LENGHT 300
#endif

#ifndef GUIC_MAX_MLTITLE_ROWS
#define GUIC_MAX_MLTITLE_ROWS 100
#endif

#ifndef GUIC_BASE_CHAR_SIZE
#define GUIC_BASE_CHAR_SIZE 15
#endif

#ifndef GUIC_BASE_MLTITLE_LAYER
#define GUIC_BASE_MLTITLE_LAYER 4
#endif

#ifndef GUIC_BASE_ENTER_LAYER
#define GUIC_BASE_ENTER_LAYER 3
#endif

#ifndef GUIC_BASE_FONT
#define GUIC_BASE_FONT
namespace guic {
	sf::Font DLLIMPORT BaseFont;
}
#endif

#ifndef GUIC_BASE_TEXTCOLOR
#define GUIC_BASE_TEXTCOLOR
namespace guic {
	sf::Color DLLIMPORT BaseTextColor;
}
#endif

#endif
