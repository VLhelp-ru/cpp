// ***** COPYRIGHT: VLhelp.ru / program@vlhelp.ru *****
#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <process.h>

float a, b, c,
      x1, y1, x2, y2, x3, y3,
      x0, y0,
      square, radius,
      maxRadius, maxx0, maxy0;
int maxPoints = 0;
int totalPoints = 0;

float points[100][2];

// Quit program on error
void ExitOnErr(char errStr[])
{
  cout << "\n";
  cout << errStr << "\n\n";
  cout << "Press any key to exit...\n";
  getch();
  exit(0);
}

// Read data file with points
void ReadData()
{
  int n = 0;
  FILE *fin; // create pointer to file
  fin = fopen("input.txt", "r"); // open file for reading
  if (fin == NULL) ExitOnErr("File not found!"); // if no file
  int i = 0;
  float x = 0, y = 0;
  while (1)
  {
    n = fscanf(fin, "%f %f", &x, &y);
	if (i >= 100) break;
    points[i][0] = x;
    points[i][1] = y;
    i++;
    if (n == -1) break;
    else if (n == 0) ExitOnErr("Wrong file structure!");
    totalPoints = i;
  }
  fclose(fin);
  if (totalPoints == 0) ExitOnErr("File is empty!");
  else if ((totalPoints > 0 && totalPoints <= 3)) ExitOnErr("Not enough points!");
}

//Count sides of triangle
void countABC()
{
  a = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
  b = sqrt(pow(x3 - x1, 2) + pow(y3 - y1, 2));
  c = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}


//Check if triangle
int IsTriangle(float a, float b, float c)
{
  if (((a + b) > c) && ((b + c) > a) && ((a + c) > b))
  {
    return 1;
  }
  else
    return 0;
}

//Check if point in circle
int InCircle(float x, float y, float x0, float y0, float r)
{
  if ((pow(x - x0, 2) + pow(y - y0, 2)) <= pow(r, 2))
    return 1;
  else
    return 0;
}

//Square of triangle
float Square(float a, float b, float c)
{
  return (1 / (4 * sqrt((a + b + c) * (b + c - a) * (a + c - b) * (a + b - c))));
}

//Radius of circle
float Radius(float a, float b, float c)
{
  //return ((a * b * c) / (4 * Square(a, b, c)));
  return ((a * b * c) / (4 * square));
}

//X-coordinate of circle
float CenterX(float s, float x1, float y1, float x2, float y2, float x3, float y3)
{
  return (1 / (4 * s)) * ((x1 * x1 + y1 * y1) * y2 + (x2 * x2 + y2 * y2) * y3 + (x3 * x3 + y3 * y3) * y1 -
			  (x3 * x3 + y3 * y3) * y2 + (x1 * x1 + y1 * y1) * y3 + (x2 * x2 + y2 * y2) * y1);
}

//Y-coordinate of circle
float CenterY(float s, float x1, float y1, float x2, float y2, float x3, float y3)
{
  return -(1 / (4 * s)) * ((x1 * x1 + y1 * y1) * x2 + (x2 * x2 + y2 * y2) * x3 + (x3 * x3 + y3 * y3) * x1 -
			   (x3 * x3 + y3 * y3) * x2 + (x1 * x1 + y1 * y1) * x3 + (x2 * x2 + y2 * y2) * x1);
}

//Count how much point in a circle
int CountPoints(float x0, float y0, float r)
{
  int tmp = 0;

  for (int i = 0; i < totalPoints; i++)
  {
    if (InCircle(points[i][0], points[i][1], x0, y0, r) == 1)
      tmp++;
  }
  return tmp;
}

//Program
void main(void)
{
  clrscr();

  cout << "\n";
  cout << "Welcome!\n";

  ReadData();

  for (int i = 0; i < totalPoints - 2; i++)
  {
    for (int j = i + 1; j < totalPoints - 1; j++)
    {
      for (int k = j + 1; k < totalPoints; k++)
      {
	x1 = points[i][0];
	y1 = points[i][1];

	x2 = points[j][0];
	y2 = points[j][1];

	x3 = points[k][0];
	y3 = points[k][1];

	countABC();
	if (IsTriangle(a, b, c) == 1)
	{
	  square = Square(a, b, c);
	  radius = Radius(a, b, c);
	  x0 = CenterX(square, x1, y1, x2, y2, x3, y3);
	  y0 = CenterY(square, x1, y1, x2, y2, x3, y3);
	  if (CountPoints(x0, y0, radius) > maxPoints)
	  {
	    maxRadius = radius;
	    maxx0 = x0;
	    maxy0 = y0;
	  }
	}
      }
    }
  }


  cout << "\n";
  cout << "Max radius: " << maxRadius << "\n";
  cout << "Max (x0, y0) = " << "(" << maxx0 << ", " << maxy0 << ")";
  cout << "\n";
  getch();
}
