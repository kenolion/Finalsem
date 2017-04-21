#ifndef GAMECAMERA_H
#define GAMECAMERA_H

class GameObject;
class GameCamera
{
public:


	float getXOffset();
	float getYOffset();
	void move(float xAmt, float yAmt);
	GameCamera(float xOffset, float yOffset);
	void setXOffset(float xOffset);
	void setYOffset(float yOffset);
	void followObject(GameObject *object);
	void centerOnObject(GameObject *object);
	float offsetXdiff;
	float offsetYdiff;
	float oldYOffset;
	float oldXOffset;
	~GameCamera();
private:
	float xOffset;
	float yOffset;

	
};
#endif // !GAMECAMERA_H
