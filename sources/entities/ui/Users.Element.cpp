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

#include "Game.h"

/**
 *
 *
 *
 */
Users::Element::Element()
: TiledEntity("ui/users-element-background.png", 2, 1)
{
  this->element = new Entity("ui/no-picture.png", this, true);
  this->element->setPosition(this->getWidth() / 2, this->getHeight() / 2);
  
  if(Support::shaders(SHADER_SIMPLE))
  {
    this->element->setGLProgram(
      GLProgramCache::getInstance()->getGLProgram("@shader.main.mask")
    );
  }

  this->buttons.add = new ExtendedButton("ui/users-element-add.png", 2, 1, this, std::bind(&Users::Element::onAdd, this));
  this->buttons.remove = new ExtendedButton("ui/users-element-remove.png", 2, 1, this, std::bind(&Users::Element::onRemove, this));

  this->buttons.add->setPosition(this->getWidth() / 2, this->getHeight() / 2);
  this->buttons.remove->setPosition(this->getWidth() / 2, this->getHeight() / 2);

  /**
   *
   *
   *
   */
  this->texts.name = new Text("@facebook.user.name", this, TextHAlignment::LEFT, true);
  this->texts.name->setPosition(130, this->getHeight() / 2 - 5);
  this->texts.name->enableBold();

  this->texts.score = new Text("@facebook.user.score", this, TextHAlignment::RIGHT, true);
  this->texts.score->setPosition(Application->getWidth() - 110, this->getHeight() / 2 - 5);
  this->texts.score->enableBold();

  /**
   *
   *
   *
   */
  this->setCascadeOpacityEnabled(true);
  this->setCameraMask(BACKGROUND);
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
  TiledEntity::onEnter();

  /**
   *
   *
   *
   */
  this->element->setTexture("ui/no-picture.png");
}

void Users::Element::onExit()
{
  TiledEntity::onExit();
}

/**
 *
 *
 *
 */
void Users::Element::onCreate()
{
  TiledEntity::onCreate();
}

void Users::Element::onDestroy(bool action)
{
  TiledEntity::onDestroy(action);
}

/**
 *
 *
 *
 */
void Users::Element::onAdd()
{
  this->buttons.add->runAction(
    Sequence::create(
      FadeTo::create(0.1, 0),
      CallFunc::create([=] () {
      this->buttons.add->_destroy();
      this->buttons.remove->add();
      }),
      nullptr
    )
  );
}

void Users::Element::onRemove()
{
  this->buttons.remove->runAction(
    Sequence::create(
      FadeTo::create(0.1, 0),
      CallFunc::create([=] () {
      this->buttons.remove->_destroy();
      this->buttons.add->add();
      }),
      nullptr
    )
  );
}

/**
 *
 *
 *
 */
void Users::Element::setType(int type)
{
  this->type = type;

  /**
   *
   *
   *
   */
  this->buttons.add->_destroy();
  this->buttons.remove->_destroy();

  /**
   *
   *
   *
   */
  switch(this->type)
  {
    case TYPE_USER:
    this->texts.score->_create();
    this->texts.score->setCameraMask(BACKGROUND);
    break;
    case TYPE_INVITE:
    this->texts.score->_destroy();
    break;
  }
}

void Users::Element::setData(FacebookFriend* element, float time)
{
  this->texts.name->data(element->name);
  this->texts.score->data(element->score);

  /**
   *
   *
   *
   */
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

  /**
   *
   *
   *
   */
  this->setOpacity(0.0);
  this->setScale(1.0);

  this->runAction(
    Sequence::create(
      DelayTime::create(time),
      Spawn::create(
        Sequence::create(
          EaseSineOut::create(
            FadeTo::create(0.5, 255.0)
          ),
          CallFunc::create([=] () {
          }),
          nullptr
        ),
        nullptr
      ),
      nullptr
    )
  );

  switch(this->type)
  {
    case TYPE_USER:
    break;
    case TYPE_INVITE:
    this->buttons.add->add();
    break;
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
