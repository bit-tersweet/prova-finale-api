#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
/***************************************************************************/
typedef enum {false, true} bool;

typedef struct grafo_idx{
    unsigned int sum;
    int index;
} grafo_idx;
/**********************/
//heaps
int parent(int i);

void swap(grafo_idx *x, grafo_idx *y);

void inserisci(grafo_idx a[], grafo_idx data, int *n);

void maxHeapify(grafo_idx a[], int i, int n);

void cancellaMax(grafo_idx *a, int *n);

void stampaClassifica(grafo_idx *a, int n);

/********************************************************************************/

//GRAFI + FUNZIONI AUSILIARIE
unsigned int getMin(int *distanze, bool *visite,int num_nodi);//scegliere la x con la distnza piu piccola

unsigned int dijikstra(int **m, int num_nodi, int counter);

bool isUnreachable(int **m, int num_nodi, int nodo); //restituisce l'indice irraggiungibile se esiste, se non esiste return 0

int getSum(int *dist, int num_nodi);
/***************************************************************************************************************/
int fastRead(int *c);

int main() {
    int c = 44;
    int cols = 0;
    int read = 0;
    int num_nodi = 0;
    int k = 0;
    int coun =-1;
    grafo_idx temp;
    grafo_idx *heap;
    bool flag = false;


    while(c!=32){
        c=getchar_unlocked();
        num_nodi = fastRead(&c);
    }
    c=getchar_unlocked();
    while((char)c!='\n'){
        k = fastRead(&c);
    }
    heap = malloc(sizeof(grafo_idx)*k);
    int **matrix = (int **) malloc(num_nodi * sizeof(int *));
    for (int i=0; i<num_nodi; i++)
        matrix[i] = (int *)malloc(num_nodi * sizeof(int));

    c = getchar_unlocked();
    if((char)c=='T') {
        printf("\n");
        while ((char) c != '\n') c = getchar_unlocked(); //legge la prima TopK inutile
        c = getchar_unlocked();
    }

    while ((char) c != '\n') c = getchar_unlocked(); //legge la prima AggiungiGrafo inutile


    c=44;
    while(c == 44 && read < num_nodi){ //leggo numero per numero, 44 = ,
        c = getchar_unlocked();
        if((char)c == EOF ||(char)c == '\0') {
            free(heap);
            free(matrix);
            return 0;
        }

        int no = fastRead(&c);
        matrix[read][cols] = no;

        //printf("%d ", read);
        if(cols == num_nodi-1 && (char)c=='\n'){ //ho finito di leggere la riga
            c = 44;
            cols = 0;
            if(read == num_nodi-1 && (char)(c=getchar_unlocked())=='A'){//se ho finito di leggere il grafo
                flag = true;
                coun++;
                int size = coun;
                temp.index=coun;
                temp.sum = dijikstra(matrix, num_nodi,coun);
                if (coun<k){
                    //                    printf("coun: %d", coun);
                    //                    printf("sum: %d\n", temp.sum);
                    inserisci(heap, temp, &size);

                }
                else {
                    size = k;
                    if (heap[0].sum > temp.sum) {
                        //                        printf("coun: %d", coun);
                        //                        printf("sum: %d\n", temp.sum);
                        cancellaMax(heap, &size);

                        inserisci(heap, temp, &size);
                    }
                }

                c = getchar_unlocked();
                while ((char) c!= '\n') c= getchar_unlocked();  //leggi tutta l'aggiungi grafo
                read = 0;
                c = 44;
                continue;

            }else if(read == num_nodi-1 && (char)(c)=='T'){//se ho finito di leggere il grafo
                if(flag ==false) { // non ho ancora aggiunto nessun grafo, stampo solo \n
                    printf("\n");
                    while ((char)c!= 'K') c= getchar_unlocked();  //leggi tutto TopK
                    //while ((char) c!= '\n') c= getchar_unlocked();  //leggi tutto TopK
                    c=getchar_unlocked(); //legge quello dopo TopK
                    //if ((char)c == EOF) return 0;
                    if((char)c == '\n'){ //se ho altre Aggiungi, continuo nel ciclo
                        //printf("entri? A\n");
                        c=getchar_unlocked();
                        if((char)c == 'A') {
                            while ((char) c != '\n') c = getchar_unlocked();  //leggi tutto AggiungiGrafo
                        }else {
                            free(heap);
                            free(matrix);
                            return 0;
                        }
                        read = 0;
                        c = 44;
                        continue;
                    }else {//altrimenti esco dal ciclo
                        free(heap);
                        free(matrix);
                        return 0;
                    }
                    continue;
                }
                coun++;
                temp.index = coun;
                temp.sum = dijikstra(matrix, num_nodi, coun);
                int size = coun;
                if (coun<k){
                    inserisci(heap, temp, &size);
                    stampaClassifica(heap, size);
                }
                else {
                    size = k;
                    if (heap[0].sum > temp.sum) {
                        //                        printf("coun: %d", coun);
                        //                        printf("sum: %d\n", temp.sum);
                        cancellaMax(heap, &size);
                        inserisci(heap, temp, &size);

                    }
                    stampaClassifica(heap, k);
                }

                while ((char)c!= 'K') c= getchar_unlocked();  //leggi tutto TopK
                //while ((char) c!= '\n') c= getchar_unlocked();  //leggi tutto TopK
                c=getchar_unlocked(); //legge quello dopo TopK
                //if ((char)c == EOF) return 0;
                if((char)c == '\n'){ //se ho altre Aggiungi, continuo nel ciclo
                    //printf("entri? A\n");
                    c=getchar_unlocked();
                    if((char)c == 'A') {
                        while ((char) c != '\n') c = getchar_unlocked();  //leggi tutto AggiungiGrafo
                    }else {
                        free(heap);
                        free(matrix);
                        return 0;
                    }
                    read = 0;
                    c = 44;
                    continue;
                }else {//altrimenti esco dal ciclo
                    free(heap);
                    free(matrix);
                    return 0;
                }
            }
            else if(read == num_nodi-1 && c == EOF) return 0;
            //se nessuna delle due condizioni è verificata, continuo a leggere i numeri delimitati dalle virgole
            read++;
            continue;
        }
        cols++;

    }
    free(heap);
    free(matrix);
    return 0;
}

