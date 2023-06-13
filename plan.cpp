#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
#include <vector>
#include <time.h>
#include <stdlib.h>

using namespace std;
using namespace sf;

//상수 처리 변경 필요
#define BLUE_CAN	8
#define RED_CAN		7
#define GOLD_CAN	4

class Score;

//고양이 클래스
class Cat
{
private:
	Vector2f position;
	float startPosX = 0;
	float startPosY = 0;
	Vector2f velocity;
	float gravity;
	bool isJumping;
	bool isFalling;
	Texture texture;
	Sprite sprite;

	// 떨어지는 동작에 대한 변수들
	float fallSpeed;
	float rotationSpeed;
	float rotation;
public:
	Cat(float x, float y)
		: position(x, y), velocity(0.f, 0.f), gravity(500.f), isJumping(false), isFalling(false)
	{
		texture.loadFromFile("./Data/Image/cat.png");
		Vector2u catTextureSize = texture.getSize();
		sprite.setTexture(texture);
		sprite.setScale(0.07f, 0.07f);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2); //가운데를 중심점으로 설정
		sprite.setPosition(position);
	}

	Vector2f getPosition() {
		return sprite.getPosition();
	}
	int getPositionX() {
		return (int)sprite.getPosition().x;
	}
	int getPositionY() {
		return (int)sprite.getPosition().y;
	}
	void setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;

		sprite.setPosition(position);
	}

	float getStartPositionX() {
		return startPosX;
	}
	float getStartPositionY() {
		return startPosY;
	}
	void setStartPosition(float x, float y) {
		startPosX = x;
		startPosY = y;
	}

	Vector2f getVelocity() {
		return velocity;
	}
	void setVelocity(Vector2f v) {
		velocity = v;
	}
	void setVelocityX(float velX) {
		velocity.x = velX;
	}
	void setVelocityY(float velY) {
		velocity.y = velY;
	}

	float getTextureSizeX() {
		return (float)texture.getSize().x;
	}
	float getTextureSizeY() {
		return (float)texture.getSize().y;
	}

	float getGravity() {
		return gravity;
	}
	 
	bool getIsJumping() {
		return isJumping;
	}
	void setIsJumping(bool Jumping) {
		isJumping = Jumping;
	}

	bool getIsFalling() {
		return isFalling;
	}
	void setIsFalling(bool isfalling) {
		isFalling = isfalling;
	}

	void setRotation(int a) {
		sprite.setRotation((float)a);
	}

	Vector2f getScale() {
		return sprite.getScale();
	}
	void setScale(float factorX, float factorY) {
		sprite.setScale((float)factorX, (float)factorY);
	}

	void changeImage(string path) {
		texture.loadFromFile(path);
	}

	void jump(Vector2f jumpVelocity)
	{
		velocity = jumpVelocity;
		isJumping = true;
		isFalling = false;
	}

	void startFalling(float speed, float rotateSpeed)
	{
		fallSpeed = speed;
		rotationSpeed = rotateSpeed;
		isJumping = false;
		isFalling = true;
		velocity = Vector2f(0, speed);
		rotation = 0.f;
	}

	void rotateAndFall(float rotateSpeed, float fallSpeed, float deltaTime)
	{
		sprite.setRotation(sprite.getRotation() + rotateSpeed * deltaTime);
		sprite.move(0.f, fallSpeed * deltaTime);
	}

	void update(float deltaTime)
	{
		if (isJumping)
		{
			// 위치 업데이트
			position += velocity * deltaTime;
			velocity.y += gravity * deltaTime;

			// 화면 경계 체크
			if (position.x - sprite.getGlobalBounds().width / 2 <= 0.f) //왼쪽 경계에 닿으면
			{
				velocity.x = -velocity.x;
				if (sprite.getScale().x < 0) //고양이가 왼쪽을 향해 있으면
					sprite.setScale(-sprite.getScale().x, sprite.getScale().y); // 이미지를 좌우 반전
			}
			else if (position.x + sprite.getGlobalBounds().width / 2 >= 1940.f) //오른쪽 경계에 닿으면
			{
				velocity.x = -velocity.x;
				if (sprite.getScale().x > 0) //고양이가 오른쪽을 향해 있으면
					sprite.setScale(-sprite.getScale().x, sprite.getScale().y); // 이미지를 좌우 반전
			}

			if (position.y - sprite.getGlobalBounds().height / 2 <= 0.f || position.y + sprite.getGlobalBounds().height / 2 >= 540.f)
			{
				velocity.y = -(velocity.y + 10);
			}

			sprite.setPosition(position);

			if (position.y >= 600.f) // 고양이가 바닥에 닿으면
			{
				isFalling = false;
				velocity = Vector2f(0.f, 0.f);
				sprite.setRotation(0.f);
			}
		}
		else if (isFalling)
		{
			rotateAndFall(rotationSpeed, fallSpeed, deltaTime);
		}
	}

	void draw(RenderWindow& window)
	{
		// 고양이 그리기
		window.draw(sprite);
	}

	FloatRect getBounds() const
	{
		return sprite.getGlobalBounds();
	}
};

//포물선 클래스
class Arc
{
	//각도와 파워에 따라 포물선 조절(*파워게이지 따로 안 만들어도 됨)
private:
	CircleShape arc;
	//위치좌표, 크기, 각도
	float posX;
	float posY;
	float startArcPosX = 0;
	float startArcPosY = 0;
	float radius;

	Vector2f velocity;
	Vector2f startArcVelocity;
	float velocityX;
	float velocityY;
	float acceleration;

	Color color;

public:
	//생성자, 소멸자
	Arc(float x, float y, float r)
	{
		posX = x;
		posY = y;
		radius = r;

		velocityX = 0;
		velocityY = 0;
		velocity.x = velocityX;
		velocity.y = velocityY;
		acceleration = 0;

		arc.setPosition(posX, posY);
		arc.setRadius(radius);
		arc.setFillColor(color.Red);
	}

	CircleShape getArc()
	{
		return arc;
	}

	//위치좌표, 크기, 각도 setter/getter
	void setArcPos(float x, float y)
	{
		posX = x;
		posY = y;
	}
	float getArcPosX()
	{
		return posX;
	}
	float getArcPosY()
	{
		return posY;
	}
	void setRadius(float r)
	{
		radius = r;
	}
	float getRadius()
	{
		return radius;
	}

	void setArcVelocity(Vector2f jumpVelocity)
	{
		velocity = jumpVelocity;
	}
	Vector2f getArcVelocity()
	{
		return velocity;
	}

	void setArcVelocityX(float v_x)
	{
		velocityX = v_x;
		velocity.x = velocityX;
	}
	float getArcVelocityX()
	{
		return velocity.x;
	}

	void setArcVelocityY(float v_y)
	{
		velocityY = v_y;
		velocity.y = velocityY;
	}
	float getArcVelocityY()
	{
		return velocity.y;
	}

