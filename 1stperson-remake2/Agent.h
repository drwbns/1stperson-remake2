/*
Copyright (c) 2010 Yunus Kara

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef Agent_H_
#define Agent_H_


class BaseController;
class AIKnowledge;
class MovableText;

//PhysX
namespace physx {
	class PxShape;
}

#include "OgreVector3.h"

namespace Ogre
{
	class SceneNode;
	class ManualObject;
}

#include "Moving.h"


class Agent : public Moving
{
	friend class World;
public:
	enum Type
	{
		AT_VIP,
		AT_GIGN
	};

	enum Race
	{
		RT_ALLY,
		RT_ENEMY
	};

protected:
	Agent(int id, Race race, Ogre::Vector3 position, float max_speed, float max_acc, float radius);
	virtual ~Agent();
	void Update() override;

public:
	virtual void orderMove(float walk, float strafe);
	virtual void orderBrake();
	virtual void orderArrive(Ogre::Vector3 pos);
	virtual void orderGoTo(Ogre::Vector3 pos);
	virtual void orderPathFollow();
	virtual void orderNextPathNode();
	virtual void Die();

	//get / set
	virtual Ogre::Vector3 GetFirePosition() = 0;

	int getID()const { return id; }
	int getRace() { return race; }
	void ChangeController(BaseController* ct);
	BaseController* getController() { return controller; }
	void add2Hp(int i);
	int getHP() { return hp; }
	bool isDead() { return dead; }

	void ShowHeadText(bool b);

	AIKnowledge* getKnowledge() { return knowledge; }
	Ogre::Vector3 *getEyePos() { return eyePos; }
	Agent* getAttacker() { return attacker; }
	void setAttacker(Agent* a) { attacker = a; }

	void setHeadText(Ogre::String s);

	float getMwaitTime() { return mWaitTime; }
	float getCwaitTime() { return cWaitTime; }
	void setWaitTime(float f) { cWaitTime = f; }
	void add2WaitTime(float f) { cWaitTime +=f; }
	float getViewRange() { return viewRange; }
	float getAttackRange() { return attackRange; }
	void setShotsFired(int i) { shotsFired = i; }
	void incShotsFired() { shotsFired++; }
	void setShotsHit(int i) { shotsHit = i; }
	void incShotsHit() { shotsHit++; }
	int getShotsFired() { return shotsFired; }
	int getShotsHit() { return shotsHit; }

	//pure
	virtual physx::PxShape* getHitBox(int i) = 0;
	virtual void SetAimMode(bool b) = 0;
	virtual void Shoot(bool first, Ogre::Vector3 trg_pos = Ogre::Vector3::ZERO) = 0;

protected:
	BaseController* controller;

	//visual
	Ogre::SceneNode* node;
	Ogre::ManualObject* lineofsight;
	Ogre::ManualObject* coverlocs;
	MovableText* headText;

	//stats & info
	AIKnowledge* knowledge;
	Type t;
	Race race;
	int id;
	int hp;
	bool dead;

	//ai helper
	Agent* attacker;
	Ogre::Vector3 *eyePos;
	float mWaitTime;
	float cWaitTime;
	float viewRange;
	float attackRange;

	//statistics
	int shotsFired;
	int shotsHit;
};

#endif