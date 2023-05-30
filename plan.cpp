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

void play_sound(const string& filename);
void delay_ms(int ms);

//고양이 클래스
class Cat
{
public:
	Cat(float x, float y)
		: position(x, y), velocity(0.f, 0.f), gravity(500.f), isJumping(false)
	{
		texture.loadFromFile("./Data/Image/cat.png");
		Vector2u catTextureSize = texture.getSize();
		sprite.setTexture(texture);
		sprite.setScale((float)100 / catTextureSize.x, (float)100 / catTextureSize.y);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2); //가운데를 중심점으로 설정
		sprite.setPosition(position);
	}

	int getPositionX()
	{
		return sprite.getPosition().x;
	}

	int getPositionY()
	{
		return sprite.getPosition().y;
	}

	float getTextureSizeX() 
	{
		return texture.getSize().x;
	}

	float getTextureSizeY()
	{
		return texture.getSize().y;
	}

	void setRotation(int a)
	{
		sprite.setRotation(a);
	}

	void setScale(float factorX, float factorY)
	{
		sprite.setScale((float)factorX, (float)factorY);
	}

	void update(float deltaTime)
	{
		if (isJumping)
		{
			// 위치 업데이트
			position += velocity * deltaTime;
			velocity.y += gravity * deltaTime;

			sprite.setPosition(position);
		}
	}

	void jump(Vector2f jumpVelocity)
	{
		velocity = jumpVelocity;
		isJumping = true;
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

private:
	Vector2f position;
	Vector2f velocity;
	float gravity;
	bool isJumping;
	Texture texture;
	Sprite sprite;
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
	float radius;
	
	float velocityX;
	float velocityY;
	float acceleration;
	
public:
	//생성자, 소멸자
	Arc(float x, float y, float r)
	{
		posX = x;
		posY = y;
		radius = r;
		
		velocityX = 0;
		velocityY = 0;
		acceleration = 0;

		arc.setPosition(posX, posY);
		arc.setRadius(radius);
	}
	
	//
	CircleShape getArc()
	{
		return arc;
	}
	
	//위치좌표, 크기, 각도 setter/getter
	void setArcPos(float x,float y)
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
	
	void setArcVelocityX(float v_x)
	{
		velocityX = v_x;
	}
	float getArcVelocityX()
	{
		return velocityX;
	}

	void setArcVelocityY(float v_y)
	{
		velocityY = v_y;
	}
	float getArcVelocityY()
	{
		return velocityY;
	}

	void setArcAcceleration(float a)
	{
		acceleration = a;
	}
	float getArcAcceleration()
	{
		return acceleration;
	}
	
	//이동(move)
	void moveArc(float dt)
	{
		setArcPos(getArcPosX() + getArcVelocityX() * dt, getArcPosY() - getArcVelocityY() * dt);

		setArcVelocityX(getArcVelocityX() + 0 * dt);
		setArcVelocityY(getArcVelocityY() - getArcAcceleration() * dt);
	}
};

//통조림 클래스
class Canned_Food
{
  //직사각형으로 구현하면 좋을 듯

private:
  //변수(필드)
  //위치좌표, 크기
	double posX;
	double posY;
	double sizeX;
	double sizeY;
  
public:
  //함수(메소드)
  //생성자, 소멸자
	Canned_Food()
	{
		posX = 50.0;
		posY = 50.0;
		sizeX = 10.0;
		sizeY = 10.0;
    }
    Canned_Food(double posX, double posY, double sizeX, double sizeY)
    {
		this->posX = posX;
		this->posY = posY;
		this->sizeX = sizeX;
	        this->sizeY = sizeY;
    }
  //위치좌표, 크기 setter/getter
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
	void setFoodpos(double posX,double posY)
	{
		this->posX = posX;
		this->posY = posY;
	}
	double getFoodposX()
	{
		return this->posX;
	}
	double getFoodposY()
	{
		return this->posY;
	}
  
  //충돌 시 획득
	void getFoodScore(double size)
	{
		//사이즈별로 점수부여
		//ex) size 10 = 1000점
		//    size 20 = 3000점
		//    size 40 = 6000점 ...
		if (size == 10.0) {
			// getScore(1000);
		}
		else if (size == 20.0) {
			// getScore(3000);
		}
		else if (size == 40.0) {
			// getScore(6000);
		}

  }

   //충돌, 획득 시 visual,sound effect
	void getCannedFoodSound()
	{
		play_sound("./Data/Sound/676402__cjspellsfish__score-2.wav");
	}

	//획득시 제거
};

//사운드 재생 함수
void play_sound(const string& filename)
{
	SoundBuffer buffer;

	if (!buffer.loadFromFile(filename))
	{
		cout << "sound loadFromFile error" << endl;
		return;
	}
	Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	delay_ms(1500);
}

