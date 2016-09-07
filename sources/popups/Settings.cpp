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
  this->buttons.menu = new ExtendedButton("ui/button-menu.png", 2, 1, this, [=] () {
    this->hide();
  });
  this->buttons.store = new ExtendedButton("ui/button-store.png", 2, 1, this, [=] () {
  });
  this->buttons.rate = new ExtendedButton("ui/button-rate.png", 2, 1, this, [=] () {
  });
  this->buttons.video = new VideoButton(this);
  this->buttons.present = new PresentButton(this);
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
  this->buttons.rate->add(position.x - 128, position.y);
  this->buttons.store->add(position.x - 256, position.y);
  this->buttons.video->add(position.x + 128, position.y);
  this->buttons.present->add(position.x + 256, position.y);
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
  this->buttons.store->remove();
  this->buttons.rate->remove();
  this->buttons.video->remove();
  this->buttons.present->remove();
}
