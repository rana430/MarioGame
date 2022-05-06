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

bool a = 0;



bool SameName = 1;//if player doesnt change his name
bool canjump = 1;
bool canmoverigt = 1;
bool canmoveleft = 1;
bool space = 0;
bool alive = 1;
bool show = 1;//bool to check if menu is displayed or not
bool Newgame = 0;//bool to reset the game and player postion
bool Full = 0;//check number of players dont exceed 10 players
int pos;
int playerNum = 1;//number of palyers played the game
int animationindicator = 0, plantanimation = 0, coinanimation = 0;
int goombaAnimation = 0;
int life = 2;
const int num = 10;
int scores = 0;
float velocityy = 0;
float velocityx = 0;
float groundMotion = 1, ground2Motion = 1, goombaMotion = 0.45, goomba2Motion = 0.45, plantmotion = 0.5, coinmotion = 1, coin2motion = 1;
Clock framespeed;
//functions
int moveright();
void moveleft();
void jump();
void pipecollision();
void coin_animation();
int detectground();
int detectblock();
int detectpipe();
void calHighScore(int, int);
void DiplayHighScore(int);//Displaying highscores function
void structOrder();//Setting struct order for each player
void MenuOptions(int);
void read();
void coincollision();
void gamend();
void coin_motion();
void die();
void groundmovement();
void mouseclick();
void goombaa();
void planten();
void block_collision();
void movementandgravity();
void Swap(int& n1, int& n2, int& n3, int& n4);//function to swap high scores of two player and their orders
void Sort(int);//function to sort players decsending according to their highscores
bool Fullmessage(int, int);//function to display message when number of players exceed 10
int detectblock();
int detectblock2();
int detectblock3();
int detectblock33();
void gameIsover();
//end of functions
Texture blocktx;
Texture block3tx;
Sprite block[12];
Texture block2tx;
Sprite block2[12];
Texture block4tx;
Sprite block3[30];
Texture skytx;
Sprite sky;
Texture mario;
Sprite player;
Texture planttx;
Sprite plant[7];
Texture groundtex;
Sprite ground[16];
Texture ground2;
Texture pipetex;
Sprite pipe[7];
Texture coinx;
Sprite coin[40];
Texture cloudtx;
Sprite	cloudi[10];
Texture goombaTx;
Sprite goomba[3];
Sprite menu;//Menu wallpaper
Texture menutx;
Sprite highScore;//highscore wallpaper
Texture highScoretx;
Sprite option; //option Wallpaper
Texture optiontx;
Sprite credit;//Credits wallpaper
Texture Credittx;
Sprite newGame;//New Game button 
Texture newGametx;
Sprite gameOver;//Game Over Condition
Texture gameOvertx;
Text Data;//text of name of players
Text point;//test of scores of players
Text text;//Text to display the score of player
Text Message;//text to display the message that number of palyers exceed the limit
Text about;//text of credits
Text playerHpoints;//txt of high score of player when game over
Text gameovermessage;
Text gameend;
Font font;
Clock goombaClock, killg, plantclock, coinclock;
Clock endgame;

bool x = 0;
bool z = 0;

SoundBuffer buffer, mariojumpb, mariodieb;
Sound sound, mariojump, mariodie;
Music music;


sf::RenderWindow window(sf::VideoMode(800, 485), "Super Mario!!");
View camera(FloatRect(0, 0, 800, 485));


