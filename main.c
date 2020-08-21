//Actividad 1: Aritmética de apuntadores
/*
Se quiere desarrollar una aplicación para llevar el control de pacientes ingresados en un hospital. De cada paciente 
interesa conocer su nombre, apellidos, edad, teléfono de contacto y la cama asignada. Inicialmente, el hospital cuenta 
con un número de camas fijas pero se sabe que si se requiere, es posible incorporar más camas (se identifican con un número 
consecutivo) en cualquier momento para poder atender más pacientes. Por cuestiones de logística, siempre que se requiera 
incrementar el número de camas, se incrementan de 5 en 5.

Diseñe e implemente una aplicación en C que se permita:

Incorporar pacientes al hospital (Tantos como se requiera. Si se llenan las camas disponibles y
llega un nuevo paciente hay que permitir su ingreso).
Conocer qué paciente se encuentra asignado a una cama dada o si ésta se encuentra disponible.
Dar de alta a un paciente por el número de cama (se retira del hospital y la cama queda disponible).
Mostrar el listado de todos los pacientes que se encuentran en el hospital, incluyendo el número de la cama asignada.
Conocer el número de camas disponibles y el número de camas ocupadas..

El problema lo analice y desarrolle junto a Julio Villazón.
*/
//Jesús González - A01422050
//16/08/2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int bed;
    char *name;
    char *lastname;
    int age;
    char *phone;
}room;

int main (int argc, const char * argv[]){
    int opc = 0, n = 0, count, morePatients = 0;
    int available, bedNumber = 0, moreBeds = 0;
    room *hospital;
    room *aux;
    room *final;

    printf("\n");
    printf("Ingresar cantidad inicial de camas en el hopsital: ");
    scanf("%d", &n);
    printf("\n");

    hospital = (room *) malloc(sizeof(room) * n);
    final = hospital + n;

    do
    {
        printf("1. Ver lista de pacientes.\n2. Ingresar pacientes.\n3. Dar de alta pacientes.\n4. Aumentar camas en el hospital.\n");
        scanf("%d", &opc);

        switch (opc)
        {
        case 0:
            break;
        case 1:
            //viewList();
            count = 1;
            printf("\n--Lista de pacientes--\n");
            printf("Bed \t Name \t\t Lastname \t Age \t Phone\n");
            for(aux = hospital; aux < final; ++aux){
                aux->bed = count;
                printf("%3d \t %10s \t %10s \t %3d \t %10s\n", 
                    aux->bed,
                    aux->name,
                    aux->lastname,
                    aux->age,
                    aux->phone);
                    count++;
            }
            break;
        case 2:
            //addPatient();
            count = 0;
            for (aux = hospital; aux < final; ++aux)
            {
                if (aux->name != NULL && aux->lastname != NULL && aux->phone != NULL && aux->age != 0)
                {
                    count++;
                }
            }
            if(count == n){
                printf("\n");
                printf("Lo siento no hay más camas dispoibles, regresa al menu para pedir más camas.\n");
                printf("\n");
                break;
            }
            available = n - count;
            printf("\n");
            printf("Hay %d camas ocupadas.\n", count);
            printf("Quédan %d camas disponibles.\n", available);
            printf("\n");

            printf("\n");
            printf("¿Cuántos pacientes quieres agregar?: ");
            scanf("%d", &morePatients);
            printf("\n");

            if(morePatients > available){
                printf("\n");
                printf("Es cantidad no es posible, solo podrás ingresar a %d paciente(s).\n", available);
                printf("Debes agregar más camas desde la cuarta opción en el menú.\n");
                printf("\n");
                morePatients = available;
            }

            count += morePatients;
            available = n - count;
            for (aux = hospital; aux < hospital + morePatients; ++aux)
            {
                if (aux->name != NULL && aux->lastname != NULL && aux->phone != NULL && aux->age != 0)
                {
                    do
                    {
                        ++aux;
                        ++morePatients;
                    } while (aux->name != NULL && aux->lastname != NULL && aux->phone != NULL && aux->age != 0);
                }

                aux->name = (char *)malloc(sizeof(char) * 12);
                printf("\n");
                printf("\nIngresa el nombre del paciente #%d: ", aux->bed);
                scanf("%s", aux->name);

                aux->lastname = (char *)malloc(sizeof(char) * 12);
                printf("Ingresa el apellido del paciente #%d: ", aux->bed);
                scanf("%s", aux->lastname);

                printf("Ingresa la edad del paciente #%d: ", aux->bed);
                scanf("%d", &aux->age);

                aux->phone = (char *)malloc(sizeof(char) * 12);
                printf("Ingresa el teléfono del paciente #%d: ", aux->bed);
                scanf("%s", aux->phone);
                printf("\n");
            }

            break;
        case 3:
            //deletePatient();
           
            do{
                printf("\n");
                printf("Ingresa el número de la cama del paciente al que quieres dar de alta: ");
                scanf("%d", &bedNumber);
                printf("\n");

                if(bedNumber > n)
                    printf("Esa cama no existe. \n");

            } while(bedNumber > n);


            aux = hospital + bedNumber-1;
            aux->name = NULL;
            aux->lastname = NULL;
            aux->phone = NULL;
            aux->age = 0;

            printf("La cama #%d se ha desocupado.\n", aux->bed);
            printf("\n");

            break;
        case 4:
            //addBeds();

            if(available != 0){
                printf("Todavia hay camas disponibles, se deben agotar las camas para poder pedir más.\n");
                break;
            }

            moreBeds = 5;

            printf("\n");
            printf("Las camas han sido agregadas. (Se agregaron 5 por cuestiones de logística)");
            printf("\n");
            
            n += moreBeds;
            hospital = (room*) realloc(hospital, sizeof(room) * n);
            final = hospital + n;

            break;

        default:
            printf("Opción no válida.\n");
        }

    } while (opc != 0);

    for(aux = hospital; aux < final; ++aux){
        free(aux->name);
        free(aux->lastname);
        free(aux->phone);
    }

    free(hospital);

    return 0;
}

