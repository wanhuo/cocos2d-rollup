/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * http://www.tooflya.com/development/
 *
 *
 * License: Tooflya Inc. Software License v1.
 *
 * Licensee may not use this software for commercial purposes. For the purpose of this license,
 * commercial purposes means that a 3rd party has to pay in order to access Software or that
 * the Website that runs Software is behind a paywall. In consideration of the License granted
 * under clause 2, Licensee shall pay Licensor a fee, via Credit-Card, PayPal or any other
 * mean which Licensor may deem adequate. Failure to perform payment shall construe as material
 * breach of this Agreement. This software is provided under an AS-IS basis and without any support,
 * updates or maintenance. Nothing in this Agreement shall require Licensor to provide Licensee with
 * support or fixes to any bug, failure, mis-performance or other defect in The Software.
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
Users* Users::instance;

/**
 *
 *
 *
 */
Users* Users::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Users::Users()
: Popup()
{
  instance = this;

  /**
   *
   *
   *
   */
  if(Support::shaders(SHADER_COMPLEX))
  {
    this->texture = RenderTexture::create(Application->getWidth(), Application->getHeight() - 380, Texture2D::PixelFormat::RGBA8888, GL_DEPTH24_STENCIL8);
    this->texture->setPosition(Application->getCenter());
    this->addChild(this->texture);

    this->texture->getSprite()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("@shader.opacity.vertical"));
    this->texture->getSprite()->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
    this->texture->getSprite()->getTexture()->setAntiAliasTexParameters();
  }

  /**
   *
   *
   *
   */
  this->buttons.rate = new ExtendedButton("ui/button-rate.png", 2, 1, this, std::bind(&Users::onRate, this));
  this->buttons.menu = new ExtendedButton("ui/button-menu.png", 2, 1, this, std::bind(&Users::onMenu, this));
  this->buttons.share = new ExtendedButton("ui/button-share.png", 2, 1, this, std::bind(&Users::onShare, this));
  this->buttons.services = new ExtendedButton("ui/button-services.png", 2, 1, this, std::bind(&Users::onServices, this));
  this->buttons.present = new PresentButton(this);
  this->buttons.video = new VideoButton(this);
  this->buttons.invite = new FacebookButton::Invite(this);

  /**
   *
   *
   *
   */
  this->scroll = new BackgroundScroll(this);
  this->scroll->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
  this->scroll->setBounceEnabled(true);
  this->scroll->setTouchEnabled(true);
  this->scroll->setSwallowTouches(false);
  this->scroll->setScrollBarEnabled(false);

  /**
   *
   *
   *
   */
  this->container = new Background(this->scroll);

  /**
   *
   *
   *
   */
  this->elements = new Pool(new Element, this->container);

  /**
   *
   *
   *
   */
  this->animation = new Entity("ui/animation.png", this->container);
  this->separator = new Entity("ui/separator-2.png", this->container);

  /**
   *
   *
   *
   */
  this->setScheduleUpdate(true);
}

Users::~Users()
{
}

/**
 *
 *
 *
 */
