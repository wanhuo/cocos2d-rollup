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
UnlockButton::UnlockButton(Node* parent)
: Button("ui/button-unlock.png", 3, 1, parent, std::bind(&UnlockButton::onAction, this))
{
}

UnlockButton::~UnlockButton()
{
}

/**
 *
 *
 *
 */
void UnlockButton::onCreate()
{
  Button::onCreate();

  /**
   *
   *
   *
   */
  this->setPosition(Application->getCenter());
  this->setCurrentFrameIndex(0);
  this->setScale(0);
  this->setOpacity(0);

  /**
   *
   *
   *
   */
  this->bind(true);

  /**
   *
   *
   *
   */
  this->runAction(
    Sequence::create(
      CallFunc::create([=] () {

      /**
       *
       *
       *
       */
      auto count = random(2, 5);
      auto d = random(0.5, 2.0);
      auto time = 0.1;

      /**
       *
       *
       *
       */
      this->runAction(
        RepeatForever::create(
          Spawn::create(
            Sequence::create(
              DelayTime::create(d),
              Repeat::create(
                Sequence::create(
                  EaseSineIn::create(
                    RotateTo::create(time, -15.0)
                  ),
                  EaseSineIn::create(
                    RotateTo::create(time, 15.0)
                  ),
                  nullptr
                ),
                count
              ),
              EaseSineIn::create(
                RotateTo::create(time, 0.0)
              ),
              nullptr
            ),
            Sequence::create(
              DelayTime::create(d),
              ScaleTo::create(time * (count + 1) * 2, 1.1),
              ScaleTo::create(time, 1.0),
              nullptr
            ),
            nullptr
            )
          )
        );
      }),
      nullptr
    )
  );

  this->runAction(
    Spawn::create(
      EaseSineIn::create(
        ScaleTo::create(0.5, 1.0)
      ),
      EaseSineIn::create(
        FadeTo::create(0.5, 255.0)
      ),
      nullptr
    )
  );
}

void UnlockButton::onDestroy(bool action)
{
  Button::onDestroy(action);
}

/**
 *
 *
 *
 */
void UnlockButton::onAction()
{
  this->stopAllActions();

  this->runAction(
    Spawn::create(
      RotateTo::create(0.1, 0.0),
      ScaleTo::create(0.1, 1.0),
      Sequence::create(
        DelayTime::create(0.1),
        Repeat::create(
          Sequence::create(
            ScaleTo::create(0.05, 1.2),
            ScaleTo::create(0.05, 1.0),
            nullptr
          ),
          10
        ),
        CallFunc::create([=] () {
        Application->environment->clear->runAction(
          Sequence::create(
            FadeTo::create(0.1, 255),
            CallFunc::create([=] () {

              /**
               *
               *
               *
               */
              this->setCurrentFrameIndex(2);

              /**
               *
               *
               *
               */
              Unlock::getInstance()->showButtons();
            }),
            FadeTo::create(0.3, 0),
            nullptr
          )
        );
        }),
        nullptr
      ),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  this->bind(false);
}
