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
//스테이지 클래스
class stage
{
private:

public:

};

//발사할 고양이 클래스
class Jumping_Cat
{
private:
  //변수(필드)
  //위치좌표, 크기, 각도, 파워(속도?, 가속도?), 공격력(파워와 같을 수 있음, 장애물을 파괴하기 위함)
  
public:
  //함수(메소드)
  //생성자, 소멸자?
  //위치좌표, 크기, 각도, 파워(속도?, 가속도?), 공격력 setter/getter
  //이동(move)
  //크기조절(마우스로 당기면 늘어나도록 떼면 줄어들도록)(크기 setter/getter랑 같을 수도)
  //각도조절(마우스 위치에 따라서 변경)(각도 setter/getter랑 같을 수도)
};

//통조림 클래스
class Canned_Food
{
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


//땅 클래스
class land
{
private:
	//위치좌표,크기
public:
	//생성자,소멸자
	//위치좌표,크기
	//통조림이 땅에 떨어졌을때 점수 부여?
};

//점수 클래스
class score
{
private:
	//현재점수
	//최고점수
public:
	//생성자, 소멸자 
	//현재점수 반환
	//현재점수 업데이트
	//최고점수 반환 
	//최고점수 업데이트
};

//별 클래스
class star
{
private:
	//현재 별 개수
	//최대 별 개수
public:
	//현재 별 개수 반환
	//별 추가
	//별 최대 개수 업데이트

};
