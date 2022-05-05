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
bool alive = 1;
bool show = 1;//bool to check if menu is displayed or not
int pos;
int playerNum = 1;//number of palyers played the game
int score = 0;
int animationindicator = 0, plantanimation = 0, coinanimation = 0;
int goombaAnimation = 0;
int life = 4;
int scores = 0;
float velocityy = 0;
float velocityx = 0;
float groundMotion = 1, ground2Motion = 1, goombaMotion = 0.4, plantmotion = 0.5, coinmotion = 1, coin2motion = 1;
Clock framespeed;
//functions
int moveright();
void moveleft();
void jump();
void coin_animation();
int detectground();
int detectpipe();
void calHighScore(int, int);
void DiplayHighScore(int);//Displaying highscores function
void structOrder();//Setting struct order for each player
void MenuOptions(int);
void read();
void coincollision();
void gamend();
void coin_motion();
//end of functions
Texture skytx;
Sprite sky;
Texture mario;
Sprite player;
Texture planttx;
Sprite plant[7];
Texture groundtex;
Sprite ground[15];
Texture ground2;
Texture pipetex;
Sprite pipe[3];
Texture coinx;
Sprite coin[40];
Texture cloudtx;
Sprite	cloudi[10];
Texture goombaTx;
Sprite goomba;
Sprite menu;//Menu wallpaper
Texture Menu;
Sprite highScore;//highscore wallpaper
Texture HighScore;
Sprite option; //option Wallpaper
Texture Option;
Sprite credit;//Credits wallpaper
Texture Credits;
Sprite newGame;//New Game button 
Texture NewGame;
Text Data;//text of name of players
Text Scores;//test of scores of players
Text text;
Text gameend;
Font font;
Clock goombaClock, killg, plantclock, coinclock;
Clock endgame;

bool x = 0;
bool z = 0;


sf::RenderWindow window(sf::VideoMode(800, 485), "Super Mario!!");
View camera(FloatRect(0, 0, 800, 485));


