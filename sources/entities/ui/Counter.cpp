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
Counter::Counter()
: Entity(Application)
{
  this->elements = new Pool(new Number, this);

  this->setPosition(Application->getCenter().x, Application->getHeight() - 256);
  this->setCascadeOpacityEnabled(true);
  this->setLocalZOrder(10);
  this->setOpacity(0);

  /**
   *
   *
   *
   */
  this->currency.background = new Entity(true);
  this->currency.handler = new Coins(this->currency.background);

  this->currency.background->setOpacity(0);
  this->currency.background->setCascadeOpacityEnabled(true);

  this->best = new Text("@counter.best", this);
  this->currency.text = new Text("@counter.currency", this->currency.background, TextHAlignment::LEFT, true);
  this->currency.icon = new Entity("ui/counter-currency-icon.png", this->currency.background, true);

  this->currency.text->setPosition(66, Application->getHeight() - 40);
  this->currency.icon->setPosition(42, Application->getHeight() - 42);

  this->best->setPosition(0, -80);

  /**
   *
   *
   *
   */
  Director::getInstance()->setNotificationNode(this->currency.background);
}

Counter::~Counter()
{
}

/**
 *
 *
 *
 */
void Counter::onCreate()
{
  Entity::onCreate();

  /**
   *
   *
   *
   */
  this->runAction(
    EaseSineIn::create(
      FadeTo::create(0.5, 255.0)
    )
  );
}

void Counter::onDestroy(bool action)
{
  Entity::onDestroy(action);
}

/**
 *
 *
 *
 */
void Counter::onMenu()
{
}

void Counter::onFinish()
{
  this->onSave();

  /**
   *
   *
   *
   */
  this->best->_create();
  this->best->stopAllActions();
  this->best->setCameraMask(BACKGROUND);
  this->best->setScale(0.8);
  this->best->setOpacity(0.0);
  this->best->data(this->values.score.best);

  this->best->runAction(
    Spawn::create(
      EaseSineOut::create(
        ScaleTo::create(0.5, 1.0)
      ),
      Sequence::create(
        EaseSineOut::create(
          FadeTo::create(0.5, 255.0)
        ),
        nullptr
      ),
      nullptr
    )
  );
}

void Counter::onGame()
{
  this->best->stopAllActions();
  this->best->runAction(
    Spawn::create(
      EaseSineIn::create(
        ScaleTo::create(0.5, 0.8)
      ),
      Sequence::create(
        EaseSineIn::create(
          FadeTo::create(0.5, 0.0)
        ),
        CallFunc::create([=] () {

          /**
           *
           *
           *
           */
          this->best->_destroy();
        }),
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
void Counter::onSave()
{
  if(this->values.score.count > this->values.score.best)
  {
    // @TODO: New best;
  }

  /**
   *
   *
   *
   */
  this->values.score.best = max(this->values.score.count, this->values.score.best);

  /**
   *
   *
   *
   */
  Storage::set("@counter.values.best", this->values.score.best);
  Storage::set("@counter.values.currency", this->values.currency.count);

  /**
   *
   *
   *
   */
  // @TODO: Send Facebook value;
}

/**
 *
 *
 *
 */
void Counter::onCount(int count)
{
  this->values.score.count += count;

  /**
   *
   *
   *
   */
  this->updateData();
}

void Counter::onCoin(int count, bool sound)
{
  this->values.currency.count += count;

  /**
   *
   *
   *
   */
  this->updateData();

  /**
   *
   *
   *
   */
  if(sound)
  {
    this->onSave();

    /**
     *
     *
     *
     */
    Sound->play("coin");
  }
}

/**
 *
 *
 *
 */
int Counter::numbers(int number, int *elements)
{
  int count = 0;
  int max = 10;

  /**
   *
   *
   *
   */
  if(number == 0)
  {
    elements[0] = 0;
    return 1;
  }

  /**
   *
   *
   *
   */
  while(number > 0 && max)
  {
    elements[count++] = number % 10;
    number /= 10;

    max--;
   }

   return number ? 0 : count;
}

/**
 *
 *
 *
 */
void Counter::reset()
{
  this->elements->clear();

  /**
   *
   *
   *
   */
  this->animation.count = 1;
  this->values.score.count = 0;
  this->values.currency.count = Storage::get("@counter.values.currency");
  this->values.score.best = Storage::get("@counter.values.best");

  /**
   *
   *
   *
   */
  auto element = (Text*) this->elements->_create();
  element->data(0);
  element->setScaleX(1.0);
  element->setPosition(0, 0, 0);
  element->setRotation(0, 0, 0);

  /**
   *
   *
   *
   */
  this->setCameraMask(BACKGROUND);

  /**
   *
   *
   *
   */
  this->updateData();
}

/**
 *
 *
 *
 */
void Counter::updateData()
{
  this->updateScoreData();
  this->updateCurrencyData();
}

void Counter::updateCurrencyData()
{
  this->currency.text->data(this->values.currency.count);
}

void Counter::updateScoreData()
{
  int numbers[10];

  /**
   *
   *
   *
   */
  auto count = this->numbers(this->values.score.count, numbers);

  /**
   *
   *
   *
   */
  CC_LOOP(this->elements)
  {
    auto element = (Number*) this->elements->element(i);

    if(convert(numbers[i]) != element->getString())
    {
      element->runAction(
        Sequence::create(
          RotateBy::create(0.1, Vec3(0, 90, 0)),
          CallFunc::create([=] () {
          element->data(numbers[i]);
          }),
          RotateBy::create(0.1, Vec3(0, 90, 0)),
          nullptr
        )
      );
    }
  }

  if(this->animation.count != count)
  {
    this->animation.count = count;

    /**
     *
     *
     *
     */
    auto element = this->elements->_create();

    element->runAction(
      Sequence::create(
        FadeTo::create(0.0, 0.0),
        FadeTo::create(0.2, 255.0),
        nullptr
      )
    );
    element->setPosition(0, 0, 0);
    element->setRotation(0, 0, 0);
    element->setScaleX(1.0);

    /**
     *
     *
     *
     */
    this->setCameraMask(BACKGROUND);

    /**
     *
     *
     *
     */
    CC_LOOP(this->elements)
    {
      auto element = (Number*) this->elements->element(this->elements->count - i - 1);

      element->runAction(
        EaseSineIn::create(
          MoveTo::create(0.2, Vec2(50.0 * i - (50.0 * (count - 1)) / 2, element->getPositionY()))
        )
      );
    }
  }
}

/**
 *
 *
 *
 */
void Counter::update(float time)
{
}
