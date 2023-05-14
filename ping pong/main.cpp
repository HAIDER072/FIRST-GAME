#include"raylib.h"
#include<stdio.h>

int main() {
	InitWindow(800, 600, "pong");
	SetWindowState(FLAG_VSYNC_HINT);
	struct Ball
	{
		float x, y;
		float speedx, speedy;
		float radius;
		void Draw() 
		{
			DrawCircle((int)x, (int)y, radius, YELLOW);
		}
	};
	struct paddle
	{
		float x, y;
		float speed;
		float width, height;

		Rectangle getrec()
		{
			return Rectangle{ x - width / 2, y - height / 2, 10, 100 };
		}


		void Draw()
		{
			DrawRectangleRec(getrec(), WHITE);
		}
	};

	Ball ball;
	ball.x= GetScreenWidth() / 2.0f;
	ball.y= GetScreenHeight() / 2.0f;
    ball.radius=5;
    ball.speedx = 300;
	ball.speedy = 300;

	paddle leftpaddle;
	leftpaddle.x = 50;
	leftpaddle.y = GetScreenHeight() / 2;
	leftpaddle.width = 10;
	leftpaddle.height = 100;
	leftpaddle.speed = 500;


	paddle rightpaddle;
	rightpaddle.x = GetScreenWidth() - 50;
	rightpaddle.y = GetScreenHeight() / 2;
	rightpaddle.width = 10;
	rightpaddle.height = 100;
	rightpaddle.speed = 500;

	const char* winnerText = nullptr;




	while (!WindowShouldClose())
	{

		ball.x += ball.speedx * GetFrameTime();
		ball.y += ball.speedy * GetFrameTime();
		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedy *= -1;
		}
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedy *= -1;
		}

		if (IsKeyDown(KEY_W))
		{
			leftpaddle.y -= leftpaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S))
		{
			leftpaddle.y += leftpaddle.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_UP))
		{
			rightpaddle.y -= rightpaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			rightpaddle.y += rightpaddle.speed * GetFrameTime();
		}

		if (CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,leftpaddle.getrec()))
		{
			if (ball.speedx < 0)
			{
				ball.speedx *= -1.1f;
				ball.speedy = (ball.y - leftpaddle.y) / (leftpaddle.height / 2) * ball.speedx;
			}
			
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, rightpaddle.getrec()))
		{
			if (ball.speedx > 0)
			{
				ball.speedx *= -1.1f;
				ball.speedy = (ball.y - rightpaddle.y) / (rightpaddle.height / 2) * -ball.speedx;
			}
		}

		if (ball.x < 0)
		{
			winnerText = "Right Player Wins!";
		}
		if (ball.x > GetScreenWidth())
		{
			winnerText = "Left Player Wins!";
		}



		if (winnerText && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedx = 300;
			ball.speedy = 300;
			winnerText = nullptr;
		}


		BeginDrawing();
			ClearBackground(BLACK);
			ball.Draw();
			leftpaddle.Draw();
			rightpaddle.Draw();
			if (winnerText)
			{
				int textwidth = MeasureText(winnerText,60);
				DrawText(winnerText, GetScreenWidth()/2 - textwidth/2, GetScreenHeight() / 2 - 30, 60, YELLOW);
			}


		DrawFPS(10, 10);
		EndDrawing();

	    }



	CloseWindow();
	return 0;
}