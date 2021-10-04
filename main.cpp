#include <simplecpp>
#include <string>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"

using namespace simplecpp;

main_program {

  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;
  int level = 1;
  int mag_counter = 0;
  int lasso_radius = LASSO_RADIUS;

  Rectangle r(WINDOW_X/2, WINDOW_Y/2, WINDOW_X, WINDOW_Y);
  r.setColor(COLOR(195,251,152));
  r.setFill(true);

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  // Draw coordinate system 
  
  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("blue"));
  Line b2(100, 0, 100, WINDOW_Y);
  b2.setColor(COLOR("blue"));
  

  //Game Controls
  Text contolsi(550+textWidth("Game Controls")/2, 50, "Game Controls:");
  Text controls1(550+textWidth("t = Release Lasso")/2, 70, "t = Release Lasso");
  Text controls2(550+textWidth("y = Retract/Yank Lasso")/2, 90, "y = Retract/Yank Lasso");
  Text controls3(550+textWidth("l = Use Lasso rope")/2, 110, "l = Use Lasso rope");
  Text controls4(550+textWidth("q = Quit")/2, 130, "q = Quit");
  Text controls5(550+textWidth("+/- = Increase/Decrease speed of lasso")/2, 150, "+/- = Increase/Decrease speed of lasso");
  Text controls6(550+textWidth("[ and ] = Change angle of lasso")/2, 170, "[ and ] = Change angle of lasso");
  Text coin1(550+textWidth("Black = BOMB (decreases score by 1)")/2, 200, "Black = BOMB (decreases score by 1)");
  Text coin2(550+textWidth("Red = BUFF (Increases loop radius)")/2, 220, "Red = BUFF (Increases loop radius)");
  Text cannon((PLAY_X_START+WINDOW_X)/2, PLAY_Y_HEIGHT + 20, "Cannon");

  string msg("Cmd: _");
  Text charPressed(200, PLAY_Y_HEIGHT+15, msg);
  char coinScoreStr[256];
  char levelstr[256];
  char coinstogo[256];
  int sum = 1;

  sprintf(coinScoreStr, "Score: %d", lasso.getNumCoins());
  sprintf(levelstr, "Level: %d", level);
  sprintf(coinstogo, "Coins remaining in this level: %d", lasso.getNumCoins() - sum);

  Text coinScore(200, PLAY_Y_HEIGHT+35, coinScoreStr);
  Text level_no(200, PLAY_Y_HEIGHT+55, levelstr);
  Text coinstogoT(270, PLAY_Y_HEIGHT+75, coinstogo);

  // Initialize coin
  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double bomb_angle_deg = BOMB_ANGLE_DEG;
  double mag_angle_deg = MAG_ANGLE_DEG;
  double coin_ax = 0;
  double coin_ay = COIN_G;
  int temp = lasso.getNumCoins();
  int magcheck;

  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  Bomb bomb(coin_speed, bomb_angle_deg, coin_ax, coin_ay, paused, rtheta);
  Mag mag(coin_speed, mag_angle_deg, coin_ax, coin_ay, paused, rtheta);

  Rectangle cover((PLAY_X_START+WINDOW_X)/2, PLAY_Y_HEIGHT + 2, 20, 20); cover.setColor(COLOR("red")); cover.setFill(true);
  Rectangle cover1((PLAY_X_START+WINDOW_X)/2, PLAY_Y_HEIGHT + 2, 15, 15); cover1.setColor(COLOR("blue")); cover1.setFill(true);


  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;

  // When t is pressed, throw lasso
  // If lasso within range, make coin stick
  // When y is pressed, yank lasso
  // When l is pressed, loop lasso
  // When q is pressed, quit
  for(;;){
    if((runTime > 0) && (currTime > runTime)) { break; }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
        case 't':
	        lasso.unpause();
	        break;
        case 'y':
	        lasso.yank();
	        break;
        case 'l':
          lasso.loopit(lasso_radius);
          lasso.check_for_coin(&coin, lasso_radius);
          lasso.check_for_bomb(&bomb);
          lasso.check_for_mag(&mag);
          magcheck = lasso.check_for_mag(&mag);
          //wait(STEP_TIME*5);
          break;
        case '[':
          if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
          break;
        case ']':
        	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
        	break;
        case '-':
        	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
        	break;
        case '=':
        	if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
        	break;
        case 'q':
	        exit(0);
        default:
	        break;
      }
    }

    //cout << lasso.getNumCoins() << " " << temp << endl; 
    lasso.nextStep(stepTime);
    coin.nextStep(stepTime);
    mag.nextStep(stepTime);

    if(coin.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	      coin.unpause();
      }
    }

    if(coin.getYPos() > PLAY_Y_HEIGHT) {
      coin.resetCoin();
      last_coin_jump_end = currTime;
    }

    //Move bomb for designated levels
    if(level%2 == 0) {
      bomb.nextStep(stepTime);

      if(bomb.isPaused()) {
        if((currTime-last_coin_jump_end) >= COIN_GAP) {
          bomb.unpause();
        }
      }

      if(bomb.getYPos() > PLAY_Y_HEIGHT) {
        bomb.resetBomb();
        last_coin_jump_end = currTime;
      }
    }

    //Reset bomb on the next level
    if(level%2 == 1) bomb.resetBomb();

    //Move mag for designated levels
    if(level%3 == 0 && mag_counter == 0 && lasso.getNumCoins() == temp + level/2) {
      mag.nextStep(stepTime);

      if(mag.isPaused()) {
        if((currTime-last_coin_jump_end) >= COIN_GAP) {
          mag.unpause();
        }
      }

      if(mag.getYPos() > PLAY_Y_HEIGHT) {
        mag.resetMag();
        last_coin_jump_end = currTime;
      }
      mag_counter++;
    }

    //Increase loop radius
    if(magcheck == 2) {
      mag.resetMag();
      lasso_radius = 2*LASSO_RADIUS;
    }

    //Reset mag on the next level
    if(level%3 == 1) {
      mag.resetMag();
      magcheck = 0;
      lasso_radius = LASSO_RADIUS;
    }

    //Update coin score
    sprintf(coinScoreStr, "Score: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);

    if(lasso.getNumCoins() - temp == level) {
      level++;
      mag_counter = 0;
      magcheck = 0;
      temp = lasso.getNumCoins();
      sprintf(levelstr, "Level: %d", level);
      level_no.setMessage(levelstr);
    }
    sum = level*(level+1)/2;
    sprintf(coinstogo, "Coins remaining in this level: %d", -lasso.getNumCoins() + sum);
    coinstogoT.setMessage(coinstogo);

    stepCount++;
    currTime += stepTime;
    wait(stepTime);
    
  } // End for(;;)

  wait(3);

} // End main_program
