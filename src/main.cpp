#include "obj_loader/objLoader.h"
#include "main.h"
#include "pipeline.h"

objLoader* objData;
double angle = 0.0f;
CGDraw CG;

void MyGlDraw(void)
{
	//Inicializa o Pipeline, carregando a identidade nas matrizes básicas
	init();
	
	//Cria a câmera
	createCamera(
		0.0f, 0.0f, 5.0f,	// posição da câmera
		0.0f, 0.0f, 0.0f,	// ponto para o qual a camera está olhando
		0.0f, 1.0f, 0.0f	// vetor "up"
	);
	
	//Construção da Janela de Projeção
	viewportGL(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
	
	//Distância d do View Plane
	viewPlaneDGL(2.1);

	//Matriz de Rotação
	// rotateGL(angle, 0.0f, 1.0f, 0.0f);
	// rotateGL(angle, 1.0f, 0.0f, 0.0f);
	//Velocidade da rotação uniforme
	// angle += 0.01f;

	// shearGL(0.9f,0.0f,0.0f);
	// scaleGL(1,3,1);
	
	//Limpa o Color Buffer
	memset(FBptr, 0, IMAGE_WIDTH * IMAGE_HEIGHT * 4);
	
	//Cria os 3 vértices do triângulo
	std::tuple <int,int> piXel[3];
	//cor do obj
	tuple <int,int,int,int> RGBA2 (0,255,0,255); //Verde
	tuple <int,int,int,int> RGBA3 (0,0,255,255); //Azul
	tuple <int,int,int,int> RGBA1 (255,0,0,255); //vermelho

	
	for(int f = 0; f < objData->faceCount; f++) {
		obj_face* obj = objData->faceList[f];
		
		for(int i = 0; i < 3; i++) {
			//Faz uma séria de multiplicações de matrizes para obter os pontos na coordenada de tela
			Point p = createPipeline(
				
				objData->vertexList[obj->vertex_index[i]]->e[0],
				objData->vertexList[obj->vertex_index[i]]->e[1],
				objData->vertexList[obj->vertex_index[i]]->e[2]
			);

			//Com os pontos de coordenada de tela obtidos, cria os pixels que serão os vértices dos triângulos
		  piXel[i] = std::make_tuple (p.x,p.y);       // move assignment
		}
		
		//Desenha o triângulo ligando os seus vértices
		//Utiliza o bresenham criado na atividade anterior
		CG.DrawTriangle(piXel[0],piXel[1],piXel[2],RGBA3,RGBA2,RGBA3);
	}
}

//********************************************************************************
int main(int argc, char **argv)
{
	//Cria o objeto que carrega o modelo
	objData = new objLoader();
	//A carga do modelo é indicada atraves do nome do arquivo. 
	objData->load((char*)argv[1]);

	//Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	//Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	//Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

