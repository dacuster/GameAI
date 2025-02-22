/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class ComponentManager : public Trackable
{
public:
	ComponentManager(Uint32 maxSize);
	~ComponentManager();

	void clear();

	PositionComponent* getPositionComponent(const ComponentID& id);
	ComponentID allocatePositionComponent(const PositionData& data = PositionComponent::getZeroPositionData(), bool shouldWrap=true);
	void deallocatePositionComponent(const ComponentID& id);

	PhysicsComponent* getPhysicsComponent(const ComponentID& id);
	ComponentID allocatePhysicsComponent(const ComponentID& positionComponentID, const PhysicsData& data = PhysicsComponent::getZeroPhysicsData());
	void deallocatePhysicsComponent(const ComponentID& id);

	SteeringComponent* getSteeringComponent(const ComponentID& id);
	ComponentID allocateSteeringComponent(const ComponentID& physicsComponentID, const SteeringData& data = SteeringComponent::getZeroSteeringData());
	void deallocateSteeringComponent(const ComponentID& id);

	void update(float elapsedTime);

private:
	std::map<ComponentID, PositionComponent*> mPositionComponentMap;
	MemoryPool mPositionPool;

	std::map<ComponentID, PhysicsComponent*> mPhysicsComponentMap;
	MemoryPool mPhysicsPool;

	std::map<ComponentID, SteeringComponent*> mSteeringComponentMap;
	MemoryPool mSteeringPool;

	static ComponentID msNextPositionComponentID;
	static ComponentID msNextPhysicsComponentID;
	static ComponentID msNextSteeringComponentID;

	void updatePhysics(float elapsedTime);
	void updateSteering(float elapsedTime);
};