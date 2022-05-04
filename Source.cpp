#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

//creating data structure to define the order a player 
struct PlayerHighScore {
	int playerOrder = 1;
	int HighScore = 0;
}; 
PlayerHighScore hs[10];



int menuOptions = 0;/*
					0->to display menu in the begining of the game
					1-> to Start playing
					2->to Display High Score
					3->To do display options Menu
					4-> to dispaly credits Menu
					*/





bool SameName = 1;//if player doesnt change his name
bool canjump = 1;
bool canmoverigt = 1;
bool canmoveleft = 1;
bool space = 0; 
bool rightc = 0;
bool marioal = 1;//1 -> mario alive //0 ->  mario died
bool enemyal = 1;//1 -> enemy alive //0 ->  enemy died
bool PlayerCase = 1; //1 -> win // 0 -> Lose 
bool Newgame = 0;//bool to reset the game and player postion
bool show = 1;//bool to check if menu is displayed or not
bool Full = 0;//check number of players dont exceed 10 players
int pos;
int playerNum = 1;//number of palyers played the game
int score = 0;
const int num = 10;
int animationindicator = 0;
float velocityy = 0;
float velocityx = 0;
float groundMotion = 1, ground2Motion = 1;
Clock framespeed;
//functions
int moveright();
void moveleft();
void jump();
int detectground();
int detectpipe();
void calHighScore(int, int);
void DiplayHighScore(int);//Displaying highscores function
void structOrder();//Setting struct order for each player
void MenuOptions(int);//function to display menu 
void Swap(int& n1, int& n2, int& n3, int& n4);//function to swap high scores of two player and their orders
void Sort(int);//function to sort players decsending according to their highscores
void Reset(bool);//function to reset the setting of the game
bool GameOver();//function to display gameover message
bool Fullmessage(int,int);//function to display message when number of players exceed 10
//end of functions
Texture skytx;
Sprite sky;
Texture mario;
Sprite player;
Texture groundtex;
Sprite ground[15];
Texture ground2;
Texture pipetex;
Sprite pipe[3];
Texture cloudtx;
Sprite	cloudi[10];
Sprite menu;//Menu wallpaper
Texture menutx;
Sprite highScore;//highscore wallpaper
Texture highScoretx;
Sprite option; //option Wallpaper
Texture Option;
Sprite credit;//Credits wallpaper
Texture Credittx;
Sprite newGame;//New Game button 
Texture newGametx;
Sprite gameOver;//Game Over Condition
Texture gameOvertx;
Sprite enemy;//enemy sprite
Texture enemytx;
Text Data;//text of name of players
Text Scores;//test of scores of players
Text text;
Text Message;
Text gameovermessage;
Font font;
Vector2f groundPos(3250, 240);


sf::RenderWindow window(sf::VideoMode(800, 485), "Super Mario!!");
View camera(FloatRect(0, 0, 800, 485));


