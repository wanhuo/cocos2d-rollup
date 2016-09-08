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
SoundButton::SoundButton(Node* parent, bool autocreate)
: ExtendedButton("ui/button-sound-1.png", 2, 1, parent, std::bind(&SoundButton::updateState, this, true), autocreate)
{
}

SoundButton::~SoundButton()
{
}

/**
 *
 *
 *
 */
void SoundButton::onCreate()
{
  ExtendedButton::onCreate();
}

void SoundButton::onDestroy(bool action)
{
  ExtendedButton::onDestroy(action);
}

/**
 *
 *
 *
 */
void SoundButton::onEnter()
{
  ExtendedButton::onEnter();

  /**
   *
   *
   *
   */
  this->updateState();
}

void SoundButton::onExit()
{
  ExtendedButton::onExit();
}

/**
 *
 *
 *
 */
void SoundButton::updateState(bool state)
{
  if(state)
  {
    Music->changeState();
    Sound->changeState();
  }

  /**
   *
   *
   *
   */
  if(Music->enabled || Sound->enabled)
  {
    this->setTexture("ui/button-sound-1.png");
  }
  else
  {
    this->setTexture("ui/button-sound-2.png");
  }

  /**
   *
   *
   *
   */
  this->updateTexturePoistion();

  /**
   *
   *
   *
   */
  this->setCurrentFrameIndex(0);
}
