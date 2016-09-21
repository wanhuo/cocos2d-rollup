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
FacebookButton::Invite::Invite(Node* parent, bool autocreate)
: ExtendedButton("ui/button-facebook-invite.png", 2, 1, parent, std::bind(&FacebookButton::Invite::onAction, this), autocreate)
{
  this->text = new Text("@facebook.invite", this, TextHAlignment::LEFT, true);
  this->text->setPosition(60, this->getHeight() / 2 + 1);
  this->text->enableBold();

  this->icon = new Entity("ui/button-currency-icon.png", this, true);
  this->icon->setScale(0.6);
  this->icon->setCascadeOpacityEnabled(true);
  this->icon->setPosition(this->getWidth() - 35, this->getHeight() / 2);

  this->currency = new Text("@buttons.facebook.currency", this->icon, TextHAlignment::RIGHT, true);
  this->currency->setScale(1.6);
  this->currency->setPosition(-5, this->icon->getHeight() / 2 + 3);
  this->currency->enableBold();

  /**
   *
   *
   *
   */
  this->setCascadeOpacityEnabled(true);
}

FacebookButton::Invite::~Invite()
{
}

/**
 *
 *
 *
 */
void FacebookButton::Invite::onCreate()
{
  ExtendedButton::onCreate();
}

void FacebookButton::Invite::onDestroy(bool action)
{
  ExtendedButton::onDestroy(action);
}

/**
 *
 *
 *
 */
void FacebookButton::Invite::onEnter()
{
  ExtendedButton::onEnter();

  /**
   *
   *
   *
   */
  this->update(0);
}

void FacebookButton::Invite::onExit()
{
  ExtendedButton::onExit();
}

/**
 *
 *
 *
 */
void FacebookButton::Invite::onAdd()
{
  ExtendedButton::onAdd();

  /**
   *
   *
   *
   */
  this->update(0);
}

void FacebookButton::Invite::onRemove()
{
  ExtendedButton::onRemove();
}

/**
 *
 *
 *
 */
void FacebookButton::Invite::onAction()
{
}

/**
 *
 *
 *
 */
void FacebookButton::Invite::update(unsigned long count)
{
  this->currency->data(count * 5);

  /**
   *
   *
   *
   */
  if(count > 0)
  {
    this->bind(true);
    this->stopAllActions();
    this->runAction(
      FadeTo::create(0.1, 255)
    );
  }
  else
  {
    this->bind(false);
    this->stopAllActions();
    this->runAction(
      FadeTo::create(0.1, 100)
    );
  }
}
