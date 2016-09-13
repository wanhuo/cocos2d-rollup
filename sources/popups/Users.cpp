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
  this->texture = RenderTexture::create(Application->getWidth(), Application->getHeight() - 300, Texture2D::PixelFormat::RGBA8888, GL_DEPTH24_STENCIL8_OES);
  this->texture->setPosition(Application->getCenter());
  this->addChild(this->texture);

  this->texture->getSprite()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("@shader.opacity.vertical"));
  this->texture->getSprite()->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
  this->texture->getSprite()->getTexture()->setAntiAliasTexParameters();

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

  /**
   *
   *
   *
   */
  this->scroll = new BackgroundScroll(this);
  this->scroll->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
  this->scroll->setContentSize(Size(Application->getWidth(), Application->getHeight() - 300));
  this->scroll->setBounceEnabled(true);
  this->scroll->setTouchEnabled(true);
  this->scroll->setSwallowTouches(false);
  this->scroll->setScrollBarEnabled(false);
  this->scroll->setPositionY(300);

  /**
   *
   *
   *
   */
  this->elements = new Pool(new Element, this->scroll);

  /**
   *
   *
   *
   */
  this->loader = new Entity("ui/loader.png", this->scroll);
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
  auto position = Vec2(Application->getCenter().x, 200.0);

  /**
   *
   *
   *
   */
  this->buttons.menu->add(position.x, position.y);
  this->buttons.rate->add(position.x - 128, position.y);
  this->buttons.share->add(position.x - 256, position.y);
  this->buttons.present->add(position.x + 256, position.y);

  /**
   *
   *
   *
   */
  if(Heyzap::available(AD_TYPE_VIDEO))
  {
    this->buttons.video->add(position.x + 128, position.y);
  }
  else
  {
    this->buttons.services->add(position.x + 128, position.y);
  }

  /**
   *
   *
   *
   */
  this->scroll->setContentSize(Size(Application->getWidth(), Application->getHeight() - 300));
  this->scroll->setPositionY(300);

  /**
   *
   *
   *
   */
  this->loader->_create();
  this->loader->setCameraMask(BACKGROUND);
  this->loader->setOpacity(0.0);
  this->loader->setScale(0.8);
  this->loader->setPosition(Application->getCenter().x, (Application->getHeight() - 300 / 2) / 2);
  this->loader->runAction(
    RepeatForever::create(
      RotateBy::create(1.0, 360.0)
    )
  );
  this->loader->runAction(
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
  Facebook::friends->get([=] (vector<FacebookFriend*> elements) {
    this->loader->_destroy();

    /**
     *
     *
     *
     */
    auto x = 200.0;
    auto y = Application->getHeight() - 200;

    auto time = 0.0;

    CC_VOOP(elements)
    {
      auto el = (Element*) this->elements->_create();

      el->setPosition(x, y);
      el->setCameraMask(BACKGROUND);
      el->data(element);

      /**
       *
       *
       *
       */
      y -= 150;
    }

     /**
      *
      *
      *
      */
    auto size = max(Application->getHeight() - 300, Application->getHeight() - this->elements->last()->getPositionY() + 200);
    auto position = Application->getHeight() - size - 300;

    /**
     *
     *
     *
     */
    this->scroll->stopAutoScroll();
    this->scroll->setTouchEnabled(true);
    this->scroll->getInnerContainer()->setPosition(Vec2(0, position));

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

    /**
     *
     *
     *
     */
    for(auto element : this->scroll->getChildren())
    {
      element->setPositionY(element->getPositionY() - Application->getHeight() + size);
    }
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
  this->elements->clear();

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
  this->buttons.menu->remove();
  this->buttons.share->remove();
  this->buttons.rate->remove();
  this->buttons.video->remove();
  this->buttons.present->remove();
  this->buttons.services->remove();
}

/**
 *
 *
 *
 */
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

/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) by Igor Mats
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

Users::Element::Element()
: Entity("ui/picture-background.png")
{
  auto holder = ClippingNode::create();
  holder->setAlphaThreshold(0.05f);
  holder->setScale(0.88);
  holder->setPosition(this->getWidth() / 2, this->getHeight() / 2);
  holder->setCascadeOpacityEnabled(true);
  holder->setStencil(
    Sprite::create(this->textureFileName)
  );

  this->addChild(holder);

  /**
   *
   *
   *
   */
  this->element = new Entity(this->textureFileName, holder, true);
  this->element->setCameraMask(BACKGROUND);
}

Users::Element::~Element()
{
}

/**
 *
 *
 *
 */
void Users::Element::onEnter()
{
  Entity::onEnter();
}

void Users::Element::onExit()
{
  Entity::onExit();
}

/**
 *
 *
 *
 */
void Users::Element::onCreate()
{
  Entity::onCreate();
}

void Users::Element::onDestroy(bool action)
{
  Entity::onDestroy(action);
}

/**
 *
 *
 *
 */
void Users::Element::data(FacebookFriend* element)
{
  {
    auto request = new HttpRequest;

    /**
     *
     *
     *
     */
    request->setUrl(element->texture);
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback([=] (HttpClient* client, HttpResponse* response) {

      /**
       *
       *
       *
       */
      if(!response->isSucceed())
      {
        // @TODO: Network unreachable;
      }
      else
      {
        vector<char>* buffer = response->getResponseData();

        /**
         *
         *
         *
         */
        auto texture = new Texture2D;
        auto image = new Image;

        image->autorelease();
        image->initWithImageData(reinterpret_cast<unsigned char*>(&(buffer->front())), buffer->size());

        texture->autorelease();
        texture->initWithImage(image);

        /**
         *
         *
         *
         */
        this->element->setTexture(texture);
      }
    });

    /**
     *
     *
     *
     */
    HttpClient::getInstance()->send(request);

    /**
     *
     *
     *
     */
    request->release();
  }
}

/**
 *
 *
 *
 */
Users::Element* Users::Element::deepCopy()
{
  return new Users::Element;
}
