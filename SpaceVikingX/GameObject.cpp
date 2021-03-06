//
//  GameObject.cpp
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#include "GameObject.h"
bool GameObject::init(){
    bool bRet = false;
    bRet = true;// CCSprite::init();
    if (bRet) {
        CCLOG("GameObject init");
        screenSize = CCDirector::sharedDirector()->getWinSize();
        isActive = true;
        gameObjectType = kObjectTypeNone;
        return bRet;
    }
    return bRet;
}


void GameObject::changeState(CharacterStates newState) {
    //CCLOG("GameObject->changeState method should be overriden");
}

void GameObject::updateStateWithDeltaTime(float deltaTime, CCArray *listOfGameObjects) {
    //CCLOG("updateStateWithDeltaTime method should be overriden");
}

CCRect GameObject::adjustedBoundingBox() {
    //CCLOG("GameObect adjustedBoundingBox should be overriden");
    return  boundingBox();
}
CCAnimation* GameObject::loadPlistForAnimationWithName(string animationName ,string className) {
    
    CCAnimation *animationToReturn = NULL;
    
    string fullFileName = className.substr(2)+".plist";
    CCLog("fullname:%s",fullFileName.c_str());
    const char* f=fullFileName.c_str();
   const char* fullPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(f).c_str();
    
    CCDictionary *plistDictionary = CCDictionary::createWithContentsOfFileThreadSafe(fullPath);
    
    if (plistDictionary == NULL) {
        CCLOG("Error reading plist: %s.plist", className.c_str());
        return NULL; // No Plist Dictionary or file found
    }
    
    CCDictionary *animationSettings =
    static_cast<CCDictionary*>( plistDictionary->objectForKey(animationName));
    if (animationSettings == NULL) {
        CCLOG("Could not locate AnimationWithName:%s",animationName.c_str());
        return NULL;
    }
    
    float animationDelay = animationSettings->valueForKey("delay")->floatValue();
    
    animationToReturn = CCAnimation::create();
    animationToReturn->setDelayPerUnit(animationDelay);
    
    
    //    CCDictionary *framesDict = static_cast<CCDictionary*> (plistDictionary->objectForKey("frames"));
    //
    //    CCArray *keys = framesDict->allKeys();
    //
    //    for (int i = 0 ; i < keys->count(); ++i)
    //    {
    //        CCString *spriteFileName = static_cast<CCString *> (keys->objectAtIndex(i));
    //        CCSpriteFrame* sprite =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFileName->getCString());
    //        mAnimation->addSpriteFrame(sprite);
    //
    //    }
    
    
    // 6: Add the frames to the animation
    string animationFramePrefix =
    animationSettings->valueForKey("filenamePrefix")->m_sString;
    string  animationFrames =
    animationSettings->valueForKey("animationFrames")->m_sString;
    
    char *strArr=new char[animationFrames.size()+1];
    strArr[animationFrames.size()]=0;
    memcpy(strArr,animationFrames.c_str(),animationFrames.size());
    
    
    const char* p;
    for (p = strtok(strArr, "," );  p;  p = strtok( NULL, "," ))
    {
        
        //       char* frameNumber = *p;
        string frameName = animationFramePrefix+p+".png";
        
        CCSpriteFrame* sprite =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
        animationToReturn->addSpriteFrame(sprite);
        
    }
    
    
    return animationToReturn;
}
GameObject:: ~GameObject(){
    
}