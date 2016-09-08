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

#ifndef _UNLOCK_H_
#define _UNLOCK_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Unlock : public Popup
{
  /**
   *
   *
   *
   */
  public:
  enum State {
    STATE_NORMAL,
    STATE_ACTIVE
  };

  struct Buttons {
    ExtendedButton* action;
    ExtendedButton* next;
    ExtendedButton* announce;
  };

  Buttons buttons;

  /**
   *
   *
   *
   */
  private:
  static Unlock* instance;

  /**
   *
   *
   *
   */
  protected:

  /**
   *
   *
   *
   */
  public:
  static Unlock* getInstance();

  Unlock();
 ~Unlock();

  int state = STATE_NORMAL;

  virtual void onEnter() override;
  virtual void onExit() override;

  virtual void show() override;
  virtual void hide() override;

  virtual void showButtons();

  virtual void changeState(int state);
};

#endif
