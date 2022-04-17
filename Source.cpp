#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

GLfloat winWidth = 500, winHeight = 750;

class scrPt
{
public:
	float x, y, z;
	void print(const char* text = " ") {
		std::cout << text << ' ' << x << ' ' << y << ' ' << z << std::endl;
	}
	scrPt operator + (scrPt const& a) {
		scrPt res;
		res.x = x + a.x;
		res.y = y + a.y;
		res.z = z + a.z;
		return res;
	}
	scrPt operator - (scrPt const& a) {
		scrPt res;
		res.x = x - a.x;
		res.y = y - a.y;
		res.z = z - a.z;
		return res;
	}
};

class MasinaPolitie {
public:
	MasinaPolitie(int x, int y) {
		pozitie.x = x;
		pozitie.y = y;

		viteza.x = 0;
		viteza.y = 0;

		size.x = 60;
		size.y = 90;
	}

	void CameraTranslation() {
		glTranslated(0, -pozitie.y, 0);
	}

	void proceseaza() {
		const float deaccelerare = 0.005;
		const float acceleratie = 0.045;
		const float viteza_maxima = 5;
		const float viraj = 2;


		if (UP_PRESSED) {
			viteza.y += acceleratie;
		}
		if (DOWN_PRESSED) {
			viteza.y -= acceleratie;
		}

		viteza.x = 0;

		if (LEFT_PRESSED) {
			viteza.x = -viraj;
		}

		if (RIGHT_PRESSED) {
			viteza.x = viraj;
		}



		if (viteza.y > 0) {
			viteza.y -= deaccelerare;
			if (viteza.y < 0)
				viteza.y = 0;
		}

		else {
			viteza.y += deaccelerare;
			if (viteza.y > 0)
				viteza.y = 0;
		}

		if (viteza.y > viteza_maxima)
			viteza.y = viteza_maxima;
		if (viteza.y < -viteza_maxima)
			viteza.y = -viteza_maxima;

		pozitie = pozitie + viteza;

		UP_PRESSED = false;
		DOWN_PRESSED = false;
		RIGHT_PRESSED = false;
		LEFT_PRESSED = false;
	}

	void deseneaza() {
		proceseaza();
		glPushMatrix();
		glTranslated(pozitie.x, pozitie.y-300, 0);
		glScaled(scale, scale, scale);

		// MASINA DE POLITIE
		// sasiu
		glColor3f(0, 0, 0);
		glRectf(-30, -45, 30, -20);
		glColor3f(1, 1, 1);
		glRectf(-30, -20, 30, 20);
		glColor3f(0, 0, 0);
		glRectf(-30, 20, 30, 45);

		// stopuri
		glColor3f(1, 0, 0);
		glRectf(25 - 50, -185 + 135, 35 - 50, -180 + 135);
		glColor3f(1, 0, 0);
		glRectf(65 - 50, -185 + 135, 75 - 50, -180 + 135);

		// faruri
		glColor3f(0.8, 0.5, 0);
		glRectf(25 - 50, -90 + 135, 35 - 50, -85 + 135);
		glColor3f(0.8, 0.5, 0);
		glRectf(65 - 50, -90 + 135, 75 - 50, -85 + 135);

		glColor3f(1, 1, 0);
		glBegin(GL_TRIANGLES);
		glVertex2f(30 - 50, -85 + 135);
		glVertex2f(0 - 50, 0 + 135);
		glVertex2f(60 - 50, 0 + 135);

		glVertex2f(40 - 50, 0 + 135);
		glVertex2f(100 - 50, 0 + 135);
		glVertex2f(70 - 50, -85 + 135);

		glEnd();
		glPopMatrix();

	}
	scrPt pozitie, viteza, size;
	float scale=1.0f;
	bool UP_PRESSED, DOWN_PRESSED, LEFT_PRESSED, RIGHT_PRESSED;


}MasinaPolitie(0,0);


class MasinaTrafic {
public:

	MasinaTrafic(GLfloat x, GLfloat y, float rotatie) {
		this->pozitie.x = x;
		this->pozitie.y = y;
		this->rotatie = rotatie;
		directie.x = 0;
		directie.y = 0;

		size.x = 60;
		size.y = 100;
	}

