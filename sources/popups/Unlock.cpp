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

#include "Game.h"

/**
 *
 *
 *
 */
Unlock* Unlock::instance;

/**
 *
 *
 *
 */
Unlock* Unlock::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Unlock::Unlock()
: Popup()
{
  instance = this;

  /**
   *
   *
   *
   */
  this->buttons.action = new UnlockButton(this);
  this->buttons.next = new ExtendedButton("ui/button-next.png", 2, 1, this, [=] () {
    this->hide();
  });
  this->buttons.announce = new ExtendedButton("ui/button-announce.png", 2, 1, this, [=] () {
  });
}

Unlock::~Unlock()
{
}

/**
 *
 *
 *
 */
void Unlock::onEnter()
{
  Popup::onEnter();
}

void Unlock::onExit()
{
  Popup::onExit();

  /**
   *
   *
   *
   */
  Application->changeState(Game::STATE_FINISH);
}

/**
 *
 *
 *
 */
void Unlock::show()
{
  Popup::show();

  /**
   *
   *
   *
   */
  this->buttons.action->add();
}

void Unlock::hide()
{
  Popup::hide();

  /**
   *
   *
   *
   */
  this->buttons.action->remove();
  this->buttons.next->remove();
  this->buttons.announce->remove();
}

void Unlock::showButtons()
{
  this->buttons.next->add(Application->getCenter().x + 64, 200);
  this->buttons.announce->add(Application->getCenter().x - 64, 200);
}

/**
 *
 *
 *
 */
void Unlock::changeState(int state)
{
  this->state = state;
}
