#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define PI 3.1416

// monte carlo simulation for sin(x) for n random numbers
double monte_carlo_sim(float a, float b, int n){
    double result, rand_x, sum = 0.0;
    int i, rd;
    for(i = 0; i < n; i++){
        rd = rand();
        // random number X within a to b
        rand_x = a+(b - a)*rd/RAND_MAX;
        sum += sin(rand_x);
    }
    result = (b - a)*sum/n;
    return result;
}
// monte carlo simulation for exp(x) for n random numbers
double monte_carlo_sim_exp(float a, float b, float lemda, int n){
    double result, rand_x, sum = 0.0;
    int i, rd;
    for(i = 0; i < n; i++){
        rd = rand();
        // random number X within a to b
        rand_x = a+(b - a)*rd/RAND_MAX;
        // f(x) = lemda*exp(-lemda*x)
        sum += lemda*exp(-(lemda*rand_x));
    }
    result = (b - a)*sum/n;
    return result;
}
void integration(){
    // integration of six(x) from 0 to PI/4
    double a = 0;
    double b = PI/4;
    // integral(sin(x)) = -cos(x);
    double analytic_result = cos(a) - cos(b);
    printf("Analytic result: %f\n", analytic_result);

    // monte carlo simulation
    int N = 6; // number of simulation run
    int MAX_RUN = 10;
    int n = 10; // initial number of IID random number
    double simulated_result[MAX_RUN];
    int num_random[MAX_RUN], i;

    for(i = 0; i < N; i++){
        simulated_result[i] = monte_carlo_sim(a, b, n);
        //printf("%f\n", simulated_result[i] - analytic_result);
        num_random[i] = n;
        n = n*10;
    }
    // print result
    printf("\nSimulated result:\n");
    printf("Random Number(N) : Estimated Integral\n");
    for(i = 0; i < N; i++){
        printf("%14d   :  %f\n", num_random[i], simulated_result[i]);
    }
}
void probability_table(){
    // open file to write probability table
    FILE *file = fopen("exp_prob_table.txt", "w");
    if(file == NULL){
        printf("File can not be opened");
        return;
    }
    // probability table from 0.00 to N-0.01
    int N = 5;
    double table[N*10][10];
    // F(x) = 1 - exp(-lemda*x)
    float lemda = 1;
    int i, j, k;
    double x, frac1, frac2;
    for(i = 0; i<N; i++){
        frac1 = 0.0;
        for(j = 0; j<10; j++){
            frac2 = 0.00;
            for(k = 0; k<10; k++){
                x = i + frac1 + frac2;
                //table[10*i+j][k] = 1 - exp(-(lemda*x)); // analytic
                table[10*i+j][k] = monte_carlo_sim_exp(0, x, lemda, 1000);
                frac2 += 0.01;
            }
            frac1 += 0.1;
        }
    }
    // output kept in file
    fprintf(file, "      ");
    frac1 = 0.00;
    for(i = 0; i<10; i++){
        fprintf(file, "%.2f     ", frac1);
        frac1 += 0.01;
    }
    fprintf(file, "\n");
    frac1 = 0.0;
    for(i = 0; i<N; i++){
        for(j = 0; j<10; j++){
            fprintf(file, "%.1f   ", frac1);
            for(k = 0; k<10; k++){
                fprintf(file, "%.4f   ", table[10*i+j][k]);
            }
            fprintf(file, "\n");
            frac1 += 0.1;
        }
    }
    fprintf(file, "\n");
}
int main(){
    srand(time(0));
    // integration of six(x) from 0 to PI/4
    integration();
    // probability table
    probability_table();

    return 0;
}
