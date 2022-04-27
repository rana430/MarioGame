#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int menuOptions = 0;/*
					0->to display menu in the begining of the game
					1-> to Start playing
					2->to Display High Score
					3->To do display options Menu
					4-> to dispaly credits Menu
					*/

bool canjump = 1;
bool canmoverigt = 1;
bool canmoveleft = 1;
bool space = 0;
int pos;
float velocityy = 0;
int animationindicator = 0;
float velocityY = 0;

//functions
void moveright();
void moveleft();
void jump();
int detectground();
int detectpipe();
//end of functions
Texture mario;
Sprite player;
Texture groundtex;
Sprite ground[4];
Texture ground2;
Texture pipetex;
Sprite pipe[3];
Sprite menu;
Texture Menu;
Sprite highScore;
Texture HighScore;
Sprite option;
Texture Option;
Sprite credit;
Texture Credits;





int main() {

	//mario

	mario.loadFromFile("mario_spritesheet.png");

	player.setTexture(mario);
	player.setScale(3, 3);


	player.setPosition(400, -10);
	player.setTextureRect(IntRect(0, 0, 16, 32));
	player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);
	//end of mario

	//Menu Sprite declaring

	Menu.loadFromFile("menu.png");
	menu.setTexture(Menu);
	menu.setPosition(0, 0);
	menu.setScale(1.25, 1.5);

	//End of Menu Sprite declaring

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
	

	//Font 
	Font font;
	font.loadFromFile("orange juice 2.0.ttf");

	//Text
	Text text;
	text.setFont(font);
	text.setString("CREDITS !!\n\n\n Moaaz \nRana \nAliaa \nAhmed \nZeyad \nNour \nMohamed");
	text.setFillColor(sf::Color(50, 255, 50, 230));

	text.setPosition(350, 10);
	text.setCharacterSize(32);

	//Credits Wallpaper
	/*Credits.loadFromFile("Credits wallpaper.png");
	credit.setTexture(Credits);
	credit.setPosition(0, 0);
	credit.setScale(0.5, 0.5);*/




	//ground



	groundtex.loadFromFile("ground.png");
	ground2.loadFromFile("ground2.png");



	for (int i = 0; i < 3; i++) {

		ground[i].setTexture(groundtex);

		ground[i].setScale(0.4, 0.6);
		ground[i].setPosition(i * ground[i].getGlobalBounds().width, 430);

	}

	ground[3].setTexture(ground2);
	ground[3].setScale(0.3, 0.4);

	ground[3].setPosition(2444, 250);

	//end of ground
	//pipe
	pipetex.loadFromFile("pipe.jpg");


	for (size_t i = 0; i < 3; i++)
	{
		pipe[i].setTexture(pipetex);
		pipe[i].setScale(1.4, 1.8);
		pipe[i].setPosition(i * 400 + 450, 320);

	}

	//end ofpipe
	sf::RenderWindow window(sf::VideoMode(800, 485), "Super Mario!!");



	View camera(FloatRect(0, 0, 800, 485));

	camera.setCenter(player.getPosition().x, player.getPosition().y + 250);
	window.setView(camera);

	while (window.isOpen())
	{

		
		
		



		//Menu displaying

		if (Mouse::isButtonPressed(Mouse::Left)) {


			Vector2i mousePressed = Mouse::getPosition(window);//variable for determine the position of the mouse in the window
			//when press on high score
			if (mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y>120 && mousePressed.y < 205) {

				menuOptions = 2;

			}
			// On pressing on Play Button
			else if (mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y > 10 && mousePressed.y < 86) {

				menuOptions = 1;

			}
			//on pressing on options button
			else if (mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y>240 && mousePressed.y < 330) {
				cout << mousePressed.x << " " << mousePressed.y << endl;
				menuOptions = 3;

			}
			//on pressing credits button
			else if (mousePressed.x > 23 && mousePressed.x < 300 && mousePressed.y>370 && mousePressed.y < 455) {
				cout << mousePressed.x << " " << mousePressed.y << endl;
				menuOptions = 4;
			}
		}
		//End od Menu Displaying




		if (space && player.getGlobalBounds().intersects(ground[detectground()].getGlobalBounds())) {
			player.setTextureRect(IntRect(0, 0, 16, 32));
			space = 0;
		}
		if (space && player.getGlobalBounds().intersects(pipe[detectpipe()].getGlobalBounds())) {


			player.setTextureRect(IntRect(0, 0, 16, 32));
			space = 0;
		}
		//Pipe collsion
		if ((player.getGlobalBounds().intersects(pipe[detectpipe()].getGlobalBounds()) && pipe[detectpipe()].getPosition().x > player.getPosition().x)) {
			if (pipe[detectpipe()].getGlobalBounds().top > (player.getPosition().y + 44)) {
				canmoverigt = 1;
			}
			else { canmoverigt = 0; }

		}
		else { canmoverigt = 1; }


		if (player.getGlobalBounds().intersects(pipe[detectpipe()].getGlobalBounds()) && pipe[detectpipe()].getPosition().x < player.getPosition().x) {
			if (pipe[detectpipe()].getGlobalBounds().top > (player.getPosition().y + 44))
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
			if (Keyboard::isKeyPressed(Keyboard::Right) && canmoverigt) {

				moveright();
				camera.move(5, 0);

			}
			if (Keyboard::isKeyPressed(Keyboard::Left) && canmoveleft) {


				moveleft();
				camera.move(-5, 0);

			}



			animationindicator = animationindicator % 3;
			player.setTextureRect(IntRect(animationindicator * 16, 0, 16, 32));






		}
		//end of while event

		//pipecoll



		//end of pipe coll


		//gravity 
		if (Keyboard::isKeyPressed(Keyboard::X) && canjump) {

			velocityy = 100;

		}
		else { velocityy = 0; }
		if (!player.getGlobalBounds().intersects(ground[detectground()].getGlobalBounds())) {

			if (player.getGlobalBounds().intersects(pipe[detectpipe()].getGlobalBounds())) {
				canjump = 1;
				if ((!player.getPosition().y + 48) == pipe[detectpipe()].getGlobalBounds().top) {

					velocityy -= 0.2;

					player.setTextureRect(IntRect(48, 0, 16, 32));
					space = 1;

				}
				else if (player.getPosition().y + 44 > pipe[detectpipe()].getGlobalBounds().top) {
					velocityy -= 0.2;
				}


			}


			else {

				velocityy -= 0.2;
				canjump = 0;
				player.setTextureRect(IntRect(48, 0, 16, 32));
				space = 1;
			}

		}
		else { canjump = 1; }




		//end of gravity
		window.clear();
		if (menuOptions == 0) {
			window.draw(menu);
		}
		else if (menuOptions == 1) {
			window.setView(camera);
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
			//window.draw(credit);
			window.draw(text);
		}


		window.display();

		player.move(0, -velocityy);

	}

	return 0;
}



















// moveright function



void moveright() {
	player.move(5, 0);

	animationindicator++;
	player.setScale(3, 3);










}
//end of move rightfunction


//moveleft function
void moveleft() {

	player.move(-5.f, 0.f);
	animationindicator++;
	player.setScale(-3, 3);









}
//end of moveleft funtion



//jump function
void jump() {


	int x = 0;
	player.move(0, 0.4);







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