int main() {
	
	structOrder();//Calling Struct order function

	
	
	
	//cloud
	cloudtx.loadFromFile("cloud.png");

	for (int i = 0; i < 10; i++) {
		cloudi[i].setTexture(cloudtx);
		cloudi[i].setScale(0.25, 0.25);
		cloudi[i].setPosition(200 * i + 100, 50);
	}
	//end of cloud
	//mario

	mario.loadFromFile("mario_spritesheet.png");
	player.setTexture(mario);
	player.setScale(3, 3);
    player.setPosition(400, 250);
	player.setTextureRect(IntRect(0, 0, 16, 32));
	player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);

	//end of mario

	//Menu Sprite declaring

	menutx.loadFromFile("menu.png");
	menu.setTexture(menutx);
	menu.setPosition(0, 0);
	menu.setScale(1.25, 1.5);

	//End of Menu Sprite declaring


	//Font 

	font.loadFromFile("VECTRO-Bold.otf");

	//Text


	text.setFont(font);
	text.setString("CREDITS !!\n\n\n  Ahmed \n  Rana \n  Aliaa \n  Moaaz \n  Zeyad \n  Nour \n  Mohamed");
	text.setFillColor(sf::Color(0, 0, 0, 180));

	text.setPosition(350, 10);
	text.setCharacterSize(32);

	//End Of Text

	
	

	//Game Over 
	gameOvertx.loadFromFile("gameOver.png");
	gameOver.setTexture(gameOvertx);
	gameOver.setPosition(200, 50);
	gameOver.setScale(1.25, 1.5);


	//End Of Game Over

	//Credits Wallpaper
	Credittx.loadFromFile("Sky.png");
	credit.setTexture(Credittx);
	credit.setPosition(0, 0);
	credit.setScale(1.25, 1.25);
	//End of credits

	//New Game button
	newGametx.loadFromFile("button-png-game-3.png");
	newGame.setTexture(newGametx);
	newGame.setPosition(230, 140);
	newGame.setScale(1.25, 1.25);

	//End of New Game


	//highscore menu for testing
	highScoretx.loadFromFile("Sky.png");
	highScore.setTexture(highScoretx);
	highScore.setPosition(0, 0);
	//End of Testing

	//options menu for testing
	Option.loadFromFile("Sky.png");
	option.setTexture(Option);
	option.setPosition(0, 0);
	//End of Testing


	//sky
	skytx.loadFromFile("sky2.png");
	sky.setTexture(skytx);
	sky.setScale(10, 8);
	//end of sky

	//enemy
	enemytx.loadFromFile("goomba.png");
	enemy.setTexture(enemytx);
	enemy.setPosition(580, 380);
	enemy.setScale(2, 2);
	//end of enemy

	//ground



	groundtex.loadFromFile("ground.png");
	ground2.loadFromFile("ground2.png");



	for (int i = 0; i < 3; i++) {

		ground[i].setTexture(groundtex);

		ground[i].setScale(0.4, 0.6);
		ground[i].setPosition(i * ground[i].getGlobalBounds().width, 410);

	}
	for (int i = 3; i < 6; i++) {
		ground[i].setTexture(ground2);
		ground[i].setScale(0.3, 0.4);
		ground[i].setPosition(2512 + ((i - 3) * 370), 120);
		if (i == 4) {
			ground[i].setPosition(2512 + ((i - 3) * 370), 370);
		}
	}

	for (int i = 7; i < 13; i++) {

		ground[i].setTexture(groundtex);

		ground[i].setScale(0.4, 0.6);
		ground[i].setPosition(3580 + ((i - 7) * ground[i].getGlobalBounds().width), 410);

	}

	//end of ground
	//pipe
	pipetex.loadFromFile("pipe.jpg");


	for (size_t i = 0; i < 3; i++)
	{
		pipe[i].setTexture(pipetex);
		pipe[i].setScale(1.4, 1.8);
		pipe[i].setPosition(i * 400 + 450, 270);

	}

	//end ofpipe
	
	window.setFramerateLimit(120);




	
	
	
	
	

	while (window.isOpen())
	{
		
		//enemy 
		if (enemy.getGlobalBounds().intersects(pipe[1].getGlobalBounds())) {
			rightc = 1;
		}
		if (enemy.getGlobalBounds().intersects(pipe[0].getGlobalBounds())) {
			rightc = 0;
		}
		if (!rightc) {
			enemy.move(1, 0);
		}
		else{
			enemy.move(-1, 0);
		}
		if (enemy.getGlobalBounds().intersects(player.getGlobalBounds()) && player.getPosition().y < 340) {
			enemy.setPosition(-100, -100);
			enemyal = 0;
		}
		else if (enemy.getGlobalBounds().intersects(player.getGlobalBounds()) && player.getPosition().y > 340) {
			marioal = 0;
			player.setPosition(-100, -100);
		}

		//end of enemy

		
		

		//Menu displaying
		Vector2i mousePressed = Mouse::getPosition(window);//variable for determine the position of the mouse in the window


		if (Mouse::isButtonPressed(Mouse::Left)) {

			//on pressing high scores button
			if ((mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y>120 && mousePressed.y < 205 && show)) {

				menuOptions = 2;
				//calling function of calculating high score
				calHighScore(score, playerNum);
				Sort(playerNum);
				show = 0;
				Newgame = 0;
				Reset(Newgame);
			}
			// On pressing on Play Button
			else if ((mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y > 10 && mousePressed.y < 86 && show)) {

				menuOptions = 1;
				show = 0;
				SameName = 1;
				Newgame = 1;
				Reset(Newgame);
				
			}
			//on pressing on options button
			else if (mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y>240 && mousePressed.y < 330 && show) {
				Newgame = 0;
				menuOptions = 3;
				show = 1;
				Reset(Newgame);
			}
			//on pressing credits button
			else if (mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y>370 && mousePressed.y < 455 && show) {
				Newgame = 0;
				menuOptions = 4;
				show = 0;
				Reset(Newgame);
			}
			//on pressing New game button
			else if (menuOptions == 3 && mousePressed.x > 230 && mousePressed.x < 540 && mousePressed.y>140 && mousePressed.y < 280 && show) {
				menuOptions = 1;
				show = 0;
				SameName = 0;
				playerNum++;
				Newgame = 1;
				Reset(Newgame);
				
				
			}
		}
		//End od Menu Displaying

		//Esc button 
		else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			
			menuOptions = 0;
			show = 1;
			Newgame = 0;
			Reset(Newgame);
			
		}


		//End of ESC button
		if (GameOver()) {
			Newgame = 0;
		}

		


		//Pipe and ground collsion
		if ((player.getGlobalBounds().intersects(pipe[detectpipe()].getGlobalBounds()) && pipe[detectpipe()].getPosition().x > player.getPosition().x)) {
			if (pipe[detectpipe()].getGlobalBounds().top > (player.getPosition().y + 42)) {
				canmoverigt = 1;
			}
			else { canmoverigt = 0; }

		}


		else { canmoverigt = 1; }


		if (player.getGlobalBounds().intersects(pipe[detectpipe()].getGlobalBounds()) && pipe[detectpipe()].getPosition().x < player.getPosition().x) {
			if (pipe[detectpipe()].getGlobalBounds().top > (player.getPosition().y + 42))
			{

				canmoveleft = 1;
			}
			else { canmoveleft = 0; }


		}
		else { canmoveleft = 1; }


		//end of pipe collision


		Event event;
		while (window.pollEvent(event)) {
			//Closing the game from X button
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//End of Closing the game from X button


			









		}
		//end of while event

		
		//ground movement
		if (ground[3].getPosition().y == 100 || ground[3].getPosition().y == 400) {
			groundMotion *= -1;
		}
		ground[3].move(0, groundMotion);
		ground[5].move(0, groundMotion);

		if (ground[4].getPosition().y == 100 || ground[4].getPosition().y == 400) {
			ground2Motion *= -1;
		}
		ground[4].move(0, -ground2Motion);

		//pipecoll



		//end of pipe coll


		//gravity and movement
		if (Keyboard::isKeyPressed(Keyboard::Right) && canmoverigt) {

			moveright();

		}

		else if (Keyboard::isKeyPressed(Keyboard::Left) && canmoveleft) {

			moveleft();
			

		}
		else { velocityx = 0; }
		if (player.getGlobalBounds().intersects(ground[detectground()].getGlobalBounds()) && ground[detectground()].getGlobalBounds().top >= (player.getPosition().y + 40)) {
			velocityy = 0;
			canjump = 1;
			if (Keyboard::isKeyPressed(Keyboard::X) && canjump) {

				velocityy = 6;
				canjump = 0;
			}

		}


		else if (player.getGlobalBounds().intersects(pipe[detectpipe()].getGlobalBounds()) && pipe[detectpipe()].getGlobalBounds().top >= (player.getPosition().y + 40)) {
			velocityy = 0;


			canjump = 1;
			if (Keyboard::isKeyPressed(Keyboard::X) && canjump) {

				velocityy = 6;
				canjump = 0;
			}


		}

		else {
			velocityy -= 0.1099;


		}



		animationindicator = animationindicator % 3;
		player.setTextureRect(IntRect(animationindicator * 16, 0, 16, 32));
		
		//end of gravity and movement
		

		
		MenuOptions(menuOptions);
		
		player.move(velocityx, -velocityy);
		camera.move(velocityx, 0);

		sky.move(velocityx, 0);
	}

	return 0;
}



