int main() {
	life--;
	gameend.setCharacterSize(32);
	gameend.setFont(font);
	gameend.setString("you have" + to_string(life) + "remaining life");
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
	for (int i = 0; i < 11; i++) {

		coin[i].setPosition(100 * i + 1265, 350);

	}
	for (int i = 11; i < 15; i++) {
		coin[i].setPosition(2512 + ((i - 11) * 60), 120);
	}
	for (int i = 15; i < 19; i++) {
		coin[i].setPosition(2882 + ((i - 15) * 60), 120);
	}
	for (int i = 19; i < 23; i++) {
		coin[i].setPosition(3252 + ((i - 19) * 60), 120);
	}
	mario.loadFromFile("mario_spritesheet.png");

	player.setTexture(mario);
	player.setScale(3, 3);


	player.setPosition(400, -11);
	player.setTextureRect(IntRect(0, 0, 16, 32));
	player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);
	//end of mario

	//Menu Sprite declaring

	Menu.loadFromFile("menu.png");
	menu.setTexture(Menu);
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

	//High score Data displaying
	Data.setFont(font);
	Data.setFillColor(sf::Color(250, 0, 150, 200));
	Data.setPosition(350, 10);
	Data.setCharacterSize(32);
	Scores.setFont(font);
	Scores.setFillColor(sf::Color(250, 0, 150, 200));
	Scores.setPosition(500, 10);
	Scores.setCharacterSize(32);
	//End of High score Data displaying


	//Credits Wallpaper
	Credits.loadFromFile("Sky.png");
	credit.setTexture(Credits);
	credit.setPosition(0, 0);
	credit.setScale(1.25, 1.25);
	//End of credits

	//New Game button
	NewGame.loadFromFile("button-png-game-3.png");
	newGame.setTexture(NewGame);
	newGame.setPosition(230, 140);
	newGame.setScale(1.25, 1.25);

	//End of New Game


	//highscore menu for testing
	HighScore.loadFromFile("Sky.png");
	highScore.setTexture(HighScore);
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

	//plant

	planttx.loadFromFile("plant.png");
	for (size_t i = 0; i < 4; i++)
	{
		plant[i].setTexture(planttx);
		plant[i].setScale(0.3, 0.3);
		plant[i].setTextureRect(IntRect(0, 0, 300, 290));


	}

	for (size_t i = 0; i < 2; i++)
	{
		plant[i].setPosition(570 + (i * 70), 350);

	}

	plant[2].setPosition(790, 350);
	plant[3].setPosition(1280, 190);

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

	//enemies

	goombaTx.loadFromFile("pngkey.com-goomba-png-1876196.png");

	goomba.setTexture(goombaTx);
	goomba.setPosition(1000, 360);
	goomba.setScale(0.3, 0.3);
	goomba.setTextureRect(IntRect(0, 0, 160, 161));

	window.setFramerateLimit(120);

	read();



	camera.setCenter(player.getPosition().x, player.getPosition().y + 250);
	window.setView(camera);

	while (window.isOpen())
	{
		while (life) {

			coincollision();






			//Menu displaying
			Vector2i mousePressed = Mouse::getPosition(window);//variable for determine the position of the mouse in the window


			if (Mouse::isButtonPressed(Mouse::Left)) {

				//on pressing high scores button
				if ((mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y>120 && mousePressed.y < 205 && show)) {

					menuOptions = 2;
					calHighScore(score, playerNum);

					show = 0;
				}
				// On pressing on Play Button
				else if ((mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y > 10 && mousePressed.y < 86 && show)) {

					menuOptions = 1;
					show = 0;
					SameName = 1;
					for (int i = 0; i < 9; i++) {
						score++;
						cout << score << " ";
					}
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
					cout << playerNum << " " << SameName;

				}
			}
			//End od Menu Displaying

			//Esc button 
			else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				menuOptions = 0;
				show = 1;
			}


			//End of ESC button



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
			//coin animation
			coin_animation();
			//plant 
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


			// goomba movement 
			if (alive) {
				goomba.setTextureRect(IntRect(goombaAnimation * 210, 0, 165, 161));
				if (goomba.getGlobalBounds().intersects(pipe[1].getGlobalBounds()) || goomba.getGlobalBounds().intersects(pipe[2].getGlobalBounds())) {
					goombaMotion *= -1;
				}
				if (goombaClock.getElapsedTime().asSeconds() > 0.8) {
					goombaAnimation++;
					goombaClock.restart();
				}
				if (alive) {
					goombaAnimation %= 2;
					goomba.move(-goombaMotion, 0);
				}
			}

			//Killing enemies
			if (player.getGlobalBounds().intersects(goomba.getGlobalBounds())) {

				if (player.getPosition().y + 42 < goomba.getGlobalBounds().top) {
					alive = 0;
					goombaMotion = 0;
					goomba.setTextureRect(IntRect(420, 0, 165, 161));
					killg.restart();

				}
				else if (killg.getElapsedTime().asSeconds() > 0.15 && !alive) {

					goomba.setScale(0, 0);

				}
				else {
					sky.setPosition(-1200, -300);
					x = 1;
					endgame.restart();


				}

			}
			if (player.getPosition().y > 600 && !x) {


				sky.setPosition(-1200, -300);
				x = 1;
				endgame.restart();



			}

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

			//coin motion
			//coin_motion();

			//end of pipe coll


			//gravity and movement
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
			}
			//end of gravity and movement



			MenuOptions(menuOptions);

			player.move(velocityx, -velocityy);
			camera.move(velocityx, 0);
			text.move(velocityx, 0);

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
	for (int i = 0; i < 10; i++) {
		hs[i].playerOrder = i + 1;
		hs[i].HighScore = 0;
		cout << hs[i].playerOrder << " ";
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
		window.draw(goomba);
		for (size_t i = 0; i < 40; i++)
		{
			window.draw(coin[i]);
		}

		for (size_t i = 0; i < 4; i++)
		{
			window.draw(plant[i]);
		}

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


	}
	else if (menuOptions == 4) {
		window.draw(credit);
		window.draw(text);

	}
	if (x) {
		window.draw(sky);
		window.draw(gameend);
		camera.setCenter(gameend.getPosition().x, gameend.getPosition().y);

		z = 1;

	}
	if (z && endgame.getElapsedTime().asSeconds() > 3) {
		x = 0;
		z = 0;
		main();

	}



	window.display();

}


//high score displaying function

void DiplayHighScore(int numplayer) {

	for (int i = 0; i < numplayer; i++) {
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


	}
}

// high score calculation function
//local val score
void calHighScore(int score, int currentplayer) {
	hs[currentplayer - 1].HighScore = score;
	if (score > hs[currentplayer - 1].HighScore) {
		hs[currentplayer - 1].HighScore = score;
		cout << score << " ";
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

//Swap function










