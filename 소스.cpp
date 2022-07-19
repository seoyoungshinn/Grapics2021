#include <GL/glut.h>
#include <math.h>
#include <vector>

int MX = 300, MY = 300;
GLfloat Delta = 0.0;
GLfloat Temp = 0.0;
GLfloat WheelTimer = 0.0;

void MyTimer(int Value) {
	WheelTimer = WheelTimer + 0.6;
	Delta = Delta + 5;
	Temp = Temp + 9;
	glutPostRedisplay();
	glutTimerFunc(1, MyTimer, 1);
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-35.0, 35.0, -35.0, 35.0, -100.0, 100.0); // 15가 좋은 view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(MX / 300.0, MY / 300.0, 1.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);  //시점변환
}
void MyMouseMove(GLint X, GLint Y) {
	MX = X;
	MY = Y;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(MX / 300.0, MY / 300.0, 1.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);  //시점변환
	glutPostRedisplay();
}
void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };
	GLfloat light_specular[] = { 1.0, 0.8, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 6, 3.0, 0.0 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

}


void DrawWheel() {
	
	//큰 도넛 (앞)
	glPushMatrix();
	glColor3f(0.2, 0.1,0.1);		//적갈색
	glTranslatef(0, 32.5, 0);
	glutSolidTorus(1.5, 20, 100, 6);
	glPopMatrix();


  
	//도넛 창살 (앞)
	glPushMatrix();
	glColor3f(0.3, 0.25, 0.22);		//갈색
	glTranslatef(0, 32.5, 0);
	glRotatef(30, 0, 0, 1);
	glScalef(1, 36, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 32.5, 0);
	glRotatef(150, 0, 0, 1);
	glScalef(1, 36, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 32.5, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(1, 36, 1);
	glutSolidCube(1);
	glPopMatrix();
	//

}



void DrawBasket() {
	glRotatef(sin(WheelTimer *0.055)*10, 0, 0, 1);   //그네 회전시에 델타 여기 걸면 됌 !!
	glTranslatef(0, -5, 0);		//기준점

	
	glPushMatrix();
	

		//스틱
		glPushMatrix();
		//glRotatef(Delta, 0, 0, 1);
		glTranslatef(0, 0, 6);
	
		glScalef(1, 10, 1);
	
		glutSolidCube(1);
		glPopMatrix();

		//스틱
		glPushMatrix();
		glTranslatef(0, 0, -6);
		glRotatef(0, 0, 0, 1);
		glScalef(1, 10, 1);
		glutSolidCube(1);
		glPopMatrix();

		// 바구니
		glPushMatrix();
		glTranslatef(0, -5, 0);
		glRotatef(90, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(1, 1, 0.45);
		glutSolidTorus(3.0, 2.5, 100, 100);
	
		glPopMatrix();

	glPopMatrix();

}

void DrawBasketBridge() {
	glColor3f(0.3, 0.25, 0.22);		//갈색
	glPushMatrix();
	glTranslatef(9, 32.5 - 16, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 12, 1);
	glutSolidCube(1);
	glPopMatrix();
}

void DrawBasketBridge6() {
	//기준
	glColor3f(0.4, 0.2, 0.2);		//적보라
	glTranslatef(-9, 16, 0);

	//1시
	glPushMatrix();

	glTranslatef(9, 16, 0);
	DrawBasketBridge();
	glPopMatrix();

	//3시
	glPushMatrix();
	glTranslatef(18, 0, 0);
	DrawBasketBridge();
	glPopMatrix();

	//5시
	glPushMatrix();
	glTranslatef(9, -16, 0);
	DrawBasketBridge();
	glPopMatrix();

	//7시
	glPushMatrix();
	glTranslatef(-9, -16, 0);
	DrawBasketBridge();
	glPopMatrix();

	//9시
	glPushMatrix();
	glTranslatef(-18, 0, 0);
	DrawBasketBridge();
	glPopMatrix();

	//11시
	glPushMatrix();
	glTranslatef(-9, 16, 0);
	DrawBasketBridge();
	glPopMatrix();

}

void DrawBasket6() {


	glPushMatrix();
		glColor3f(0.7, 0.2, 0.4);	//핫핑크
		glTranslatef(cos((WheelTimer + 60) * 0.0175) * 19 , sin((WheelTimer+60) * 0.0175) * 19-1	, 0);
		DrawBasket();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(cos((WheelTimer-60) * 0.0175) * 19, sin((WheelTimer-60) * 0.0175) * 19 - 1, 0);
		DrawBasket();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(cos((WheelTimer + 180) * 0.0175) * 19, sin((WheelTimer + 180) * 0.0175) * 19 - 1, 0);
		DrawBasket();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.5, 0.2, 0.4);	//진핑크
		glTranslatef(cos((WheelTimer) * 0.0175) * 19, sin((WheelTimer) * 0.0175) * 19 - 1, 0);
	DrawBasket();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(cos((WheelTimer + 120) * 0.0175) * 19, sin((WheelTimer + 120) * 0.0175) * 19 - 1, 0);
		DrawBasket();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(cos((WheelTimer-120) * 0.0175) * 19, sin((WheelTimer-120 ) * 0.0175) * 19-1, 0);
		DrawBasket();
	glPopMatrix();



}


void DrawFerrisWheel() {		//관람차 합체



	

//얇은기둥

	glColor3f(0.186, 0.157, 0.209);		//쥐색
	glPushMatrix();
	glTranslatef(0, 25, 0);
	glScalef(1, 8, 1);
	glutSolidCube(2);
	glPopMatrix();
	
//기둥
	glPushMatrix();
	glTranslatef(0, 9, 0);
	glScalef(1, 4, 1);
	glutSolidCube(4);
	glPopMatrix();

//받침
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(0, 0, 0);
	glutSolidCone(6, 9, 100, 100);
	glPopMatrix();

	//움직여야함
	glPushMatrix();
	glTranslatef(0, 32.5, 0);		//회전 기준점


	//회전축
		glPushMatrix();
		glRotatef(Delta, 0, 0, 1);
		//glTranslatef(0, 32.5, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(1, 6, 1);
		glutSolidCube(2);
		glPopMatrix();

	//큰 바퀴 두개 
		glPushMatrix();
			glRotatef(WheelTimer, 0, 0, 1);		//회전축 기준으로 뱅글뱅글
			glTranslatef(0, -32.5, 6);
			DrawWheel();
			glTranslatef(0, 0, -12);
			DrawWheel();
		glPopMatrix();

	//도넛 브릿지 6개
		glPushMatrix();
		glRotatef(WheelTimer, 0, 0, 1);
			glTranslatef(0, -32.5, 0);
			DrawBasketBridge6();
		glPopMatrix();

	//바구니 6개
		glPushMatrix();
			DrawBasket6();
		glPopMatrix();



	
	glPopMatrix();

}







void DropSeatStick() {  // 자이로드롭 좌석 1개, 원점 기준, 
	//glutSolidCube(5);
	
	//막대기
	glPushMatrix();
	glTranslatef(0, -6.5, 0);
	glScalef(0.7, 10, 1);
	glutSolidCube(1);
	glPopMatrix();

	//좌석
	glPushMatrix();
	glTranslatef(0, -12, 0);
	//glutSolidCube(3);
	glScalef(1.7, 0.9, 1.7);
	glutSolidDodecahedron();
	glPopMatrix();

}

void DropSeat() {
	//glutSolidCube(5);
	glRotatef(90, 1, 0, 0);
	glRotatef(sin(Delta * 0.08) * 13 - 90, 1, 0, 0);

   //막대기
	glPushMatrix();
	glTranslatef(0, -6.5, 0);
	glScalef(0.7, 10, 1);
	glutSolidCube(1);
	glPopMatrix();

	//좌석
	glPushMatrix();
	glTranslatef(0, -12, 0);
	//glutSolidCube(3);
	glScalef(1.7, 0.9, 1.7);
	glutSolidDodecahedron();
	glPopMatrix();



}

void DropSeat6() {


	//기준 자이로드롭 꼭대기, 시계방향으로
	glColor3f(0.6, 0.5, 0.5);  //연분홍	
	
	glPushMatrix();
		glTranslatef(-18, 0, 0);
		DropSeat();
	glPopMatrix();

	glPushMatrix();

		glTranslatef(9, 0, 18);
		DropSeat();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(9, 0, -18);
		DropSeat();
	glPopMatrix();


	glColor3f(0.4, 0.3, 0.8);  //보라
	glPushMatrix();
		glTranslatef(18, 0, 0);
		DropSeat();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-9, 0, -18);
		DropSeat();
	glPopMatrix();



	glPushMatrix();
		glTranslatef(-9, 0, 18);
		DropSeat();
	glPopMatrix();
}


