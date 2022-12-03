ListItems menuItems[3] =
{
	{ "Файл", "", "" },
	{ "Настройки", "", "" },
	{ "Справка", "", "" },
};

//////////////////////////////////////////////////////////////////////
// guic::ListItems - структура, содержащая в себе значения:
// name - текст ячейки списка
// imagename - путь к изображению ячейки
// description - описание (std::string)
// Описание в системе не читается, заполняется для внешнего обращения
//////////////////////////////////////////////////////////////////////

ListItems fileMenuItems[2] =
{
	{ "Новый", "", "" },
	{ "Открыть", "", "" }
};

ListItems settingsMenuItems[1] =
{
	{ "Вид", "", "" }
};

ListItems helpMenuItems[3] =
{
	{ "Справка по элементам", "", "" }
};

ListItems titledImageItems[5] =
{
	{ "C#", "resources/items/C#.png", "" },
	{ "JS", "resources/items/JS.png", "" },
	{ "OBJ", "resources/items/OBJ.png", "" },
	{ "SQL", "resources/items/SQL.png", "" },
	{ "Source Code", "resources/items/SRC.png", "" }
};
