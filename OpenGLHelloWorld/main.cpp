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
			glClearColor(255, 0, 0, 0);
			break;
		case 'b':
			glClearColor(0, 0, 255, 0);
			break;
		case 'v':
			glClearColor(0, 255, 0, 0);
			break;
		case 'n':
			glClearColor(0, 0, 0, 0);
			break;
		case 'm':
			glClearColor(127, 255, 255, 0);
			break;
		case 't':
			glClearColor(64, 224, 208, 0);
			break;
		case 'o':
			glClearColor(255, 128, 0, 0);
			break;
		default:
			glClearColor(255, 255, 255, 0);
			break;
	}

	//	redessiner la fenêtre
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	//	Écrire ici le code d’initialisation
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Laboratoire 1");

	//	enregistre les fonctions de rappel
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(getKeyStroke);

	//	démarre la boucle de traitement des événements 
	glutMainLoop();

	return 0;
}

