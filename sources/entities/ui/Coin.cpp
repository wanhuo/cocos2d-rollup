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
Coin::Coin()
: Entity("ui/counter-coins-icon.png")
{
}

Coin::~Coin()
{
}

/**
 *
 *
 *
 */
void Coin::onCreate()
{
  Entity::onCreate();

  /**
   *
   *
   *
   */
  auto v = Vec2(0, 0);
  auto c = Menu::getInstance()->buttons.present->getPosition();

  auto r = random(30.0, 70.0);
  auto a = random(0.0, 360.0);
  auto x = c.x + r * cos(a);
  auto y = c.y + r * sin(a);

  v.x = x - c.x;
  v.y = y - c.y;

  v.normalize();

  /**
   *
   *
   *
   */;
  this->setScale(1.0);
  this->setOpacity(255);
  this->setPosition(x, y);
  this->setRotation(random(-45, 45));

  /**
   *
   *
   *
   */
  auto time = random(1.0, 1.5);

  /**
   *
   *
   *
   */
  this->runAction(
    Spawn::create(
      EaseSineOut::create(
        FadeTo::create(time, 0)
      ),
      Sequence::create(
        DelayTime::create(time / 2),
        EaseSineOut::create(
          ScaleTo::create(time / 2, random(1.0, 1.2))
        ),
        nullptr
      ),
      Sequence::create(
        EaseSineOut::create(
          MoveBy::create(time, v * random(1.0, 200.0))
        ),
        CallFunc::create([=] () {
        this->_destroy(true);
        }),
        nullptr
      ),
      nullptr
    )
  );
}

void Coin::onDestroy(bool action)
{
  Entity::onDestroy(action);

  /**
   *
   *
   *
   */
  if(action)
  {
    Application->counter->currency.icon->runAction(
      Sequence::create(
        ScaleTo::create(0.0, 1.1),
        ScaleTo::create(0.1, 1.0),
        nullptr
      )
    );

    Application->counter->onCoin();
  }
}

/**
 *
 *
 *
 */
void Coin::update(float time)
{
}

/**
 *
 *
 *
 */
Coin* Coin::deepCopy()
{
  return new Coin;
}
