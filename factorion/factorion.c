// gathers factorions, we know the biggest is 40585, 
// since this we don't have tow orry about overflow

#include <stdio.h>
#include <math.h>
//gcc file.c -o executable

int factorial(int x){
    int y = 1;
    while(x){
        y *= x;
        x--;
    }
    return y;
}

int convert_to_base(int x, int y){
    int count = 0;
    int total = 0;
    while(x){
        total += (x % 10) * (int)pow(y, count);
        x /= 10;
        count++;
    }
    return total;
    
}

int main(){
    // Gather all factorions
    const int limit = 150;
    const int collect_number = 10;
    // working with abses up to 10 to prevent annoying digits
    const int base = 6;

    // work out correct array length of calc array so if limit = 100 len = 3  if 99 len = 2
    int calc_array_len = 0;
    int temp_limit;
    while(temp_limit){
        temp_limit /= 10;
        calc_array_len++;
    }

    // initiliase array of 0's
    int i;
    int j = 0;
    int factorions[collect_number];
    for (i = 0; i < collect_number; i++) {
        factorions[i] = 0;
    }

    int calc_array[calc_array_len];
    int n;
    int temp_count;
    int running_total;
    int temp_i;
    i = 1;
    while (i <= limit) {
        running_total = 0;
        n = i;
        // for every number iterate through its digits and sum up their factorial
        while (n) {
            running_total += factorial(n % 10);
            n /= 10;
            printf("%i ", running_total);
            // early return
            if(running_total > i){
                break;
            }
        }

        if(running_total== convert_to_base(i, base)){
            factorions[j] = i;
            j++;
        }

        // now we need to increase the number realtive to its base
        i++;
        temp_i = i;
        temp_count = 0;
        while(1){
            if((temp_i % 10) - base >= 0){
                i -= (base * (int)pow(10, temp_count));
                temp_count += 1;
                i += (int)pow(10, temp_count);
                temp_i /= 10;
            }else{
                break;
            }
        }
        
    } 
    for (i = 0; i < collect_number; i++) {
        printf("Factorion: %i \n", factorions[i]);
        fflush( stdout );
    }

    return 0;
}



