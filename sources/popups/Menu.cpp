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
  this->buttons.play = new ExtendedButton("ui/button-play.png", 2, 1, this, std::bind(&Menu::onPlay, this));
  this->buttons.restart = new ExtendedButton("ui/button-restart.png", 2, 1, this, std::bind(&Menu::onRestart, this));
  this->buttons.store = new ExtendedButton("ui/button-store.png", 2, 1, this, std::bind(&Menu::onStore, this));
  this->buttons.settings = new ExtendedButton("ui/button-settings.png", 2, 1, this, std::bind(&Menu::onSettings, this));
  this->buttons.rate = new ExtendedButton("ui/button-rate.png", 2, 1, this, std::bind(&Menu::onRate, this));
  this->buttons.social = new ExtendedButton("ui/button-social.png", 2, 1, this, std::bind(&Menu::onUsers, this));
  this->buttons.share = new ExtendedButton("ui/button-share.png", 2, 1, this, std::bind(&Menu::onShare, this));
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
  switch(this->state)
  {
    case STATE_MENU:
    break;
    case STATE_FINISH:
    if(Director::getInstance()->getCaptureState())
    {
      Application->environment->capture->add(Application->getCenter().x, Application->getCenter().y);
    }
    break;
  }

  /**
   *
   *
   *
   */
  switch(this->state)
  {
    case STATE_MENU:
    this->buttons.play->add(Application->getCenter().x, 200);
    break;
    case STATE_FINISH:
    this->buttons.restart->add(Application->getCenter().x, 200);
    break;
  }

  /**
   *
   *
   *
   */
  if(Heyzap::available(AD_TYPE_VIDEO))
  {
    this->buttons.video->add(Application->getCenter().x + 128, 200);
  }
  else
  {
    this->buttons.share->add(Application->getCenter().x + 128, 200);
  }

  /**
   *
   *
   *
   */
  this->buttons.rate->add(Application->getCenter().x - 128, 200);
  this->buttons.store->add(Application->getCenter().x - 256, 200);
  this->buttons.present->add(Application->getCenter().x + 256, 200);
  this->buttons.social->add(Application->getCenter().x * 2 - 128 * 1.35, Application->getHeight() - 64);
  this->buttons.settings->add(Application->getCenter().x * 2 - 64, Application->getHeight() - 64);
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
void Menu::onPlay()
{
  Application->changeState(Game::STATE_GAME);
}

void Menu::onRestart()
{
  Application->changeState(Game::STATE_GAME);

  Application->environment->clear->runAction(
    Sequence::create(
      FadeTo::create(0.3, 255.0),
      CallFunc::create([=] () {
      Application->reset();
      }),
      DelayTime::create(0.1),
      FadeTo::create(0.3, 0.0),
      nullptr
    )
  );
}

void Menu::onStore()
{
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
}

void Menu::onSettings()
{
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
}

void Menu::onUsers()
{
  if(!Facebook::status())
  {
    Facebook::connect([=] (bool state) {
      //
    });
  }
  else
  {
    Application->environment->onUsers();

    this->hide();

    Application->environment->clear->runAction(
      Sequence::create(
        DelayTime::create(0.5),
        CallFunc::create([=] () {
        Application->changeState(Game::STATE_USERS);
        }),
        nullptr
      )
    );
  }
}

void Menu::onRate()
{
  Application->onRate();
}

void Menu::onShare()
{
  Application->onShare(
    Application->getFrameWidth(),
    Application->getFrameHeight(),
    0,
    0,
    false,
    "", // @TODO: Add share text;
    [=] (int a) {
    }
  );
}

/**
 *
 *
 *
 */
void Menu::show()
{
  Popup::show();

  /**
   *
   *
   *
   */
  this->background->setOpacity(0);
  this->background->runAction(
    Spawn::create(
      Sequence::create(
        ScaleTo::create(0.5, 1.0),
        nullptr
      ),
      FadeTo::create(0.5 * 3, 200.0),
      nullptr
    )
  );
}

void Menu::hide()
{
  Popup::hide();

  /**
   *
   *
   *
   */
  this->background->runAction(
    Spawn::create(
      Sequence::create(
        ScaleTo::create(0.5, 2.0),
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
  this->buttons.share->remove();
  this->buttons.settings->remove();
  this->buttons.video->remove();
  this->buttons.present->remove();

  /**
   *
   *
   *
   */
  Application->environment->capture->remove();
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
