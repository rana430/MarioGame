#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

struct PlayerHighScore {

	string playername;
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
int playerNum = 0;
int score = 0;
bool canjump = 1;
bool canmoverigt = 1;
bool canmoveleft = 1;
bool space = 0;
int pos;
bool show = 1;
float velocityy = 0;
int animationindicator = 0;
float velocityx = 0;
Clock framespeed;
//functions
int moveright();
void moveleft();
void jump();
int detectground();
int detectpipe();
int calHighScore(int);
void DiplayHighScore(int);
void menuOption(int);
//end of functions
Texture skytx;
Sprite sky;
Texture mario;
Sprite player;
Texture groundtex;
Sprite ground[8];
Texture ground2;
Texture pipetex;
Sprite pipe[3];
Texture cloudtx;
Sprite	cloudi[10];
Sprite menu;
Texture Menu;
Sprite highScore;
Texture HighScore;
Sprite option;
Texture Option;
Sprite credit;
Texture Credits;
Text text;
Text Data;//text of high score
Font font;


View camera(FloatRect(0, 0, 800, 485));
sf::RenderWindow window(sf::VideoMode(800, 485), "Super Mario!!");




int main() {
	//Calculating high score
	cout << "Enter Player Name :\n";
	cin >> hs[0].playername;

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
	text.setString("CREDITS !!\n\n\nMoaaz \nRana \nAliaa \nAhmed \nZeyad \nNour \nMohamed");
	text.setFillColor(sf::Color(150, 150, 50, 230));

	text.setPosition(350, 10);
	text.setCharacterSize(32);

	//Credits Wallpaper
	Credits.loadFromFile("sky2.png");
	credit.setTexture(Credits);
	credit.setPosition(0, 0);
	credit.setScale(0.5, 0.5);





	//highscore menu for testing
	HighScore.loadFromFile("highscore.png");
	highScore.setTexture(HighScore);
	highScore.setPosition(0, 0);
	//End of Testing

	//options menu for testing
	Option.loadFromFile("option-menu.jpg");
	option.setTexture(Option);
	option.setPosition(0, 0);
	//End of Testing


	//sky
	skytx.loadFromFile("sky2.png");
	sky.setTexture(skytx);
	sky.setScale(10, 8);
	//end of sky

	//ground



	groundtex.loadFromFile("ground.png");
	ground2.loadFromFile("ground2.png");



	for (int i = 0; i < 3; i++) {

		ground[i].setTexture(groundtex);

		ground[i].setScale(0.4, 0.6);
		ground[i].setPosition(i * ground[i].getGlobalBounds().width, 410);

	}

	ground[3].setTexture(ground2);
	ground[3].setScale(0.3, 0.4);

	ground[3].setPosition(2512, 260);

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
	sf::RenderWindow window(sf::VideoMode(800, 485), "Super Mario!!");
	window.setFramerateLimit(120);




	camera.setCenter(player.getPosition().x, player.getPosition().y + 250);
	window.setView(camera);

	while (window.isOpen())
	{







		//Menu displaying

		if (Mouse::isButtonPressed(Mouse::Left)) {


			Vector2i mousePressed = Mouse::getPosition(window);//variable for determine the position of the mouse in the window
			//when press on high score
			if (mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y>120 && mousePressed.y < 205 && show) {

				menuOptions = 2;
				show = 0;
			}
			// On pressing on Play Button
			else if (mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y > 10 && mousePressed.y < 86 && show) {


				menuOptions = 1;
				show = 0;

			}
			//on pressing on options button
			else if (mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y>240 && mousePressed.y < 330 && show) {

				menuOptions = 3;
				show = 0;
			}
			//on pressing credits button
			else if (mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y>370 && mousePressed.y < 455) {

				menuOptions = 4;
				show = 0;
			}
		}
		//End od Menu Displaying





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


		else if (player.getGlobalBounds().intersects(pipe[detectpipe()].getGlobalBounds()) && pipe[detectpipe()].getGlobalBounds().top >= (player.getPosition().y + 42)) {
			velocityy = 0;


			canjump = 1;
			if (Keyboard::isKeyPressed(Keyboard::X) && canjump) {

				velocityy = 6;
				canjump = 0;
			}


		}

		else {
			velocityy -= 0.1;


		}



		animationindicator = animationindicator % 3;
		player.setTextureRect(IntRect(animationindicator * 16, 0, 16, 32));

		//end of gravity and movement
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
			window.draw(player);


			for (size_t i = 0; i < 3; i++)
			{
				window.draw(ground[i]);
			}
			window.draw(ground[3]);
			for (size_t i = 0; i < 3; i++)
			{
				window.draw(pipe[i]);
			}
		}
		else if (menuOptions == 2) {
			window.draw(highScore);
		}
		
		else if (menuOptions == 3) {
			window.draw(option);
		}
		else if (menuOptions == 4) {
			window.draw(text);
		}


		window.display();

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
	for (size_t i = 0; i < 4; i++)
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
void menuOption(int flag) {

	if (flag == 0) {
		window.draw(menu);
	}
	else if (flag == 1) {
		window.setView(camera);

		window.draw(sky);
		for (int i = 0; i < 10; i++) {
			window.draw(cloudi[i]);
		}
		window.draw(player);


		for (size_t i = 0; i < 3; i++)
		{
			window.draw(ground[i]);
		}
		window.draw(ground[3]);
		for (size_t i = 0; i < 3; i++)
		{
			window.draw(pipe[i]);
		}
	}
	else if (flag == 2) {
		window.draw(highScore);
	}

	else if (flag == 3) {
		window.draw(option);
	}
	else if (flag == 4) {
		window.draw(credit);
		window.draw(text);
	}

}


// high score calculation function
//local val score
int calHighScore(int score, int currentplayer) {
	hs[currentplayer].HighScore = score;
	while (SameName) {
		if (score > hs[currentplayer].HighScore) {

			hs[currentplayer].HighScore = score;
		}
	}
}
//Displaying high score
void DiplayHighScore(int numPlayer) {
	Data.setFont(font);
	Data.setFillColor(sf::Color(150, 150, 50, 230));
	Data.setPosition(350, 10);
	Data.setCharacterSize(32);
	for (int i = 0; i < numPlayer; i++) {
		Data.setString(hs[i].playername + "\t" + to_string(hs[i].HighScore)+"\n");
		window.draw(Data);
	}
}
//Swap function

