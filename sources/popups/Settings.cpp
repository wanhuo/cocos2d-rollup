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
Settings* Settings::instance;

/**
 *
 *
 *
 */
Settings* Settings::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Settings::Settings()
: Popup()
{
  instance = this;

  /**
   *
   *
   *
   */
  this->buttons.menu = new ExtendedButton("ui/button-menu.png", 2, 1, this, std::bind(&Settings::onMenu, this));
  this->buttons.services = new ExtendedButton("ui/button-services.png", 2, 1, this, std::bind(&Settings::onServices, this));
  this->buttons.restore = new ExtendedButton("ui/button-restore.png", 2, 1, this, std::bind(&Settings::onRestore, this));
  this->buttons.noad = new ExtendedButton("ui/button-noad.png", 2, 1, this, std::bind(&Settings::onNoad, this));
  this->buttons.sound = new SoundButton(this);
}

Settings::~Settings()
{
}

/**
 *
 *
 *
 */
void Settings::onEnter()
{
  Popup::onEnter();

  /**
   *
   *
   *
   */
  Vec2 position;

  position.x = Application->getCenter().x;
  position.y = 200.0;

  /**
   *
   *
   *
   */
  this->buttons.menu->add(position.x, position.y);
  this->buttons.services->add(position.x - 128, position.y);
  this->buttons.sound->add(position.x - 256, position.y);
  this->buttons.restore->add(position.x + 128, position.y);
  this->buttons.noad->add(position.x + 256, position.y);
}

void Settings::onExit()
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
void Settings::onMenu()
{
  this->hide();
}

void Settings::onServices()
{
  Application->onLeaderboards();
}

void Settings::onRestore()
{
  Application->onRestorePurchases();
}

void Settings::onNoad()
{
  Application->onNoad();
}

/**
 *
 *
 *
 */
void Settings::show()
{
  Popup::show();
}

void Settings::hide()
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
