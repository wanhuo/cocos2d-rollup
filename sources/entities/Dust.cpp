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
  this->initWithFile("environments/1/dust.png");
  this->autorelease();
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
  this->setOpacity(0);
  this->setScale(0.005 * 0.2);

  /**
   *
   *
   *
   */
  auto time = 3.0;//random(1.0, 10.0);
  auto move = random(0.5, 1.0);
  auto scale = 1.0;

  if(probably(10))
  {
    move = 10.0;
    time = 1.0;
    scale = 1.3;
  }
  else if(probably(20))
  {
    move = random(1.0, 5.0);
    time = random(3.0, 5.0);
    scale = 1.3;
  }

  this->action = Speed::create(
    Spawn::create(
      Sequence::create(
        MoveBy::create(time, Vec3(0.0, move, 0.0)),
        CallFunc::create([=] () {
        this->_destroy(true);
        }),
        nullptr
      ),
      FadeTo::create(time / 2, random(100, 255)),
      Sequence::create(
        ScaleTo::create(time / 4 * 2, 0.005 * 0.2),
        ScaleTo::create(time / 4 * 2, 0.005 * 0.2 * scale),
        nullptr
      ),
      Sequence::create(
        DelayTime::create(random(2.0, 5.0)),
        CallFunc::create([=] () {
        this->action->setSpeed(1.0);
        }),
        nullptr
      ),
      nullptr
    ),
    1.0
  );

  if(probably(50))
  {
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          DelayTime::create(0.2),
          CallFunc::create([=] () {
          this->setOpacity(this->getOpacity() + random(-100.0, 100.0));
          }),
          nullptr
        )
      )
    );
  }

  this->runAction(this->action);
}

void Dust::onDestroy(bool action)
{
  BillBoard::onDestroy(action);

  /**
   *
   *
   *
   */
  if(action)
  {
    if(this->element)
    {
      this->element->dusts--;
    }
  }
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
void Dust::setElement(Plate* element)
{
  this->element = element;
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
