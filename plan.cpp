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

//점프할 고양이 클래스
class Jumping_Cat
{
private:
	//직사각형으로 구현
	RectangleShape jumping_cat;
	double posX; //왼쪽 위 x좌표
	double posY; //왼쪽 위 y좌표
	double width;
	double height;
	double angle;
	double power; //많이 당길수록 파워 증가 -> 포물선이 길어진다
	double velocity;
    //고양이의 능력(시간 여유 시 구현, 일정 스테이지 이상 클리어 시 새로운 고양이를 준다, 고양이별로 각자의 능력을 가짐, 충돌 전 클릭을 하면 고양이의 능력이 발현(ex-분신술))
    //-> 기본 고양이를 부모 클래스로 해서 여러 능력을 가진 고양이들을 상속으로 구현
public: 
	//생성자
	Jumping_Cat() {
		posX = 100;
		posY = 200;
		width = 20;
		height = 8;
		angle = 45;
		power = 0;
		velocity = 2;
	}
	
	//소멸자
	~Jumping_Cat() {

	}
	
	//직사각형 반환
	RectangleShape getJumpingCat()
	{
		return jumping_cat;
	}
	//위치좌표, 크기, 각도, 파워(속도?, 가속도?), 공격력 setter/getter
    //이동(move)
	//고양이 크기 조절(마우스로 당기면 늘어나도록 떼면 줄어들도록)(크기 setter/getter랑 같을 수도)
    //고양이 각도 조절(마우스 위치에 따라서 변경)(각도 setter/getter랑 같을 수도)
    //충돌 시 visual,sound effect
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
public:
	//생성자, 소멸자
	Arc(float x, float y, float r)
	{
		posX = x;
		posY = y;
		radius = r;

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
	
	//이동(move)
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
		sizeY = 10.0
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
		this->sizeY = sizeY
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
	void setObstaclePos(double posX,double posY){
		this->posX;
		this->posY;
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
	
	//고양이가 바닥에 닿으면 게임 오버
};

//점수 클래스
class Score
{
private:
	//현재점수
	//최고점수
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
	}
	
	//위치, 크기 등 setter/getter
	//현재점수 반환
	//현재점수 업데이트(통조림의 크기, 개수, 파괴한 장애물에 따라 점수 부여)
	//최고점수 반환 
	//최고점수 업데이트
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
	Texture catTexture;
	catTexture.loadFromFile("./Data/Image/cat.png");
	Vector2u catTextureSize = catTexture.getSize();
	Sprite catSprite(catTexture);
	catSprite.setScale((float)100 / catTextureSize.x, (float)100 / catTextureSize.y);
	catSprite.setPosition(200, 200);

	//사람 스프라이트 생성
	Texture manTexture;
	manTexture.loadFromFile("./Data/Image/man.png");
	Vector2u manTextureSize = manTexture.getSize();
	Sprite manSprite(manTexture);
	manSprite.setScale((float)100 / manTextureSize.x, (float)100 / manTextureSize.y);
	manSprite.setPosition(0, 0);

	//캔 스프라이트 생성
	Texture canTexture;
	canTexture.loadFromFile("./Data/Image/canned_food.jpg");
	Vector2u textureSize = canTexture.getSize();
	Sprite canSprite(canTexture);
	canSprite.setScale((float)100 / textureSize.x, (float)100/textureSize.y);
	canSprite.setPosition(100, 100);

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
	text.setFillColor(Color::Yellow);
	text.setPosition(jn.getPosX(), jn.getPosY());

	int x = 0, x2 = 0, y = 0, y2 = 0;  //드래그 처리를 위한 좌표 초기화
	int cat_is_clicked = 0;            //마우스로 고양이를 클릭했는지 저장할 변수
	while (window.isOpen())
	{
		// 이벤트 처리
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					x = event.mouseButton.x;
					y = event.mouseButton.y;
					if (x > 200 && x < 300 && y > 200 && y < 300)
						cat_is_clicked = 1;
					cout << x << " " << y << "\n";
				}
			}
			else if (event.type == Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					x2 = event.mouseButton.x;
					y2 = event.mouseButton.y;
					cout << x2 << " " << y2 << "\n";

					// 드래그를 너무 조금했을 때는 무시하고 아니면 날아감
					int diffX = x - x2;
					int diffY = y - y2;
					if (abs(diffX) <= 20 && abs(diffY) <= 20) {
						int x = 0, x2 = 0, y = 0, y2 = 0;  //좌표 초기화
						cat_is_clicked = 0;
					}
					else {
						//고양이를 다시 원본 크기로
						if (cat_is_clicked == 1) {
							cat_is_clicked = 0;
							//날아가는 코드 구현
							cout << "Flying\n";
						}
						cout << "Dragged\n";
					}
				}
			}
		}

		// 게임 로직

		// 그리기
		window.clear();

		window.draw(text);
		window.draw(floorSprite);
		window.draw(catSprite);
		window.draw(canSprite);

		window.display();

		//사운드 수정중...
		Canned_Food can1;
		can1.getCannedFoodSound();
	}

	return 0;
}
