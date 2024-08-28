#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

#define N 21

double getArrage(int weight, int worth) {
    return  (double)worth/ weight;
}

struct Wod {
    int id;
    int weight;
    int worth;
    double arrageworth;  
    double getpackage;
    int reallid;
};

int main() {
    struct Wod wod[1000];
    int n, packagemax;
    scanf("%d %d", &n, &packagemax);
    int packagepath[n];
    
    for(int i = 0; i < n; i++) {
        scanf("%d %d %d", &wod[i].id,&wod[i].weight,&wod[i].worth);
		packagepath[i] =i;
		wod[i].reallid=i;
        wod[i].arrageworth = getArrage(wod[i].weight, wod[i].worth);
    }
//    //输出每个物品的信息
//    for(int i = 0; i < n; i++) {
//        printf("%d %d %d %.2f\n", wod[i].id, wod[i].worth, wod[i].weight, wod[i].arrageworth);
//    }
    // 根据arrageworth从高到低排序，数值高的在前，用数组packagepath记录reallid
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            if(wod[packagepath[i]].arrageworth < wod[packagepath[j]].arrageworth)  {
                int temp=packagepath[i];
                packagepath[i]=packagepath[j];
                packagepath[j]=temp;
            }
        }
    }
    

    int package = 0;
    int i = 0;

    while (package <= packagemax && i < n) {
        if(package + wod[packagepath[i]].weight <= packagemax) {
            wod[packagepath[i]].getpackage = 1.00;
            package += wod[packagepath[i]].weight;
        } else {
            wod[packagepath[i]].getpackage = (double)(packagemax - package) / wod[packagepath[i]].weight;
            package = packagemax;
        }
        i++;
    }

  	double count=0;
    
    for(int i = 0; i < n; i++) {
        printf("%.2f ", wod[i].getpackage);
        count=count+wod[i].getpackage*wod[i].worth;
    }
   printf("\n%.2f",count);
   
    
    return 0;
}

    
// 3 20
// 4 25 18
// 2 24 15
// 8 15 10


    



