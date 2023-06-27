#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
SoftDMD dmd(1, 1, 7, 6, 5, 3, 4, 2);
int x = 15, y = 7, speedx = 1, speedy = 1, aux1, aux2, aux3, aux4, ScoreA, ScoreB;

void setup() {
  pinMode(9, OUTPUT);
  dmd.setBrightness(255);
  dmd.selectFont(SystemFont5x7);
  dmd.begin();
  dmd.drawString(1, 0, F("PING "));
  dmd.drawString(2, 8, F(" PONG"));
  delay(2000);
  showScore();
  startGame();
}

void loop() {
  drawBall();
  drawPlayerA();
  drawPlayerB();
  moveBall();
  delay(100);
}

void drawBall() {
  analogWrite(9, 0);
  dmd.setPixel(aux1, aux2, GRAPHICS_OFF);
  dmd.setPixel(x, y, GRAPHICS_ON);
  aux1 = x;
  aux2 = y;
}

void drawPlayerA() {
  int analogA = map(analogRead(A0), 0, 1023, -3, 15);
  dmd.drawLine(1, aux3, 1, aux3 + 3, GRAPHICS_OFF);
  dmd.drawLine(1, analogA, 1, analogA + 3, GRAPHICS_ON);
  aux3 = analogA;
  if (x == 1 && y >= aux3 && y <= aux3 + 3) {
    analogWrite(9, 30);
    speedx = -speedx;
  }
}

void drawPlayerB() {
  int analogB = map(analogRead(A5), 0, 1023, -3, 15);
  dmd.drawLine(30, aux4, 30, aux4 + 3, GRAPHICS_OFF);
  dmd.drawLine(30, analogB, 30, analogB + 3, GRAPHICS_ON);
  aux4 = analogB;
  if (x == 30 && y >= aux4 && y <= aux4 + 3) {
    analogWrite(9, 30);
    speedx = -speedx;
  }
}

void moveBall() {
  if (x > 31) {
    ScoreA++;
    if (ScoreA > 99)
      ScoreA = 0;
    showScore();
    speedx = -speedx;
    startGame();
  } else if (x < 0) {
    ScoreB++;
    if (ScoreB > 99)
      ScoreB = 0;
    showScore();
    speedx = -speedx;
    startGame();
  }
  if (y > 15) {
    speedy = -speedy;
    analogWrite(9, 30);
  } else if (y < 0) {
    speedy = -speedy;
    analogWrite(9, 30);
  }
  x = x + speedx;
  y = y + speedy;
}

void showScore() {
  dmd.clearScreen();
  dmd.drawString(2, 0, "A: " + String(ScoreA));
  dmd.drawString(2, 8, "B: " + String(ScoreB));
  delay(2000);
  dmd.clearScreen();
}

void startGame() {
  dmd.clearScreen();
  x = 15, y =7;
dmd.drawString(2,4,F("READY!"));
delay(2000);
dmd.clearScreen();  
}
