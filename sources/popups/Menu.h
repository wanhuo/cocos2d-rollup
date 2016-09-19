/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * http://www.tooflya.com/development/
 *
 *
 * License: Tooflya Inc. Software License v1.
 *
 * Licensee may not use this software for commercial purposes. For the purpose of this license,
 * commercial purposes means that a 3rd party has to pay in order to access Software or that
 * the Website that runs Software is behind a paywall. In consideration of the License granted
 * under clause 2, Licensee shall pay Licensor a fee, via Credit-Card, PayPal or any other
 * mean which Licensor may deem adequate. Failure to perform payment shall construe as material
 * breach of this Agreement. This software is provided under an AS-IS basis and without any support,
 * updates or maintenance. Nothing in this Agreement shall require Licensor to provide Licensee with
 * support or fixes to any bug, failure, mis-performance or other defect in The Software.
 *
 * @cocos2d
 *
 */

#ifndef _MENU_H_
#define _MENU_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Menu : public Popup
{
  /**
   *
   *
   *
   */
  public:
  enum State {
    STATE_MENU,
    STATE_FINISH
  };

  struct Buttons {
    ExtendedButton* play;
    ExtendedButton* restart;
    ExtendedButton* store;
    ExtendedButton* rate;
    ExtendedButton* share;
    ExtendedButton* social;
    ExtendedButton* settings;
    ExtendedButton* video;
    ExtendedButton* present;
    AnnounceButton* announce;

    ExtendedButton* state;
    ExtendedButton* add;
  };

  Buttons buttons;

  /**
   *
   *
   *
   */
  private:
  static Menu* instance;

  /**
   *
   *
   *
   */
  protected:
  Entity* background;

  virtual void onPlay();
  virtual void onRestart();
  virtual void onStore();
  virtual void onSettings();
  virtual void onRate();
  virtual void onUsers();
  virtual void onShare();

  /**
   *
   *
   *
   */
  public:
  static Menu* getInstance();

  Menu();
 ~Menu();

  int state = STATE_MENU;

  virtual void onEnter() override;
  virtual void onExit() override;

  virtual void show() override;
  virtual void hide() override;

  virtual void changeState(int state);
};

#endif
