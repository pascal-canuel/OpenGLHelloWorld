#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

GLclampf randomColorValue()
{
	double random = rand() % 100 + 1;
	return (GLclampf)(random / 100);
}

//	Fonction de rendu
void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//	Fonction de rappel pour capture les touches du clavier
void getKeyStroke(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		glClearColor(1, 0, 0, 0);
		break;
	case 'b':
		glClearColor(0, 0, 1, 0);
		break;
	case 'v':
		glClearColor(0, 1, 0, 0);
		break;
	case 'n':
		glClearColor(0, 0, 0, 0);
		break;
	case 'm':
		glClearColor(0.5, 0, 1, 0);
		break;
	case 't':
		glClearColor(0.25, 0.88, 0.82, 0);
		break;
	case 'o':
		glClearColor(1, 0.5, 0, 0);
		break;
	case '\x1b':	//	ECHAP
		glutLeaveMainLoop();
		break;
	default:
		glClearColor(1, 1, 1, 0);
		break;
	}

	//	redessiner la fen�tre
	glutPostRedisplay();
}

//	Fonction de rappel pour capture les touches sp�ciales du clavier
void getSpecialKeyStroke(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		glutFullScreen();
		break;
	case GLUT_KEY_DOWN:
		glutLeaveFullScreen();
		break;
	case GLUT_KEY_RIGHT:
	{
		//	TODO la fen�tre doit toujours �tre visible en entier, peu importe sa grandeur
		int width = glutGet(GLUT_WINDOW_WIDTH), height = glutGet(GLUT_WINDOW_HEIGHT);
		int borderWidth = glutGet(GLUT_SCREEN_WIDTH), borderHeight = glutGet(GLUT_SCREEN_HEIGHT);

		width >= borderWidth ? width = borderWidth : width += 50;
		height >= borderHeight ? height = borderHeight : height += 50;

		glutReshapeWindow(width, height);
		break;
	}
	case GLUT_KEY_LEFT:
		glutReshapeWindow(glutGet(GLUT_WINDOW_WIDTH) - 50, glutGet(GLUT_WINDOW_HEIGHT) - 50);
		break;
	case GLUT_KEY_F1:
	{
		glutReshapeWindow(glutGet(GLUT_SCREEN_WIDTH) / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2);
		glutPositionWindow(0, 0);
	}
	break;
	case GLUT_KEY_F2:
	{
		int halfWidth = glutGet(GLUT_SCREEN_WIDTH) / 2, halfHeight = glutGet(GLUT_SCREEN_HEIGHT) / 2;
		glutReshapeWindow(halfWidth, halfHeight);
		glutPositionWindow(halfWidth, halfHeight);
	}
	break;
	case GLUT_KEY_F3:
	{
		int halfWidth = glutGet(GLUT_SCREEN_WIDTH) / 2, halfHeight = glutGet(GLUT_SCREEN_HEIGHT) / 2;
		glutReshapeWindow(halfWidth, halfHeight);
		glutPositionWindow(halfWidth / 2, halfHeight / 2);
	}
	break;
	case GLUT_KEY_F4:
		glClearColor(randomColorValue(), randomColorValue(), randomColorValue(), 0);
		glutPostRedisplay();
		break;
	}
}


int main(int argc, char **argv)
{
	//	initialiser la valeur de base utilis�e pour la fonction rand()
	srand((int)time(0));

	//	�crire ici le code d�initialisation
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Laboratoire 1");

	//	enregistre les fonctions de rappel
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(getKeyStroke);
	glutSpecialFunc(getSpecialKeyStroke);

	//	d�marre la boucle de traitement des �v�nements 
	glutMainLoop();

	return 0;
}

