#include "stdafx.h"
#include <stdio.h>

#define UP 49
#define DOWN 50
#define LEFT 51
#define RIGHT 52


class Caterpillar
{
	struct Module
	{
		char sign;
		Module* next;
		Module* previous;
	};

	Module* head;
	Module* tail;
	int positionX, positionY, direction;
public:

	Caterpillar(char sign, int positionX, int positionY)
	{
		head = new Module;
		head->next = nullptr;
		head->previous = nullptr;
		head->sign = sign;
		tail = head;
		this->positionX = positionX - 1;
		this->positionY = positionY - 1;
		this->direction = RIGHT;
	}

	void pushFront(char sign)
	{
		Module* temp = new Module;
		temp->sign = sign;
		temp->next = head;
		temp->previous = nullptr;
		head->previous = temp;
		head = temp;
	}

	void pushBack(char sign)
	{
		Module* temp = new Module;
		temp->sign = sign;
		temp->next = nullptr;
		tail->next = temp;
		temp->previous = tail;
		tail = temp;
	}

	void removeFront()
	{
		if (head->next == nullptr && head->previous == nullptr)
		{
			Module* tmp = head;
			head = nullptr;
			tail = nullptr;
			delete tmp;
		}
		else
		{
			Module* temp = head->next;
			temp->previous = nullptr;
			delete head;
			head = temp;
		}
	}

	void removeBack()
	{
		if (head->next == nullptr && head->previous == nullptr)
		{
			Module* tmp = head;
			head = nullptr;
			tail = nullptr;
			delete tmp;
		}
		else
		{
			Module* temp = tail->previous;
			temp->next = nullptr;
			delete tail;
			tail = temp;
		}
	}

	void print()
	{
		Module* temp = head;
		while (temp != nullptr)
		{
			printf("%c", temp->sign);
			temp = temp->next;
		}
		if (head == nullptr)
			printf("#");
	}

	bool alive()
	{
		if (head == nullptr)
			return false;
		else return true;
	}

	void makeTur(char** field)
	{
		if (field[positionY][positionX] >= '1' && field[positionY][positionX] <= '4')
		{
			direction = field[positionY][positionX];
		}
		else if (field[positionY][positionX] >= 'a' && field[positionY][positionX] <= 'z')
		{
			pushFront(field[positionY][positionX]);
			field[positionY][positionX]--;
		}
		else if (field[positionY][positionX] >= 'A' && field[positionY][positionX] <= 'Z')
		{
			pushBack(field[positionY][positionX] + 32);
			field[positionY][positionX]--;
		}
		else if (field[positionY][positionX] == 'a' - 1)
			removeFront();
		else if (field[positionY][positionX] == 'A' - 1)
			removeBack();
	}

	void move(int width, int height)
	{
		switch (direction)
		{
		case UP:
			positionY--;
			if (positionY < 0)
				positionY = height - 1;
			break;
		case DOWN:
			positionY++;
			if (positionY > height - 1)
				positionY = 0;
			break;
		case LEFT:
			positionX--;
			if (positionX < 0)
				positionX = width - 1;
			break;
		case RIGHT:
			positionX++;
			if (positionX > width - 1)
				positionX = 0;
			break;
		}
	}

	int getX()
	{
		return positionX + 1;
	}
	int getY()
	{
		return positionY + 1;
	}
};


int main()
{
	int width, height, numberOfMoves;
	int positionX, positionY, length;
	int tur = 0;
	scanf("%d %d %d", &width, &height, &numberOfMoves);
	scanf("%d %d %d", &positionX, &positionY, &length);

	char* startSigns = new char[length]; //modules
	scanf("%s", startSigns);

	char** field = new char*[height]; //field
	for (int i = 0; i < height; i++)
		field[i] = new char[width];

	for (int i = 0; i < height; i++)
	{
		scanf("%s", field[i]);
	}

	Caterpillar gasienica(startSigns[0], positionX, positionY);
	
	if (length > 1)
	{
		for (int i = 1; i < length; i++)
		{
			gasienica.pushBack(startSigns[i]);
		}
	}

	while (tur < numberOfMoves && gasienica.alive())
	{
		if (tur > 0)
			gasienica.move(width, height);

		gasienica.makeTur(field);
		tur++;
	}

	printf("%d %d ", gasienica.getX(), gasienica.getY());
	gasienica.print();
	printf("\n");

	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (field[i][j] == 96)
				field[i][j] = 64;
			printf("%c", field[i][j]);
		}
		printf("\n");
	}

    return 0;
}

