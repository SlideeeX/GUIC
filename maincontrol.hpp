if(fileMenu.Highlight(window.getModal())){ // ���� �� ������ ������ ������
	if(fileMenu.Highlight(window.getModal(), 0)){ // ���� �� ������ ��� ������� 0 ������ ������
		fileMenu.showItemBackground(0); // �������� ������ ��� ������ ��� ������� 0
	} else if (fileMenu.Highlight(window.getModal(), 1)){ // ���� �� ������ ��� ������� 1 ������ ������
		fileMenu.showItemBackground(1); // �������� ������ ��� ������ ��� ������� 1
	} else if (fileMenu.Highlight(window.getModal(), 2)){ // ���� �� ������ ��� ������� 2 ������ ������
		fileMenu.showItemBackground(2); // �������� ������ ��� ������ ��� ������� 2
	}
}

if(settingsMenu.Highlight(window.getModal())){ // ���� �� ������ ������ ������
	if(settingsMenu.Highlight(window.getModal(), 0)){ // ���� �� ������ ��� ������� 0 ������ ������
		settingsMenu.showItemBackground(0); // �������� ������ ��� ������ ��� ������� 0
	}
}

if(helpMenu.Highlight(window.getModal())){ // ���� �� ������ ������ ������
	if(helpMenu.Highlight(window.getModal(), 0)){ // ���� �� ������ ��� ������� 0 ������ ������
		helpMenu.showItemBackground(0); // �������� ������ ��� ������ ��� ������� 0
	}
}

if(menu.Highlight(window.getModal())){ // ���� �� ������ ������ ������
	if(menu.Highlight(window.getModal(), 0)){ // ���� �� ������ ��� ������� 0 ������ ������
		fileMenu.show(); // �������� ������ fileMenu
		menu.showItemBackground(0); // �������� ������ ��� ������ ��� ������� 0
	} else if(menu.Highlight(window.getModal(), 1)){ // ���� �� ������ ��� ������� 1 ������ ������
		settingsMenu.show(); // �������� ������ settingsMenu
		menu.showItemBackground(1); // �������� ������ ��� ������ ��� ������� 1
	} else if(menu.Highlight(window.getModal(), 2)){ // ���� �� ������ ��� ������� 2 ������ ������
		helpMenu.show(); // �������� ������ helpMenu
		menu.showItemBackground(2); // �������� ������ ��� ������ ��� ������� 2
	}
}

if(trigger.LMB(window.getModal())){
	ModalWindow subwindow(300, 200, "�, ����", sf::Style::Close); // ������� ������ ������ "��������� ����"
	
	//////////////////////////////////////////////////////////////
	// sf::Style::Close ����� ����, ��������� � ������������ SFML
	//////////////////////////////////////////////////////////////
	
	Interface subinterface(IntRect(0, 0, 300, 200), &lightbackground); // ������� ������ ������ "���������"
	subinterface.show(); // �������� ������
	subwindow.add(subinterface); // �������� ������
	
	Title subtitle(IntRect(50, 50, 50, 20), "������"); // ������� ������ ������ "���������"
	subtitle.show(); // �������� ������
	subwindow.add(subtitle); // �������� ������
	
	while(subwindow.isOpen()){ // ����, ���� ���� �������
		subwindow.control(); // �������� ����������
		subwindow.display(); // �������� �������
	}
}

if(button.LMB(window.getModal())){ // ���� �� ������ ������ ����� ������ ����
	if(mltitle.getCharacterSize()==GUIC_BASE_CHAR_SIZE){ // ���� ������ ������ ����� ��������
		mltitle.setCharacterSize(GUIC_BASE_CHAR_SIZE+10); // �������� �� �������+10
	} else {
		mltitle.setCharacterSize(GUIC_BASE_CHAR_SIZE); // ����� �������� �� �������
	}
}
	
if(!fileMenu.Highlight(window.getModal()) && !menu.Highlight(window.getModal(), 0)){ // ���� �� ������ �� ������ ������
	fileMenu.hide(); // �������� ������ fileMenu
}
if(!settingsMenu.Highlight(window.getModal()) && !menu.Highlight(window.getModal(), 1)){
	settingsMenu.hide(); // �������� ������ settingsMenu
}
if(!helpMenu.Highlight(window.getModal()) && !menu.Highlight(window.getModal(), 2)){
	helpMenu.hide(); // �������� ������ helpMenu
}
