#include <iostream>
#include <GUIC/Settings.hpp>
#include <GUIC/BaseGUIC.hpp> // ����������� ����������

using namespace guic; // ������� ������������ GUIC

#include "main.hpp" // ���������� ������ �� ��������

int screen_w = sf::VideoMode::getDesktopMode().width; // �������� ������ ������
int screen_h = sf::VideoMode::getDesktopMode().height; // �������� ������ ������

int main(){
	setlocale(LC_ALL, "Rus"); // ���������� ������� ����
	
	sf::Image lightbackground; // ������� ����������� "lightbackground"
	sf::Image darkbackground; // ������� ����������� "lightbackground"
	lightbackground.loadFromFile("resources/interface/lightbackground.png"); // ��������� ����������� �� �����
	darkbackground.loadFromFile("resources/interface/background.png"); // ��������� ����������� �� �����
	
	ModalWindow window(screen_w, screen_h, "GUIC");  // ������� ������ ������ "��������� ����"
	
	Vector2i position = window.getPosition(); // �������� ������� ����
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// sf::Vector2i - ������� ������ SFML, ���������� 2 �������� (2i - int, 2f - float, 2), ���������� � ������������ SFML
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	position.x -= 8; // ���������� �������
	position.y -= 2; // ���������� �������
	
	window.setPosition(position); // �������� ������� ���������� ����

	BaseFont.loadFromFile("resources/interface/UbuntuMono-B.ttf"); // ��������� ������� ����� �� �����
	BaseTextColor = sf::Color::Black; // ���������� ������� ���� "׸����"
	
	//////////////////////////////////////////////////////////////////////////////////////
	// guic::BaseFont ��� ������� ����� �������, ���� �� ������� - �� ����� ����� �����
	// guic::BaseTextColor ��� ������� ���� �������, ���� �� ������� - �� ����� ����� �����
	// sf::Font ������ ������ ������ "�����", ��������� � ������������ SFML
	//////////////////////////////////////////////////////////////////////////////////////
	
	Interface background(IntRect(0, 0, screen_w, screen_h), &darkbackground); // ������� ������ ������ "���������", ����� ������ ���� ����
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// sf::IntRect ��� ������� ������ SFML - �������������, ��� sf::IntRect(���������� x, ���������� y, ������, ������)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	List menu(IntRect(0, 0, screen_w, 20), menuItems, &lightbackground, 3); // ������� ������ ������ "������"
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// guic::menuItems - ��������� ���� ListItems, ��������� � main.hpp
	// &lightbackground - ��������� �� ����������� (� ����� �������� ��������)
	// 3 - ���������� ����� ������. ���� ������� �������� ������ - ��������� ������� �� ����� ��������
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	menu.setListSide(sf::Vector2i(1, 0)); // ���������� �������, � ������� ������������� ������
	
	///////////////////////////////////////////////////////////////////////////////
	// sf::Vector2i(1, 0) - �����
	// sf::Vector2i(-1, 0) - ������
	// sf::Vector2i(0, 1) - �������
	// sf::Vector2i(0, -1) - �����
	// ����������� ��������, �������� sf::Vector2i(1, -1) ��� sf::Vector2i(-1, 1)
	//////////////////////////////////////////////////////////////////////////////
	
	List fileMenu(IntRect(menu.getItemRect(0).left, 20, 100, 40), fileMenuItems, &lightbackground, 2); // ������� ������ ������ "������"
	fileMenu.setListSide(Vector2i(1, 0)); // ���������� �������, � ������� ������������� ������
	fileMenu.maximizeWidth(); // ��������������� ������ �� ������
	
	////////////////////////////////////////////////////////////////////////////////////////
	// ��� �� ���������� guic::List::maximizeHeight()
	// guic::List::getItemRect(int num) - �������� ������������� ������ �� ������ ��� ������� num
	////////////////////////////////////////////////////////////////////////////////////////
	
	List settingsMenu(IntRect(menu.getItemRect(1).left, 20, 100, 20), settingsMenuItems, &lightbackground, 1); // ������� ������ ������ "������"
	settingsMenu.setListSide(Vector2i(1, 0)); // ���������� �������, � ������� ������������� ������
	settingsMenu.maximizeWidth(); // ��������������� ������ �� ������
	
	List helpMenu(IntRect(menu.getItemRect(2).left, 20, 200, 20), helpMenuItems, &lightbackground, 1); // ������� ������ ������ "������"
	helpMenu.setListSide(Vector2i(1, 0)); // ���������� �������, � ������� ������������� ������
	helpMenu.maximizeWidth(); // ��������������� ������ �� ������
	
	window.add(fileMenu); // �������� ������ � ��������� ����
	window.add(settingsMenu); // �������� ������ � ��������� ����
	window.add(helpMenu); // �������� ������ � ��������� ����
	window.add(background); // �������� ������ � ��������� ����
	window.add(menu); // �������� ������ � ��������� ����
	
	/////////////////////////////////////////////////////
	// guic::ModalWindow::remove() ������� ������ �� ����
	/////////////////////////////////////////////////////
	
	Container container(IntRect(150, 150, 500, 500)); // ������� ������ ������ "���������"
	container.show(); // �������� ������
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ������ ������ guic::Container ��������� ��������� � ���� �������. ������������� ��� ����� ������������ ����������
	// guic::Container �� ������������ guic::Addable::setSprite()
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	Interface interface(IntRect(0, 0, 500, 500), &lightbackground); // ������� ������ ������ "���������"
	interface.show(); // ���������� ������
	container.add(interface); // �������� ������ � ���������
	
	Title title(IntRect(0, 0, 50, 40), "������ �����", 20); // ������� ������ ������ "���������"
	title.show(); // ���������� ������
	container.add(title); // �������� ������ � ���������
	
	MultilineTitle mltitle(IntRect(50, 100, 150, 50), "����� ��� ���� ������ ����������� ����� �� ����� ���"); // ������� ������ ������ "����������� �����"
	mltitle.show(); // ���������� ������
	container.add(mltitle); // �������� ������ � ���������
	
	Trigger trigger(IntRect(0, GUIC_BASE_LIST_INTERVAL, title.getTitleWidth(), title.getTitleHeight())); // ������� ������ ������ "�������"
	trigger.show(); // ���������� ������
	container.add(trigger); // �������� ������ � ���������
	
	Button button(IntRect(50, 50, 175, 50), "������"); // ������� ������ ������ "������"
	button.show(); // ���������� ������
	container.add(button); // �������� ������ � ���������
	
	List list(IntRect(200, 0, 100, 500), titledImageItems, &lightbackground, 5); // ������� ������ ������ "������"
	list.show(); // ���������� ������
	container.add(list); // �������� ������ � ���������
	
	Enter enter(IntRect(70, 300, 300, 50), &darkbackground); // ������� ������ ������ "����"
	enter.show(); // ���������� ������
	container.add(enter); // �������� ������ � ���������
	
	window.add(container); // �������� ��������� � ��������� ����
	
	menu.setItemBackgrounds(Color::Blue); // ���������� ���� ���� �����
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	// sf::Color ������� ������ ������ SFML, ���������� � ���� �����.
	// �����! sf::Color::White - ��� ���������� ����. ����� ���������� �����, ����������� ��������
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	fileMenu.setItemBackgrounds(Color::Blue); // ���������� ���� ���� �����
	settingsMenu.setItemBackgrounds(Color::Blue); // ���������� ���� ���� �����
	helpMenu.setItemBackgrounds(Color::Blue); // ���������� ���� ���� �����
	
	background.show(); // �������� ������
	menu.show(); // �������� ������
	
	while(window.isOpen()){ // ����, ���� ���� �������
		window.control(); // �������� ����������
		
		menu.hideItemBackgrounds(); // �������� ��� �����
		fileMenu.hideItemBackgrounds(); // �������� ��� �����
		settingsMenu.hideItemBackgrounds(); // �������� ��� �����
		helpMenu.hideItemBackgrounds(); // �������� ��� �����
		
		///////////////////////////////////////////////////////////////////////////////////////////////
		// ��� �� ���������� guic::List::hideItemBackground(num)
		///////////////////////////////////////////////////////////////////////////////////////////////
		
		#include "maincontrol.hpp" // ���������� ������ � �����������
		
		window.display(); // �������� �������
	}
}
