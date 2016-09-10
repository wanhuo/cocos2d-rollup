/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * http://www.tooflya.com/development/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @version of cocos2d is 3.5
 *
 */

#include "Game.h"

/**
 *
 *
 *
 */
TimeButton::TimeButton(const char* textureFileName, int horizontalFramesCount, int verticalFramesCount, Node* parent, bool autocreate)
: ExtendedButton(textureFileName, horizontalFramesCount, verticalFramesCount, parent, [=] () {
this->onAction();
}, autocreate)
{
  this->icon = new Entity("ui/button-currency-icon.png", this);
  this->text = new Text("@buttons.time", this);

  /**
   *
   *
   *
   */
  this->icon->setScale(0.5);

  /**
   *
   *
   *
   */
  this->setCascadeOpacityEnabled(true);
  this->setScheduleUpdate(true);
}

TimeButton::~TimeButton()
{
}

/**
 *
 *
 *
 */
void TimeButton::onCreate()
{
  ExtendedButton::onCreate();
}

void TimeButton::onDestroy(bool action)
{
  ExtendedButton::onDestroy(action);
}

/**
 *
 *
 *
 */
void TimeButton::onEnter()
{
  ExtendedButton::onEnter();

  /**
   *
   *
   *
   */
  this->updateState();
}

void TimeButton::onExit()
{
  ExtendedButton::onExit();
}

/**
 *
 *
 *
 */
void TimeButton::onAdd()
{
}

void TimeButton::onRemove()
{
}

/**
 *
 *
 *
 */
void TimeButton::onNormal()
{
  this->text->_destroy();

  /**
   *
   *
   *
   */
  this->runAction(
    Sequence::create(
      DelayTime::create(random(1.0, 5.0)),
      CallFunc::create([=] () {

      /**
       *
       *
       *
       */
      auto count = random(2, 5);
      auto d = random(2.0, 5.0);
      auto time = 0.1;

      /**
       *
       *
       *
       */
      this->runAction(
        RepeatForever::create(
          Spawn::create(
            Sequence::create(
              DelayTime::create(d),
              Repeat::create(
                Sequence::create(
                  EaseSineIn::create(
                    RotateTo::create(time, -15.0)
                  ),
                  EaseSineIn::create(
                    RotateTo::create(time, 15.0)
                  ),
                  nullptr
                ),
                count
              ),
              EaseSineIn::create(
                RotateTo::create(time, 0.0)
              ),
              nullptr
            ),
            Sequence::create(
              DelayTime::create(d),
              ScaleTo::create(time * (count + 1) * 2, 1.1),
              ScaleTo::create(time, 1.0),
              nullptr
            ),
            nullptr
            )
          )
        );
      }),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  this->bind(true);
}

void TimeButton::onWait()
{
  if(!Application->getActionManager()->getActionByTag(1, this->text))
  {
    this->text->_create();
    this->text->setText("@buttons.time");
    this->text->setOpacity(255);
    this->text->setPosition(this->getWidth() / 2, this->getHeight() / 2 - 19);

    /**
     *
     *
     *
     */
    this->icon->_destroy();
  }

  /**
   *
   *
   *
   */
  this->bind(false);
}

/**
 *
 *
 *
 */
void TimeButton::onAction()
{
}

void TimeButton::onAction(int count, Node* element)
{
  Application->counter->currency.handler->add(count, element);

  /**
   *
   *
   *
   */
  this->count = Storage::get(this->id + ".count") + 1;

  /**
   *
   *
   *
   */
  this->stopAllActions();

  /**
   *
   *
   *
   */
  this->text->_create();
  this->text->setText("@buttons.currency");
  this->text->data(count);
  this->text->setOpacity(0);
  this->text->runAction(
    Sequence::create(
      FadeTo::create(0.5, 255),
      DelayTime::create(1.5),
      nullptr
    ),
    1
  );

  /**
   *
   *
   *
   */
  this->icon->_create();
  this->icon->setOpacity(0);
  this->icon->runAction(
    Sequence::create(
      FadeTo::create(0.5, 255),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  this->text->setPosition(this->getWidth() / 2 - this->icon->getWidthScaled() / 2 - 2.0, this->getHeight() / 2 - 19);
  this->icon->setPosition(this->text->getPositionX() + this->text->getWidth() / 2 + this->icon->getWidthScaled() / 2 + 2.0, this->getHeight() / 2 - 22);

  /**
   *
   *
   *
   */
  this->runAction(
    Spawn::create(
      RotateTo::create(0.1, 0.0),
      ScaleTo::create(0.1, 1.0),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  this->runAction(
    Sequence::create(
      DelayTime::create(2.0),
      CallFunc::create([=] () {

        /**
         *
         *
         *
         */
        this->text->runAction(
          Sequence::create(
            FadeTo::create(0.5, 0),
            CallFunc::create([=] () {
            this->text->setText("@buttons.time");
            this->text->setPosition(this->getWidth() / 2, this->getHeight() / 2 - 19);
            this->text->runAction(
              FadeTo::create(0.5, 255)
            );
            }),
            nullptr
          ),
          1
        );

        /**
         *
         *
         *
         */
        this->icon->runAction(
          Sequence::create(
            FadeTo::create(0.5, 0),
            CallFunc::create([=] () {
            this->icon->_destroy();
            }),
            nullptr
          )
        );
      }),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  Storage::set(this->id + ".count", this->count);
}

/**
 *
 *
 *
 */
void TimeButton::changeState(int state)
{
  {
    this->state = state;

    switch(this->state)
    {
      case STATE_NORMAL:
      this->onNormal();
      break;
      case STATE_WAIT:
      this->onWait();
      break;
    }

    this->setCameraMask(BACKGROUND);
  }
}

/**
 *
 *
 *
 */
void TimeButton::updateState()
{
  this->time = Times::parse(Storage::get(this->id + ".time", true));

  /**
   *
   *
   *
   */
  if(this->time - Times::now() < 0)
  {
    this->changeState(STATE_NORMAL);
  }
  else
  {
    this->changeState(STATE_WAIT);
  }
}

void TimeButton::updateTime(int time)
{
  this->time = Times::now() + Times::minute() * time + 3000;
  Storage::set(this->id + ".time", convert(this->time));

  /**
   *
   *
   *
   */
  this->changeState(STATE_WAIT);
}

/**
 *
 *
 *
 */
void TimeButton::update(float time)
{
  ExtendedButton::update(time);

  /**
   *
   *
   *
   */
  switch(this->state)
  {
    case STATE_WAIT:
    if(!Application->getActionManager()->getActionByTag(1, this->text))
    {
      if(this->time - Times::now() > 1000)
      {
        auto data = Times::format(this->time - Times::now());

        /**
         *
         *
         *
         */
        this->text->data(data.m, data.s);
      }
      else
      {
        this->changeState(STATE_NORMAL);
      }
    }
    break;
  }
}
