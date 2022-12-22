#include <iostream>
#include <string>


class Plane {

private:
	std::string model;
	int power = 0;
	bool condition = false;

	void TurnOnEngine() {
		condition = true;
	}
	void TurnOffEngine() {
		condition = false;
	}
public:
	void SetPower(int val) {
		power = val;
	}
	void SetModel(std::string val) {
		model = val;
	}
	void Move(int val) {
		TurnOnEngine();
		power = val;
		std::cout << "Engine On" << std::endl;
	}
	void MoveStop() {
		TurnOffEngine();
		power = 0;
		std::cout << "Engine Off" << std::endl;
	}
	bool GetCondition() {
		return condition;
	}
};


class PassengerPlane : Plane {
private:
	int seats = 0;
public:
	void SetSeats(int val) {
		seats = val;
	}
};


class Fighter : Plane {

	friend void Disarm(Fighter t1);

private:
	int ammo = 0;
public:
	virtual void Shooting() {
		if (ammo > 0) ammo--;

	}
	void SetAmmo(int val) {
		ammo = val;
	}

};


class HeavyFighter : Fighter {

	friend void Disarm(Fighter t1);

private:
	int ammo = 0;
	int rockets = 0;
public:
	void Shooting() override {
		if (ammo > 0) ammo--;
		if (rockets > 0) rockets--;
	}
	void SetAmmo(int val) {
		ammo = val;
	}
	void SetRockets(int val) {
		rockets = val;
	}

};

class Bomber :Plane {

	friend void Disarm(Bomber t2);

private:
	int bombs = 0;
public:
	void SetBombs(int val) {
		bombs = val;
	}
};

void Disarm(Fighter t1) {
	t1.ammo = 0;
}
void Disarm(Bomber t1) {
	t1.bombs = 0;
}



int main() {
}