int main() {
	life--;
	gameend.setCharacterSize(32);
	gameend.setFont(font);
	gameend.setString("you have " + to_string(life) + " remaining life");
	gameend.setFillColor(Color(0, 0, 0, 180));

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
	coinx.loadFromFile("coins.png");
	for (int i = 0; i < 40; i++) {
		coin[i].setTexture(coinx);
		coin[i].setScale(1.1, 1.1);
		coin[i].setTextureRect(IntRect(0, 0, 36, 32));
		//coin[i].setPosition(100 * i +1260, 350);
	}
	for (int i = 0; i < 15; i++) {

		coin[i].setPosition(100 * i + 1765, 350);

	}
	for (int i = 15; i < 19; i++) {
		coin[i].setPosition(3390 + ((i - 15) * 60), 120);
	}
	for (int i = 19; i < 23; i++) {
		coin[i].setPosition(3760 + ((i - 19) * 60), 120);
	}
	for (int i = 23; i < 27; i++) {
		coin[i].setPosition(4130 + ((i - 23) * 60), 120);
	}
	mario.loadFromFile("mario_spritesheet.png");

	player.setTexture(mario);
	player.setScale(3, 3);


	player.setPosition(400, -11);
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


	about.setFont(font);
	about.setString("CREDITS !!\n\n\n  Ahmed \n  Rana \n  Aliaa \n  Moaaz \n  Zeyad \n  Nour \n  Mohamed");
	about.setFillColor(sf::Color(0, 0, 0, 180));

	about.setPosition(350, 10);
	about.setCharacterSize(32);

	//End Of Text
	
	//high score board data
	Data.setFont(font);
	Data.setFillColor(sf::Color(0, 0, 0, 180));
	Data.setPosition(200, 18);
	Data.setCharacterSize(32);
	point.setFont(font);
	point.setFillColor(sf::Color(0, 0, 0, 200));
	point.setPosition(500, 18);
	point.setCharacterSize(32);
	
	//End of high score board
	
	//high score of player when gameover

	playerHpoints.setFont(font);
	playerHpoints.setFillColor(sf::Color(0, 0, 0, 180));
	playerHpoints.setString("High Score: " + to_string(hs[playerNum - 1].HighScore));
	playerHpoints.setCharacterSize(32);

	//End if high score
	//Game Over 
	gameOvertx.loadFromFile("gameOver.png");
	gameOver.setTexture(gameOvertx);
	gameOver.setPosition(200, 50);
	gameOver.setScale(1.25, 1.5);


	//End Of Game Over


	//Game over message

	playerHpoints.setFont(font);
	playerHpoints.setFillColor(sf::Color(0, 0, 0, 180));
	playerHpoints.setString("Score: " + to_string(scores));
	playerHpoints.setCharacterSize(32);
	
	//ENd of game over message

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
	optiontx.loadFromFile("Sky.png");
	option.setTexture(optiontx);
	option.setPosition(0, 0);
	//End of Testing


	//sky
	skytx.loadFromFile("sky.png");
	sky.setTexture(skytx);
	sky.setScale(10, 8);
	//end of sky

	// block
	blocktx.loadFromFile("qblock.png");
	block3tx.loadFromFile("blockN.png");
	for (int i = 0; i < 12; i++) {
		block[i].setTexture(blocktx);
		block[0].setPosition(460, 230);
		block[i].setScale(0.11, 0.11);
	}
	for (int i = 1; i < 3; i++) {
		block[i].setPosition(650 + ((i - 1) * 100), 230);
	}
	for (int i = 3; i < 5; i++) {
		block[i].setPosition(625 + ((i - 3) * 150), 80);
	}
	for (int i = 5; i < 8; i++) {
		block[i].setPosition(6300 + (i - 5) * 50, 80);
	}
	block2tx.loadFromFile("block.png");
	for (int i = 0; i < 12; i++) {
		block2[i].setTexture(block2tx);
		block2[i].setScale(0.11, 0.11);
	}
	for (int i = 0; i < 3; i++) {
		block2[i].setPosition(600 + (i * 100), 230);
	}
	for (int i = 3; i < 10; i++) {
		block2[i].setPosition(6200 + (i - 3) * 50, 230);
	}

	block4tx.loadFromFile("dblock.png");
	for (int i = 0; i < 30; i++) {
		block3[i].setTexture(block4tx);
		block3[i].setScale(0.3, 0.3);
	}
	for (int i = 0; i < 5; i++) {
		block3[i].setPosition(6710 + (i * 44), 362);
	}
	for (int i = 5; i < 9; i++) {
		block3[i].setPosition(6754 + (i - 5) * 44, 314);
	}
	for (int i = 9; i < 12; i++) {
		block3[i].setPosition(6798 + (i - 9) * 44, 266);
	}
	for (int i = 12; i < 14; i++) {
		block3[i].setPosition(6842 + (i - 12) * 44, 218);
	}
	block3[14].setPosition(6886, 170);
	//plant

	planttx.loadFromFile("plant.png");
	for (size_t i = 0; i < 7; i++)
	{
		plant[i].setTexture(planttx);
		plant[i].setScale(0.3, 0.3);
		plant[i].setTextureRect(IntRect(0, 0, 300, 290));


	}

	for (size_t i = 0; i < 2; i++)
	{
		plant[i].setPosition(1070 + (i * 70), 350);

	}

	plant[2].setPosition(1290, 350);
	plant[3].setPosition(1780, 190);
	plant[4].setPosition(4610, 350);
	for (size_t i = 5; i < 7; i++)
	{
		plant[i].setPosition(4910 + ((i - 5) * 1000), 190);
	}
	//ground



	groundtex.loadFromFile("ground.png");
	ground2.loadFromFile("ground2.png");



	for (int i = 0; i < 4; i++) {

		ground[i].setTexture(groundtex);

		ground[i].setScale(0.4, 0.6);
		ground[i].setPosition(i * ground[i].getGlobalBounds().width, 410);

	}
	for (int i = 4; i < 7; i++) {
		ground[i].setTexture(ground2);
		ground[i].setScale(0.3, 0.4);
		ground[i].setPosition(3012 + ((i - 3) * 370), 120);
		if (i == 5) {
			ground[i].setPosition(3012 + ((i - 3) * 370), 370);
		}
	}

	for (int i = 7; i < 10; i++) {

		ground[i].setTexture(groundtex);

		ground[i].setScale(0.4, 0.6);
		ground[i].setPosition(4520 + ((i - 7) * ground[i].getGlobalBounds().width), 410);

	}
	/*for (int i = 10; i < 13; i++) {
		ground[i].setScale(0.4, 0.6);
		ground[i].setPosition(6800 + (i - 10) * 500, 410);
	}
	*/

	//end of ground
	//pipe
	pipetex.loadFromFile("pipe.jpg");


	for (size_t i = 0; i < 7; i++)
	{
		pipe[i].setTexture(pipetex);
		pipe[i].setScale(1.4, 1.8);

	}
	for (size_t i = 0; i < 3; i++)
	{
		pipe[i].setPosition(i * 400 + 950, 270);

	}
	for (size_t i = 3; i < 5; i++)
	{
		pipe[i].setPosition(4880 + ((i - 3) * 1000), 270);
	}

	//end ofpipe

	//enemies

	goombaTx.loadFromFile("pngkey.com-goomba-png-1876196.png");
	for (int i = 0; i < 3; i++) {
		goomba[i].setTexture(goombaTx);
		goomba[i].setScale(0.3, 0.3);
		goomba[i].setTextureRect(IntRect(0, 0, 160, 161));
	}
	goomba[0].setPosition(1500, 360);
	for (int i = 1; i < 3; i++) {
		goomba[i].setPosition(5015 + (i - 1) * 800, 360);
	}
	window.setFramerateLimit(120);
	//sound

	buffer.loadFromFile("coin.ogg");
	mariodieb.loadFromFile("lost.ogg");
	mariodie.setBuffer(mariodieb);

	sound.setBuffer(buffer);
	mariojumpb.loadFromFile("mariojump.ogg");
	mariojump.setBuffer(mariojumpb);
	music.openFromFile("overworld.ogg");
	music.play();
	music.setLoop(z);

	read();
	camera.setCenter(player.getPosition().x, player.getPosition().y + 250);
	window.setView(camera);
	

	while (window.isOpen())
	{
		while (life) {

			coincollision();

			//Menu displaying
			mouseclick();
			//End od Menu Displaying

			//Pipe and ground collsion

			pipecollision();

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
			//coin animation
			coin_animation();
			//plant 
			planten();

			// goomba 

			goombaa();

			//ground movement

			groundmovement();
			//block
			block_collision();

			//gravity and movement
			movementandgravity();

			//end of gravity and movement

			MenuOptions(menuOptions);

			player.move(velocityx, -velocityy);
			menu.move(velocityx, 0);
			camera.move(velocityx, 0);
			text.move(velocityx, 0);
			highScore.move(velocityx, 0);
			gameOver.move(velocityx, 0);
			about.move(velocityx, 0);
			Data.move(velocityx, 0);
			point.move(velocityx, 0);
			option.move(velocityx, 0);
			newGame.move(velocityx, 0);
			credit.move(velocityx, 0);
			Message.move(velocityx, 0);
			sky.move(velocityx, 0);
		}
	}
	return 0;
}



