void delay_ms(int ms)
{
	Clock Timer;
	while (Timer.getElapsedTime().asMilliseconds() < ms);
}

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
	Obstacle1(){
		posX=100;
		posY=200;
		sizeX=40;
		sizeY=50;
	}
	Obstacle1(double posX, double posY, double sizeX, double sizeY){
		this->posX=posX;
		this->posY=posY;
		this->sizeX=sizeX;
		this->sizeY=sizeY;
	}
  //위치좌표, 크기, 등 setter/getter
	void setObstaclePos(double posX, double posY){
		this->posX = posX;
		this->posY = posY;
	}
	double getObstaclePosX(){
		return posX;
	}
	double getObstaclePosY(){
		return posY;
	}
	void setObstacleSizeX(double X){
		sizeX = X;
	}
	void setObstacleSizeY(double Y){
		sizeY = Y;
	}
	double getObstacleSizeX(){
		return sizeX;
	}
	double getObstacleSizeY(){
		return sizeY;
	}
		
  //충돌시 visual,sound effect
};


//바닥 클래스 -> 바닥을 스프라이트로 만들려면 Sprite 클래스를 상속받아야 하나?
class Floor
{
private:
	//위치좌표,크기
	float posX;
	float posY;
	float size;
	
public:
	//생성자,소멸자
	Floor(float x, float y, float s)
	{
		posX = x;
		posY = y;
		size = s;
	}
	
	//위치좌표,크기
	void setFloorPos(float x,float y)
	{
		posX = x;
		posY = y;
	}
	float getFloorPosX()
	{
		return posX;
	}
	float getFloorPosY()
	{
		return posY;
	}
	void setFloorSize(float s)
	{
		size = s;
	}
	float getFloorSize()
	{
		return size;
	}
	
	//고양이가 바닥에 닿으면 게임 오버
};

