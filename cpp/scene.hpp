#ifndef _SCENE_HPP_
#define _SCENE_HPP_


#include "common.hpp"


class btBroadphaseInterface;
class btCollisionDispatcher;
class btCollisionShape;
class btConstraintSolver;
class btDefaultCollisionConfiguration;
class btDynamicsWorld;
class btOverlappingPairCache;
class btClock;

class Body;
class Trace;


ATTRIBUTE_ALIGNED16(class) Scene : public EventEmitter {
	
public:
	
	typedef std::vector<V8_VAR_OBJ> ObjVec;
	
	void *operator new (size_t size) { return btAlignedAlloc(size, 16); }
	void operator delete (void *ptr) { btAlignedFree(ptr); }
	
	static void init(V8_VAR_OBJ target);
	static bool isScene(V8_VAR_OBJ obj);
	
	~Scene();
	
	void _destroy();
	
	void refBody(Body* body);
	void unrefBody(Body* body);
	
	btDynamicsWorld *getWorld() { return _physWorld; }
	
	void doUpdate(float dt);
	void doUpdate();
	
	V8_VAR_OBJ doHit(const btVector3 &from, const btVector3 &to);
	ObjVec doTrace(const btVector3 &from, const btVector3 &to);
	
	
protected:
	
	Scene();
	
	static V8_STORE_FT _protoScene;
	static V8_STORE_FUNC _ctorScene;
	
	bool _isDestroyed;
	
	btClock *_clock;
	btAlignedObjectArray<Body*> _bodies;
	
	btDefaultCollisionConfiguration *_physConfig;
	btCollisionDispatcher *_physDispatcher;
	btBroadphaseInterface *_physBroadphase;
	btConstraintSolver *_physSolver;
	btDynamicsWorld *_physWorld;
	
	btVector3 _cacheGrav;
	
	
private:
	
	static NAN_METHOD(newCtor);
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_GETTER(gravityGetter);
	static NAN_SETTER(gravitySetter);
	
	static NAN_METHOD(update);
	static NAN_METHOD(hit);
	static NAN_METHOD(trace);
	
};


#endif // _SCENE_HPP_