// moveright function
void read() {
	text.setFont(font);
	text.setString("score:" + to_string(scores));
	text.setPosition(0, 0);
	text.setCharacterSize(30);
}
void coincollision() {
	for (size_t i = 0; i < 40; i++)
	{
		if (player.getGlobalBounds().intersects(coin[i].getGlobalBounds())) {
			scores++;
			coin[i].setScale(0, 0);
			text.setString("score:" + to_string(scores));


		}


	}
}



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
	for (size_t i = 0; i < 13; i++)
	{
		if (player.getPosition().x > ground[i].getGlobalBounds().left && (ground[i].getGlobalBounds().left + ground[i].getGlobalBounds().width) * i) {


			j = i;

		}
	}

	return j;

}
int detectpipe() {
	int m = 0;
	for (size_t i = 0; i < 7; i++)
	{
		if (player.getGlobalBounds().intersects(pipe[i].getGlobalBounds())) {

			m = i;
		}

	}

	return m;
}
//Seting Struct Order
void structOrder() {
	for (int i = 0; i < 10; i++) {
		hs[i].playerOrder = i + 1;
		

	}
}

//Menu function

void MenuOptions(int n) {
	window.clear();
	if (menuOptions == 0) {
		window.draw(menu);
	}
	else if (menuOptions == 1) {
		window.setView(camera);

		window.draw(sky);
		for (int i = 0; i < 10; i++) {
			window.draw(cloudi[i]);
		}
		window.draw(text);
		window.draw(player);
		for (size_t i = 0; i < 3; i++)
		{
			window.draw(goomba[i]);

		}
		for (size_t i = 0; i < 40; i++)
		{
			window.draw(coin[i]);
		}
		for (size_t i = 0; i < 10; i++)
		{
			window.draw(block2[i]);

			window.draw(block[i]);
		}
		for (size_t i = 0; i < 30; i++)
		{
			window.draw(block3[i]);
		}


		for (size_t i = 0; i < 7; i++)
		{
			window.draw(plant[i]);
		}

		for (size_t i = 0; i < 13; i++)
		{
			window.draw(ground[i]);
		}
		for (size_t i = 0; i < 5; i++)
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
		window.draw(about);

	}
	else if (menuOptions == 5) {
		gameIsover();
		window.draw(sky);
		window.draw(gameOver);
		window.draw(gameovermessage);
		window.draw(playerHpoints);
	}


	die();

	window.display();

}