	void setArcAcceleration(float a)
	{
		acceleration = a;
	}
	float getArcAcceleration()
	{
		return acceleration;
	}

	void setStartArcPosition(float x, float y)
	{
		startArcPosX = x;
		startArcPosY = y;
	}
	float getStartArcPositionX()
	{
		return startArcPosX;
	}
	float getStartArcPositionY()
	{
		return startArcPosY;
	}

	void setStartArcVelocity(Vector2f startVelocity)
	{
		startArcVelocity = startVelocity;
	}
	Vector2f getStartArcVelocity()
	{
		return startArcVelocity;
	}

	//이동(move)
	void moveArc(float dt)
	{
		setArcPos(getArcPosX() + getArcVelocityX() * dt, getArcPosY() + getArcVelocityY() * dt);
		setArcVelocityY(getArcVelocityY() + getArcAcceleration() * dt);

		arc.setPosition(getArcPosX(), getArcPosY());
	}
};

//통조림 클래스
class Canned_Food
{
	//직사각형으로 구현하면 좋을 듯

private:
	//변수(필드)
	//위치좌표, 크기

	Vector2f position;
	Texture texture;
	Sprite sprite;

	//double posX;
	//double posY;
	double sizeX;
	double sizeY;

	int sp;

public:
	//함수(메소드)
	//생성자, 소멸자
	Canned_Food() {}
	void setinfo(float x, float y, int sp)
	{
		position.x = x;
		position.y = y;
		//캔 스프라이트 생성
		this->sp = sp;
		if (sp == 1)
			texture.loadFromFile("./Data/Image/canned_food.png"); // 파랑 캔
		else if (sp == 2)
			texture.loadFromFile("./Data/Image/canned_food_red.png"); // 빨간 캔
		else if (sp == 3)
			texture.loadFromFile("./Data/Image/canned_food_gold.png"); // 금색 캔
		Vector2u textureSize = texture.getSize();
		sprite.setTexture(texture);
		sprite.setScale((float)50 / textureSize.x, (float)50 / textureSize.y);
		sprite.setPosition(position);
	}
	~Canned_Food()
	{

	}
	//위치좌표, 크기 setter/getter
	void setFoodPos(double posX, double posY)
	{
		position.x = posX;
		position.y = posY;
	}
	int getPosition()
	{
		return position.x;
	}
	void setFoodSize(double sizeX, double sizeY)
	{
		this->sizeX = sizeX;
		this->sizeY = sizeY;
	}
	double getFoodSizeX()
	{
		return this->sizeX;
	}
	double getFoodSizeY()
	{
		return this->sizeY;
	}
	int getsp()
	{
		return this->sp;
	}
	Sprite* getsprite()
	{
		return &sprite;
	}

	//충돌 시 획득
	void getFoodScore(Score* score, int size);

	//충돌, 획득 시 visual,sound effect
	//획득시 제거

	void draw(RenderWindow& window)
	{
		window.draw(sprite);
	}

	FloatRect getBounds() const
	{
		return sprite.getGlobalBounds();
	}
};

class Floodlight
{
private:
	Vector2f position;
	bool isMovingRight;
	Texture texture;
	Sprite sprite;

public:
	Floodlight(float x, float y)
		: position(x, y), isMovingRight(true)
	{
		texture.loadFromFile("./Data/Image/floodlight.png");
		Vector2u lightTextureSize = texture.getSize();
		sprite.setTexture(texture);
		sprite.setScale((float)113.4 / lightTextureSize.x, (float)107.5 / lightTextureSize.y);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, 0); //윗변 가운데를 중심점으로 설정 
		sprite.setPosition(position);
	}

	void swing()
	{
		if (isMovingRight)
		{
			sprite.setRotation(sprite.getRotation() - 1);
			if (sprite.getRotation() == 270)
				isMovingRight = false;
		}
		else
		{
			sprite.setRotation(sprite.getRotation() + 1);
			if (sprite.getRotation() == 90)
				isMovingRight = true;
		}
	}

	void draw(RenderWindow& window)
	{
		window.draw(sprite);
	}

	FloatRect getBounds() const
	{
		return sprite.getGlobalBounds();
	}
};

//장애물1 클래스(새장,전등,컵,그릇,다른 고양이 등)
class Obstacle1
{
	//장애물 여러 개 만들 때 상속으로 구현할지 논의 필요
	//직사각형으로 구현하면 좋을 듯

private:
	//변수(필드)
	//위치좌표, 크기
	double posX;
	double posY;
	double sizeX;
	double sizeY;
	//장애물이 움직이지 않고 고정됨

public:
	//함수(메소드)
	//생성자, 소멸자
	Obstacle1() {
		posX = 100;
		posY = 200;
		sizeX = 40;
		sizeY = 50;
	}
	Obstacle1(double posX, double posY, double sizeX, double sizeY) {
		this->posX = posX;
		this->posY = posY;
		this->sizeX = sizeX;
		this->sizeY = sizeY;
	}
	//위치좌표, 크기, 등 setter/getter
	void setObstaclePos(double posX, double posY) {
		this->posX = posX;
		this->posY = posY;
	}
	double getObstaclePosX() {
		return posX;
	}
	double getObstaclePosY() {
		return posY;
	}
	void setObstacleSizeX(double X) {
		sizeX = X;
	}
	void setObstacleSizeY(double Y) {
		sizeY = Y;
	}
	double getObstacleSizeX() {
		return sizeX;
	}
	double getObstacleSizeY() {
		return sizeY;
	}


};
class Backlight :Obstacle1
{
private:
	Texture backlightTexture;
	Vector2u backlightSize;
	Sprite backlightSprite1;
	Sprite backlightSprite2;
	Sprite backlightSprite3;
	Sprite backlightSprite4;
	Sprite backlightSprite5;
	Sprite backlightSprite6;
public:
	Backlight()
	{

		backlightTexture.loadFromFile("./Data/Image/backlight.png");
		backlightSize = backlightTexture.getSize();
		backlightSprite1.setTexture(backlightTexture);
		backlightSprite1.setScale((float)100 / backlightSize.x, (float)100 / backlightSize.y);
		backlightSprite1.setOrigin(backlightSize.x / 2, backlightSize.y / 2);
		backlightSprite1.setPosition(1340, 275);//bottle1
		backlightSprite1.setColor(Color(255, 0, 0, 128));
		backlightSprite2.setTexture(backlightTexture);
		backlightSprite2.setScale((float)100 / backlightSize.x, (float)100 / backlightSize.y);
		backlightSprite2.setOrigin(backlightSize.x / 2, backlightSize.y / 2);
		backlightSprite2.setPosition(1650, 219); //bottle2
		backlightSprite2.setColor(Color(255, 0, 0, 128));
		backlightSprite3.setTexture(backlightTexture);
		backlightSprite3.setScale((float)100 / backlightSize.x, (float)100 / backlightSize.y);
		backlightSprite3.setOrigin(backlightSize.x / 2, backlightSize.y / 2);
		backlightSprite3.setPosition(590, 310);//basket
		backlightSprite3.setColor(Color(255, 0, 0, 128));
		backlightSprite4.setTexture(backlightTexture);
		backlightSprite4.setScale((float)100 / backlightSize.x, (float)100 / backlightSize.y);
		backlightSprite4.setOrigin(backlightSize.x / 2, backlightSize.y / 2);
		backlightSprite4.setPosition(1254, 270);
		backlightSprite4.setColor(Color(255, 0, 0, 128));
		backlightSprite5.setTexture(backlightTexture);
		backlightSprite5.setScale((float)100 / backlightSize.x, (float)100 / backlightSize.y);
		backlightSprite5.setOrigin(backlightSize.x / 2, backlightSize.y / 2);
		backlightSprite5.setPosition(1324, 270);
		backlightSprite5.setColor(Color(255, 0, 0, 128));
		backlightSprite5.setTexture(backlightTexture);
		backlightSprite5.setScale((float)150 / backlightSize.x, (float)150 / backlightSize.y);
		backlightSprite5.setOrigin(backlightSize.x / 2, backlightSize.y / 2);
		backlightSprite5.setPosition(1370, 119);//clock
		backlightSprite5.setColor(Color(255, 0, 0, 128));
	}
	void drawlight(RenderWindow& window)
	{
		window.draw(backlightSprite1);
		window.draw(backlightSprite2);
		window.draw(backlightSprite3);
		window.draw(backlightSprite4);
		window.draw(backlightSprite5);
		window.draw(backlightSprite6);
	}
	void rotate()
	{
		backlightSprite1.setRotation(backlightSprite1.getRotation() - 1);
		backlightSprite2.setRotation(backlightSprite2.getRotation() - 1);
		backlightSprite3.setRotation(backlightSprite3.getRotation() - 1);
		backlightSprite4.setRotation(backlightSprite4.getRotation() - 1);
		backlightSprite5.setRotation(backlightSprite5.getRotation() - 1);
		backlightSprite6.setRotation(backlightSprite6.getRotation() - 1);
	}
};

