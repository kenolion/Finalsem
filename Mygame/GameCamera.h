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
	void centerOnObject(GameObject *object);
	~GameCamera();
private:
	float xOffset;
	float yOffset;

	
};
#endif // !GAMECAMERA_H
