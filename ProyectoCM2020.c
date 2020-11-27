#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n = 100; //número de particulas 
float particula[4][n];  //:  particula[0][i]: coordenada "x" de la particula i. particula[1][i]: coordenada "y" de la particula i.
                          //:  particula[2][i]: velocidad "x" de la particula i. particula[3][i]: velocidad "y" de la particula i.
float auxparticula[4][n];

//Definición de las parámetros a variar 

float e=2;  //valor de epsilon
float s=0.1; //valor de sigma
float t=30; //tiempo en el que se moverán las partículas
int l=1000;  
float dt=0.03; //valor del intervalo de tiempo t/l


float fx(float xi, float yi, float xj, float yj); //fuerza en "x" que experimenta la partícula i debido a la partícula j
float fy(float xi, float yi, float xj, float yj);//fuerza en "y" que experimenta la partícula i debido a la partícula j


int main(){
int nij = sqrt(n);
//Asignamos posiciones iniciales
   

int cont = 0;

  for(int i = 0; i < nij ; i++)
{
    for(int j = 0; j < nij ; j++)
    {
        particula[0][cont] = i; 
        particula[1][cont] = j; 
        cont = cont + 1;
    }

}



 //Asignamos velocidades iniciales
    for(int i = 2; i < 4; i++)
{
    for(int j = 0; j < n; j++)
    {
        particula[i][j] = 0; 
    }
    
}



  //imprimimos posiciones iniciales

FILE *gg = fopen("datos_iniciales","wt");
for (int j = 0; j < n; j++)
{
    for(int i=0; i<2; i++)
    {
        fprintf(gg, "%f %f\n", particula[0][j], particula[1][j]);
    }
}
fclose(gg);

 FILE *flujo = fopen("script","wt");
    fprintf(flujo, "set xrange [-20:20]\n");
    fprintf(flujo, "set yrange [-20:20]\n");
   
    fprintf(flujo, "set terminal png \n");
    fprintf(flujo, "set output 'ini.png' \n");
     fprintf(flujo, "plot 'datos_iniciales' u 1:2 with points pt 7 ps 1 \n");
   
    //Se cierra el archivo.
    fclose(flujo);
system("gnuplot -p script");




//Se ejecuta l-1 veces el algoritmo para asi encontrar las posiciones y velocidades en el instante t.
for (int q = 0; q < l; q++)
{
   //POSICIONES
    //para x:
    for(int j = 0; j < n; j++)
    {

        //Se calcula la fuerza total en x sobre la particula j
        float fxt=0;
        for (int g = 0; g < n; g++)
        {
            if (g==j)
            {
                
            }else
            {
                fxt = fxt + fx(particula[0][j],particula[1][j],particula[0][g],particula[1][g]);
            }
            
            
        }
        

        //nueva posiccion en x de la particula j.
        auxparticula[0][j] = particula[0][j] + (dt*(particula[2][j])) +((1.0/2.0)*dt*dt*(fxt)); 
    }


    //para y:
    for(int j = 0; j < n; j++)
    {

        //Se calcula la fuerza total en y sobre la particula j
        float fyt=0;
        for (int g = 0; g < n; g++)
        {
            if (g==j)
            {
                
            }else
            {
                fyt = fyt + fy(particula[0][j],particula[1][j],particula[0][g],particula[1][g]);
            }
            
            
        }
        

        //nueva posiccion en y de la particula j.
        auxparticula[1][j] = particula[1][j] + (dt*(particula[3][j])) +((1.0/2.0)*dt*dt*(fyt)); 
    }



 //VELOCIDADES

 //para x:
for(int j = 0; j < n; j++)
{

    //Se calcula la fuerza total en x sobre la particula j
     float fxt=0;
     for (int g = 0; g < n; g++)
      {
          if (g==j)
          {
                
          }else
          {
                fxt = fxt + fx(particula[0][j],particula[1][j],particula[0][g],particula[1][g]);
           }
            
            
         }
        

       //nueva velocidad en x de la particula j.
        auxparticula[2][j] = particula[2][j] + (dt*(fxt)) ; 
        if (10<= particula[0][j] || particula[0][j]<=0){
        auxparticula[2][j] = -auxparticula[2][j];
        
        }
 }


 //para y:
for(int j = 0; j < n; j++)
{

     //Se calcula la fuerza total en y sobre la particula j
     float fyt=0;
     for (int g = 0; g < n; g++)
     {
          if (g==j)
          {
                
          }else
          {
              fyt = fyt + fy(particula[0][j],particula[1][j],particula[0][g],particula[1][g]);
          }
            
            
      }
        

        //nueva velocidad en y de la particula j.
        auxparticula[3][j] = particula[3][j] + (dt*(fyt)) ; 
        if (10<= particula[1][j] || particula[1][j]<=0){
        auxparticula[3][j] = -auxparticula[3][j];
        
        }
    }


    //Para este instante, el array "auxparticula[][]" contiene ya la informacion de todas las nuevas posiciones y velocidades.
    //Ahora que ya no importa si se modifica el array "particula[][]" pasaremos toda la informacion del array "auxparticula[][]"
    //al array "particula[][]" (antes era preciso que no se modificara "particula[][]" porque este se tenia que usar para todos los calculos)



    //Asignamos nuevas posiciones iniciales
    for(int i = 0; i < 2; i++)
{
    for(int j = 0; j < n; j++)
    {
        particula[i][j] = auxparticula[i][j]; 
    }
    
}


    //Asignamos nuevas velocidades iniciales
    for(int i = 2; i < 4; i++)
{
    for(int j = 0; j < n; j++)
    {
        particula[i][j] = auxparticula[i][j];
    }
    
}

FILE *gg = fopen("datos_iniciales","wt");
for (int j = 0; j < n; j++)
{
    for(int i=0; i<2; i++)
    {
        fprintf(gg, "%f %f\n", particula[0][j], particula[1][j]);
    }
}
fclose(gg);

 FILE *flujo = fopen("script","wt");
    fprintf(flujo, "set xrange [-20:20]\n");
    fprintf(flujo, "set yrange [-20:20]\n");
    
    fprintf(flujo, "set terminal png \n");
    fprintf(flujo, "set output 'ini%i.png' \n",q);
    fprintf(flujo, "plot 'datos_iniciales' u 1:2 with points pt 7 ps 1\n");
   
    //Se cierra el archivo.
    fclose(flujo);

    system("gnuplot -p script");





    
}
    

    //Esto ejecutará el comando entre comillas en la consola por lo tanto gnuplot ejecutará el script (:
   
     
   
    



}

//declaración de las funciones fx y fy 

float fx(float xi, float yi, float xj, float yj){

  return 4.0*e*(((12.0*(pow(s,12)))/(pow((pow(xi-xj,2))+(pow(yi-yj,2)),7)))-(((6.0*(pow(s,6)))/(pow((pow(xi-xj,2))+(pow(yi-yj,2)),4)))))*(xi-xj);

}

float fy(float xi, float yi, float xj, float yj){

  return 4.0*e*(((12.0*(pow(s,12)))/(pow((pow(xi-xj,2))+(pow(yi-yj,2)),7)))-(((6.0*(pow(s,6)))/(pow((pow(xi-xj,2))+(pow(yi-yj,2)),4)))))*(yi-yj);

}
