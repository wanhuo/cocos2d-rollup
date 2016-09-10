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
AnnounceButton::AnnounceButton(Node* parent, const function<void()>& action, bool autocreate)
: ExtendedButton("ui/button-announce.png", 2, 1, parent, action, autocreate)
{
  this->icon = new Entity("ui/button-currency-icon.png", this, true);
  this->icon->setScale(0.5);

  this->text = new Text("@buttons.currency", this, true);

  this->text->data(50);
  this->text->setPosition(this->getWidth() / 2 - this->icon->getWidthScaled() / 2 - 2.0, this->getHeight() / 2 - 27);
  this->icon->setPosition(this->text->getPositionX() + this->text->getWidth() / 2 + this->icon->getWidthScaled() / 2 + 2.0, this->getHeight() / 2 - 30);

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
