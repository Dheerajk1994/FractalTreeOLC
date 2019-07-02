#define OLC_PGE_APPLICATION

#include <iostream>
#include "olcPixelGameEngine.h"
#include <math.h>

struct Branch {
	olc::Vector2 origin;
	olc::Vector2 end;

	Branch(){}

	Branch(olc::Vector2 _origin, olc::Vector2 _end) {
		origin = _origin;
		end = _end;
	}

};

class Application : public olc::PixelGameEngine {
private:
	float branchAngle = std::atan(1) * 4 / 4;
	float branchHeightRatio = 0.5f;
public:
	Application() 
	{
		sAppName = "Fractal Tree";
	}

	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::BLACK);
		if (GetKey(olc::Q).bHeld) {
			branchAngle -= 0.001;
		}
		else if (GetKey(olc::W).bHeld) {
			branchAngle += 0.001;
		}

		if (GetKey(olc::E).bHeld) {
			branchHeightRatio -= 0.001;
		}
		else if (GetKey(olc::R).bHeld) {
			branchHeightRatio += 0.001;
		}

		DrawBranch(olc::Vector2(ScreenWidth() / 2, ScreenHeight()), olc::Vector2(ScreenWidth() / 2, ScreenHeight()  - ScreenHeight() / 4), 12);
		return true;
	}
	
private:
	void DrawBranch(olc::Vector2 begin, olc::Vector2 end, float limit) {

		olc::Pixel p;
		p.r = 250 / limit * 0.1f;
		p.g = 250 / limit * 0.7f;
		p.b = 250 / limit;
		p.a = 250;

		DrawLine(begin.x, begin.y, end.x, end.y, p);

		if (limit > 0) {
			float dx = end.x - begin.x;
			float dy = end.y - begin.y;

			float distance = std::sqrt(dx * dx + dy * dy);
			float angle = std::atan2(dx, dy);

			float aX = end.x + std::sin(angle + branchAngle) * distance * branchHeightRatio;
			float aY = end.y + std::cos(angle + branchAngle) * distance * branchHeightRatio;
														 
			float bX = end.x + std::sin(angle - branchAngle) * distance * branchHeightRatio;
			float bY = end.y + std::cos(angle - branchAngle) * distance * branchHeightRatio;
			
			DrawBranch(end, olc::Vector2(aX, aY), limit - 1);
			DrawBranch(end, olc::Vector2(bX, bY), limit - 1);
		}
	}

	float NewX(olc::Vector2 begin, olc::Vector2 end, float angle) {
		return (((end.x - begin.x) * std::cos(angle)) - ((begin.y - end.y) * std::sin(angle) + begin.x));
	}

	float NewY(olc::Vector2 begin, olc::Vector2 end, float angle) {
		return (((begin.y - end.y) * std::cos(angle)) - ((end.x - begin.x) * std::sin(angle) + begin.y));
	}

};


int main(int argc, char* argv[]) {

	Application myApplication;

	if (myApplication.Construct(800, 800, 1, 1)) {
		myApplication.Start();
	}


	return 0;
}