/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) by Igor Mats
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
 * @cocos2d
 *
 */

#include "Game.h"

/**
 *
 *
 *
 */
FacebookButton::State::State(Node* parent, bool autocreate)
: ExtendedButton("ui/button-facebook-state.png", 2, 1, parent, std::bind(&FacebookButton::State::onAction, this), autocreate)
{
  this->text = new Text("@facebook.state.connect", this, TextHAlignment::LEFT, true);
  this->text->setPosition(60, this->getHeight() / 2 + 1);
  this->text->enableBold();

  this->icon = new Entity("ui/button-currency-icon.png", this, true);
  this->icon->setScale(0.6);
  this->icon->setCascadeOpacityEnabled(true);
  this->icon->setPosition(this->getWidth() - 35, this->getHeight() / 2);

  this->currency = new Text("@buttons.facebook.currency", this->icon, TextHAlignment::RIGHT, true);
  this->currency->setScale(1.6);
  this->currency->setPosition(-5, this->icon->getHeight() / 2 + 3);
  this->currency->data(200);
  this->currency->enableBold();

  /**
   *
   *
   *
   */
  this->setCascadeOpacityEnabled(true);
}

FacebookButton::State::~State()
{
}

/**
 *
 *
 *
 */
void FacebookButton::State::onCreate()
{
  ExtendedButton::onCreate();

  /**
   *
   *
   *
   */
  if(!Facebook::status())
  {
    this->text->setText("@facebook.state.connect");

    if(!Storage::get("@facebook.currency"))
    {
      this->currency->_create();
      this->icon->_create();
    }
  }
  else
  {
    this->text->setText("@facebook.state.disconnect");

    this->currency->_destroy();
    this->icon->_destroy();
  }
}

void FacebookButton::State::onDestroy(bool action)
{
  ExtendedButton::onDestroy(action);
}

/**
 *
 *
 *
 */
void FacebookButton::State::onAction()
{
  if(!Facebook::status())
  {
    Facebook::connect([=] (bool state) {
      if(state)
      {
        if(!Storage::get("@facebook.currency"))
        {
          Application->counter->currency.handler->add(200, this);

          /**
           *
           *
           *
           */
          Storage::set("@facebook.currency", true);
        }
      }

      /**
       *
       *
       *
       */
      this->onCreate();
    });
  }
  else
  {
    Facebook::disconnect();

    /**
     *
     *
     *
     */
    this->onCreate();
  }
}
