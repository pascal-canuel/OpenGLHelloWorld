#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>

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
		default:
			glClearColor(1, 1, 1, 0);
			break;
	}

	//	redessiner la fen�tre
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	//	�crire ici le code d�initialisation
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Laboratoire 1");

	//	enregistre les fonctions de rappel
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(getKeyStroke);

	//	d�marre la boucle de traitement des �v�nements 
	glutMainLoop();

	return 0;
}

