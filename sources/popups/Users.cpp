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
Users* Users::instance;

/**
 *
 *
 *
 */
Users* Users::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Users::Users()
: Popup()
{
  instance = this;

  /**
   *
   *
   *
   */
  this->buttons.menu = new ExtendedButton("ui/button-menu.png", 2, 1, this, std::bind(&Users::onMenu, this));
  this->buttons.services = new ExtendedButton("ui/button-services.png", 2, 1, this, std::bind(&Users::onServices, this));
  this->buttons.restore = new ExtendedButton("ui/button-restore.png", 2, 1, this, std::bind(&Users::onRestore, this));
  this->buttons.noad = new ExtendedButton("ui/button-noad.png", 2, 1, this, std::bind(&Users::onNoad, this));
  this->buttons.sound = new SoundButton(this);
}

Users::~Users()
{
}

/**
 *
 *
 *
 */
void Users::onEnter()
{
  Popup::onEnter();

  /**
   *
   *
   *
   */
  this->buttons.menu->add(Application->getCenter().x, 200);
  this->buttons.services->add(Application->getCenter().x - 128, 200);
  this->buttons.sound->add(Application->getCenter().x - 256, 200);
  this->buttons.restore->add(Application->getCenter().x + 128, 200);
  this->buttons.noad->add(Application->getCenter().x + 256, 200);
}

void Users::onExit()
{
  Popup::onExit();

  /**
   *
   *
   *
   */
  Application->changeState(Game::STATE_MENU);
}

/**
 *
 *
 *
 */
void Users::onMenu()
{
  this->hide();
}

void Users::onServices()
{
  Application->onLeaderboards();
}

void Users::onRestore()
{
  Application->onRestorePurchases();
}

void Users::onNoad()
{
  Application->onNoad();
}

/**
 *
 *
 *
 */
void Users::show()
{
  Popup::show();
}

void Users::hide()
{
  Popup::hide();

  /**
   *
   *
   *
   */
  this->buttons.menu->remove();
  this->buttons.services->remove();
  this->buttons.sound->remove();
  this->buttons.restore->remove();
  this->buttons.noad->remove();
}
