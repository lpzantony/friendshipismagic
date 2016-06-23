/*
 * aiinterface.cpp
 *
 *  Created on: 22 juin 2016
 *      Author: admin
 */

#include "aiinterface.h"
#include <vector>
#include "monster.h"
#include "playerandstuff.h"
#include "../matrix/matrix.h"
#include "../dijkstra/dijkstra.h"
#include "../dijkstrainterface/vertexinterface.h"
#include "../../player.h"
#include "../dijkstra/previous.h"
#include "monstercontroller.h"

AiInterface::AiInterface() {
	monsterController = new MonsterController();
}

AiInterface::~AiInterface() {
	delete(monsterController);
}

void AiInterface::setPath(Monster& monster, PlayerAndStuff& playerstuff, Matrix& g){
	float posX = playerstuff.player->getPos().x;
	float posY = playerstuff.player->getPos().y;
	int iX = int(posX + 0.5);
	int iY = int(posY+ 0.5);

	VertexInterface* vertex = new VertexInterface();
	vertex->setVertex('J', iX, iY );
	VertexInterface& v = *vertex;

	Dijkstra dijkstra;
	auto& previous = dijkstra.dijkstra(g, v);
	monsterController->storePath(monster, previous);
	monsterController->currentPosition = {iX,iY};
	VertexInterface* next = previous.getValue(vertex);
	monsterController->nextPosition = {next->getX(),next->getY()};
}

AiInterface::Action AiInterface::giveOrder(Monster& monster, PlayerAndStuff& playerstuff, Matrix& g){
	//for all types of monster
	 AiInterface::setPath(monster, playerstuff, g);
	 return monsterController->translateOrder();
}
