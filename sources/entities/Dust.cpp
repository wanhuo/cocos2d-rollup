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

  this->setScale(0.005 * 0.2);
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

  /**
   *
   *
   *
   */
  //this->setOpacity(255);

  /**
   *
   *
   *
   */
  this->runAction(
    Spawn::create(
      Sequence::create(
        FadeTo::create(0.5, random(100, 200)),
        FadeTo::create(0.5, 0),
        CallFunc::create([=] () {
        this->_destroy();
        }),
        nullptr
      ),
      Sequence::create(
        MoveBy::create(1.0, Vec3(0.0, random(2.0, 10.0), 0.0)),
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
Dust* Dust::deepCopy()
{
  return new Dust;
}
