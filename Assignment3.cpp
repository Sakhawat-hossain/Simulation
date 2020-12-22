#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#include<graphics.h>
#include<conio.h>

#define PI 3.1416

void histogram(float *errorSample, int sampleNum, float d){
    int maxInterval = 100;
    int i, j;
    float intervalArr[maxInterval+1], densityArr[maxInterval];
    int freqArr[maxInterval], intervalNum = 0;
    // making array of end points of interval; initializing fregArr[i]
    intervalArr[0] = errorSample[0] - d;
    while(intervalArr[intervalNum]<errorSample[sampleNum-1]){
        intervalArr[intervalNum+1] = intervalArr[intervalNum]+d;
        freqArr[intervalNum] = 0;
        intervalNum++;
    }
    // calculation of frequency
    for(i = 0; i<sampleNum; i++){
        for(j = 0; j<intervalNum; j++){
            if(errorSample[i] < intervalArr[j+1]){
                freqArr[j] += 1;
                break;
            }
        }
    }
    printf("Interval number: %d\n", intervalNum);
    // plot histogram
    int gd = DETECT, gm; // VGA, gm = 0;
    //initgraph(&gd, &gm, "C:\\TC\\BGI");
    char pathtodriver[] = "";//"C:\\TC\\BGI";
    initgraph(&gd, &gm, pathtodriver);

    int errorcode = graphresult();
    if (errorcode != grOk)
    {
        printf("Graphics error: %s", grapherrormsg(errorcode));
        return;
    }

    int left, top, right, bottom;
    int x0 = 250, y0 = 400, xscale = 50, yscale = 1000, xleft = 150, xright=250;
    setlinestyle(SOLID_LINE,0,2);

    line(x0-xleft, y0, x0+xright, y0);// x-axis
    line(x0-xleft, y0, x0-xleft+10, y0-5); // for arrows
    line(x0-xleft, y0, x0-xleft+10, y0+5);
    line(x0+xright-10, y0-5, x0+xright, y0);
    line(x0+xright-10, y0+5, x0+xright, y0);
    outtextxy(x0-xleft-20, y0-10, "X'");
    outtextxy(x0+xright+10, y0-10, "X");
    outtextxy(x0, y0+5, "O");

    for(i = 0; i<intervalNum; i++){
        left = (x0 + xscale*intervalArr[i]);
        top = (y0 - yscale*freqArr[i]/sampleNum);
        right = (x0 + xscale*intervalArr[i+1]);
        bottom = y0;
        bar(left, top, right, bottom);
    }
    getch();
    closegraph();
}

void densityFrequencyComp(float *errorSample, int sampleNum, float mu, float sigma, float d){
    int maxInterval = 100;
    int i, j;
    float intervalArr[maxInterval+1], densityArr[maxInterval];
    int freqArr[maxInterval], intervalNum = 0;
    // making array of end points of interval; initializing fregArr[i]
    intervalArr[0] = errorSample[0] - d;
    while(intervalArr[intervalNum]<errorSample[sampleNum-1]){
        intervalArr[intervalNum+1] = intervalArr[intervalNum]+d;
        freqArr[intervalNum] = 0;
        intervalNum++;
    }
    // calculation of frequency
    for(i = 0; i<sampleNum; i++){
        for(j = 0; j<intervalNum; j++){
            if(errorSample[i] < intervalArr[j+1]){
                freqArr[j] += 1;
                break;
            }
        }
    }
    // calculation of probability from density function
    // f(x) = (1/(2*pi*sigma^2)^1/2)*exp(-(x-mu)^2 / 2*sigma^2)
    float temp, x;
    for(i = 0; i<intervalNum; i++){
        x = intervalArr[i] + d/2;
        temp = exp(-pow(x - mu, 2) / (2*sigma*sigma));
        densityArr[i] = temp / (sigma*sqrt(2*PI));
    }
    //printf("Interval number: %d\n", inum);
    // plot histogram
    int gd = DETECT, gm; // VGA, gm = 0; //initgraph(&gd, &gm, "C:\\TC\\BGI");
    char pathtodriver[] = "";//"C:\\TC\\BGI";
    initgraph(&gd, &gm, pathtodriver);

    int errorcode = graphresult();
    if (errorcode != grOk)
    {
        printf("Graphics error: %s", grapherrormsg(errorcode));
        return;
    }

    int left, top, right, bottom;
    int x0 = 250, y0 = 400, xscale = 50, yscale = 1000, xleft = 150, xright=250;
    setlinestyle(SOLID_LINE,0,2);

    line(x0-xleft, y0, x0+xright, y0);// x-axis
    line(x0-xleft, y0, x0-xleft+10, y0-5); // for arrows
    line(x0-xleft, y0, x0-xleft+10, y0+5);
    line(x0+xright-10, y0-5, x0+xright, y0);
    line(x0+xright-10, y0+5, x0+xright, y0);
    outtextxy(x0-xleft-20, y0-10, "X'");
    outtextxy(x0+xright+10, y0-10, "X");
    outtextxy(x0, y0+5, "O");
    // plot bar
    for(i = 0; i<intervalNum; i++){
        left = (x0 + xscale*intervalArr[i]);
        top = (y0 - yscale*freqArr[i]/sampleNum);
        right = (x0 + xscale*intervalArr[i+1]);
        bottom = y0;
        bar(left, top, right, bottom);
    }
    // plot probability line
    setcolor(RED);
    setlinestyle(SOLID_LINE,0,2);
    yscale = 500;
    for(i = 0; i<intervalNum-1; i++){
        left = x0 + xscale*(intervalArr[i]+d/2);
        top = y0 - yscale*densityArr[i];
        right = x0 + xscale*(intervalArr[i+1]+d/2);
        bottom = y0 - yscale*densityArr[i+1];
        line(left, top, right, bottom);
    }

    getch();
    closegraph();
}