//점수 클래스
class Score
{
private:
	//현재점수
	float currScore;
	//최고점수
	float maxScore;
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
		maxScore = 0;
	}
	
	//위치, 크기 등 setter/getter
	void setScorePos(float x,float y)
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
	
	//현재점수 반환
	void setCurrScore(float c_s)
	{
		currScore = c_s;
	}
	
	//현재점수 업데이트(통조림의 크기, 개수, 파괴한 장애물에 따라 점수 부여)
	float getCurrScore()
	{
		return currScore;
	}
	
	//최고점수 반환 
	void setMaxScore(float m_s)
	{
		maxScore = m_s;
	}
	
	//최고점수 업데이트
	float getMaxScore()
	{
		return maxScore;
	}
};

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
	Star(int stagemaxstar){
		curstar=0;
		this->stagemaxstar = stagemaxstar;
	}
	//현재 별 개수 setter/getter
	void setStar(int score){
		int cs=0;
		if(score>=30000) // 일정 점수 이상은 별 3개
		{
			cs=3;
		}else if(score>=20000 && score<30000)
		{
			cs=2;
		}else if(score>=10000 && score<20000)
		{
			cs=1;
		}
		
		if(cs>curstar)
			curstar=cs;
	}
	int getStar(){
		return curstar;
	}
	//별 최대 개수 setter/getter
	void setMaxStar()
	{
		if(stagemaxstar<curstar)
			stagemaxstar=curstar;
	}
	int getMaxStar(){
		return stagemaxstar;
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

//+ 물체 충돌 감지 함수(직사각형 2개 인자로 받고 충돌이 일어났는지 판단하여 boolean 값 반환)
//sfml의 Rect class 이용
bool checkCollision(const FloatRect& rect1, const FloatRect& rect2)
{
	return rect1.intersects(rect2);
}

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

	// 바닥 스프라이트 생성
	Texture floorTexture;
	floorTexture.loadFromFile("./Data/Image/floor.png");
	Sprite floorSprite(floorTexture);

	//고양이 스프라이트 생성
	Cat cat(100.f, 300.f);
	Vector2f dragStartPosition;
	Vector2f dragEndPosition;
	//Vector2u catTextureSize = catTexture.getSize();

	//사람 스프라이트 생성
	Texture girlTexture;
	girlTexture.loadFromFile("./Data/Image/girl.png");
	Vector2u girlTextureSize = girlTexture.getSize();
	Sprite girlSprite(girlTexture);
	girlSprite.setScale((float)100 / girlTextureSize.x, (float)100 / girlTextureSize.y);
	girlSprite.setPosition(0, 0);

	//조명등 스프라이트 생성
	Texture lightTexture;
	lightTexture.loadFromFile("./Data/Image/floodlight.png");
	Vector2u lightTextureSize = lightTexture.getSize();
	Sprite lightSprite(lightTexture);
	lightSprite.setScale((float)159.4 / lightTextureSize.x, (float)189.6 / lightTextureSize.y);
	lightSprite.setPosition(480, 0);

	//캔 스프라이트 생성
	Texture canTexture;
	canTexture.loadFromFile("./Data/Image/canned_food.png");
	Vector2u textureSize = canTexture.getSize();
	Sprite canSprite(canTexture);
	canSprite.setScale((float)100 / textureSize.x, (float)100/textureSize.y);
	canSprite.setPosition(800, 100);

	//Score score; => 생성자 형식에 맞게 작성해주세요!
	
	
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
	text.setPosition(jn.getPosX(), jn.getPosY());

	// 게임 오버 또는 클리어 여부 표시할 text 설정
	Text game_status;
	game_status.setFont(font);
	game_status.setCharacterSize(40);
	game_status.setPosition(350, 260);

	Clock clock;

	bool cat_is_clicked = false;       //마우스로 고양이를 클릭했는지 저장할 변수
	while (window.isOpen())
	{
		// 이벤트 처리
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (jn.getLeftJump() > 0) {
				if (event.type == Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == Mouse::Left)
					{
						dragStartPosition = Vector2f(event.mouseButton.x, event.mouseButton.y);
						if (dragStartPosition.x > cat.getPositionX() - 50 && dragStartPosition.x < cat.getPositionX() + 50 && dragStartPosition.y > cat.getPositionY() - 50 && dragStartPosition.y < cat.getPositionY() + 50)
							cat_is_clicked = true;
						cout << dragStartPosition.x << " " << dragStartPosition.y << "\n";
					}
				}
				else if (event.type == Event::MouseButtonReleased)
				{
					if (event.mouseButton.button == Mouse::Left)
					{
						dragEndPosition = Vector2f(event.mouseButton.x, event.mouseButton.y);
						Vector2f dragDistance = dragStartPosition - dragEndPosition;
						
						float jumpVelocityScale = 4.2f;
						Vector2f jumpVelocity = jumpVelocityScale * dragDistance;
		
						cout << dragEndPosition.x << " " << dragEndPosition.y << "\n";

						cat.setRotation(0);
						cat.setScale(0.1f, 0.1f);
						// 드래그를 너무 조금했을 때는 무시하고 아니면 날아감
						cout << "diff: " << dragDistance.x << " " << dragDistance.y << "\n";
						if (abs(dragDistance.x) <= 20 && abs(dragDistance.y) <= 20) {
							cat_is_clicked = false;
						}
						else {
							if (cat_is_clicked == true) {
								cat_is_clicked = false;

								//날아가는 코드 구현
								cat.jump(jumpVelocity);

								jn.reduceJump(); //점프횟수 감소
								text.setString("Chance: " + to_string(jn.getLeftJump()));
							}
							cout << "Dragged\n";
						}
						int x = 0, x2 = 0, y = 0, y2 = 0;  //좌표 초기화
					}
				}
			}
		}

		// 게임 로직
		float deltaTime = clock.restart().asSeconds();

		cat.update(deltaTime);

		if (cat_is_clicked == true) {
			int x1 = Mouse::getPosition(window).x;
			int y1 = Mouse::getPosition(window).y;
			int move_pos_x = dragStartPosition.x - x1;
			int move_pos_y = dragStartPosition.y - y1;
			cout << x1 << " " << y1 << "\n";

			float ang = atan2(double(y1 - dragStartPosition.y), double(x1 - dragStartPosition.x)) * 180 / 3.141592;
			if (ang < 0) ang += 360;
			cat.setRotation(ang+180);

			float drag_dis = sqrt(pow(dragStartPosition.x - x1, 2) + pow(dragStartPosition.y - y1, 2)); //드래그한 거리
			if(drag_dis < 70)
				cat.setScale((float)(100 + drag_dis) / cat.getTextureSizeX(), (float)(100 - drag_dis) / cat.getTextureSizeY());
		}
		// 그리기
		window.clear(Color::White);

		if (jn.getLeftJump() <= 0) {
			// 일정 점수 이상이면 게임 클리어라고 뜨도록 해야함
			// 클리어한 경우 ...

			// 클리어하지 못한 경우
			game_status.setString("Game Over");
			game_status.setFillColor(Color::Red);
			window.draw(game_status);
		}
		else {
			window.draw(text);
			window.draw(floorSprite);
			window.draw(lightSprite);
			window.draw(girlSprite);
			window.draw(canSprite);
			cat.draw(window);
		}

		window.display();

		//사운드 수정중...
		Canned_Food can1;
		//can1.getCannedFoodSound(); //소리가 나는 동안 다음 문장이 실행이 안돼서 수행 속도가 떨어져요! 수정 필요해 보여요!
	}

	return 0;
}