// moveright function



int moveright() {

	velocityx = 2;

	player.setScale(3, 3);
	if (framespeed.getElapsedTime().asSeconds() > 0.1) {
		animationindicator++;
		framespeed.restart();
	}

	return velocityx;
}










//end of move rightfunction


//moveleft function
void moveleft() {
	velocityx = -2;


	player.setScale(-3, 3);


	if (framespeed.getElapsedTime().asSeconds() > 0.1) {
		animationindicator++;
		framespeed.restart();
	}





}
//end of moveleft funtion



//jump function
void jump() {


	velocityy = 8;







}
//end of jumpfunction


int detectground() {
	int j = 0;
	for (size_t i = 0; i < 15; i++)
	{
		if (player.getPosition().x > ground[i].getGlobalBounds().left && (ground[i].getGlobalBounds().left + ground[i].getGlobalBounds().width) * i) {


			j = i;

		}
	}

	return j;

}
int detectpipe() {
	int m = 0;
	for (size_t i = 0; i < 3; i++)
	{
		if (player.getGlobalBounds().intersects(pipe[i].getGlobalBounds())) {

			m = i;
		}

	}

	return m;
}


//Seting Struct Order
void structOrder() {
	for (int i = 0; i < num; i++) {
		hs[i].playerOrder = i + 1;
		hs[i].HighScore = 0;
	}

}

