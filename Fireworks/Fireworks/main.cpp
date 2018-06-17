#include "lib/slGraphics.h"

#include <time.h>
#include <math.h>
#include <vector>

const float gravity = 0.10f;
const float PI = 3.14159;
const float TWO_PI = PI * 2.0f;
const float HALF_PI = PI * 0.5f;

class Particle {
public:
	float x, y;
	float velX, velY;

	int color;

	// Time To Life
	int TTL;

	Particle(float nx, float ny, int ncolor) {
		x = nx;
		y = ny;
		color = ncolor;

		float vel = (rand() / RAND_MAX) * 5.0f + 1.0f;

		float ang = rand() % 360;

		ang = map(ang, 0, 360, 0, TWO_PI);

		velX = cos(ang) * vel;
		velY = sin(ang) * vel;

		TTL = rand() % 10 + 5;
	}

	bool update() {
		TTL--;

		if (TTL <= 0) 
			return false;

		velY += gravity;

		x += velX;
		y += velY;
		
		return true;
	}

	void render() {
		draw('o', (int)x, (int)y, color);
	}
};

class Firework {

public:
	float x, y;
	float velX, velY;

	int color;

	Firework() {
		x = rand() % (getWindowWidth()-8) + 4;
		y = getWindowHeight() + 1;
		velX = ((rand() % 100)*2.0f - 100.0f) / 100.0f;
		velY = -(rand() % 2 + 2);
	
		color = rand() % 16;
	}

	bool update() {
		velY += gravity;

		if (velY >= -0.5) 
			return false;

		x += velX;
		y += velY;
		
		return true;
	}

	void render() {
		draw('#', (int)x, (int)y, color);
	}
};


int main() {
	setWindowSize(160, 60);
	srand(time(NULL));

	vector<Firework> fireworks;
	vector<Particle> particles;

	float fps = 20.0f;

	while (true) {
		int start = clock();

		clearScreen();

		if (rand() % 100 < 20) {
			fireworks.push_back(Firework());
		}

		for (int i = 0; i < fireworks.size(); i++) {
			Firework *f = &fireworks[i];
			if (!f->update()) {
				// Explosion
				int total = rand() % 30 + 50;

				for (int j = 0; j < total; j++) {
					particles.push_back(Particle(f->x, f->y, f->color));
				}
				
				fireworks[i] = fireworks[fireworks.size()-1];
				fireworks.pop_back();
			}
			else {
				f->render();
			}
		}

		for (int i = 0; i < particles.size(); i++) {
			Particle *p = &particles[i];

			if (!p->update()) {
				particles[i] = particles[particles.size() - 1];
				particles.pop_back();
			}
			else {
				p->render();
			}
		}
		int stop = clock();

		float delay = (1000.0f / fps) - (stop - start);

		if(delay > 0)
			Sleep(delay);
	}


	system("pause");

	return 0;
}