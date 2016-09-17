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

  this->buttons.facebook.state = new FacebookButton::State(this);
  this->buttons.facebook.add = new FacebookButton::Add(this);

  this->line1 = new Entity("ui/separator-2.png", this, true);
  this->line2 = new Entity("ui/separator-2.png", this, true);

  this->line1->setPosition(Application->getCenter().x, Application->getCenter().y - 15);
  this->line2->setPosition(Application->getCenter().x, Application->getCenter().y - 200);

  /**
   *
   *
   *
   */
  this->buttons.steps = new Steps(this);
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
  this->buttons.menu->add(Application->getCenter().x, 200);
  this->buttons.services->add(Application->getCenter().x - 128, 200);
  this->buttons.sound->add(Application->getCenter().x - 256, 200);
  this->buttons.restore->add(Application->getCenter().x + 128, 200);
  this->buttons.noad->add(Application->getCenter().x + 256, 200);

  this->buttons.facebook.state->add(Application->getCenter().x, Application->getCenter().y - 68);
  this->buttons.facebook.add->add(Application->getCenter().x, Application->getCenter().y - 148);

  this->buttons.steps->add(Application->getCenter().x, Application->getCenter().y + 300);

  /**
   *
   *
   *
   */
  this->line1->setOpacity(0.0);
  this->line1->setScale(0.8);
  this->line1->runAction(
    Spawn::create(
      EaseSineOut::create(
        ScaleTo::create(0.5, 1.0)
      ),
      EaseSineOut::create(
        FadeTo::create(0.5, 255.0)
      ),
      nullptr
    )
  );

  this->line2->setOpacity(0.0);
  this->line2->setScale(0.8);
  this->line2->runAction(
    Spawn::create(
      EaseSineOut::create(
        ScaleTo::create(0.5, 1.0)
      ),
      EaseSineOut::create(
        FadeTo::create(0.5, 255.0)
      ),
      nullptr
    )
  );
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
  this->buttons.steps->remove();
  this->buttons.facebook.state->remove();
  this->buttons.facebook.add->remove();

  this->line1->runAction(
    Spawn::create(
      EaseSineIn::create(
        ScaleTo::create(0.5, 0.8)
      ),
      EaseSineIn::create(
        FadeTo::create(0.5, 0.0)
      ),
      nullptr
    )
  );
  this->line2->runAction(
    Spawn::create(
      EaseSineIn::create(
        ScaleTo::create(0.5, 0.8)
      ),
      EaseSineIn::create(
        FadeTo::create(0.5, 0.0)
      ),
      nullptr
    )
  );
}
