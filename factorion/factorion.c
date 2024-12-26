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
    if(y == 10){
        return x;
    }
    int count = 0;
    int total = 0;
    while(x){
        total += (x % 10) * (int)pow(y, count);
        x /= 10;
        count++;
    }
    return total;
}

int sum_factorial_digits(int n){
    int i = n;
    int running_total = 0;
    while (n) {
        running_total += factorial(n % 10);
        n /= 10;
        // early return
        if(running_total > i){
            break;
        }
    }
    return running_total;
}

int increment_with_base(int i, int base){
    i++;
    if(base == 10){
        return i;
    }
    int temp_i = i;
    int temp_count = 0;
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
    return i;
}

int main(){
    // Gather all factorions
    const int limit = 50000;
    const int collect_number = 5;
    // working with abses up to 10 to prevent annoying digits
    const int base = 10;

    // initiliase array of 0's, j is used to see where to add the next index
    int i;
    int j = 0;
    int factorions[collect_number];
    for (i = 0; i < collect_number; i++) {
        factorions[i] = 0;
    }

    i = 1;
    while (i <= limit) {        
        if(sum_factorial_digits(i) == convert_to_base(i, base)){
            factorions[j] = i;
            j++;
        }

        // now we need to increase the number realtive to its base
        i = increment_with_base(i, base);
    }

    for (i = 0; i < collect_number; i++) {
        printf("Factorion: %i \n", factorions[i]);
        fflush( stdout );
    }

    return 0;
}