class Cup1 :Obstacle1
{
private:
	Vector2f position;
	Texture texture;
	Sprite sprite;
public:
	Cup1(float x, float y)
		: position(x, y)
	{
		texture.loadFromFile("./Data/Image/cup1.jpg");
		Vector2u cup1TextureSize = texture.getSize();
		sprite.setTexture(texture);
		sprite.setScale((float)30 / cup1TextureSize.x, (float)30 / cup1TextureSize.y);
		sprite.setPosition(position);

	}
	Vector2f getPosition() {
		return sprite.getPosition();
	}
	void draw(RenderWindow& window)
	{
		window.draw(sprite);
	}
	FloatRect getBounds() const
	{
		return sprite.getGlobalBounds();
	}
};
class Cup2 :Obstacle1
{
private:
	Vector2f position;
	Texture texture;
	Sprite sprite;
public:
	Cup2(float x, float y)
		: position(x, y)
	{
		texture.loadFromFile("./Data/Image/cup2.jpg");
		Vector2u cup1TextureSize = texture.getSize();
		sprite.setTexture(texture);
		sprite.setScale((float)30 / cup1TextureSize.x, (float)30 / cup1TextureSize.y);
		sprite.setPosition(position);

	}
	Vector2f getPosition() {
		return sprite.getPosition();
	}
	void draw(RenderWindow& window)
	{
		window.draw(sprite);
	}
	FloatRect getBounds() const
	{
		return sprite.getGlobalBounds();
	}
};
class Basket :Obstacle1
{
private:
	Vector2f position;
	Texture texture;
	Sprite sprite;
public:
	Basket(float x, float y)
		: position(x, y)
	{
		texture.loadFromFile("./Data/Image/basket.png");
		Vector2u cup1TextureSize = texture.getSize();
		sprite.setTexture(texture);
		sprite.setScale((float)120 / cup1TextureSize.x, (float)69 / cup1TextureSize.y);
		sprite.setPosition(position);

	}
	Vector2f getPosition() {
		return sprite.getPosition();
	}
	void draw(RenderWindow& window)
	{
		window.draw(sprite);
	}
	FloatRect getBounds() const
	{
		return sprite.getGlobalBounds();
	}
};
class Micro :Obstacle1
{
private:
	Vector2f position;
	Texture texture;
	Sprite sprite;
public:
	Micro(float x, float y)
		: position(x, y)
	{
		texture.loadFromFile("./Data/Image/micro.jpg");
		Vector2u cup1TextureSize = texture.getSize();
		sprite.setTexture(texture);
		sprite.setScale((float)130 / cup1TextureSize.x, (float)88 / cup1TextureSize.y);
		sprite.setPosition(position);

	}
	Vector2f getPosition() {
		return sprite.getPosition();
	}
	void draw(RenderWindow& window)
	{
		window.draw(sprite);
	}
	FloatRect getBounds() const
	{
		return sprite.getGlobalBounds();
	}
};
class Bottle :Obstacle1
{
private:
	Vector2f position;
	Texture texture;
	Sprite sprite;
public:
	Bottle(float x, float y)
		: position(x, y)
	{
		texture.loadFromFile("./Data/Image/bottle.png");
		Vector2u cup1TextureSize = texture.getSize();
		sprite.setTexture(texture);
		sprite.setScale((float)40 / cup1TextureSize.x, (float)80 / cup1TextureSize.y);
		sprite.setPosition(position);

	}
	Vector2f getPosition() {
		return sprite.getPosition();
	}
	void draw(RenderWindow& window)
	{
		window.draw(sprite);
	}
	FloatRect getBounds() const
	{
		return sprite.getGlobalBounds();
	}
};
class Ob_Clock :Obstacle1
{
private:
	Vector2f position;
	Texture texture;
	Sprite sprite;
public:
	Ob_Clock(float x, float y)
		: position(x, y)
	{
		texture.loadFromFile("./Data/Image/clock.png");
		Vector2u cup1TextureSize = texture.getSize();
		sprite.setTexture(texture);
		sprite.setScale((float)140 / cup1TextureSize.x, (float)140 / cup1TextureSize.y);
		sprite.setPosition(position);

	}
	Vector2f getPosition() {
		return sprite.getPosition();
	}
	void draw(RenderWindow& window)
	{
		window.draw(sprite);
	}
	FloatRect getBounds() const
	{
		return sprite.getGlobalBounds();
	}
};

