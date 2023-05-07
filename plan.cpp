#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
#include <vector>
#include <time.h>
#include <stdlib.h>

using namespace std;
using namespace sf;

// 필요한 객체와 기능을 생각해보기(어떤 클래스, 어떤 변수, 어떤 함수 ?)

//발사할 고양이 클래스
class Jumping_Cat
{
  //직사각형으로 구현하면 좋을 듯
private:
  //변수(필드)
  //위치좌표, 크기, 각도, 파워(속도?, 가속도?), 공격력(파워와 같을 수 있음, 장애물을 파괴하기 위함)
  //고양이의 능력(시간 여유 시 구현, 일정 스테이지 이상 클리어 시 새로운 고양이를 준다, 고양이별로 각자의 능력을 가짐, 충돌 전 화면을 탭하면 고양이의 능력이 발현(ex-분신술))
  //-> 기본 고양이를 부모 클래스로 해서 여러 능력을 가진 고양이들을 상속으로 구현
public: 
  //함수(메소드)
  //생성자, 소멸자?
  //위치좌표, 크기, 각도, 파워(속도?, 가속도?), 공격력 setter/getter
  //이동(move)
  //고양이 크기 조절(마우스로 당기면 늘어나도록 떼면 줄어들도록)(크기 setter/getter랑 같을 수도)
  //고양이 각도 조절(마우스 위치에 따라서 변경)(각도 setter/getter랑 같을 수도)
};

//포물선 클래스
class Arc
{
    //각도와 파워에 따라 포물선 조절(*파워게이지 따로 안 만들어도 됨)
private:
	//위치좌표, 크기, 각도
public:
	//생성자, 소멸자
	//위치좌표, 크기, 각도 setter/getter
	//이동(move)
};

//통조림 클래스
class Canned_Food
{
  //직사각형으로 구현하면 좋을 듯
private:
  //변수(필드)
  //위치좌표, 크기
  
public:
  //함수(메소드)
  //생성자, 소멸자?
  //위치좌표, 크기 setter/getter
};

//장애물1 클래스(츄르로 해도 괜찮을 듯)
class Obstacle1
{
  //장애물 여러 개 만들 때 상속으로 구현할지 논의 필요
  //직사각형으로 구현하면 좋을 듯
private:
  //변수(필드)
  //위치좌표, 크기, 장애물과 충돌했을때 장애물의 움직임(각도, 속도/가속도(중력가속도?), 등)->장애물이 움직이지 않고 그냥 장애물이 바로 파괴되는 방식으로 할지 논의 필요
  //+강도(장애물의 체력)
  
public:
  //함수(메소드)
  //생성자, 소멸자?
  //위치좌표, 크기, 강도, 등 setter/getter
  //이동(move)?
  //데미지 판정(고양이의 공격력으로 장애물의 체력 감소 적용)
};


//바닥 클래스
class Floor
{
private:
	//위치좌표,크기
public:
	//생성자,소멸자
	//위치좌표,크기
	//통조림이 땅에 떨어졌을때 점수 부여? or 그냥 고양이와 통조림이 충돌하면 점수 부여
};

//점수 클래스
class Score
{
private:
	//현재점수
	//최고점수
	//위치, 크기(글자 크기 등)
public:
	//생성자, 소멸자 
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
	//현재 별 개수
	//최대 별 개수
public:
	//현재 별 개수 반환
	//일정 점수 이상을 획득할 때마다 별 하나씩 추가
	//별 최대 개수 업데이트
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
	//현재 획득한 별 개수
	//획득한 최고 점수(default = 0)
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
	//현재 레벨
	//모은 별 개수
	//레벨업까지 모아야할 별 개수
public:
	//생성자, 소멸자 
	//위치, 크기, 레벨, 별개수 setter/getter
};

int main()
{
	// 창 생성
	sf::RenderWindow window(sf::VideoMode(800, 600), "Jumping cat");

	// 새 그래픽 스프라이트 생성
	sf::Texture catTexture;
	catTexture.loadFromFile("cat.png");
	sf::Sprite catSprite(catTexture);

	// 새 위치 설정
	catSprite.setPosition(400, 300);

	while (window.isOpen())
	{
		// 이벤트 처리
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// 게임 로직

		// 그리기
		window.clear();
		window.draw(catSprite);
		window.display();
	}

	return 0;
}