void DrawDropTop() {			//자이로드롭 합체

	//받침
	glPushMatrix();
	glColor3f(0.1, 0.2, 0.4);  //남색
	glRotatef(270, 1, 0, 0);
	glTranslatef(0, 0, 0);
	glutSolidCone(6, 9, 100, 100);
	glPopMatrix();

	//기둥
	glPushMatrix();
	glTranslatef(0, 12, 0);
	glScalef(1, 6, 1);
	glutSolidCube(4);
	glPopMatrix();

	//얇은기둥
	glPushMatrix();
	glTranslatef(0, 30, 0);
	glScalef(1, 13, 1);
	glutSolidCube(2);
	glPopMatrix();


	///////////////////////////////////////////////////
	//기준점
	glColor3f(0.1, 0.4, 0.5);  //하늘색
	glTranslatef(0, 43, 0);
	glutSolidCube(5);


	//누운도넛, -20까지만 떨어지도록
	glPushMatrix();
		glTranslatef(0, sin(Delta * 0.015) * 10 -10, 0);
		glTranslatef(0, 0, -32);	//기본 위치, 가운데가 Z축임
		glRotatef(90, 1, 0, 0);		//누운 도넛
		DrawWheel();
	glPopMatrix();

	//좌석 6개 붙이기
	glPushMatrix();
		glTranslatef(0, sin(Delta * 0.015) * 10 - 10, 0);
		DropSeat6();
	glPopMatrix();



}

