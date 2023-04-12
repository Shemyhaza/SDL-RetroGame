#pragma once

#include "ECS.h"

class PositionComponent : public Component {

private:
	int xPos = 0;
	int	yPos = 0;

public:
	int x() { return xPos; }
	int y() { return yPos; }

	virtual void init() override {
		
		xPos = 0;
		yPos = 0;
	}

	virtual void update() override {

		xPos++;
		yPos++;
	}

	void setPos(int x, int y) {

		xPos = x;
		yPos = y;
	}

};