void Users::onEnter()
{
  Popup::onEnter();

  /**
   *
   *
   *
   */
  this->showButtons();

  /**
   *
   *
   *
   */
  this->elements->clear();

  /**
   *
   *
   *
   */
  this->invitations.clear();
  this->listen = false;

  /**
   *
   *
   *
   */
  this->scroll->setContentSize(Size(Application->getWidth(), Application->getHeight() - 380));
  this->scroll->getInnerContainer()->setPosition(Vec2(0, 0));
  this->scroll->setPositionY(380);

  /**
   *
   *
   *
   */
  this->container->setPosition(0, Application->getHeight() - 380);

  /**
   *
   *
   *
   */
  this->animation->_create();
  this->animation->setCameraMask(BACKGROUND);
  this->animation->setOpacity(0.0);
  this->animation->setScale(0.8);
  this->animation->setPosition(Application->getCenter().x, (Application->getHeight() - 380) / 2 - this->animation->getHeight() / 2);
  this->animation->runAction(
    RepeatForever::create(
      RotateBy::create(1.0, 360.0)
    )
  );
  this->animation->runAction(
    Spawn::create(
      EaseSineOut::create(
        ScaleTo::create(0.5, 1.0)
      ),
      EaseSineOut::create(
        FadeTo::create(0.5, 255.0)
      ),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  this->x =  100.0;
  this->y = -150.0;

  /**
   *
   *
   *
   */
  this->time = 0.0;

  /**
   *
   * @Facebook
   * | @Getting scores of user who have played this application;
   */
  Facebook::score->get([=] (vector<FacebookFriend*> elements) {
    CC_VOOP(elements)
    {
      auto current = (Element*) this->elements->_create();

      current->setPosition(this->x, this->y);
      current->setType(Element::TYPE_USER);
      current->setData(element, this->time);

      /**
       *
       *
       *
       */
      this->y -= 110;

      /**
       *
       *
       *
       */
      this->time += 0.1;
    }

    /**
     *
     *
     *
     */
    this->y += 30;

    /**
     *
     *
     *
     */
    this->separator->_create();
    this->separator->setCameraMask(BACKGROUND);
    this->separator->setPosition(Application->getCenter().x, this->y);
    this->separator->setScale(0.8);
    this->separator->setOpacity(0.0);
    this->separator->runAction(
      Sequence::create(
        DelayTime::create(this->time),
        Spawn::create(
          EaseSineOut::create(
            ScaleTo::create(0.2, 1.0)
          ),
          EaseSineOut::create(
            FadeTo::create(0.2, 255.0)
          ),
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
    this->y -= 80;

     /**
      *
      *
      *
      */
    auto size = max(Application->getHeight() - 380, abs(this->y) + 100);

     /**
      *
      *
      *
      */
    this->scroll->setInnerContainerSize(
      Size(
        Application->getWidth(),
        size
      )
    );
    this->container->setPosition(0, size);

    /**
     *
     *
     *
     */
    this->update(true);
  });
}

void Users::onExit()
{
  Popup::onExit();

  /**
   *
   *
   *
   */
  Application->changeState(Game::STATE_MENU);
}

/**
 *
 *
 *
 */
void Users::onMenu()
{
  this->hide();
}

void Users::onShare()
{
  Application->onShare(
    Application->getFrameWidth(),
    Application->getFrameHeight(),
    0,
    0,
    false,
    "", // @TODO: Add share text;
    [=] (int a) {
    }
  );
}

void Users::onRate()
{
  Application->onRate();
}

void Users::onServices()
{
  Application->onLeaderboards();
}

/**
 *
 *
 *
 */
void Users::show()
{
  Popup::show();
}

void Users::hide()
{
  Popup::hide();

  /**
   *
   *
   *
   */
  this->hideButtons();

  /**
   *
   *
   *
   */
  for(auto element : this->container->getChildren())
  {
    element->stopAllActions();
    element->runAction(
      Spawn::create(
        EaseSineIn::create(
          FadeTo::create(0.25, 0.0)
        ),
        nullptr
      )
    );
  }
}

/**
 *
 *
 *
 */
void Users::showButtons()
{
  this->buttons.menu->add(Application->getCenter().x, 200);
  this->buttons.rate->add(Application->getCenter().x - 128, 200);
  this->buttons.share->add(Application->getCenter().x - 256, 200);
  this->buttons.present->add(Application->getCenter().x + 256, 200);
  this->buttons.invite->add(Application->getCenter().x, 320);

  /**
   *
   *
   *
   */
  if(Heyzap::available(AD_TYPE_VIDEO))
  {
    this->buttons.video->add(Application->getCenter().x + 128, 200);
  }
  else
  {
    this->buttons.services->add(Application->getCenter().x + 128, 200);
  }
}

void Users::hideButtons()
{
  this->buttons.menu->remove();
  this->buttons.share->remove();
  this->buttons.rate->remove();
  this->buttons.video->remove();
  this->buttons.present->remove();
  this->buttons.services->remove();
  this->buttons.invite->remove();
}

/**
 *
 *
 *
 */
void Users::invitationsCreate(Element* element)
{
  this->invitations.push_back(element);

   /**
    *
    *
    *
    */
  this->invitationsUpdate();
}

void Users::invitationsDestroy(Element* element)
{
   this->invitations.erase(
    std::remove(
      this->invitations.begin(),
      this->invitations.end(),
      element
    ),
    this->invitations.end()
  );

   /**
    *
    *
    *
    */
  this->invitationsUpdate();
}

void Users::invitationsUpdate()
{
  this->buttons.invite->update(this->invitations.size());
}

/**
 *
 *
 *
 */
void Users::update(bool reset)
{
  this->listen = false;

  /**
   *
   *
   *
   */
  if(!reset) this->time = 0.0;

  /**
   *
   *
   *
   */
  Facebook::friends->get([=] (vector<FacebookFriend*> elements) {
    this->animation->_destroy();

    /**
     *
     *
     *
     */
    CC_VOOP(elements)
    {
      auto current = (Element*) this->elements->_create();

      current->setPosition(this->x, this->y);
      current->setType(Element::TYPE_INVITE);
      current->setData(element, this->time);

      /**
       *
       *
       *
       */
      this->y -= 110;

      /**
       *
       *
       *
       */
      this->time += 0.1;
    }

   /**
    *
    *
    *
    */
    auto size = max(Application->getHeight() - 380, abs(this->y) + 100);
    auto position = Application->getHeight() - size - 380;

    /**
     *
     *
     *
     */
    if(elements.size())
    {
      this->scroll->stopAutoScroll();
    }

     /**
      *
      *
      *
      */
    this->scroll->setInnerContainerSize(
      Size(
        Application->getWidth(),
        size
      )
    );
    auto test = (this->scroll->getInnerContainer()->getPositionY() - 110 * elements.size());
    this->scroll->getInnerContainer()->setPosition(
      Vec2(
        0.0,
        (reset ? position :  test)
      )
    );
    this->container->setPosition(0, size);

    /**
     *
     *
     *
     */
    if(elements.size() >= 10)
    {
      Application->runAction(
        Sequence::create(
          DelayTime::create(this->time),
          CallFunc::create([=] () {
            this->listen = true;
          }),
          nullptr
        )
      );

      /**
       *
       *
       *
       */
      this->animation->_create();
      this->animation->setCameraMask(BACKGROUND);
      this->animation->setOpacity(0.0);
      this->animation->setScale(0.2);
      this->animation->setPosition(Application->getCenter().x, this->y);
      this->animation->runAction(
        RepeatForever::create(
          RotateBy::create(1.0, 360.0)
        )
      );
      this->animation->runAction(
        Spawn::create(
          EaseSineOut::create(
            ScaleTo::create(0.5, 0.3)
          ),
          EaseSineOut::create(
            FadeTo::create(0.5, 255.0)
          ),
          nullptr
        )
      );
    }
  }, reset);
}

/**
 *
 *
 *
 */
void Users::update(float time)
{
  if(this->listen)
  {
    if(this->scroll->getInnerContainer()->getPositionY() > -200.0)
    {
      this->update();
    }
  }
}

void Users::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
  if(Support::shaders(SHADER_COMPLEX))
  {
    this->texture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    this->scroll->getInnerContainer()->setVisible(true);
    this->scroll->getInnerContainer()->visit(renderer, parentTransform, parentFlags);
    this->texture->end();

    /**
     *
     *
     *
     */
    this->scroll->getInnerContainer()->setVisible(false);
  }

  /**
   *
   *
   *
   */
  Popup::visit(renderer, parentTransform, parentFlags);
}