void Fire() {		//불꽃
	glPushMatrix();
	glScalef(1, 2, 1);
	glutSolidOctahedron();
	glPopMatrix();

}

void DrawFestival() {	//폭죽
	
	Fire();

		//	glTranslatef(0, 30, 0);  //얘가 기준점 ㅎㅏ면 되겟다

	glColor3f(0.8, 0.8, 0.4);
	glTranslatef(0, 0, 4);
	Fire();
	glColor3f(0.9, 0.2, 0.1);
	glTranslatef(0, 0, -8);
	Fire();
	glColor3f(0.1, 0.8, 0.8);
	glTranslatef(4, 0, 4);
	Fire();
	glColor3f(0.3, 0.6, 0.3);
	glTranslatef(-8, 0, 4);
	Fire();
	glColor3f(0.6, 0.3, 0.3);
	glTranslatef(0, 0, 2);
	Fire();
	glColor3f(0.1, 0.9, 0.0);
	glTranslatef(3, 0, -2);
	Fire();
	glColor3f(0.4, 0.2, 0.9);
	glTranslatef(-3, 0, 2);
	Fire();
	
}
void DrawFlowers() {
	glPushMatrix();

	//받침
	glColor3f(0.4, 0.8, 0.4);
	glPushMatrix();
	glTranslatef(-18, 0, 0);
		glPushMatrix();
			glRotatef(90, 0, 1, 0);
			glRotatef(45, 1, 0, 0);
			glTranslatef(0, 12, 0);
			glutSolidCone(4, 13, 100, 100);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18, 0, 0);
		glPushMatrix();
			glRotatef(270, 0, 1, 0);
			glRotatef(45, 1, 0, 0);
			glTranslatef(0, 12, 0);
			glutSolidCone(4, 13, 100, 100);
		glPopMatrix();
	glPopMatrix();


	glPushMatrix();
		glTranslatef(0, 13, 0);

		glPushMatrix();		//줄기
		glColor3f(0.1, 0.5, 0.2);
			glScalef(1, 13, 1);
			glutSolidCube(2);
		glPopMatrix();


		glPushMatrix();		//꽃 회전
			glTranslatef(0, 10, 0);
			glRotatef(Delta, 0, 0, 1);
	


				//꽃잎 여섯장	
				glPushMatrix();
				glColor3f(0.8, 0.4, 0.1);
					glTranslatef(0,6.8, 0);
					glutSolidTorus(3.0, 2.5, 100, 100);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(6.5,3.5, 0);
					glutSolidTorus(3.0, 2.5, 100, 100);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(6.5,-3, 0);
					glutSolidTorus(3.0, 2.5, 100, 100);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0, -6.8, 0);
					glutSolidTorus(3.0, 2.5, 100, 100);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-6.5, -3, 0);
					glutSolidTorus(3.0, 2.5, 100, 100);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-6.5, 3.5, 0);
					glutSolidTorus(3.0, 2.5, 100, 100);
				glPopMatrix();
				//

				glPushMatrix();
				glColor3f(0.8, 0.8, 0.1);
				glScalef(2.2, 2.2, 2.2);
				glutSolidDodecahedron();		//봉오리
				glPopMatrix();

		glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	
	}


