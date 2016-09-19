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
FacebookButton::Add::Add(Node* parent, bool autocreate)
: ExtendedButton("ui/button-facebook-add.png", 2, 1, parent, std::bind(&FacebookButton::Add::onAction, this), autocreate)
{
  this->text = new Text("@facebook.add", this, TextHAlignment::LEFT, true);
  this->text->setPosition(60, this->getHeight() / 2 + 1);
  this->text->enableBold();

  this->icon = new Entity("ui/button-currency-icon.png", this, true);
  this->icon->setScale(0.6);
  this->icon->setCascadeOpacityEnabled(true);
  this->icon->setPosition(this->getWidth() - 35, this->getHeight() / 2);

  this->currency = new Text("@buttons.facebook.currency", this->icon, TextHAlignment::RIGHT, true);
  this->currency->setScale(1.6);
  this->currency->setPosition(-5, this->icon->getHeight() / 2 + 3);
  this->currency->data(50);
  this->currency->enableBold();

  /**
   *
   *
   *
   */
  this->setCascadeOpacityEnabled(true);
}

FacebookButton::Add::~Add()
{
}

/**
 *
 *
 *
 */
void FacebookButton::Add::onCreate()
{
  ExtendedButton::onCreate();
}

void FacebookButton::Add::onDestroy(bool action)
{
  ExtendedButton::onDestroy(action);
}

/**
 *
 *
 *
 */
void FacebookButton::Add::onAction()
{
  if(!Facebook::status())
  {
    ((FacebookButton::State*) Menu::getInstance()->buttons.state)->onAction();
  }
  else
  {
    Popup::popup->hide([=] () {
    Application->changeState(Game::STATE_USERS);
    });
  }
}
