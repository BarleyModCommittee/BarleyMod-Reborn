#include "pch.h"

void onBoardInit(MyBoard board)
{

}

void onBoardUpdateGameObject(MyBoard board)
{

}

void InitBoardEvents()
{
	PVZEvent::BoardInitAfterEvent((int)onBoardInit);
	UpdateGameObjectsEvent((int)onBoardUpdateGameObject);
}
