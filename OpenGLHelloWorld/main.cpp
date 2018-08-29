#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>

void renderScene()
{
	glClearColor(0, 0, 255, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc, char **argv)
{
	//	�crire ici le code d�initialisation
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Laboratoire 1");

	//	enregistre la fonction de rendu
	glutDisplayFunc(renderScene);

	//	d�marre la boucle de traitement des �v�nements 
	glutMainLoop();

	return 0;
}
