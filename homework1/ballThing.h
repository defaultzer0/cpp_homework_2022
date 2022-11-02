#pragma once
#include <math.h>
#include <sstream>
#include <iostream>

const double ACCELERATION_OF_GRAVITY = 9.8;

/*
	Расстояние, которое можно считать за соударение мячей
*/
const double EPSILON = 0.1;

struct Point {
	Point() : x_(0), y_(0) {}
	Point(double x, double y) : x_(x), y_(y) {}

	friend std::ostream& operator<<(std::ostream& os, Point& other);

	double x_{};
	double y_{};
};

struct Velocity {
	Velocity() : vx_(0), vy_(0) {}
	Velocity(double vx, double vy) : vx_(vx), vy_(vy) {}

	friend std::ostream& operator<<(std::ostream& os, Velocity& other);

	double vx_{};
	double vy_{};
};

struct Stats {
	Stats() : point_(0, 0), velocity_(0, 0), time_(0) {}
	Stats(Point point, Velocity velocity, double time) : point_(point), velocity_(velocity), time_(time) {}

	friend std::ostream& operator<<(std::ostream& os, Stats& other);

	Point point_{};
	Velocity velocity_{};
	double time_{};
};

class Ball {
public:
	Ball() {
		currentCoordinate_ = Point();
		currentSpeed_ = Velocity();
		currentFlightTime_ = 0;
	}

	Ball(double x, double y) {
		currentCoordinate_ = Point(x, y);
		currentSpeed_ = Velocity(0, 0);
		currentFlightTime_ = 0;
	}

	//friend std::istream& operator<<(std::istream* is, Ball& other);

	// Угол альфа считается в радианах
	void push(double alpha, double v) {
		currentSpeed_.vx_ = v * cos(alpha);
		currentSpeed_.vy_ = v * sin(alpha);
	}

	void fly(double t, Ball& other) {
		double tLeft = (-currentSpeed_.vy_ - sqrt(pow(currentSpeed_.vy_, 2) + 2 * ACCELERATION_OF_GRAVITY * currentCoordinate_.y_)) / (-ACCELERATION_OF_GRAVITY);
		double tNeed = 0;
		double epsX = fabs(currentCoordinate_.x_ - other.getPosition().x_);
		double epsY = fabs(currentCoordinate_.y_ - other.getPosition().y_);

		if (epsX < EPSILON && epsY < EPSILON) {
			currentSpeed_.vx_ = -currentSpeed_.vx_;
			other.push(asin(other.getVelocity().vy_ / -other.getVelocity().vx_), sqrt(pow(other.getVelocity().vx_, 2) + pow(other.getVelocity().vy_, 2)));
			
			currentCoordinate_.x_ = currentCoordinate_.x_ + currentSpeed_.vx_ * t;
			currentCoordinate_.y_ = currentCoordinate_.y_ + currentSpeed_.vy_ * t -
				ACCELERATION_OF_GRAVITY * pow(t, 2) / 2;
			currentSpeed_.vy_ = currentSpeed_.vy_ - ACCELERATION_OF_GRAVITY * t;
			currentFlightTime_ = t;

			return;
		}

		if (tLeft < t) {
			currentCoordinate_.x_ = currentCoordinate_.x_ + currentSpeed_.vx_ * (tLeft);
			currentCoordinate_.y_ = currentCoordinate_.y_ + currentSpeed_.vy_ * (tLeft) -
				ACCELERATION_OF_GRAVITY * pow((tLeft), 2) / 2;
			currentSpeed_.vy_ = currentSpeed_.vy_ - ACCELERATION_OF_GRAVITY * (tLeft);
			
			tNeed = t - tLeft;
			currentSpeed_.vy_ = -currentSpeed_.vy_;

			currentCoordinate_.x_ = currentCoordinate_.x_ + currentSpeed_.vx_ * (tNeed);
			currentCoordinate_.y_ = currentCoordinate_.y_ + currentSpeed_.vy_ * (tNeed)-
				ACCELERATION_OF_GRAVITY * pow((tNeed), 2) / 2;
			currentSpeed_.vy_ = currentSpeed_.vy_ - ACCELERATION_OF_GRAVITY * (tNeed);

			currentFlightTime_ = t;

			return;
		}

		if (tLeft < t && epsX < EPSILON && epsY < EPSILON) {
			currentSpeed_.vx_ = -currentSpeed_.vx_;
			other.push(asin(other.getVelocity().vy_ / -other.getVelocity().vx_), sqrt(pow(other.getVelocity().vx_, 2) + pow(other.getVelocity().vy_, 2)));
			
			currentCoordinate_.x_ = currentCoordinate_.x_ + currentSpeed_.vx_ * (tLeft);
			currentCoordinate_.y_ = currentCoordinate_.y_ + currentSpeed_.vy_ * (tLeft)-
				ACCELERATION_OF_GRAVITY * pow((tLeft), 2) / 2;
			currentSpeed_.vy_ = currentSpeed_.vy_ - ACCELERATION_OF_GRAVITY * (tLeft);

			tNeed = t - tLeft;
			currentSpeed_.vy_ = -currentSpeed_.vy_;

			currentCoordinate_.x_ = currentCoordinate_.x_ + currentSpeed_.vx_ * (tNeed);
			currentCoordinate_.y_ = currentCoordinate_.y_ + currentSpeed_.vy_ * (tNeed)-
				ACCELERATION_OF_GRAVITY * pow((tNeed), 2) / 2;
			currentSpeed_.vy_ = currentSpeed_.vy_ - ACCELERATION_OF_GRAVITY * (tNeed);

			currentFlightTime_ = t;

			return;
		}

		currentCoordinate_.x_ = currentCoordinate_.x_ + currentSpeed_.vx_ * t;
		currentCoordinate_.y_ = currentCoordinate_.y_ + currentSpeed_.vy_ * t -
			ACCELERATION_OF_GRAVITY * pow(t, 2) / 2;
		currentSpeed_.vy_ = currentSpeed_.vy_ - ACCELERATION_OF_GRAVITY * t;
		currentFlightTime_ = t;
	}

	Point getPosition() {
		return currentCoordinate_;
	}

	Velocity getVelocity() {
		return currentSpeed_;
	}

	Stats getStats() {
		return Stats(currentCoordinate_, currentSpeed_, currentFlightTime_);
	}

private:
	Point currentCoordinate_{};
	Velocity currentSpeed_{};
	double currentFlightTime_{};
};

std::ostream& operator<<(std::ostream& os, Stats& other) {
	os << "Current x position: " << other.point_.x_ << std::endl <<
		"Current y position: " << other.point_.y_ << std::endl <<
		"Current x-axis speed: " << other.velocity_.vx_ << std::endl <<
		"Current y-axis speed: " << other.velocity_.vy_ << std::endl <<
		"Current flight time: " << other.time_ << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, Point& other) {
	os << "x coordinate: " << other.x_ << std::endl <<
		"y coordinate: " << other.y_ << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, Velocity& other) {
	os << "vx: " << other.vx_ << std::endl <<
		"vy: " << other.vy_ << std::endl;
	return os;
}

/*std::istream& operator>>(std::istream& is, Ball& other) {
	double x;
	double y;
	double vx;
	double vy;
	double time;

	is.exceptions(std::istream::failbit | std::istream::badbit);
	try {
		std::cin >> x >> y >> vx >> vy >> time;
		Ball ball = Ball(x, y, vx, vy, time);
		other = ball;
	}
	catch (std::istream::failure error) {
		std::cout << "Failed to enter data" << std::endl;
		is.clear();
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return is;
}
*/