//점수 클래스
class Score
{
private:
	//현재점수
	int currScore;
	//클리어 가능 점수(clearScore)
	int clearScore;
	//최고점수
	int maxScore;
	//위치, 크기(글자 크기 등)
	float posX;
	float posY;
	float size;

public:
	//생성자, 소멸자
	Score(float x, float y, float s)
	{
		posX = x;
		posY = y;
		size = s;

		currScore = 0;
		clearScore = 0;
		maxScore = 0;
	}

	//위치, 크기 등 setter/getter
	void setScorePos(float x, float y)
	{
		posX = x;
		posY = y;
	}
	float getScorePosX()
	{
		return posX;
	}
	float getScorePosY()
	{
		return posY;
	}
	void setScoreSize(float s)
	{
		size = s;
	}
	float getScoreSize()
	{
		return size;
	}

	//현재점수 업데이트(통조림의 크기, 개수에 따라 점수 부여)
	void setCurrScore(int c_s)
	{
		currScore = c_s;
	}

	//현재점수 반환
	int getCurrScore()
	{
		return currScore;
	}

	//클리어 가능 점수 업데이트
	void setClearScore(int c_s)
	{
		clearScore = c_s;
	}

	//클리어 가능 점수 반환
	int getClearScore()
	{
		return clearScore;
	}
	
	//최고점수 업데이트
	void setMaxScore(int m_s)
	{
		maxScore = m_s;
	}

	//최고점수 반환
	int getMaxScore()
	{
		return maxScore;
	}
};

// 
void Canned_Food::getFoodScore(Score* score, int size)
{
	//사이즈별로 점수부여
	//ex) size 1 = 1000점
	//    size 2 = 1500점
	//    size 3 = 3000점 ...
	if (size == 1) {//파랑
		score->setCurrScore(score->getCurrScore() + 1000);
	}
	else if (size == 2) {//빨강
		score->setCurrScore(score->getCurrScore() + 1500);
	}
	else if (size == 3) {//골드
		score->setCurrScore(score->getCurrScore() + 3000);
	}
}

//별 클래스
class Star
{
private:
	//위치, 크기

	//현재 별 개수
	int curstar;
	//이 스테이지 누적 최대 별 개수
	int stagemaxstar;//스테이지 종료시 업데이트
public:
	//생성자
	Star() {
		curstar = 0;
		this->stagemaxstar = 0;
	}
	Star(int stagemaxstar) {
		curstar = 0;
		this->stagemaxstar = stagemaxstar;
	}
	//현재 별 개수 setter/getter
	void setStar(int score) {
		int cs = 0;
		if (score >= 30000) // 일정 점수 이상은 별 3개 (이 부분만 내용 추가하면 될 듯)
		{
			cs = 3;
		}
		else if (score >= 20000 && score < 30000)
		{
			cs = 2;
		}
		else if (score >= 10000 && score < 20000)
		{
			cs = 1;
		}

		if (cs > curstar)
			curstar = cs;
	}
	int getStar() {
		return curstar;
	}
	//별 최대 개수 setter/getter
	void setMaxStar()
	{
		if (stagemaxstar < curstar)
			stagemaxstar = curstar;
	}
	int getMaxStar() {
		return stagemaxstar;
	}
	void drawstar(RenderWindow& window)
	{
		Texture onestar, twostar, threestar;
		Texture staryTexture;
		staryTexture.loadFromFile("./Data/Image/star_y.png");
		Texture stargTexture;
		stargTexture.loadFromFile("./Data/Image/star_g.png");
		Vector2u starySize = staryTexture.getSize();
		Vector2u stargSize = stargTexture.getSize();
		if (curstar == 0) {
			onestar = stargTexture;
			twostar = stargTexture;
			threestar = stargTexture;
		}
		else if (curstar == 1) {
			onestar = staryTexture;
			twostar = stargTexture;
			threestar = stargTexture;
		}
		else if (curstar == 2) {
			onestar = staryTexture;
			twostar = staryTexture;
			threestar = stargTexture;
		}
		else if (curstar == 3) {
			onestar = staryTexture;
			twostar = staryTexture;
			threestar = staryTexture;
		}
		Sprite starySprite1(onestar);
		Sprite starySprite2(twostar);
		Sprite starySprite3(threestar);
		starySprite1.setScale((float)100 / starySize.x, (float)100 / starySize.y);
		starySprite1.setPosition(340, 120);
		starySprite2.setScale((float)100 / starySize.x, (float)100 / starySize.y);
		starySprite2.setPosition(415, 90);
		starySprite3.setScale((float)100 / starySize.x, (float)100 / starySize.y);
		starySprite3.setPosition(490, 120);
		window.draw(starySprite1);
		window.draw(starySprite2);
		window.draw(starySprite3);
	}

};



//점프횟수 클래스
class Jump_number
{
private:
	int maxJump;  //최대 점프 횟수
	int leftJump; //남은 점프 횟수
	int posX;
	int posY;
	int size;
public:
	Jump_number() {  //기본생성자
		maxJump = 3;
		leftJump = 3;
		posX = 0;
		posY = 0;
		size = 20;
	}

	Jump_number(int mJump, int lJump, int x, int y, int s) {
		maxJump = mJump;
		leftJump = lJump;
		posX = x;
		posY = y;
		size = s;
	}

	~Jump_number() {

	}

	//최대 점프 횟수, 남은 점프 횟수, 위치, 크기 setter/getter
	void setMaxJump(int mJump) {
		maxJump = mJump;
	}
	int getMaxJump() {
		return maxJump;
	}

	void setLeftJump(int lJump) {
		leftJump = lJump;
	}
	int getLeftJump() {
		return leftJump;
	}

	void setPosition(int x, int y) {
		posX = x;
		posY = y;
	}
	int getPosX() {
		return posX;
	}
	int getPosY() {
		return posY;
	}

	void setSize(int s) {
		size = s;
	}
	int getSize() {
		return size;
	}

	//점프 횟수 감소 함수
	void reduceJump() {
		leftJump -= 1;
	}
};

class MainMenu
{
private:
	RectangleShape StartButton;
	//위치좌표,크기
	float SBposX;
	float SBposY;
	Vector2f SBsize;
	Color SBcolor;

	RectangleShape QuitButton;
	//위치좌표,크기
	float QBposX;
	float QBposY;
	Vector2f QBsize;
	Color QBcolor;

	float MainTposX;
	float MainTposY;
	float MainTsize;

	float SBTposX;
	float SBTposY;
	float SBTsize;

