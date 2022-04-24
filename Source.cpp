

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int flag = 0;
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



int main() {

	//mario
	mario.loadFromFile("mario.png");

	player.setTexture(mario);
	player.setTextureRect(IntRect(0, 0, 16, 32));
	player.setPosition(400, 336);
	player.setScale(3, 3);
	//player.setOrigin(player.getGlobalBounds().left, 32);
	//end of mario




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
		pipe[i].setPosition(i * 400 + 450, 350);

	}

	//end ofpipe
	RenderWindow window(VideoMode(800, 485), "Test");



	View camera(FloatRect(0, 0, 800, 485));

	camera.setCenter(400, 250);
	window.setView(camera);

	while (window.isOpen())
	{
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
			if (pipe[detectpipe()].getGlobalBounds().top >= (player.getPosition().y + 95)) {
				canmoverigt = 1;
			}
			else { canmoverigt = 0; }

		}
		else { canmoverigt = 1; }


		if (player.getGlobalBounds().intersects(pipe[detectpipe()].getGlobalBounds()) && pipe[detectpipe()].getPosition().x < player.getPosition().x) {
			if (pipe[detectpipe()].getGlobalBounds().top >= (player.getPosition().y + 95)) {
				canmoveleft = 1;
			}
			else { canmoveleft = 0; }


		}
		else { canmoveleft = 1; }


		//end of pipe collision


		Event event;
		while (window.pollEvent(event)) {



			if (Keyboard::isKeyPressed(Keyboard::Right) && canmoverigt) {

				moveright();
				camera.move(5, 0);

			}
			if (Keyboard::isKeyPressed(Keyboard::Left) && canmoveleft) {


				moveleft();
				camera.move(-5, 0);

			}



			animationindicator = animationindicator % 3;







		}
		//end of while event

		//pipecoll



		//end of pipe coll


		//gravity 
		if (Keyboard::isKeyPressed(Keyboard::X) && canjump) {

			velocityy = 80;

		}
		else { velocityy = 0; }
		if (!player.getGlobalBounds().intersects(ground[detectground()].getGlobalBounds()) && !player.getGlobalBounds().intersects(pipe[detectpipe()].getGlobalBounds())) {
			velocityy -= 0.2;
			canjump = 0;
			player.setTextureRect(IntRect(48, 0, 16, 32));
			space = 1;
		}

		else
		{
			canjump = 1;

		}



		//end of gravity
		window.setView(camera);
		window.clear();
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

		window.display();

		player.move(0, -velocityy);

	}

	return 0;
}



















// moveright function



void moveright() {
	player.move(5, 0);

	player.setScale(3, 3);

	player.setTextureRect(IntRect(animationindicator * 16, 0, 16, 32));
	animationindicator++;






}
//end of move rightfunction


//moveleft function
void moveleft() {
	player.move(-5, 0);
	player.setScale(-3, 3);

	player.setTextureRect(IntRect(animationindicator * 16, 0, 16, 32));
	animationindicator++;






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