int fastRead(int *c){
    int x = 0;
    for(;(*c)>47 && (*c)<58;(*c) = getchar_unlocked()) //se è un numero (ASCII)
        x = (x<<1) + (x<<3) + (*c) - 48;
    return x;
}

int getSum(int *dist, int num_nodi){
    int sum=0;
    for (int i = 0; i < num_nodi; i++){
        sum +=dist[i];
        //printf("%d\n", dist[i]);
    }
    return sum;
}

unsigned int getMin(int *distanze, bool *visite, int num_nodi){
    int m= INT_MAX, m_idx=0;
    for(int i = 0; i < num_nodi; i++){
        if(visite[i]==false && distanze[i]<=m){
            m = distanze[i];
            m_idx = i;
        }
    }
    return m_idx;
}

unsigned int dijikstra(int **m, int num_nodi, int counter){
    int z = 0;
    for(int i = 1; i < num_nodi; i++){
        if(m[0][i]!=0){
            i = num_nodi;
        }else{
            z++;
        }
    }
    if(z==(num_nodi-1)) return 0;

    int *d; // d[i] ha la distanza minima dal nodo 0  al nodo i
    bool *visitati; //nodi visitati
    d = malloc(sizeof(int)*num_nodi);
    visitati = malloc(sizeof(bool)*num_nodi);
    //d[0] = 0; //il nodo di partenza è raggiunbile subito
    //setto tutti irraggiunbili e non visitati
    for(int i=0; i < num_nodi; i++){
        visitati[i] = false;
        d[i] = INT_MAX;
    }
    d[0]=0;
    int p = 0;
    do{
        int min = getMin(d, visitati, num_nodi);
        visitati[min] = true;
        //per la prima riga non c'è bisogno di fare il controllo
        if (!visitati[0] && m[min][0] && d[min] != INT_MAX && d[min] + m[min][0] < d[0]) {
            d[0] = d[min] + m[min][0];
        }
        for(int j = 1; j < num_nodi; j++) {
            bool flag = isUnreachable(m, num_nodi, j);
            flag = flag && isUnreachable(m, num_nodi, min);
            if (!visitati[j] && m[min][j] && d[min] != INT_MAX && d[min] + m[min][j] < d[j] && flag == false) {
                d[j] = d[min] + m[min][j];
            }
            else if(flag==true)
                d[j]=0;

        }
        p++;
    }while(p <= num_nodi);
    int s = getSum(d, num_nodi);
    free(d);
    free(visitati);

    return s;
}

bool isUnreachable(int **m, int num_nodi, int nodo){
    //    int count=0;
    //    int idx = 0;
    if(m[0][nodo]==0) {
        for (int j = 1; j < num_nodi; j++)
            if (j != nodo && m[j][nodo] != 0)
                return false;
        return true;
    }
    return false;

    //    //printf("%d", count);
    //    if(count == (num_nodi-2))
    //        idx++;
    //
    //    if(idx) {
    //        return true;
    //    }
    //    return false;
}

/****************************************************************************************/

/**********************/
//heaps
int parent(int i) {
    return (i - 1) / 2;
}

void swap(grafo_idx *x, grafo_idx *y) {
    grafo_idx temp = *x;
    *x = *y;
    *y = temp;
}
void maxHeapify(grafo_idx a[], int n, int heapsize){
    int l = 2*n + 1; //left
    int r = 2*n + 2; //right

    int posmax = n;
    if (l <= heapsize && a[l].sum > a[posmax].sum)
        posmax = l;
    else posmax = n;
    if (r <= heapsize && a[r].sum > a[posmax].sum)
        posmax = r;

    // swap e ricorsivo
    if (posmax != n) {
        swap(&a[n], &a[posmax]);
        maxHeapify(a, posmax, heapsize);
    }
}

void inserisci(grafo_idx a[], grafo_idx data, int *heapsize) { //*n è la dimensione dell'array
    // inserisci come foglia
    a[*heapsize].sum = data.sum;
    a[*heapsize].index = data.index;
    *heapsize+= 1;

    // Portalo avanti finchè non è minore del padre
    int i = *heapsize - 1;
    while (i > 0 && a[parent(i)].sum <= a[i].sum) {
        swap(&a[parent(i)], &a[i]);
        i = parent(i);
    }
}
void stampaClassifica(grafo_idx *a, int heapsize) {
    int i=0;
    for (; i < heapsize-1; i++)
        printf("%d ", a[i].index);

    printf("%d", a[i].index);
    printf("\n");
}

void cancellaMax(grafo_idx *a, int *heapsize) {
    if(*heapsize<1) return;
    *heapsize-=1;
    a[0] = a[*heapsize];
    //solita storia
    maxHeapify(a, 0, *heapsize);
}
/********************************************************************************/
