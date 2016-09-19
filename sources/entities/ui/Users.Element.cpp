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
: Entity("ui/users-element-background.png")
{
  this->element = new Entity("ui/no-picture.png", this, true);
  this->element->setPosition(this->getWidth() / 2, this->getHeight() / 2);
  this->element->setLocalZOrder(-2);
  
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

  this->buttons.add->setLocalZOrder(-1);
  this->buttons.remove->setLocalZOrder(-1);

  /**
   *
   *
   *
   */
  this->texts.name = new Text("@facebook.user.name", this, TextHAlignment::LEFT, true);
  this->texts.name->setPosition(130, this->getHeight() / 2 - 2);

  this->texts.score = new Text("@facebook.user.score", this, TextHAlignment::RIGHT, true);
  this->texts.score->setPosition(Application->getWidth() - 110, this->getHeight() / 2 - 2);

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
  Entity::onEnter();

  /**
   *
   *
   *
   */
  this->element->setTexture("ui/no-picture.png");
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
void Users::Element::onAdd()
{
  Application->counter->currency.handler->add(20, this);

  this->buttons.remove->_create();
  this->buttons.remove->setScale(0.0);
  this->buttons.remove->setRotation(90.0);
  this->buttons.remove->setOpacity(255.0);
  this->buttons.remove->runAction(
    Spawn::create(
      RotateTo::create(0.1, 0.0),
      Sequence::create(
        ScaleTo::create(0.1, 1.0),
        CallFunc::create([=] () {
        this->buttons.remove->bind(true, false);
        }),
        nullptr
      ),
      nullptr
    )
  );

  this->buttons.add->bind(false);

  /**
   *
   *
   *
   */
  Users::getInstance()->invitationsCreate(this);
}

void Users::Element::onRemove()
{
  this->buttons.remove->runAction(
    Sequence::create(
      ScaleTo::create(0.1, 0.0),
      CallFunc::create([=] () {
      this->buttons.remove->_destroy();
      }),
      nullptr
    )
  );

  this->buttons.add->bind(true, false);

  /**
   *
   *
   *
   */
  Users::getInstance()->invitationsDestroy(this);
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
          this->buttons.add->bind(false);
          this->buttons.add->bind(true, false);
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
