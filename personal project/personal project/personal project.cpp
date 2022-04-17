#include <bangtal.h>
#include <stdio.h>

SceneID scene1, scene2;
ObjectID OX[9], blank[9], start, restart, end;
char turn = 'X';
int count = 0;

const char* imageOX[9] = {
	"images/0.png",
	"images/1.png",
	"images/2.png",
	"images/3.png",
	"images/4.png", 
	"images/5.png", 
	"images/6.png", 
	"images/7.png", 
	"images/8.png" 
};
const char* imageBlank[9] = {
	"images/blank0.png",
	"images/blank1.png",
	"images/blank2.png",
	"images/blank3.png",
	"images/blank4.png",
	"images/blank5.png",
	"images/blank6.png",
	"images/blank7.png",
	"images/blank8.png"
};

int boardX[9] = { 350, 550, 750, 350, 550, 750, 350, 550, 750 };
int boardY[9] = { 450, 450, 450, 250, 250, 250, 50, 50, 50 };
int OX_index[9];
bool OX_index_filled[9];

int win()
{
	if (OX_index[0] == 0 && OX_index[1] == 0 && OX_index[2] == 0 ||
		OX_index[3] == 0 && OX_index[4] == 0 && OX_index[5] == 0 ||
		OX_index[6] == 0 && OX_index[7] == 0 && OX_index[8] == 0 ||
		OX_index[0] == 0 && OX_index[3] == 0 && OX_index[6] == 0 ||
		OX_index[1] == 0 && OX_index[4] == 0 && OX_index[7] == 0 ||
		OX_index[2] == 0 && OX_index[5] == 0 && OX_index[8] == 0 ||
		OX_index[0] == 0 && OX_index[4] == 0 && OX_index[8] == 0 ||
		OX_index[2] == 0 && OX_index[4] == 0 && OX_index[6] == 0
		)
		return 0;
	else if (OX_index[0] == 1 && OX_index[1] == 1 && OX_index[2] == 1 ||
		OX_index[3] == 1 && OX_index[4] == 1 && OX_index[5] == 1 ||
		OX_index[6] == 1 && OX_index[7] == 1 && OX_index[8] == 1 ||
		OX_index[0] == 1 && OX_index[3] == 1 && OX_index[6] == 1 ||
		OX_index[1] == 1 && OX_index[4] == 1 && OX_index[7] == 1 ||
		OX_index[2] == 1 && OX_index[5] == 1 && OX_index[8] == 1 ||
		OX_index[0] == 1 && OX_index[4] == 1 && OX_index[8] == 1 ||
		OX_index[2] == 1 && OX_index[4] == 1 && OX_index[6] == 1
		)
		return 1;
	else if (OX_index_filled[0] == true &&
		OX_index_filled[1] == true &&
		OX_index_filled[2] == true &&
		OX_index_filled[3] == true &&
		OX_index_filled[4] == true &&
		OX_index_filled[5] == true &&
		OX_index_filled[6] == true &&
		OX_index_filled[7] == true &&
		OX_index_filled[8] == true
		)
		return 2;
	return -1;
}

void resetGame()
{
	count = 0;
	for (int i = 0; i < 9; i++) {
		hideObject(OX[i]);
		showObject(blank[i]);
		OX_index_filled[i] = false;
		OX_index[i] = 2;
	}
	hideObject(end);
	hideObject(restart);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	if (object == start) {
		enterScene(scene2);
	}
	else if (object == restart) {
		resetGame();
	}
	else if (object == end) {
		endGame();
	}

	for (int i = 0; i < 9; i++) {
		if (object == blank[i]) {
			hideObject(blank[i]);
			locateObject(OX[count], scene2, boardX[i], boardY[i]);
			showObject(OX[count]);

			OX_index[i] = count % 2;
			count++;
			OX_index_filled[i] = true;
		}
		if (object == OX[i])
			showMessage("you can't do that");
	}
	
	if (win() == 0) {
		showMessage("X wins!");	
		showObject(restart);
		showObject(end);
	}
	else if (win() == 1) {
		showMessage("O wins!");
		showObject(restart);
		showObject(end);
	}
	else if (win() == 2) {
		showMessage("draw!");
		showObject(restart);
		showObject(end);
	}
}

int main()
{
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	setMouseCallback(mouseCallback);

	scene1 = createScene("배경1", "images/background1.png");
	scene2 = createScene("배경2", "images/background2.png");

	start = createObject("images/start.png");
	locateObject(start, scene1, 570, 200);
	showObject(start);

	restart = createObject("images/restart.png");
	locateObject(restart, scene2, 1000, 100);

	end = createObject("images/end.png");
	locateObject(end, scene2, 1000, 50);

	for (int i = 0; i < 9; i++) {
		OX[i] = createObject(imageOX[i]);
		blank[i] = createObject(imageBlank[i]);
		locateObject(blank[i], scene2, boardX[i], boardY[i]);
		showObject(blank[i]);

		OX_index_filled[i] = false;
		OX_index[i] = 2;
	}

	startGame(scene1);

	return 0;
}