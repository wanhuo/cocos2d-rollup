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
TimeButton::TimeButton(const char* textureFileName, int horizontalFramesCount, int verticalFramesCount, Node* parent, const function<void()>& action, bool autocreate)
: Button(textureFileName, horizontalFramesCount, verticalFramesCount, parent, action, autocreate)
{
  this->text = new Text("test", this);
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
  Button::onCreate();
}

void TimeButton::onDestroy(bool action)
{
  Button::onDestroy(action);
}

/**
 *
 *
 *
 */
void TimeButton::onEnter()
{
  Button::onEnter();

  /**
   *
   *
   *
   */
  this->updateState();
}

void TimeButton::onExit()
{
  Button::onExit();
}

/**
 *
 *
 *
 */
void TimeButton::onNormal()
{
  this->text->_destroy();
}

void TimeButton::onWait()
{
  this->text->_create();

  if(this->time - Times::now() < 0)
  {
    this->updateTime();
  }
}

/**
 *
 *
 *
 */
void TimeButton::changeState(int state)
{
  if(this->state != state)
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
  }
}

/**
 *
 *
 *
 */
void TimeButton::updateState()
{
  this->time = Times::parse(Storage::get(this->id, true));

  /**
   *
   *
   *
   */
  if(this->time - Times::now() < 0)
  {
    this->changeState(STATE_NORMAL);
  }
  {
    this->changeState(STATE_WAIT);
  }
}

void TimeButton::updateTime()
{
  this->time = Times::now() + Times::minute() * 1;
  Storage::set(this->id, convert(this->time));
}

/**
 *
 *
 *
 */
void TimeButton::update(float time)
{
  Button::update(time);

  /**
   *
   *
   *
   */
  switch(this->state)
  {
    case STATE_WAIT:
    if(this->time - Times::now() > 0)
    {
      auto data = Times::format(this->time - Times::now());

      /**
       *
       *
       *
       */
      this->text->data(data.m, data.s, 0);
    }
    else
    {
      this->changeState(STATE_NORMAL);
    }
    break;
  }
}