//high score displaying function

void DiplayHighScore(int numplayer) {

	for (int i = 0; i < numplayer; i++) {
		Data.setFont(font);
		Data.setFillColor(sf::Color(0, 0, 0, 180));
		Data.setPosition(200, 18 + i * 40);
		Data.setCharacterSize(32);
		point.setFont(font);
		point.setFillColor(sf::Color(0, 0, 0, 200));
		point.setPosition(500, 18 + i * 40);
		point.setCharacterSize(32);
		Data.setString("Player " + to_string(hs[i].playerOrder));
		point.setString("\t\t" + to_string(hs[i].HighScore) + "\n");
		window.draw(Data);
		window.draw(point);


	}
}


void coin_animation() {
	for (int i = 0; i < 40; i++) {
		coin[i].setTextureRect(IntRect(36 * coinanimation, 0, 36, 32));
	}

	if (coinclock.getElapsedTime().asSeconds() > 0.15) {
		coinanimation++;
		coinclock.restart();
	}
	coinanimation %= 6;
}



void coin_motion() {

	for (int i = 11; i < 15; i++) {
		if (coin[i].getPosition().y == 100 || coin[i].getPosition().y == 400) {
			coinmotion *= -1;
		}
		coin[i].move(0, coinmotion);
	}
	for (int i = 19; i < 23; i++) {
		if (coin[i].getPosition().y == 100 || coin[i].getPosition().y == 400) {
			coinmotion *= -1;
		}
		coin[i].move(0, coinmotion);
	}


	for (int i = 15; i < 19; i++) {

		if (coin[i].getPosition().y == 100 || coin[i].getPosition().y == 400) {
			coin2motion *= -1;
		}
		coin[i].move(0, coin2motion);
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

void Swap(int& n1, int& n2, int& n3, int& n4) {
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

				Swap(hs[i].HighScore, hs[j].HighScore, hs[i].playerOrder, hs[j].playerOrder);
			}
		}
	}
}

