#include "coin.h"
#include "lasso.h"

void Coin::initCoin() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR(210,72,166));
  coin_circle.setFill(true);
  addPart(&coin_circle);
}

void Coin::resetCoin() {
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

void Bomb::initBomb() {
  bomb_start_x = (PLAY_X_START+WINDOW_X)/2;
  bomb_start_y = PLAY_Y_HEIGHT;
  bomb_circle.reset(bomb_start_x, bomb_start_y, BOMB_SIZE);
  bomb_circle.setColor(COLOR("black"));
  bomb_circle.setFill(true);
  addPart(&bomb_circle);
}

void Bomb::resetBomb() {
  double bomb_speed = COIN_SPEED;
  double bomb_angle_deg = BOMB_ANGLE_DEG;
  bomb_ax = 0;
  bomb_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(bomb_start_x, bomb_start_y, bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta);
}

void Mag::initMag() {
  mag_start_x = (PLAY_X_START+WINDOW_X)/2;
  mag_start_y = PLAY_Y_HEIGHT;
  mag_circle.reset(mag_start_x, mag_start_y, MAG_SIZE);
  mag_circle.setColor(COLOR("red"));
  mag_circle.setFill(true);
  addPart(&mag_circle);
}

void Mag::resetMag() {
  double mag_speed = COIN_SPEED;
  double mag_angle_deg = MAG_ANGLE_DEG;
  mag_ax = 0;
  mag_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(mag_start_x, mag_start_y, mag_speed, mag_angle_deg, mag_ax, mag_ay, paused, rtheta);
}

