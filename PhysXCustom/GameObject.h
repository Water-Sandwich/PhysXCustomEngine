#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

//ALL GAMEOBJECTS MUST BE CREATED WITH "new"!!!
class GameObject {
public:
	//called every frame
	virtual void Update(float deltaTime) {};

	//code to render just the object
	inline virtual void Render() { };

	//mark object for addition
	virtual void AddThis();

	//mark object for deletion
	virtual void DeleteThis();

	virtual ~GameObject();
};

#endif