//function to display that number of players exceed the limit
bool Fullmessage(int n, int limit) {
	if (n >= limit && menuOptions == 3) {

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



void pipecollision() {




	if ((player.getGlobalBounds().intersects(pipe[detectpipe()].getGlobalBounds()) && pipe[detectpipe()].getPosition().x > player.getPosition().x)) {
		if (pipe[detectpipe()].getGlobalBounds().top > (player.getPosition().y + 42)) {
			canmoverigt = 1;
		}
		else { canmoverigt = 0; }

	}
	else if ((player.getGlobalBounds().intersects(block[detectblock()].getGlobalBounds()) && block[detectblock()].getPosition().x > player.getPosition().x)) {

		if (block[detectblock()].getGlobalBounds().top > (player.getPosition().y + 42)) {
			canmoverigt = 1;
		}
		else { canmoverigt = 0; }
	}
	else if ((player.getGlobalBounds().intersects(block2[detectblock2()].getGlobalBounds()) && block2[detectblock2()].getPosition().x > player.getPosition().x)) {

		if (block2[detectblock2()].getGlobalBounds().top > (player.getPosition().y + 42)) {
			canmoverigt = 1;
		}
		else { canmoverigt = 0; }
	}
	else if (player.getGlobalBounds().intersects(block3[detectblock33()].getGlobalBounds())) {
		if (block3[detectblock3()].getGlobalBounds().top > (player.getPosition().y + 35)) {
			canmoverigt = 1;
		}
		else { canmoverigt = 0; }
		canmoverigt = 0;


	}

	else { canmoverigt = 1; }




	if (player.getGlobalBounds().intersects(pipe[detectpipe()].getGlobalBounds()) && pipe[detectpipe()].getPosition().x < player.getPosition().x) {
		if (pipe[detectpipe()].getGlobalBounds().top > (player.getPosition().y + 42))
		{

			canmoveleft = 1;
		}
		else { canmoveleft = 0; }


	}


	else if ((player.getGlobalBounds().intersects(block2[detectblock2()].getGlobalBounds()) && block2[detectblock2()].getPosition().x < player.getPosition().x)) {

		if (block2[detectblock2()].getGlobalBounds().top > (player.getPosition().y + 42)) {
			canmoveleft = 1;
		}
		else { canmoveleft = 0; }
	}






	else { canmoveleft = 1; }
}



void die() {




	if (x) {
		
		
		window.draw(sky);
		window.draw(gameend);
		camera.setCenter(gameend.getPosition().x, gameend.getPosition().y);
		z = 1;

	}
	if (z && endgame.getElapsedTime().asSeconds() > 2) {
		x = 0;
		z = 0;
		if (life - 1 == 0) {
			
			menuOptions = 5;
			endgame.restart();
			menuOptions = 0;
			show = 1;
			scores = 0;
			life = 4;

		}
		
		else {
			main();
		}
	}
}

void groundmovement() {



	if (ground[4].getPosition().y == 100 || ground[4].getPosition().y == 400) {
		groundMotion *= -1;
	}
	ground[4].move(0, groundMotion);
	ground[6].move(0, groundMotion);

	if (ground[5].getPosition().y == 100 || ground[5].getPosition().y == 400) {
		ground2Motion *= -1;
	}
	ground[5].move(0, -ground2Motion);



}

void mouseclick() {
	Vector2i mousePressed = Mouse::getPosition(window);//variable for determine the position of the mouse in the window


	if (Mouse::isButtonPressed(Mouse::Left)) {

		//on pressing high scores button
		if ((mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y>120 && mousePressed.y < 205 && show)) {

			menuOptions = 2;
			//calling function of calculating high score
			calHighScore(scores, playerNum);
			Sort(playerNum);

			show = 0;
		}
		// On pressing on Play Button
		else if (mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y > 10 && mousePressed.y < 86 && show) {
			
			menuOptions = 1;
			show = 0;
			SameName = 1;

		}
		//on pressing on options button
		else if (mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y>240 && mousePressed.y < 330 && show) {

			menuOptions = 3;
			show = 1;
		}
		//on pressing credits button
		else if (mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y>370 && mousePressed.y < 455 && show) {

			menuOptions = 4;
			show = 0;
		}
		//on pressing New game button
		else if (menuOptions == 3 && mousePressed.x > 230 && mousePressed.x < 540 && mousePressed.y>140 && mousePressed.y < 280 && show) {
			menuOptions = 1;
			show = 0;
			SameName = 0;
			playerNum++;
			scores = 0;
			life = 4;
			sky.setPosition(0, 0);
			main();
			
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		menuOptions = 0;
		show = 1;
		
		
	}


}

void goombaa() {
	for (int i = 0; i < 3; i++) {
		if (alive) {
			goomba[i].setTextureRect(IntRect(goombaAnimation * 210, 0, 165, 161));

			if (goomba[0].getGlobalBounds().intersects(pipe[1].getGlobalBounds()) || goomba[0].getGlobalBounds().intersects(pipe[2].getGlobalBounds())) {
				goombaMotion *= -1;
			}
			if (goomba[1].getGlobalBounds().intersects(pipe[3].getGlobalBounds()) || goomba[1].getGlobalBounds().intersects(goomba[2].getGlobalBounds())) {
				goomba2Motion *= -1;
			}
			if (goombaClock.getElapsedTime().asSeconds() > 0.8) {
				goombaAnimation++;
				goombaClock.restart();
			}
			if (alive) {
				goombaAnimation %= 2;
				goomba[0].move(-goombaMotion, 0);
				goomba[1].move(-goomba2Motion, 0);
				goomba[2].move(goomba2Motion, 0);
			}

		}


		if (player.getGlobalBounds().intersects(goomba[i].getGlobalBounds()) && alive) {

			if (player.getPosition().y + 40 < goomba[i].getGlobalBounds().top) {
				alive = 0;
				goombaMotion = 0;
				goomba[i].setTextureRect(IntRect(420, 0, 165, 161));
				killg.restart();
				a = 1;

			}
			else {
				sky.setPosition(-1200, -300);
				x = 1;


				endgame.restart();


			}




		}
		if (killg.getElapsedTime().asSeconds() > 0.15 && a) {

			goomba[i].setScale(0, 0);
			alive = 1;
			a = 0;
			goombaMotion = 1;
		}
		if (player.getPosition().y > 600 && !x) {


			sky.setPosition(-1200, -300);
			x = 1;
			endgame.restart();



		}
	}



}
void planten() {



	for (size_t i = 0; i < 7; i++)
	{

		plant[i].setTextureRect(IntRect((plantanimation * 300) + 32, 0, 220, 280));

		if (player.getGlobalBounds().intersects(plant[i].getGlobalBounds())) {





			sky.setPosition(-1200, -300);
			x = 1;
			endgame.restart();
		}

	}
	if (plantclock.getElapsedTime().asSeconds() > 0.2)
	{
		plantanimation++;
		plantclock.restart();
	}
	plantanimation %= 2;

	if (plant[3].getPosition().y == 190 || plant[3].getPosition().y == 340) {

		plantmotion *= -1;

	}

	plant[3].move(0, -plantmotion);
	for (size_t i = 5; i < 7; i++)
	{
		plant[i].move(0, -plantmotion);

	}
	for (size_t i = 5; i < 7; i++)
	{
		if (plant[i].getPosition().y < 190) {


			plantmotion *= -1;
		}

	}

}


void movementandgravity() {
	if (!x) {
		if (Keyboard::isKeyPressed(Keyboard::Right) && canmoverigt) {

			moveright();

		}

		else if (Keyboard::isKeyPressed(Keyboard::Left) && canmoveleft) {

			moveleft();


		}
		else { velocityx = 0; }
		if (player.getGlobalBounds().intersects(ground[detectground()].getGlobalBounds()) && ground[detectground()].getGlobalBounds().top >= (player.getPosition().y + 32)) {
			velocityy = 0;
			player.setPosition(player.getPosition().x, ground[detectground()].getGlobalBounds().top - 48);
			canjump = 1;
			if (Keyboard::isKeyPressed(Keyboard::X) && canjump) {

				mariojump.play();
				velocityy = 6;
				canjump = 0;
			}

		}


		else if (player.getGlobalBounds().intersects(pipe[detectpipe()].getGlobalBounds()) && pipe[detectpipe()].getGlobalBounds().top >= (player.getPosition().y + 40)) {
			velocityy = 0;


			canjump = 1;
			if (Keyboard::isKeyPressed(Keyboard::X) && canjump) {
				mariojump.play();
				velocityy = 6;
				canjump = 0;
			}




		}
		else if (player.getGlobalBounds().intersects(block[detectblock()].getGlobalBounds()) && block[detectblock()].getGlobalBounds().top >= (player.getPosition().y + 40)) {
			velocityy = 0;


			canjump = 1;
			if (Keyboard::isKeyPressed(Keyboard::X) && canjump) {
				mariojump.play();
				velocityy = 6;
				canjump = 0;
			}




		}

		else if (player.getGlobalBounds().intersects(block2[detectblock2()].getGlobalBounds()) && block2[detectblock2()].getGlobalBounds().top >= (player.getPosition().y + 40)) {
			velocityy = 0;


			canjump = 1;
			if (Keyboard::isKeyPressed(Keyboard::X) && canjump) {
				mariojump.play();
				velocityy = 6;
				canjump = 0;
			}




		}
		else if (player.getGlobalBounds().intersects(block3[detectblock3()].getGlobalBounds()) && block3[detectblock3()].getGlobalBounds().top >= (player.getPosition().y + 40)) {
			velocityy = 0;


			canjump = 1;
			if (Keyboard::isKeyPressed(Keyboard::X) && canjump) {
				mariojump.play();
				velocityy = 6;
				canjump = 0;
			}




		}

		else {

			velocityy -= 0.1099;
		}



	}



	animationindicator = animationindicator % 3;
	player.setTextureRect(IntRect(animationindicator * 16, 0, 16, 32));

}

void block_collision() {
	for (int i = 0; i < 12; i++) {
		if (player.getGlobalBounds().intersects(block[i].getGlobalBounds()) && player.getPosition().y - 40 > block[i].getGlobalBounds().top + block[i].getGlobalBounds().height && player.getPosition().x > block[i].getGlobalBounds().left) {
			velocityy = 0;
			block[i].setTexture(block3tx);
			block[i].setScale(0.1, 0.1);
		}

		if (player.getGlobalBounds().intersects(block2[i].getGlobalBounds()) && player.getPosition().y - 42 > block2[i].getGlobalBounds().top + block2[i].getGlobalBounds().height && player.getPosition().x > block2[i].getGlobalBounds().left) {
			block2[i].setScale(0, 0);
			velocityy = 0;
		}

	}
}
int detectblock() {
	int m = 0;

	for (int i = 0; i < 12; i++) {
		if (player.getGlobalBounds().intersects(block[i].getGlobalBounds())) {

			m = i;
			return m;
		}


	}

}
int detectblock2() {

	int n = 0;
	for (int i = 0; i < 12; i++) {

		if (player.getGlobalBounds().intersects(block2[i].getGlobalBounds())) {


			n = i;
			return n;
		}

	}

}














int detectblock3() {
	int m = 0;
	int n = 0;
	for (int i = 0; i < 30; i++) {
		if (player.getGlobalBounds().intersects(block3[i].getGlobalBounds())) {

			m = i;
			return m;
		}
	}
}
int detectblock33() {
	int m = 0;
	int n = 0;
	for (int i = 0; i < 30; i++) {
		if (player.getGlobalBounds().intersects(block3[i].getGlobalBounds()) && player.getPosition().x + 22 <= block3[i].getGlobalBounds().left) {

			m = i;
			return m;
		}
	}
}

void gameIsover() {
	
	gameOver.setPosition(200, 50);
	gameovermessage.setPosition(230, 300);
	playerHpoints.setPosition(400, 300);
	sky.setPosition(0, 0);
	
}