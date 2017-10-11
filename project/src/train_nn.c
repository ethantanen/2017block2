//
//  nn_new.c
//  
//
//  Created by Ethan Tanen on 10/10/17.
//
//

#include "nn_new.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define in 2
#define hid 2
#define out 1


int main (int argc, char **argv){
    
    int i,j;
    
    double Error = 0, error_threshold = .0001, learning_rate = .5;
    
    int train_total = 4;
    
    double input[4][in+1] = {{0,1,1},{0,0,0},{0,1,0},{0,0,1}};
    double target[4][out+1] = {{0,0},{0,1},{0,1},{0,1}};
    
    
    double hidden_activation[hid+1];
    double output_activation[out+1];
    
    double hidden_output[hid+1];
    double output_output[out+1];
    
    double hidden_ld[hid+1];
    double output_ld[out+1];
    
    
    double weights_ih[in+1][hid+1];
    double weights_ho[hid+1][out+1];
    
    /**************
     Randomize Weights
     ***************/
    for(i=0; i<=in; i++){
        for(j=0; j<=hid; j++){
            double rand_w = (double)rand()/(double)RAND_MAX;
            if(rand_w>.5)
                rand_w -= .7;
            weights_ih[i][j] = rand_w;
        }
    }
    
    for(i=0; i<=hid; i++){
        for(j=0; j<=out; j++){
            double rand_w = (double)rand()/(double)RAND_MAX;
            if(rand_w>.5)
                rand_w -= .7;
            weights_ho[i][j] = rand_w;
        }
    }
    
    for(int epoch = 0; epoch <100000; epoch++){
        /***********
         Forward Propagate
         ***********/
        
        Error = 0;
        
        int rand_index = rand() % train_total;
        
        for(int c = 0; c < train_total; c++){
        
            int train_index = (c + rand_index) % train_total;
            
            //calc hidden_activaton & hidden_output
            for(i=1; i<=hid; i++){
                hidden_activation[i] = weights_ih[0][i];
                for(int j=1; j<=in; j++){
                    hidden_activation[i] += weights_ih[j][i] * input[train_index][j];
                }
                hidden_output[i] = sigmoid(hidden_activation[i]);
            }
            
            //calc output_activatin & output_output
            for(i=1; i<=out; i++){
                output_activation[i] = weights_ho[0][i];
                for(int j=1; j<=hid; j++){
                    output_activation[i] += weights_ho[j][i] * hidden_output[j];
                }
                output_output[i] = sigmoid(output_activation[i]);
            }
            
            /*****************
             Backpropagation
             ******************/
            
            //calc output_ld & system error
            for(i=1; i<=out; i++){
                output_ld[i] =  sig_prime(output_output[i])*(output_output[i]-target[train_index][i]);
                Error += .5 * (target[train_index][i]-output_output[i])*(target[train_index][i]-output_output[i]);
            }
            
            //calc hidden_ld
            for(i=1; i<=hid;i++){
                double sum = 0;
                for(j=1; j<=out; j++){
                    sum += output_ld[j] * weights_ho[i][j];
                }
                hidden_ld[i] = sig_prime(hidden_output[i]) * sum;
            }
            
            
            //calc hidden_bg and update weights
            for(i=1; i<=hid; i++){
                weights_ih[0][i] -= learning_rate * hidden_ld[i];
                for(j=1; j<=in; j++){
                    weights_ih[j][i] -= learning_rate * hidden_ld[i] * input[train_index][j];
                }
            }
            
            //calc out_bd and update weights
            for(i=1; i<=out; i++){
                weights_ho[0][i] -= learning_rate * output_ld[i];
                for(j=1; j<=hid; j++){
                    weights_ho[j][i] -= learning_rate * output_ld[i] * hidden_output[j];
                }
            }
        
            
            if(epoch % 10000){
                printf("\nError: %f, Epoch: %d\n",Error,epoch);
                printf("Input = %f  %f, Target= %f, Output = %f\n",input[train_index][1],input[train_index][2],target[train_index][1],output_output[1]);
            }
        }
        
        if(Error < error_threshold || epoch ==10000000-1 ){
            printf("Network Trained, Error: %f, Epoch: %d\n",Error,epoch);
            break;
        }
    
    }
    
}

/*********
UTILITIES
************/
double sigmoid(double activation){
    return 1/(1+exp(-1*activation));
}

double sig_prime(double activation){
    return activation*(1-activation);
}
