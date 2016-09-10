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
ExtendedButton::ExtendedButton(const char* textureFileName, int horizontalFramesCount, int verticalFramesCount, Node* parent, const function<void()>& action, bool autocreate)
: Button(textureFileName, horizontalFramesCount, verticalFramesCount, parent, action, autocreate)
{
  this->bind(false);
}

ExtendedButton::~ExtendedButton()
{
}

/**
 *
 *
 *
 */
void ExtendedButton::onEnter()
{
  Button::onEnter();

  /**
   *
   *
   *
   */
  this->setScale(0.8);
  this->setOpacity(0.0);
  this->setRotation(0.0);
}

void ExtendedButton::onExit()
{
  Button::onExit();
}

/**
 *
 *
 *
 */
void ExtendedButton::onCreate()
{
  Button::onCreate();
}

void ExtendedButton::onDestroy(bool action)
{
  Button::onDestroy(action);
}

/**
 *
 *
 *
 */
void ExtendedButton::onAdd()
{
  this->bind(true);
}

void ExtendedButton::onRemove()
{
  this->bind(false);
}

/**
 *
 *
 *
 */
void ExtendedButton::add(float x, float y)
{
  if(!this->state->create)
  {
    this->_create()->stopAllActions();

    /**
     *
     *
     *
     */
    if(x || y)
    {
      this->setPosition(x, y);
    }

    /**
     *
     *
     *
     */
    this->runAction(
      Spawn::create(
        EaseSineOut::create(
          ScaleTo::create(0.5, 1.0)
        ),
        Sequence::create(
          EaseSineOut::create(
            FadeTo::create(0.5, 255.0)
          ),
          CallFunc::create([=] () {

            /**
             *
             *
             *
             */
            this->onAdd();
          }),
          nullptr
        ),
        nullptr
      )
    );
  }
}

void ExtendedButton::remove(bool action)
{
  if(this->state->create)
  {
    this->onRemove();

    /**
     *
     *
     *
     */
    this->runAction(
      Spawn::create(
        EaseSineIn::create(
          ScaleTo::create(0.5, 0.8)
        ),
        Sequence::create(
          EaseSineIn::create(
            FadeTo::create(0.5 - 0.1, 0.0)
          ),
          CallFunc::create([=] () {

            /**
             *
             *
             *
             */
            this->_destroy(action);
          }),
          nullptr
        ),
        nullptr
      )
    );
  }
}
