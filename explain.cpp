
//fortress_ex.cpp 파일의 포물선(arc)조절 및 포탄(고양이) 발사(이동) 방법
/*
{
if (isAim == true)
		{
			int tLDrawCount = 0;

			tl.setTLPosX(tl.getCurrTLPositionX());
			tl.setTLPosY(tl.getCurrTLPositionY());

			tl.setTLVelocityX(a.getAPower());
			tl.setTLVelocityY(a.getAAngle());

			for (float tldt = 0; tldt <= 0.02; tldt += 0.0001)
			{
				if (tLDrawCount == 0 || tLDrawCount % 10 == 0)
				{
					window.draw(tl.getTargetLine());
				}

				tl.moveTargetLine(tldt);
				tLDrawCount++;
			}
		}


		if (dt <= 0.5 && isFire == true)
		{
			isMoving = true;

			window.draw(c.getCannonBall());

			c.moveCannonBall(0.02);
		}
		else
		{
			isFire = false;
			isMoving = false;
		}

		dt += 0.001;

		// 화면을 표시한다. 
		window.display();
	}
*/
