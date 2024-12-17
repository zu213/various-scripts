// if a coin with probability prob_heads of being heads is flipped until it is tails,
// What is its average ?

#include <stdio.h>

int main(){

    const float prob_tails = 0.5;

    // Numerical method
    const int limit = 100;
    const int check_interval = 10;
    const int array_length = (limit / check_interval) + 1;

    float prob_every_thousand[array_length];
    float current_total = 0;
    float current_prob_tails = prob_tails;
    float remaining_prob = 1;

    int i;
    for (i = 0; i <= limit; i++) {
        if( (i % check_interval) == 0){
            prob_every_thousand[i / check_interval] = (current_total);
        }
        // Add the chance of getting tails at each flip * the score it gives
        current_total += current_prob_tails * i;
        remaining_prob -= current_prob_tails;
        current_prob_tails = remaining_prob * prob_tails;
    } 
    for (i = 0; i < array_length; i++) {
        printf("Numerically: %i iterations %f\n", (i * check_interval) + 1 ,prob_every_thousand[i]);
        fflush( stdout );
    }


    // algerbraically
    // As the first heads is not guaranteed we take away 1
    float average = 1 / (prob_tails) - 1;
    printf("Algebraically: %f\n", average);

    return 0;
}



