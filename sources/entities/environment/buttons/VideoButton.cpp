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
VideoButton::VideoButton(Node* parent, bool autocreate)
: TimeButton("ui/button-video.png", 2, 1, parent, autocreate)
{
  this->id = "timers.time.video";
}

VideoButton::~VideoButton()
{
}

/**
 *
 *
 *
 */
void VideoButton::onNormal()
{
  TimeButton::onNormal();

  /**
   *
   *
   *
   */
  this->text->_create();
  this->text->setText("@buttons.currency");
  this->text->data(100);
  this->text->setOpacity(0);
  this->text->runAction(
    Sequence::create(
      FadeTo::create(0.5, 255),
      DelayTime::create(5.5),
      nullptr
    ),
    1
  );

  /**
   *
   *
   *
   */
  this->icon->_create();
  this->icon->setOpacity(0);
  this->icon->runAction(
    Sequence::create(
      FadeTo::create(0.5, 255),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  this->text->setPosition(this->getWidth() / 2 - this->icon->getWidthScaled() / 2 - 2.0, this->getHeight() / 2 - 19);
  this->icon->setPosition(this->text->getPositionX() + this->text->getWidth() / 2 + this->icon->getWidthScaled() / 2 + 2.0, this->getHeight() / 2 - 22);
}

void VideoButton::onWait()
{
  TimeButton::onWait();
}

/**
 *
 *
 *
 */
void VideoButton::onAction()
{
  TimeButton::onAction(100, Menu::getInstance()->buttons.video);

  /**
   *
   *
   *
   */
  this->updateTime(1);
}
