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
AnnounceButton::AnnounceButton(Node* parent, const function<void()>& action, int type, bool autocreate)
: ExtendedButton(type == TYPE_SMALL ? "ui/button-announce-1.png" : "ui/button-announce-2.png", 2, 1, parent, action, autocreate)
{
  this->type = type;

  /**
   *
   *
   *
   */
  switch(this->type)
  {
    case TYPE_SMALL:
    this->icon = new Entity("ui/button-currency-icon.png", this, true);
    this->icon->setScale(0.5);

    this->text = new Text("@buttons.currency", this, true);

    this->text->data(50);
    this->text->setPosition(this->getWidth() / 2 - this->icon->getWidthScaled() / 2 - 2.0, this->getHeight() / 2 - 27);
    this->icon->setPosition(this->text->getPositionX() + this->text->getWidth() / 2 + this->icon->getWidthScaled() / 2 + 2.0, this->getHeight() / 2 - 30);
    break;
    case TYPE_LARGE:
    this->text = new Text("@buttons.announce", this, TextHAlignment::LEFT, true);
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
    break;
  }

  /**
   *
   *
   *
   */
  this->setCascadeOpacityEnabled(true);
}

AnnounceButton::~AnnounceButton()
{
}

/**
 *
 *
 *
 */
void AnnounceButton::onCreate()
{
  ExtendedButton::onCreate();
}

void AnnounceButton::onDestroy(bool action)
{
  ExtendedButton::onDestroy(action);
}

/**
 *
 *
 *
 */
void AnnounceButton::onAction()
{
  this->action();
}
