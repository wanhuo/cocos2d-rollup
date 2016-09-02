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
Dust::Dust()
: BillBoard()
{
  this->initWithFile("environments/dust.png");
  this->autorelease();

  this->setScale(0.005 * 0.2);

  this->enableShadow(false);
  this->enableLight(false);
}

Dust::~Dust()
{
}

/**
 *
 *
 *
 */
void Dust::onCreate()
{
  BillBoard::onCreate();

  /**
   *
   *
   *
   */
   this->setPositionY(0);
   this->setOpacity(0);
  auto delay = random(0.0, 15.0);

  auto move_to = random(0.5, 10.0);
  auto move_time = random(1.0, 5.0);

  auto alpha_to = random(100, 200);
  auto alpha_time = move_time;

  this->runAction(
    Spawn::create(
      Sequence::create(
        DelayTime::create(delay),
        MoveBy::create(move_time, Vec3(0, move_to, 0)),
        nullptr
      ),
      Sequence::create(
        DelayTime::create(delay),
        FadeTo::create(alpha_time, alpha_to),
        CallFunc::create([=] () {
        this->_destroy();
        this->_create();
        }),
        nullptr
      ),
      Sequence::create(
        DelayTime::create(delay),
        nullptr
      ),
      nullptr
    )
  );
}

void Dust::onDestroy(bool action)
{
  BillBoard::onDestroy(action);
}

/**
 *
 *
 *
 */
void Dust::onEnter()
{
  BillBoard::onEnter();
}

void Dust::onExit()
{
  BillBoard::onExit();
}

/**
 *
 *
 *
 */
void Dust::update(float time)
{
  BillBoard::update(time);
}

/**
 *
 *
 *
 */
Dust* Dust::deepCopy()
{
  return new Dust;
}
