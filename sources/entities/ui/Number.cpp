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
Number::Number()
: Text("@counter.number", nullptr, TextHAlignment::CENTER)
{
  this->setGlobalZOrder(10);
  this->ignoreAnchorPointForPosition(true);
}

Number::~Number()
{
}

/**
 *
 *
 *
 */
void Number::onCreate()
{
  Text::onCreate();

  /**
   *
   *
   *
   */
  this->Text::data(1);
}

void Number::onDestroy(bool action)
{
  Text::onDestroy(action);
}

/**
 *
 *
 *
 */
const char* Number::data(int data)
{
  this->setScaleX(this->getScaleX() * -1.0);

  /**
   *
   *
   *
   */
  switch(data)
  {
    default:
    this->setAnchorPoint(Vec2(0.59, 0.5));
    break;
    case 1:
    this->setAnchorPoint(Vec2(0.85, 0.5));
    break;
  }

  /**
   *
   *
   *
   */
  return Text::data(data);
}

/**
 *
 *
 *
 */
Number* Number::deepCopy()
{
  return new Number;
}
