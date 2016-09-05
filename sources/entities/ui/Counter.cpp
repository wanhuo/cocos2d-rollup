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

  this->setPosition(Application->getCenter().x - 25, Application->getHeight() - 256);
  this->setCascadeOpacityEnabled(true);
  this->setOpacity(0);
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
void Counter::onCount(int c)
{
  int numbers[10];

  /**
   *
   *
   *
   */
  auto count = this->numbers(this->values.score.count += c, numbers);

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

    this->runAction(
      EaseSineIn::create(
        MoveTo::create(0.2, Vec2(Application->getCenter().x - (50.0 * (count - 1)) / 2, this->getPositionY()))
      )
    );
  }
}

void Counter::onCoin(int c)
{
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
}

/**
 *
 *
 *
 */
void Counter::update(float time)
{
}
