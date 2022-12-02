if(fileMenu.Highlight(window.getModal())){ // Если на список наведён курсор
	if(fileMenu.Highlight(window.getModal(), 0)){ // Если на ячейку под номером 0 наведён курсор
		fileMenu.showItemBackground(0); // Показать задний фон ячейки под номером 0
	} else if (fileMenu.Highlight(window.getModal(), 1)){ // Если на ячейку под номером 1 наведён курсор
		fileMenu.showItemBackground(1); // Показать задний фон ячейки под номером 1
	} else if (fileMenu.Highlight(window.getModal(), 2)){ // Если на ячейку под номером 2 наведён курсор
		fileMenu.showItemBackground(2); // Показать задний фон ячейки под номером 2
	}
}

if(settingsMenu.Highlight(window.getModal())){ // Если на список наведён курсор
	if(settingsMenu.Highlight(window.getModal(), 0)){ // Если на ячейку под номером 0 наведён курсор
		settingsMenu.showItemBackground(0); // Показать задний фон ячейки под номером 0
	}
}

if(helpMenu.Highlight(window.getModal())){ // Если на список наведён курсор
	if(helpMenu.Highlight(window.getModal(), 0)){ // Если на ячейку под номером 0 наведён курсор
		helpMenu.showItemBackground(0); // Показать задний фон ячейки под номером 0
	}
}

if(menu.Highlight(window.getModal())){ // Если на список наведён курсор
	if(menu.Highlight(window.getModal(), 0)){ // Если на ячейку под номером 0 наведён курсор
		fileMenu.show(); // Показать объект fileMenu
		menu.showItemBackground(0); // Показать задний фон ячейки под номером 0
	} else if(menu.Highlight(window.getModal(), 1)){ // Если на ячейку под номером 1 наведён курсор
		settingsMenu.show(); // Показать объект settingsMenu
		menu.showItemBackground(1); // Показать задний фон ячейки под номером 1
	} else if(menu.Highlight(window.getModal(), 2)){ // Если на ячейку под номером 2 наведён курсор
		helpMenu.show(); // Показать объект helpMenu
		menu.showItemBackground(2); // Показать задний фон ячейки под номером 2
	}
}

if(trigger.LMB(window.getModal())){
	ModalWindow subwindow(300, 200, "О, окно", sf::Style::Close); // Создать объект класса "Модальное окно"
	
	//////////////////////////////////////////////////////////////
	// sf::Style::Close стиль окна, подробнее в документации SFML
	//////////////////////////////////////////////////////////////
	
	Interface subinterface(IntRect(0, 0, 300, 200), &lightbackground); // Создать объект класса "Интерфейс"
	subinterface.show(); // Показать объект
	subwindow.add(subinterface); // Добавить объект
	
	Title subtitle(IntRect(50, 50, 50, 20), "Привет"); // Создать объект класса "Заголовок"
	subtitle.show(); // Показать объект
	subwindow.add(subtitle); // Добавить объект
	
	while(subwindow.isOpen()){ // Цикл, пока окно открыто
		subwindow.control(); // Включить управление
		subwindow.display(); // Показать объекты
	}
}

if(button.LMB(window.getModal())){ // Если на кнопку нажата левая кнопка мыши
	if(mltitle.getCharacterSize()==GUIC_BASE_CHAR_SIZE){ // Если размер текста равен базовому
		mltitle.setCharacterSize(GUIC_BASE_CHAR_SIZE+10); // Изменить на базовый+10
	} else {
		mltitle.setCharacterSize(GUIC_BASE_CHAR_SIZE); // Иначе изменить на базовый
	}
}
	
if(!fileMenu.Highlight(window.getModal()) && !menu.Highlight(window.getModal(), 0)){ // Если на списки не наведён курсор
	fileMenu.hide(); // Спрятать объект fileMenu
}
if(!settingsMenu.Highlight(window.getModal()) && !menu.Highlight(window.getModal(), 1)){
	settingsMenu.hide(); // Спрятать объект settingsMenu
}
if(!helpMenu.Highlight(window.getModal()) && !menu.Highlight(window.getModal(), 2)){
	helpMenu.hide(); // Спрятать объект helpMenu
}