void DrawA() {
	glPushMatrix();		//줄기
	glScalef(1, 13, 1);
	glutSolidCube(2);
	glPopMatrix();
}




void MyDisplay() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.4, 0.7, 0.65);// 잔디밭 색
	 
	glPushMatrix();
		glScalef(40, 0.8, 40); // x-z방향 넓은 판
		glutSolidCube(1.5);
	glPopMatrix();


//	glPopMatrix();


	glPushMatrix();

		glTranslatef(8, 0, -11);
		glScalef(0.4, 0.4, 0.4);		
		DrawFerrisWheel();
	glPopMatrix();


	glPushMatrix();
		glColor3f(0.3, 0.6, 0.3);
		glTranslatef(-8, 0, 14);
		glScalef(0.4, 0.4, 0.4);
		DrawDropTop();
	glPopMatrix();

	

	glPushMatrix();
		glScalef(0.4, 0.4, 1);
		glTranslatef(0, 80, 0);
		glRotatef(Delta, 0, 0, 0);		//폭죽1
		DrawFestival();
	glPopMatrix();


	glPushMatrix();
		glScalef(0.4, 0.4, 1);
		glTranslatef(0, 80, 0);
		glRotatef(Temp, 0, 0, 0);		//폭죽2
		DrawFestival();
	glPopMatrix();

	glPushMatrix();
		glScalef(0.1, 0.1, 0.1);



		glPushMatrix();
			glTranslatef(180, 2, 280);
			DrawFlowers();
		glPopMatrix();



		glPushMatrix();
			glTranslatef(140, 2, 280);
			DrawFlowers();
		glPopMatrix();



		glPopMatrix();
	glPopMatrix();


	

	glFlush();
	glPopMatrix();

	

}


int main(int argc, char** argv) {
	glutInit(&argc, argv);               //GLUT 윈도우 함수
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL Drawing Example");
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	//glutIdleFunc(MyIdle);
	//glutSpecialFunc(MySpecial);
	glutMotionFunc(MyMouseMove);
	//glutKeyboardFunc(MyKeyboard);
	glClearColor(0.4, 0.4, 0.4, 1);
	InitLight();

	glutTimerFunc(400, MyTimer, 1);
	glutMainLoop();

	return 0;
}