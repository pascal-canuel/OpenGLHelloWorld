#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Shader_Loader.h"

float posXndc;
float posYndc;

GLuint program;

GLclampf randomColorValue()
{
	double random = rand() % 100 + 1;
	return (GLclampf)(random / 100);
}

void createDrawing() 
{
	glLineWidth(15.0);

	GLfloat sommets[20] = { -0.5f, 0.0f, 0.0f,1.0f,   
							0.5f, 0.0f, 0.0f,1.0f,   
							-0.25f, -1.0f, 0.0f,1.0f,  
							0.0f, 0.5f, 0.0f, 1.0f,   
							0.25f, -1.0f, 0.0f,1.0f };
	GLuint buffSommets;
	glGenBuffers(1, &buffSommets); //	Création du buffer
	glEnableVertexAttribArray(0); //	Activation du buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffSommets); //	Binding du buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(sommets), sommets, GL_STREAM_DRAW); //	Insertion des données dans le buffer	
	glVertexAttribPointer(0, 4, GL_FLOAT, FALSE, 0, NULL); //	Explication des données du buffer
	

	GLfloat couleurs[20] = { 0.5f, 0.0f, 0.0f,1.0f,   
							0.5f, 0.0f, 0.0f,1.0f,  
							0.0f, 1.0f, 0.0f,1.0f,  
							0.0f, 0.0f, 1.0f, 1.0f,   
							0.0f, 1.0f, 0.3f,1.0f };

	GLuint buffCouleurs;
	glGenBuffers(1, &buffCouleurs); //	Création du buffer
	glEnableVertexAttribArray(1); //	Activation du buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffCouleurs); //	Binding du buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(couleurs), couleurs, GL_STREAM_DRAW); //	Insertion des données dans le buffer	
	glVertexAttribPointer(1, 4, GL_FLOAT, FALSE, 0, NULL); //	Explication des données du buffer	
}

//	Fonction de rendu
void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);

	glPointSize(15.0);
	//glLineWidth(15);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//createDrawing();
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDrawArrays(GL_LINES, 0, 4);
	//glDrawArrays(GL_LINES, 2, 4);

	GLfloat sommets[4] = { posXndc, posYndc, 0.0f,1.0f };
	GLuint buffSommets;
	glGenBuffers(1, &buffSommets); //	Création du buffer
	glEnableVertexAttribArray(0); //	Activation du buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffSommets); //	Binding du buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(sommets), sommets, GL_STREAM_DRAW); //	Insertion des données dans le buffer	
	glVertexAttribPointer(0, 4, GL_FLOAT, FALSE, 0, NULL); //	Explication des données du buffer

	glDrawArrays(GL_POINTS, 0, 1);


	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);

	glFlush();
}

void getMouse(int button, int state, int x, int y)
{
	int w = glutGet(GLUT_WINDOW_WIDTH);
	float Xndc = roundf((((float)x * (1 + 1)) / glutGet(GLUT_WINDOW_WIDTH) - 1)  * 100) / 100;
	float Yndc = roundf(((-1.0 * (y - glutGet(GLUT_WINDOW_HEIGHT)) * (1 + 1)) / glutGet(GLUT_WINDOW_HEIGHT) - 1) * 100) / 100;

	if (GLUT_LEFT_BUTTON == button && GLUT_DOWN == state) {
		std::cout << "X: " << x << std::endl;
		std::cout << "Xndc: " << Xndc << std::endl;
		posXndc = Xndc;
		posYndc = Yndc;
	}
	else if (GLUT_RIGHT_BUTTON == button && GLUT_DOWN == state) {
		std::cout << "Y: " << y << std::endl;
		std::cout << "Yndc: " << Yndc << std::endl;
		posXndc = Xndc;
		posYndc = Yndc;
	}
		
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
	{
		glDeleteProgram(program);
		glutLeaveMainLoop();
		break;
	}	
	default:
		glClearColor(1, 1, 1, 0);
		break;
	}

	//	redessiner la fenêtre
	glutPostRedisplay();
}

//	Fonction de rappel pour capture les touches spéciales du clavier
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
		//	TODO la fenêtre doit toujours être visible en entier, peu importe sa grandeur
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
	//	initialiser la valeur de base utilisée pour la fonction rand()
	srand((int)time(0));

	//	Écrire ici le code d’initialisation
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Laboratoire 1");

	glewInit();

	//	enregistre les fonctions de rappel
	//createDrawing();
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(getKeyStroke);
	glutSpecialFunc(getSpecialKeyStroke);
	glutMouseFunc(getMouse);
	//	fonction de rappel de la fermeture de l’application ???

	Core::Shader_Loader shaderLoader;
	
	program = shaderLoader.CreateProgram((char *)"Vertex_Shader.glsl", (char *)"Fragment_Shader.glsl");

	//	démarre la boucle de traitement des événements 
	glutMainLoop();

	return 0;
}