	float QBTposX;
	float QBTposY;
	float QBTsize;

public:
	//생성자,소멸자
	MainMenu()
	{
		SBposX = 355;
		SBposY = 300;
		SBsize.x = 250;
		SBsize.y = 60;

		StartButton.setPosition(SBposX, SBposY);
		StartButton.setSize(SBsize);
		StartButton.setFillColor(SBcolor.Blue);

		QBposX = 355;
		QBposY = 400;
		QBsize.x = 250;
		QBsize.y = 60;

		QuitButton.setPosition(QBposX, QBposY);
		QuitButton.setSize(QBsize);
		QuitButton.setFillColor(QBcolor.Blue);

		MainTposX = 200;
		MainTposY = 100;
		MainTsize = 100;

		SBTposX = 435;
		SBTposY = 300;
		SBTsize = 40;

		QBTposX = 440;
		QBTposY = 400;
		QBTsize = 40;
	}

	RectangleShape getSB()
	{
		return StartButton;
	}

	RectangleShape getQB()
	{
		return QuitButton;
	}

	//위치좌표,크기
	void setSBPos(float x, float y)
	{
		SBposX = x;
		SBposY = y;
	}
	float getSBPosX()
	{
		return SBposX;
	}
	float getSBPosY()
	{
		return SBposY;
	}
	void setSBSize(Vector2f s)
	{
		SBsize = s;
	}
	Vector2f getSBSize()
	{
		return SBsize;
	}

	void setQBPos(float x, float y)
	{
		QBposX = x;
		QBposY = y;
	}
	float getQBPosX()
	{
		return QBposX;
	}
	float getQBPosY()
	{
		return QBposY;
	}
	void setQBSize(Vector2f s)
	{
		QBsize = s;
	}
	Vector2f getQBSize()
	{
		return QBsize;
	}

	void setMainTPos(float x, float y)
	{
		MainTposX = x;
		MainTposY = y;
	}
	float getMainTPosX()
	{
		return MainTposX;
	}
	float getMainTPosY()
	{
		return MainTposY;
	}
	void setMainTSize(float s)
	{
		MainTsize = s;
	}
	float getMainTSize()
	{
		return MainTsize;
	}

	void setSBTPos(float x, float y)
	{
		SBTposX = x;
		SBTposY = y;
	}
	float getSBTPosX()
	{
		return SBTposX;
	}
	float getSBTPosY()
	{
		return SBTposY;
	}
	void setSBTSize(float s)
	{
		SBTsize = s;
	}
	float getSBTSize()
	{
		return SBTsize;
	}

	void setQBTPos(float x, float y)
	{
		QBTposX = x;
		QBTposY = y;
	}
	float getQBTPosX()
	{
		return QBTposX;
	}
	float getQBTPosY()
	{
		return QBTposY;
	}
	void setQBTSize(float s)
	{
		QBTsize = s;
	}
	float getQBTSize()
	{
		return QBTsize;
	}
};

//메뉴 클래스
class Menu
{
	// 재생, 일시정지, 다시 시작, 소리조절 등
private:
	//위치, 크기

	//현재상태(플레이중, 일시정지)

	//소리크기
public:
	//생성자,소멸자

	//위치, 크기, 현재상태 ,소리 크기 setter/getter

	//다시시작요청
	//상태변환시 visual,sound effect(sfml 이용해 구현)
};


//<시간 여유 시 추가로 구현>
//고양이의 능력(일정 스테이지 이상 클리어 시 새로운 고양이를 준다, 고양이별로 각자의 능력을 가짐, 충돌 전 클릭을 하면 고양이의 능력이 발현(ex-분신술))

//스테이지 클래스
class Stage
{
private:
	//위치좌표, 크기
	//최고로 많이 획득한 별 개수 -> 별 클래스에서 받아오기
	//획득한 최고 점수(default = 0) -> 점수 클래스에서 받아오기
public:
	//생성자, 소멸자 
	//위치, 크기, 최고점수, 별개수 setter/getter
};

//생명 클래스
class Heart
{
	//레벨 클리어 실패 시 하나씩 감소
	//30분마다 하나씩 증가
private:
	//위치좌표, 크기
	//현재 남은 생명 개수
public:
	//생성자, 소멸자 
	//위치, 크기, 생명 개수 setter/getter
};

//사용자 레벨 클래스
class Level
{
	//별을 일정 개수 이상 모으면 레벨업
private:
	//위치좌표, 크기
	//레벨 배열 생성, 배열의 인덱스 번호는 레벨을 뜻함, 배열의 값은 레벨업까지 모아야할 별 개수를 뜻함
	//현재 레벨
	//모은 별 개수 -> 별 클래스에서 받아와서 누적, 현재 레벨의 레벨업까지 모아야할 별 개수와 같은지 비교 후 같다면 현재 레벨 + 1
	//레벨업까지 모아야할 별 개수
public:
	//생성자, 소멸자 
	//위치, 크기, 레벨, 별개수 setter/getter
};