	void deseneaza() {
	
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glPushMatrix();
		glTranslated(pozitie.x, pozitie.y, 0);
		MasinaPolitie.CameraTranslation();
		glRotated(this->rotatie, 0, 0, 1);
		
	
		glColor3f(0.0, 0, 0);
		glRectf(30, -50, -30, 50);


		//Roti
		glColor3f(0.7, 1, 0);//Culoare
		glRectf(35, -40, 30, -30);
		glRectf(35, 30, 30, 40);
		glRectf(-30, -40, -35, -30);
		glRectf(-30, 30, -35, 40);

		//geamuri
		glColor3f(0, 0.5, 1.0f);
		glRecti(26, -40, -26, 25);

		//plafon
		glColor3f(0, 0, 0);
		glRecti(23, -35, -23, 14);

		//Conturi geamuri
		glLineWidth(3);
		glBegin(GL_LINES);

		glVertex2i(-23, 14);
		glVertex2i(-26, 25);

		glVertex2i(23, 14);
		glVertex2i(26, 25);

		glVertex2i(-23, -35);
		glVertex2i(-26, -40);

		glVertex2i(23, -35);
		glVertex2i(26, -40);

		glLineWidth(2);
		glVertex2i(-30, -10);
		glVertex2i(30, -10);

		glEnd();
		glPopMatrix();

	}
	scrPt pozitie, directie, size;
	float rotatie;


};
MasinaTrafic Test(100, 100, 45), Test2(50, 50, 89);

static void init(void)
{
	glClearColor(0.6235294, 0.239215, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-winWidth/2,winWidth/2 , -winHeight/2,winHeight/2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-newWidth/2, newWidth/2, -newHeight/2, newHeight/2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	glClear(GL_COLOR_BUFFER_BIT);
}

void mouse(int button, int state, int x)
{
	switch (button) {
	case GLUT_KEY_LEFT:
		MasinaPolitie.LEFT_PRESSED = true;
		break;
	case GLUT_KEY_RIGHT:
		MasinaPolitie.RIGHT_PRESSED = true;
		break;
	case GLUT_KEY_UP:
		MasinaPolitie.UP_PRESSED = true;
		break;

	case GLUT_KEY_DOWN:
		MasinaPolitie.DOWN_PRESSED = true;
		break;
	default:
		break;
	}
}


class Trafic {
private:
	std::vector<MasinaTrafic*> masini;
	int nr_masini = 0;

public:
	Trafic(int nr_masini, int offset, int distanta, float rotire) {
		this->nr_masini = nr_masini;
		for (int i = 0; i < nr_masini; i++) {
			masini.push_back(new MasinaTrafic(offset, i * distanta, rotire));

		}
	}

	bool Coliziune(MasinaTrafic masina) {
		return (MasinaPolitie.pozitie.x + MasinaPolitie.size.x >= masina.pozitie.x &&
			MasinaPolitie.pozitie.x <= masina.pozitie.x + masina.size.x &&
			MasinaPolitie.pozitie.y - 300 + MasinaPolitie.size.y >= masina.pozitie.y &&
			MasinaPolitie.pozitie.y - 300 <= masina.pozitie.y + masina.size.y);

	}

	void Deseneaza() {
		for (int i = 0; i < this->nr_masini; i++) {
			masini[i]->deseneaza();
			if (Coliziune(*masini[i])) {
				MasinaPolitie.scale *= 1.03f;
				masini.erase(masini.begin()+i);
			}
		}
	}

};
Trafic id1(37, -150, 570, 180);
void desenDrum(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// DRUMUL
	glColor3f(0.2, 0.2, 0.2);
	glRectf(-200., -1000., 200., 1000.);
	// Linia ce separa benzile
	glColor3f(1, 1, 1);
	glRectf(-10., -1000., 10., 1000.);
	//Translatie camera
	MasinaPolitie.CameraTranslation();

	glEnable(GL_LINE_STIPPLE);//linie intrerupta
	glLineStipple(4, 0X00FF);
	glLineWidth(7.0);// grosime linie
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2i(-100, 50000);
	glVertex2i(-100, -50000);

	glVertex2i(100, 50000);
	glVertex2i(100, -50000);
	glEnd();

	MasinaPolitie.deseneaza();
	id1.Deseneaza();

	

	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Trafic - Masina de politie");

	init();

	glutDisplayFunc(desenDrum);
	glutReshapeFunc(winReshapeFcn);


	glutSpecialFunc(mouse);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glutMainLoop();

}
