#include <iostream>
#include <GUIC/Settings.hpp>
#include <GUIC/BaseGUIC.hpp> // Подключение библиотеки

using namespace guic; // Именное пространство GUIC

#include "main.hpp" // Подключить хеадер со списками

int screen_w = sf::VideoMode::getDesktopMode().width; // Получить ширину экрана
int screen_h = sf::VideoMode::getDesktopMode().height; // Получить высоту экрана

int main(){
	setlocale(LC_ALL, "Rus"); // Установить русский язык
	
	sf::Image lightbackground; // Создать изображение "lightbackground"
	sf::Image darkbackground; // Создать изображение "lightbackground"
	lightbackground.loadFromFile("resources/interface/lightbackground.png"); // Загрузить изображение из файла
	darkbackground.loadFromFile("resources/interface/background.png"); // Загрузить изображение из файла
	
	ModalWindow window(screen_w, screen_h, "GUIC");  // Создать объект класса "Модальное окно"
	
	Vector2i position = window.getPosition(); // Получить позицию окна
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// sf::Vector2i - базовый объект SFML, содержащий 2 значения (2i - int, 2f - float, 2), подпробнее в документации SFML
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	position.x -= 8; // Калибровка вручную
	position.y -= 2; // Калибровка вручную
	
	window.setPosition(position); // Изменить позицию модального окна

	BaseFont.loadFromFile("resources/interface/UbuntuMono-B.ttf"); // Загрузить базовый шрифт из файла
	BaseTextColor = sf::Color::Black; // Установить базовый цвет "Чёрный"
	
	//////////////////////////////////////////////////////////////////////////////////////
	// guic::BaseFont это базовый шрифт текстов, если не указать - не будет виден текст
	// guic::BaseTextColor это базовый цвет текстов, если не указать - не будет виден текст
	// sf::Font создаёт объект класса "Шрифт", подробнее в документации SFML
	//////////////////////////////////////////////////////////////////////////////////////
	
	Interface background(IntRect(0, 0, screen_w, screen_h), &darkbackground); // Создать объект класса "Интерфейс", здесь играет роль фона
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// sf::IntRect это базовый объект SFML - прямоугольник, где sf::IntRect(Координата x, координата y, ширина, высота)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	List menu(IntRect(0, 0, screen_w, 20), menuItems, &lightbackground, 3); // Создать объект класса "Список"
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// guic::menuItems - структура типа ListItems, подробнее в main.hpp
	// &lightbackground - указатель на изображение (В целях экономии ресурсов)
	// 3 - количество ячеек списка. Если вписать значение больше - программа вылетит на этапе загрузки
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	menu.setListSide(sf::Vector2i(1, 0)); // Установить сторону, с которой располагаются ячейки
	
	///////////////////////////////////////////////////////////////////////////////
	// sf::Vector2i(1, 0) - Слева
	// sf::Vector2i(-1, 0) - Справа
	// sf::Vector2i(0, 1) - Наверху
	// sf::Vector2i(0, -1) - Внизу
	// Допускается сложение, например sf::Vector2i(1, -1) или sf::Vector2i(-1, 1)
	//////////////////////////////////////////////////////////////////////////////
	
	List fileMenu(IntRect(menu.getItemRect(0).left, 20, 100, 40), fileMenuItems, &lightbackground, 2); // Создать объект класса "Список"
	fileMenu.setListSide(Vector2i(1, 0)); // Установить сторону, с которой располагаются ячейки
	fileMenu.maximizeWidth(); // Максимизировать ячейки по ширине
	
	////////////////////////////////////////////////////////////////////////////////////////
	// Так же существует guic::List::maximizeHeight()
	// guic::List::getItemRect(int num) - получить прямоугольник ячейки из списка под номером num
	////////////////////////////////////////////////////////////////////////////////////////
	
	List settingsMenu(IntRect(menu.getItemRect(1).left, 20, 100, 20), settingsMenuItems, &lightbackground, 1); // Создать объект класса "Список"
	settingsMenu.setListSide(Vector2i(1, 0)); // Установить сторону, с которой располагаются ячейки
	settingsMenu.maximizeWidth(); // Максимизировать ячейки по ширине
	
	List helpMenu(IntRect(menu.getItemRect(2).left, 20, 200, 20), helpMenuItems, &lightbackground, 1); // Создать объект класса "Список"
	helpMenu.setListSide(Vector2i(1, 0)); // Установить сторону, с которой располагаются ячейки
	helpMenu.maximizeWidth(); // Максимизировать ячейки по ширине
	
	window.add(fileMenu); // Добавить объект в модальное окно
	window.add(settingsMenu); // Добавить объект в модальное окно
	window.add(helpMenu); // Добавить объект в модальное окно
	window.add(background); // Добавить объект в модальное окно
	window.add(menu); // Добавить объект в модальное окно
	
	/////////////////////////////////////////////////////
	// guic::ModalWindow::remove() удаляет объект из окна
	/////////////////////////////////////////////////////
	
	Container container(IntRect(150, 150, 500, 500)); // Создать объект класса "Контейнер"
	container.show(); // Показать объект
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Объект класса guic::Container позволяет размещать в себя объекты. Располагаться они будут относительно контейнера
	// guic::Container не поддерживает guic::Addable::setSprite()
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	Interface interface(IntRect(0, 0, 500, 500), &lightbackground); // Создать объект класса "Интерфейс"
	interface.show(); // Показывать объект
	container.add(interface); // Добавить объект в контейнер
	
	Title title(IntRect(0, 0, 50, 40), "Тыкать здесь", 20); // Создать объект класса "Заголовок"
	title.show(); // Показывать объект
	container.add(title); // Добавить объект в контейнер
	
	MultilineTitle mltitle(IntRect(50, 100, 150, 50), "Съешь ещё этих мягких французских булок да выпей чаю"); // Создать объект класса "Мнострочный текст"
	mltitle.show(); // Показывать объект
	container.add(mltitle); // Добавить объект в контейнер
	
	Trigger trigger(IntRect(0, GUIC_BASE_LIST_INTERVAL, title.getTitleWidth(), title.getTitleHeight())); // Создать объект класса "Триггер"
	trigger.show(); // Показывать объект
	container.add(trigger); // Добавить объект в контейнер
	
	Button button(IntRect(50, 50, 175, 50), "Кнопка"); // Создать объект класса "Кнопка"
	button.show(); // Показывать объект
	container.add(button); // Добавить объект в контейнер
	
	List list(IntRect(200, 0, 100, 500), titledImageItems, &lightbackground, 5); // Создать объект класса "Список"
	list.show(); // Показывать объект
	container.add(list); // Добавить объект в контейнер
	
	Enter enter(IntRect(70, 300, 300, 50), &darkbackground); // Создать объект класса "Ввод"
	enter.show(); // Показывать объект
	container.add(enter); // Добавить объект в контейнер
	
	window.add(container); // Добавить контейнер в модальное окно
	
	menu.setItemBackgrounds(Color::Blue); // Установить цвет фона ячеек
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	// sf::Color базовый объект класса SFML, содержащий в себе цвета.
	// Важно! sf::Color::White - это прозрачный цвет. Чтобы установить белый, используйте картинку
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	fileMenu.setItemBackgrounds(Color::Blue); // Установить цвет фона ячеек
	settingsMenu.setItemBackgrounds(Color::Blue); // Установить цвет фона ячеек
	helpMenu.setItemBackgrounds(Color::Blue); // Установить цвет фона ячеек
	
	background.show(); // Показать объект
	menu.show(); // Показать объект
	
	while(window.isOpen()){ // Цикл, пока окно открыто
		window.control(); // Включить управление
		
		menu.hideItemBackgrounds(); // Спрятать фон ячеек
		fileMenu.hideItemBackgrounds(); // Спрятать фон ячеек
		settingsMenu.hideItemBackgrounds(); // Спрятать фон ячеек
		helpMenu.hideItemBackgrounds(); // Спрятать фон ячеек
		
		///////////////////////////////////////////////////////////////////////////////////////////////
		// Так же существует guic::List::hideItemBackground(num)
		///////////////////////////////////////////////////////////////////////////////////////////////
		
		#include "maincontrol.hpp" // Подключить хеадер с управлением
		
		window.display(); // Показать объекты
	}
}