void chiSquareTest(float *errorSample, int sampleNum, float d){
    int maxInterval = 100;
    int i, j;
    float intervalArr[maxInterval+1], chiArr[maxInterval];
    int freqArr[maxInterval], intervalNum = 0;
    // making array of end points of interval; initializing fregArr[i]
    intervalArr[0] = errorSample[0] - d;
    while(intervalArr[intervalNum]<errorSample[sampleNum-1]){
        intervalArr[intervalNum+1] = intervalArr[intervalNum]+d;
        freqArr[intervalNum] = 0;
        intervalNum++;
    }
    // npj value
    float pj = 1.0/intervalNum;
    float npj = sampleNum*pj;
    // calculation of frequency
    for(i = 0; i<sampleNum; i++){
        for(j = 0; j<intervalNum; j++){
            if(errorSample[i] < intervalArr[j+1]){
                freqArr[j] += 1;
                break;
            }
        }
    }
    // calculation of chi-square test value
    // (Nj - npj)^2 / npj
    float totalVal = 0;
    for(i = 0; i<intervalNum; i++){
        chiArr[i] = (freqArr[i] - npj)*(freqArr[i] - npj) / npj;
        totalVal += chiArr[i];
        printf("%d   %d    %.3f    %.3f\n", i, freqArr[i], npj, chiArr[i]);
    }
    printf("%.4f\n", totalVal);
}

int main(){
    // open file to read data on errors in the diameter of ball bearings
    FILE *file = fopen("errors-diameter.txt", "r");
    if(file == NULL){
        printf("File can not be opened");
        return 0;
    }

    int bufferLength = 100;
    int sampleNum = 154;
    char buffer[bufferLength];
    float errorSample[sampleNum];
    char *token;

    int idx = 0;
    while(fgets(buffer, bufferLength, file)){
        //printf("%s", buffer);
        token = strtok(buffer, " ");
        while(token != NULL){
            float err = strtof(token, NULL);
            errorSample[idx] = err;
            idx++;
            //printf("%.2f  ", err);
            token = strtok(NULL, " ");
        }
        //printf("\n");
    }
    //hypothesize families of distributions form
    // sorting error
    int i, j;
    float temp;
    for(i = 0; i<sampleNum-1; i++){
        temp = errorSample[i];
        for(j = i+1; j<sampleNum; j++){
            if(errorSample[j] < temp){
                errorSample[i] = errorSample[j];
                errorSample[j] = temp;
                temp = errorSample[i];
            }
        }
    }
    // summary statistics
    float mean, median, variance, cv, skewness, sum = 0.0, t;
    printf("Maximum: %.2f\n", errorSample[sampleNum-1]);
    printf("Minimum: %.2f\n", errorSample[0]);
    printf("Mean: ");
    for(i = 0; i<sampleNum; i++)
        sum += errorSample[i];
    mean = sum/sampleNum;
    printf("%.3f    %.3f    %.3f\n", mean, mean-errorSample[0], errorSample[sampleNum-1]-mean);
    median = (errorSample[(sampleNum-1)/2] + errorSample[sampleNum/2])/2;
    printf("Median: %.3f\n", median);
    // mean and median are almost equal
    sum = 0.0;
    for(i = 0; i<sampleNum; i++)
        sum += (errorSample[i]-mean)*(errorSample[i]-mean);
    variance = sum / sampleNum;
    cv = sqrt(variance)/mean;
    printf("Variance: %.3f\n", variance);
    printf("Co-efficient of Variance: %.3f\n", cv);

    sum = 0.0;
    for(i = 0; i<sampleNum; i++)
        sum += pow(errorSample[i]-mean, 3);
    t = (sampleNum-1)*(sampleNum-2);
    skewness = (sampleNum*sum)/(t*pow(variance, 3/2));
    printf("Skewness: %.3f\n", skewness);

    // histograms
    float d = 0.1;
    //histogram(errorSample, sampleNum, d);
    d = 0.2;
    //histogram(errorSample, sampleNum, d);
    d = 0.3;
    //histogram(errorSample, sampleNum, d);
    d = 0.4;
    //histogram(errorSample, sampleNum, d);

    // estimation of parameters, mu and sigma for normal distribution
    float mu, sigma;
    mu = mean;
    sigma = sqrt(variance); //(sampleNum-1)*variance/sampleNum
    printf("\nEstimated parameters:\n");
    printf("Mu: %.3f\n", mu);
    printf("Sigma: %.3f\n", sigma);

    // fitness test
    d = 0.2;
    //densityFrequencyComp(errorSample, sampleNum, mu, sigma, d);

    //chi-square test
    chiSquareTest(errorSample, sampleNum, d);

    return 0;
}
