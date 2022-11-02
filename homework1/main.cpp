#include "ballThing.h"

/*
	Ниже происходит задание начальных координат шаров
*/
const double X_POS_FIRST = 0;
const double Y_POS_FIRST = 1;
const double X_POS_SECOND = 0.05;
const double Y_POS_SECOND = 1.003;

/*
	Константы, отвечающие за варианты меню
*/
const unsigned PUSH = 1;
const unsigned FLY = 2;
const unsigned POS = 3;
const unsigned SPEED = 4;
const unsigned STAT = 5;
const unsigned EXIT = 6;
const unsigned FIRST = 1;
const unsigned SECOND = 2;

void ballSimulationsMenu();

void choiceMenu() {
	std::cout << "Choose one of the options:\n \
		1. Push the ball at an angle to the horizon.\n \
		2. Calculate the flight of the ball in time t.\n \
		3. Get the current position of the ball.\n \
		4. Get the current speed of the ball.\n \
		5. Display detailed information about the ball.Its position, speedand flight time.\n \
		6. Exit" << std::endl;
}

int main() {
	ballSimulationsMenu();

	return 0;
}

void ballSimulationsMenu() {
	unsigned choiceOption;
	unsigned choiceBall;

	std::cout << "The location of both balls is already set" << std::endl;
	Ball first = Ball(X_POS_FIRST, Y_POS_FIRST);
	Ball second = Ball(X_POS_SECOND, Y_POS_SECOND);

	while (true) {
		std::cin.exceptions(std::istream::failbit | std::istream::badbit);
		try
		{
			choiceMenu();
			std::cin >> choiceOption;
			std::cout << "Choose which ball you want to work with:\n \
						1. First\n \
						2. Second" << std::endl;
			std::cin >> choiceBall;

			switch (choiceOption)
			{
			case PUSH: {
				if (choiceBall != FIRST && choiceBall != SECOND) {
					break;
				}

				std::cout << "Enter at what angle(in radians) you want to throw the ball and its speed" << std::endl;
				double alpha, velocity;
				std::cin >> alpha >> velocity;
				choiceBall == FIRST ? first.push(alpha, velocity) : second.push(alpha, velocity);
				break;
			}

			case FLY: {
				if (choiceBall != FIRST && choiceBall != SECOND) {
					break;
				}

				std::cout << "Enter the flight time for which you want to calculate" << std::endl;
				double time;
				std::cin >> time;
				choiceBall == FIRST ? first.fly(time, second) : second.fly(time, second);
				break;
			}

			case POS: {
				if (choiceBall != FIRST && choiceBall != SECOND) {
					break;
				}

				Point pos = Point();
				choiceBall == FIRST ? pos = first.getPosition() : pos = second.getPosition();
				std::cout << pos;
				break;
			}

			case SPEED: {
				if (choiceBall != FIRST && choiceBall != SECOND) {
					break;
				}

				Velocity speed = Velocity();
				choiceBall == FIRST ? speed = first.getVelocity() : speed = second.getVelocity();
				std::cout << speed;
				break;
			}

			case STAT: {
				if (choiceBall != FIRST && choiceBall != SECOND) {
					break;
				}

				Stats stats = Stats();
				choiceBall == FIRST ? stats = first.getStats() : stats = second.getStats();
				std::cout << stats;
				break;
			}

			case EXIT:
				break;

			default:
				break;
			}

			if (choiceOption == EXIT) {
				break;
			}
		}
		catch (std::istream::failure e)
		{
			std::cout << "Failed to enter data" << std::endl;
			std::cin.clear(); // на случай, если предыдущий ввод завершился с ошибкой
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

	}

}