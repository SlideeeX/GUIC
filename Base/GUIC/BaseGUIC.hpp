#ifndef BASEGUIC_HPP
#define BASEGUIC_HPP

#include "Variables.hpp"

#include "GUIC_Settings.hpp"

#ifndef GUIC_MAX_MLTITLE_LENGHT
#define GUIC_MAX_MLTITLE_LENGHT 300
#endif

#ifndef GUIC_MAX_MLTITLE_ROWS
#define GUIC_MAX_MLTITLE_ROWS 100
#endif

#ifndef GUIC_MAX_LIST_ITEMS
#define GUIC_MAX_LIST_ITEMS 100
#endif

#ifndef GUIC_MAX_ITEMS
#define GUIC_MAX_ITEMS 10000
#endif

#ifndef GUIC_BASE_LIST_INTERVAL
#define GUIC_BASE_LIST_INTERVAL 5
#endif

#ifndef GUIC_BASE_LIST_TAB
#define GUIC_BASE_LIST_TAB 5
#endif

#ifndef GUIC_MAX_LAYER
#define GUIC_MAX_LAYER 5
#endif

#ifndef GUIC_BASE_BUTTON_FRAMEFAT
#define GUIC_BASE_BUTTON_FRAMEFAT 4
#endif

#ifndef GUIC_BASE_CHAR_SIZE
#define GUIC_BASE_CHAR_SIZE 15
#endif

#ifndef GUIC_BASE_HIGH_LAYER
#define GUIC_BASE_HIGH_LAYER 0
#endif

#ifndef GUIC_BASE_CONTAINER_LAYER
#define GUIC_BASE_CONTAINER_LAYER 0
#endif

#ifndef GUIC_BASE_INTERFACE_LAYER
#define GUIC_BASE_INTERFACE_LAYER 1
#endif

#ifndef GUIC_BASE_LIST_LAYER
#define GUIC_BASE_LIST_LAYER 2
#endif

#ifndef GUIC_BASE_BUTTON_LAYER
#define GUIC_BASE_BUTTON_LAYER 3
#endif

#ifndef GUIC_BASE_TITLE_LAYER
#define GUIC_BASE_TITLE_LAYER 4
#endif

#ifndef GUIC_BASE_MLTITLE_LAYER
#define GUIC_BASE_MLTITLE_LAYER 5
#endif

#include "Addable.hpp"
#include "Addable.cpp"

#include "Interface.hpp"
#include "Interface.cpp"

#include "Trigger.hpp"
#include "Trigger.cpp"

#include "Title.hpp"
#include "Title.cpp"

#include "Button.hpp"
#include "Button.cpp"

#include "MultilineTitle.hpp"
#include "MultilineTitle.cpp"

#include "List.hpp"
#include "List.cpp"

#include "Container.hpp"
#include "Container.cpp"

#include "ModalWindow.hpp"
#include "ModalWindow.cpp"

#endif
