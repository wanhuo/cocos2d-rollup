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
Menu* Menu::instance;

/**
 *
 *
 *
 */
Menu* Menu::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Menu::Menu()
: Popup()
{
  instance = this;

  /**
   *
   *
   *
   */
  this->background = new Entity("ui/background-menu.png", this, true);
  this->background->setPosition(Application->getCenter());
  this->background->setScale(2.0);

  /**
   *
   *
   *
   */
  this->buttons.play = new ExtendedButton("ui/button-play.png", 2, 1, this, [=] () {
    Application->changeState(Game::STATE_GAME);
  });
  this->buttons.restart = new ExtendedButton("ui/button-restart.png", 2, 1, this, [=] () {
    Application->changeState(Game::STATE_GAME);

    Application->environment->clear->runAction(
      Sequence::create(
        FadeTo::create(0.3, 255.0),
        CallFunc::create([=] () {
        Application->reset();
        }),
        FadeTo::create(0.3, 0.0),
        nullptr
      )
    );
  });
  this->buttons.store = new ExtendedButton("ui/button-store.png", 2, 1, this, [=] () {
    Application->environment->onStore();

    this->hide();

    Application->environment->clear->runAction(
      Sequence::create(
        DelayTime::create(0.5),
        CallFunc::create([=] () {
        Application->changeState(Game::STATE_STORE);
        }),
        nullptr
      )
    );
  });
  this->buttons.settings = new ExtendedButton("ui/button-settings.png", 2, 1, this, [=] () {
    Application->environment->onSettings();

    this->hide();

    Application->environment->clear->runAction(
      Sequence::create(
        DelayTime::create(0.5),
        CallFunc::create([=] () {
        Application->changeState(Game::STATE_SETTINGS);
        }),
        nullptr
      )
    );
  });
  this->buttons.rate = new ExtendedButton("ui/button-rate.png", 2, 1, this, [=] () {
  });
  this->buttons.social = new ExtendedButton("ui/button-social.png", 2, 1, this, [=] () {
  });
  this->buttons.video = new VideoButton(this);
  this->buttons.present = new PresentButton(this);
}

Menu::~Menu()
{
}

/**
 *
 *
 *
 */
void Menu::onEnter()
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
  switch(this->state)
  {
    case STATE_MENU:
    this->buttons.play->add(position.x, position.y);
    break;
    case STATE_FINISH:
    this->buttons.restart->add(position.x, position.y);
    break;
  }

  this->buttons.rate->add(position.x - 128, position.y);
  this->buttons.store->add(position.x - 256, position.y);
  this->buttons.video->add(position.x + 128, position.y);
  this->buttons.present->add(position.x + 256, position.y);
  this->buttons.social->add(position.x * 2 - 128 * 1.35, Application->getHeight() - 64);
  this->buttons.settings->add(position.x * 2 - 64, Application->getHeight() - 64);
}

void Menu::onExit()
{
  Popup::onExit();
}

/**
 *
 *
 *
 */
void Menu::show()
{
  this->_create();

  this->background->setOpacity(0);
  this->background->runAction(
    Spawn::create(
      Sequence::create(
        ScaleTo::create(0.5, 1.0),
        CallFunc::create([=] () {
        this->onShow();
        }),
        nullptr
      ),
      FadeTo::create(0.5 * 3, 200.0),
      nullptr
    )
  );
}

void Menu::hide()
{
  this->background->runAction(
    Spawn::create(
      Sequence::create(
        ScaleTo::create(0.5, 2.0),
        CallFunc::create([=] () {
        this->onHide();
        }),
        nullptr
      ),
      FadeTo::create(0.5, 0.0),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  this->buttons.play->remove();
  this->buttons.restart->remove();
  this->buttons.store->remove();
  this->buttons.rate->remove();
  this->buttons.social->remove();
  this->buttons.settings->remove();
  this->buttons.video->remove();
  this->buttons.present->remove();
}

/**
 *
 *
 *
 */
void Menu::changeState(int state)
{
  this->state = state;
}
