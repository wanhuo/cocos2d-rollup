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
  this->icon = new Entity("ui/button-currency-icon.png", this);
  this->separator = new Entity("ui/separator-1.png", this);

  this->texts.separator = new Text("@store.separator.1", this->separator, true);
  this->texts.currency = new Text("@buttons.unlock.currency", this);
  this->texts.text = new Text("@buttons.unlock.character", this);

  this->texts.separator->setPosition(this->separator->getWidth() / 2 , this->separator->getHeight() / 2 + 5);
  this->texts.text->setPosition(Application->getCenter().x, Application->getCenter().y + 200);

  this->texts.currency->data(100);
  this->texts.currency->setPosition(Application->getCenter().x - this->icon->getWidthScaled() / 2 - 2.0, Application->getCenter().y - 147);
  this->icon->setPosition(this->texts.currency->getPositionX() + this->texts.currency->getWidth() / 2 + this->icon->getWidthScaled() / 2 + 7.0, Application->getCenter().y - 151);

  this->separator->setCascadeOpacityEnabled(true);

  /**
   *
   *
   *
   */
  this->buttons.action = new UnlockButton(this);
  this->buttons.next = new ExtendedButton("ui/button-next.png", 2, 1, this, [=] () {
    this->hide();
  });
  this->buttons.announce = new AnnounceButton(this, [=] () {
    // TODO: Add share;
    Application->counter->currency.handler->add(50, this->buttons.announce);
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

  /**
   *
   *
   *
   */
  this->separator->runAction(
    Spawn::create(
      EaseSineIn::create(
        FadeTo::create(0.2, 0.0)
      ),
      Sequence::create(
        EaseSineIn::create(
          ScaleTo::create(0.2, 0.8)
        ),
        CallFunc::create([=] () {
        this->separator->_destroy();
        }),
        nullptr
      ),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  Unlock::getInstance()->texts.text->runAction(
    Spawn::create(
      EaseSineOut::create(
        ScaleTo::create(0.2, 0.8)
      ),
      EaseSineOut::create(
        FadeTo::create(0.2, 0.0)
      ),
      nullptr
    )
  );
}

void Unlock::showButtons()
{
  auto state = Store::getInstance()->element(true);

  /**
   *
   *
   *
   */
  if(state.category == Store::CATEGORY_RARE)
  {
    this->separator->_create();
    this->separator->setPosition(Application->getCenter().x, Application->getCenter().y + 135);
    this->separator->setScale(0.8);
    this->separator->setOpacity(0.0);
    this->separator->runAction(
      Spawn::create(
        Sequence::create(
          DelayTime::create(0.2),
          EaseSineOut::create(
            ScaleTo::create(0.2, 1.0)
          ),
          nullptr
        ),
        Sequence::create(
          DelayTime::create(0.2),
          EaseSineOut::create(
            FadeTo::create(0.2, 255.0)
          ),
          nullptr
        ),
        nullptr
      )
    );
  }

  /**
   *
   *
   *
   */
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