//Menu function

void MenuOptions(int n) {
	window.clear();
	if (menuOptions == 0) {
		window.draw(menu);
	}
	else if (menuOptions == 1){

		window.setView(camera);

		window.draw(sky);

		// Enemy displaying
		if (marioal)
			window.draw(player);
		if (enemyal)
			window.draw(enemy);


		for (int i = 0; i < 10; i++) {
			window.draw(cloudi[i]);
		}
		window.draw(player);


		for (size_t i = 0; i < 15; i++)
		{
			window.draw(ground[i]);
		}
		for (size_t i = 0; i < 3; i++)
		{
			window.draw(pipe[i]);
		}
		
	}
	else if (menuOptions == 2) {
		window.draw(highScore);
		
		DiplayHighScore(playerNum);
		



	}
	else if (menuOptions == 3) {
		window.draw(option);
		window.draw(newGame);
		if (Fullmessage(playerNum, num)) {
			window.draw(Message);
		}
		


	}
	else if (menuOptions == 4) {
		window.draw(credit);
		window.draw(text);

	}




	window.display();

}
//End of Menu displaying function



//high score displaying function

void DiplayHighScore(int numplayer) {

	for (int i = 0; i < numplayer; i++) {
		//High score Data displaying
		Data.setFont(font);
		Data.setFillColor(sf::Color(0, 0, 0, 180));
		Data.setPosition(200, 18 + i * 40);
		Data.setCharacterSize(32);
		Scores.setFont(font);
		Scores.setFillColor(sf::Color(0, 0, 0, 200));
		Scores.setPosition(500, 18 + i * 40);
		Scores.setCharacterSize(32);
		Data.setString("Player " + to_string(hs[i].playerOrder));
		Scores.setString("\t\t" + to_string(hs[i].HighScore) + "\n");
		window.draw(Data);
		window.draw(Scores);
		//End of High score Data displaying

	}
}

// high score calculation function
//local val score
void calHighScore(int score, int currentplayer) {
	hs[currentplayer - 1].HighScore = score;
	if (score > hs[currentplayer - 1].HighScore) {
		hs[currentplayer - 1].HighScore = score;
		
	}

}

	



//Swap function

void Swap(int& n1, int& n2,int& n3,int& n4) {
	int temp;
	temp = n1;
	n1 = n2;
	n2 = temp;
	//swap player numbers
	int tempn;
	tempn = n3;
	n3 = n4;
	n4 = tempn;
	
}


//Sorting Function
void Sort(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 1 + i; j < n; j++) {
			if (hs[i].HighScore < hs[j].HighScore) {

				Swap(hs[i].HighScore, hs[j].HighScore,hs[i].playerOrder,hs[j].playerOrder);
			}
		}
	}
}


//Reset function
void Reset(bool New) {
	if (New) {
		score = 0;
		player.setPosition(400, -11);
		player.setScale(3, 3);
		sky.setPosition(0, 0);
		enemy.setPosition(580, 380);
		enemyal = 1;
		marioal = 1;
		camera.setCenter(player.getPosition().x, player.getPosition().y + 250);
		window.setView(camera);

	}
	else {
		camera.setCenter(400, 240);
		window.setView(camera);
		
	}
}

//function of Displaying gameover data 
bool GameOver() {
	window.clear();
	if (!PlayerCase || !marioal) {
		
		window.draw(sky);
		window.draw(gameOver);
		return true;
		
	}
	else {
		return false;
	}
	window.display();
}
//function to display that number of players exceed the limit
bool Fullmessage(int n,int limit) {
	if (n>=limit && menuOptions==3) {
		
		Message.setFont(font);
		Message.setFillColor(sf::Color(0, 0, 0, 180));
		Message.setPosition(150, 90);
		Message.setCharacterSize(32);
		Message.setString("Number of Players Exceeded The Limit !!!!");
		show = 0;
		
		return true;
	}
	else {
		return false;
	}
}