int main()
{
	// 창 생성
	RenderWindow window(VideoMode(960, 540), "Jumping cat");
	window.setFramerateLimit(60);	//프레임 정해주기

	//메인메뉴 생성
	MainMenu mainmenu;
	bool is_SB_clicked = false;
	bool is_QB_clicked = false;

	//포물선 클래스 생성
	Arc arc(180, 450, 3);
	arc.setStartArcPosition(arc.getArcPosX(), arc.getArcPosY());

	//고양이 스프라이트 생성
	Cat cat(180.f, 465.f);
	cat.setStartPosition(cat.getPositionX(), cat.getPositionY());
	Vector2f dragStartPosition;
	Vector2f dragEndPosition;

	//사람 스프라이트 생성
	Texture girlTexture;
	girlTexture.loadFromFile("./Data/Image/girl.png");
	Vector2u girlTextureSize = girlTexture.getSize();
	Sprite girlSprite(girlTexture);
	girlSprite.setScale((float)200 / girlTextureSize.x, (float)200 / girlTextureSize.y);
	girlSprite.setPosition(0, 340);

	//조명등 스프라이트 생성
	Floodlight floodlight(800, 0);


	Score score(0, 30, 20);

	//남은 점프 횟수 표시할 text 설정
	Jump_number jn;
	Text text;
	Font font;

	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
		return 42; // Robust error handling!
	}

	text.setFont(font);
	text.setString("Chance: " + to_string(jn.getLeftJump()));
	text.setCharacterSize(jn.getSize());
	text.setFillColor(Color::Black);
	text.setPosition((float)jn.getPosX(), (float)jn.getPosY());

	Text main_text;
	main_text.setFont(font);
	main_text.setString("Jumping Cat");
	main_text.setCharacterSize((int)mainmenu.getMainTSize());
	main_text.setFillColor(Color::Black);
	main_text.setPosition(mainmenu.getMainTPosX(), mainmenu.getMainTPosY());

	Text SBT;
	SBT.setFont(font);
	SBT.setString("Start");
	SBT.setCharacterSize((int)mainmenu.getSBTSize());
	SBT.setFillColor(Color::Black);
	SBT.setPosition(mainmenu.getSBTPosX(), mainmenu.getSBTPosY());

	Text QBT;
	QBT.setFont(font);
	QBT.setString("Quit");
	QBT.setCharacterSize((int)mainmenu.getQBTSize());
	QBT.setFillColor(Color::Black);
	QBT.setPosition(mainmenu.getQBTPosX(), mainmenu.getQBTPosY());

	Text game_score;
	game_score.setFont(font);
	game_score.setString("Score: " + to_string(score.getCurrScore()));
	game_score.setCharacterSize((int)score.getScoreSize());
	game_score.setFillColor(Color::Blue);
	game_score.setPosition(score.getScorePosX(), score.getScorePosY());

	Text final_score;
	final_score.setFont(font);
	final_score.setString("Score: " + to_string(score.getCurrScore()));
	final_score.setCharacterSize((int)score.getScoreSize());
	final_score.setFillColor(Color::Blue);
	//위치 세팅 바꾸기
	final_score.setPosition(350, 300);

	// 게임 오버 또는 클리어 여부 표시할 text 설정
	Text game_status;
	game_status.setFont(font);
	game_status.setCharacterSize(40);
	game_status.setPosition(350, 260);

	Clock clock;

	//효과음, 배경음악
	Music music;
	if (!music.openFromFile("./Data/Sound/background_music.ogg"))
		return -1;
	music.play();
	music.setVolume(10.f);
	music.setLoop(true);

	SoundBuffer buffer;
	if (!buffer.loadFromFile("./Data/Sound/676402__cjspellsfish__score-2.wav"))
		cout << "ccan sound err\n" << endl;
	Sound csound;
	csound.setBuffer(buffer);

	SoundBuffer gbuffer;
	if (!gbuffer.loadFromFile("./Data/Sound/Coin-2.wav"))
		cout << "gccan sound err\n" << endl;
	Sound gcsound;
	gcsound.setBuffer(gbuffer);
	gcsound.setVolume(30);
	gcsound.setPitch(1.4);

	SoundBuffer bbuffer;
	if (!bbuffer.loadFromFile("./Data/Sound/Coin-3.wav"))
		cout << "gccan sound err\n" << endl;
	Sound bcsound;
	bcsound.setBuffer(bbuffer);
	bcsound.setVolume(30);
	bcsound.setPitch(1.1);

	Music dragSound;
	if (!dragSound.openFromFile("./Data/Sound/meow.wav"))
		cout << "drag sound err\n";
	dragSound.setVolume(70);

	Music jumpSound;
	if (!jumpSound.openFromFile("./Data/Sound/jump.wav"))
		cout << "jump sound err\n";

	//배경화면 스프라이트 생성
	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("./Data/Image/background.png"))
		return -1;
	Vector2u backgroundSize = backgroundTexture.getSize();
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale((float)(window.getSize().x * 2) / backgroundSize.x, (float)window.getSize().y / backgroundSize.y);

	//배경 시점
	View view(Vector2f(window.getSize().x / 2, window.getSize().y / 2), Vector2f(window.getSize().x, window.getSize().y));
	//게임 진행 중 점수 표시 이동,배경
	View scoreview;
	scoreview.setViewport(FloatRect(0, 0,1,1.6));
	RectangleShape scoreboard;
	scoreboard.setPosition(0, 0);
	scoreboard.setSize(Vector2f(135, 60));
	scoreboard.setFillColor(Color(150, 15, 40 ,200));
	scoreboard.setOutlineColor(Color(120, 25, 20, 200));
	scoreboard.setOutlineThickness(1);

	//별 
	Star star;

	//장애물
	Cup1 cup1(1150, 240);
	Cup2 cup2(1600, 269);
	Basket basket(530, 270);
	Bottle bottle(1204, 220);
	Micro micro(1284, 210);
	Ob_Clock ob_clock(1300, 53);

	// can
	Canned_Food blue_can[BLUE_CAN];
	Canned_Food red_can[RED_CAN];
	Canned_Food gold_can[GOLD_CAN];
	/* 1000 * 8 + 1500 * 7 + 3000 * 4 = 30500*/
	blue_can[0].setinfo(660, 290, 1); blue_can[1].setinfo(800, 400, 1); blue_can[2].setinfo(750, 250, 1); blue_can[3].setinfo(900, 100, 1);
	blue_can[4].setinfo(860, 230, 1); blue_can[5].setinfo(940, 240, 1); blue_can[6].setinfo(1100, 350, 1); blue_can[7].setinfo(1500, 70, 1);

	red_can[0].setinfo(1000, 200, 2); red_can[1].setinfo(1100, 170, 2); red_can[2].setinfo(1300, 360, 2);
	red_can[3].setinfo(1040, 300, 2); red_can[4].setinfo(1400, 330, 2); red_can[5].setinfo(1500, 300, 2); red_can[6].setinfo(1600, 90, 2);

	gold_can[0].setinfo(1200, 400, 3); gold_can[1].setinfo(1700, 120, 3); gold_can[2].setinfo(1200, 150, 3); gold_can[3].setinfo(1800, 180, 3);

	Canned_Food can;
	
	//클리어 점수 세팅
	int total_can = BLUE_CAN + RED_CAN + GOLD_CAN;
	score.setClearScore(total_can * 1000);

	//마우스
	Vector2f mcm;
	mcm = Vector2f(0, 0);
	int mouseispressed = 0;
	Vector2i pixelPos1;
	Vector2i pixelPos2;
	
	//준비상태인가 0=발사전 1=발사후
	int ready = 0;

	bool reset = false;

	bool cat_is_clicked = false;  //마우스로 고양이를 클릭했는지 저장할 변수
	int collisionNum = 0;         //장애물과 충돌한 횟수를 저장할 변수
	float jumpVelocityScale = 10.0f;
	while (window.isOpen())
	{
		// 이벤트 처리
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (is_SB_clicked == false)
			{
				if (event.type == Event::MouseButtonReleased)
				{
					if (event.mouseButton.button == Mouse::Left)
					{
						Vector2i Mpos = Mouse::getPosition(window);
						if ((Mpos.x > mainmenu.getSBPosX() && Mpos.x < mainmenu.getSBPosX() + mainmenu.getSBSize().x) && (Mpos.y > mainmenu.getSBPosY() && Mpos.y < mainmenu.getSBPosY() + mainmenu.getSBSize().y))
						{
							is_SB_clicked = true;
						}
						else if ((Mpos.x > mainmenu.getQBPosX() && Mpos.x < mainmenu.getQBPosX() + mainmenu.getQBSize().x) && (Mpos.y > mainmenu.getQBPosY() && Mpos.y < mainmenu.getQBPosY() + mainmenu.getQBSize().y))
						{
							is_QB_clicked = true;
						}
					}
				}
			}
			else if (jn.getLeftJump() > 0 && cat.getIsJumping() == false) { //날아가는 도중에는 고양이 드래그 안 되도록 조건 추가
				
					if (event.type == Event::MouseButtonPressed)
					{
						if (event.mouseButton.button == Mouse::Left)
						{
							if (view.getCenter().x < window.getSize().x * 0.6) { //준비상태에서 화면이 다른곳 보고있으면 드래그 안됨
								dragStartPosition = Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);
								if (dragStartPosition.x > cat.getPositionX() - cat.getTextureSizeX() * cat.getScale().x / 2 && dragStartPosition.x < cat.getPositionX() + cat.getTextureSizeX() * cat.getScale().x / 2 && dragStartPosition.y > cat.getPositionY() - cat.getTextureSizeY() * cat.getScale().y / 2 && dragStartPosition.y < cat.getPositionY() + cat.getTextureSizeY() * cat.getScale().y / 2) {
									cat_is_clicked = true;
									dragSound.openFromFile("./Data/Sound/meow.wav");
									dragSound.play();
								}
							}
						}
						mouseispressed = 1;
						pixelPos1 = Mouse::getPosition(window);

					}
					else if (event.type == Event::MouseButtonReleased)
					{
						if (event.mouseButton.button == Mouse::Left)
						{
							if (view.getCenter().x < window.getSize().x * 0.6) { //준비상태에서 화면이 다른곳 보고있으면 드래그 안됨
								dragEndPosition = Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);
								Vector2f dragDistance = dragStartPosition - dragEndPosition;

								//최대 속도 제한
								float drag_dis = (float)sqrt(pow(dragDistance.x, 2) + pow(dragDistance.y, 2)); //마우스 버튼을 뗐을 때, 드래그한 거리
								if (drag_dis > 70) {
									float drag_ratio = 70 / drag_dis;
									dragDistance.x *= drag_ratio;
									dragDistance.y *= drag_ratio;
								}
								Vector2f jumpVelocity = jumpVelocityScale * dragDistance;

								cat.setRotation(0);
								cat.setScale(0.07f, 0.07f); //고양이 크기 원래상태로 되돌리기

								// 드래그를 너무 조금하거나 오른쪽으로 하면 무시하고 아니면 날아감
								if ((abs(dragDistance.x) <= 20 && abs(dragDistance.y) <= 20) || dragDistance.x < 0) {
									cat_is_clicked = false;
								}
								else {
									if (cat_is_clicked == true) {
										cat_is_clicked = false;
										reset = false;

										//포물선 그리기 위한 속도, 가속도, 위치 세팅
										arc.setArcVelocity(jumpVelocity);
										arc.setStartArcVelocity(arc.getArcVelocity());
										arc.setArcAcceleration(cat.getGravity());

										arc.setArcPos(arc.getStartArcPositionX(), arc.getStartArcPositionY());


										//날아가는 코드 구현
										cat.jump(jumpVelocity);
										//날아갈 때 소리 재생
										jumpSound.openFromFile("./Data/Sound/jump.wav");
										jumpSound.play();
										ready = 1;
									}
								}
								int x = 0, x2 = 0, y = 0, y2 = 0;  //좌표 초기화
							}
						}
						mouseispressed = 0;
					}
			}
		}

		if (is_QB_clicked == true)
		{
			window.close();
		}

		// 게임 로직
		float deltaTime = clock.restart().asSeconds();

		floodlight.swing();
		
		if (cat.getPositionY() > window.getSize().y || collisionNum == 9) //고양이가 밑으로 떨어지거나 충돌횟수가 9번이면
		{
			collisionNum = 0; //장애물 충돌 횟수 초기화

			cat.changeImage("./Data/Image/cat.png");
			reset = true;

			jn.reduceJump(); //점프횟수 감소
			text.setString("Chance: " + to_string(jn.getLeftJump()));
		}

		if (reset == false)
		{
			cat.update(deltaTime);
		}
		else
		{
			if (cat.getScale().x < 0)
				cat.setScale(abs(cat.getScale().x), cat.getScale().y);
			cat.setPosition(cat.getStartPositionX(), cat.getStartPositionY());
			cat.setRotation(0);
			cat.setVelocity(Vector2f(0, 0));
			cat.setIsFalling(false);
			cat.setIsJumping(false);
			if (ready == 1) {
				view.setCenter(window.getSize().x / 2, window.getSize().y / 2); // 화면도 초기화
				ready = 0;
			}
		}
		
		if (cat_is_clicked == true) {
			Vector2f move_pos;
			int x1 = Mouse::getPosition(window).x;
			int y1 = Mouse::getPosition(window).y;
			int move_pos_x = (int)dragStartPosition.x - x1;
			int move_pos_y = (int)dragStartPosition.y - y1;
			move_pos.x = move_pos_x;
			move_pos.y = move_pos_y; 

			float ang = (float)(atan2(double(y1 - dragStartPosition.y), double(x1 - dragStartPosition.x)) * 180 / 3.141592);
			if (ang < 0) ang += 360;
			if (move_pos_x > 0)
				cat.setRotation((int)ang + 180);

			float drag_dis = (float)sqrt(pow(dragStartPosition.x - x1, 2) + pow(dragStartPosition.y - y1, 2)); //실시간으로 드래그한 거리
			if (drag_dis <= 70)
				cat.setScale((float)(1597 * 0.07 + drag_dis) / cat.getTextureSizeX(), (float)(1277 * 0.07 - drag_dis) / cat.getTextureSizeY());

			//최대 속도 제한 수정
			if (drag_dis > 70) {
				float drag_ratio = 70 / drag_dis;
				move_pos.x *= drag_ratio;
				move_pos.y *= drag_ratio;
			}
			Vector2f jumpVelocity = jumpVelocityScale * move_pos;


			//포물선 그리기 위한 속도, 가속도, 위치 세팅
			arc.setArcVelocity(jumpVelocity);
			arc.setStartArcVelocity(arc.getArcVelocity());
			arc.setArcAcceleration(cat.getGravity());

			arc.setArcPos(arc.getStartArcPositionX(), arc.getStartArcPositionY());
		}
		

		//전등과 부딪히면 떨어짐
		if (cat.getBounds().intersects(floodlight.getBounds()))
		{
			cat.changeImage("./Data/Image/dizzycat.png"); //눈이 빙글빙글 도는 고양이 이미지로 바꿈
			cat.startFalling(200.f, 300.f);
		}
		cat.update(deltaTime);

		//장애물과 충돌시 튕겨나감.
		Vector2f direction;
		if (cat.getBounds().intersects(cup1.getBounds()) || cat.getBounds().intersects(cup2.getBounds()) ||
			cat.getBounds().intersects(basket.getBounds()) || cat.getBounds().intersects(bottle.getBounds()) ||
			cat.getBounds().intersects(ob_clock.getBounds()) || cat.getBounds().intersects(micro.getBounds()))
		{
			// 고양이와 컵1 충돌 체크
			if (cat.getBounds().intersects(cup1.getBounds())) {
				// 충돌 방향 계산
				direction = cat.getPosition() - cup1.getPosition();
			}
			// 고양이와 컵2 충돌 체크
			else if (cat.getBounds().intersects(cup2.getBounds()))
				direction = cat.getPosition() - cup2.getPosition();

			// 고양이와 바구니 충돌 체크
			else if (cat.getBounds().intersects(basket.getBounds()))
				direction = cat.getPosition() - basket.getPosition();

			// 고양이와 병 충돌 체크
			else if (cat.getBounds().intersects(bottle.getBounds()))
				direction = cat.getPosition() - bottle.getPosition();

			// 고양이와 시계 충돌 체크
			else if (cat.getBounds().intersects(ob_clock.getBounds()))
				direction = cat.getPosition() - ob_clock.getPosition();

			// 고양이와 전자레인지 충돌 체크
			else if (cat.getBounds().intersects(micro.getBounds()))
				direction = cat.getPosition() - micro.getPosition();

			// 단위 벡터로 정규화
			direction = direction / sqrtf(direction.x * direction.x + direction.y * direction.y);
			// 튕겨나가는 속도 설정
			float bounceSpeed = 500.0f;
			Vector2f bounceVelocity = direction * bounceSpeed;
			// 속도 업데이트
			cat.setVelocity(bounceVelocity);

			//장애물 충돌 횟수 증가
			if (cat.getIsFalling() == false) //전등에 부딪혀서 떨어지는 경우는 제외
				collisionNum += 1;
		}

		//can과 충돌
		if (cat.getIsFalling() == false)//전등에 부딪힌 후 떨어질 때는 통조림 안 먹어짐.
		{
			for (int i = 0; i < 8; i++) {
				if (cat.getBounds().intersects(blue_can[i].getBounds()))
				{
					blue_can[i].getFoodScore(&score, 1);                //파란캔
					game_score.setString("Score: " + to_string(score.getCurrScore()));
					blue_can[i].getsprite()->setPosition(5000, 5000);
					csound.play();
				}
			}
			for (int i = 0; i < 7; i++) {
				if (cat.getBounds().intersects(red_can[i].getBounds()))
				{
					red_can[i].getFoodScore(&score, 2);               //빨간캔
					game_score.setString("Score: " + to_string(score.getCurrScore()));
					red_can[i].getsprite()->setPosition(5000, 5000);
					bcsound.play();
				}
			}
			for (int i = 0; i < 4; i++) {
				if (cat.getBounds().intersects(gold_can[i].getBounds()))
				{
					gold_can[i].getFoodScore(&score, 3);               //금캔
					game_score.setString("Score: " + to_string(score.getCurrScore()));
					gold_can[i].getsprite()->setPosition(5000, 5000);
					gcsound.play();
				}
			}
		}

		//화면이 변경되면 작동 중지하도록 변경
		//배경 시점 변경
		if (cat.getPosition().x > window.getSize().x / 2 &&
			cat.getPosition().x < window.getSize().x * 1.503 && cat.getIsJumping()==true) {

			view.setCenter(cat.getPositionX(), window.getSize().y / 2);
		}

		if (cat.getIsJumping() == false) {

			if ((mouseispressed == 1) && (cat_is_clicked == false) && pixelPos1.x > 0 && pixelPos1.x < backgroundSize.x)
			{
				pixelPos2 = Mouse::getPosition(window);

				mcm = Vector2f(pixelPos1 - pixelPos2);
				mcm.x /=5;
				mcm.y = 0;

				if (view.getCenter().x < window.getSize().x / 2 - mcm.x) // 화면이 배경 왼-밖으로 나가면 안됨
				{
					if(mcm.x<0)
					    mcm.x = 0;
				}
				if (view.getCenter().x > window.getSize().x * 2 - window.getSize().x / 2 - mcm.x) // 화면이 배경 오-밖으로 나가면 안됨
				{
					if (mcm.x >0)
						mcm.x = 0;
				}

				view.move(mcm);
			}
		}
		/*	backlight.rotate();*/

		star.setStar(score.getCurrScore());

		// 그리기
		window.clear(Color::White);

		if (is_SB_clicked == false)
		{
			window.draw(mainmenu.getSB());
			window.draw(mainmenu.getQB());
			
			window.draw(main_text);
			window.draw(SBT);
			window.draw(QBT);
		}
		else if (jn.getLeftJump() <= 0) {
			// 일정 점수 이상이면 게임 클리어라고 뜨도록 해야함 + 통조림을 다 먹으면
			// 클리어한 경우

			view.setCenter(Vector2f(960 / 2, 540 / 2));
			window.setView(view);

			if (score.getCurrScore() >= score.getClearScore())
			{
				game_status.setString("Game Clear");
				game_status.setFillColor(Color::Blue);

				final_score.setString("Score: " + to_string(score.getCurrScore()));

				window.draw(game_status);
				window.draw(final_score);
				star.drawstar(window);
			}
			else {
				// 클리어하지 못한 경우
				game_status.setString("Game Over");
				game_status.setFillColor(Color::Red);

				final_score.setString("Score: " + to_string(score.getCurrScore()));

				window.draw(game_status);
				window.draw(final_score);
				star.drawstar(window);
			}
		}
		else {
			window.setView(view);
			window.draw(backgroundSprite);
			//window.draw(backlightSprite);
			/*backlight.drawlight(window);*/
			floodlight.draw(window);
			for (int i = 0; i < 8; i++) {
				if (blue_can[i].getPosition() != 5000)
					blue_can[i].draw(window);
			}
			for (int i = 0; i < 7; i++) {
				if (red_can[i].getPosition() != 5000)
					red_can[i].draw(window);
			}
			for (int i = 0; i < 4; i++) {
				if (gold_can[i].getPosition() != 5000)
					gold_can[i].draw(window);
			}
			cat.draw(window);
			window.draw(girlSprite);
			cup1.draw(window);
			cup2.draw(window);
			bottle.draw(window);
			basket.draw(window);
			micro.draw(window);
			ob_clock.draw(window);


			//포물선 화면에 그려주기
			if (cat_is_clicked == true)
			{
				arc.setArcVelocity(arc.getStartArcVelocity());

				arc.setArcPos(arc.getStartArcPositionX(), arc.getStartArcPositionY());

				int ArcDrawCount = 0;

				for (float tldt = 0; tldt <= 0.015; tldt += 0.0001)
				{
					if (ArcDrawCount == 0 || ArcDrawCount % 10 == 0)
					{
						window.draw(arc.getArc());
					}

					arc.moveArc(tldt);
					ArcDrawCount++;
				}
			}
			window.setView(scoreview);
			window.draw(scoreboard);
			window.draw(game_score);
			window.draw(text);
		}

		window.display();


	}

	return 0;
}
