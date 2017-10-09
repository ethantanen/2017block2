//
//  neuralnet2.c
//  
//
//  Created by Ethan Tanen on 10/8/17.
//
//

#include "neuralnet2.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main (int argc, char **argv){
    
    double learning_rate = .0001;
    double Error;
    
    int in = 2+1; //plus one is the bias node
    int hid = 2+1;
    int out = 2;
    
    double weights_ih[in][hid];
    double weights_ho[hid][out];
    
    double input_activation[in];
    double hidden_activation[hid];
    double output_activation[out];
    
    double input_output[in];
    double hidden_output[hid];
    double output_output[out];
    
    double output_ld[out];
    double hidden_ld[out];
    
    double input[2]={1,1};
    double target[2]={0,0};
    
    
    //set biases output which is always one
    input_output[0] =1;
    hidden_output[0]=1;
    
    //populate input_output with input data
    for(int i=1; i<in; i++){
        input_output[i] = target[i-1];
    }
    
    
    //randomize weights
    for(int i=0; i<in+1; i++){
        for(int j=0; j<hid+1; j++){
            weights_ih[i][j] = (double)rand()/(double)RAND_MAX;
        }
    }
    
    for(int i=0; i<hid+1; i++){
        for(int j=0; j<out; j++){
            weights_ih[i][j] = (double)rand()/(double)RAND_MAX;
        }
    }
    
    
    for(int c =0; c < 100000000; c++){
    
    //NOTE: the zeroth node in a node array is the bias node
    
    //compute hidden layer activations
    for(int i=1; i<hid; i++){
        hidden_activation[i] =  weights_ih[0][i];//the weight that connects node i in the hidden layer to node k in the input layer
        for(int j=1; j<in; j++){
            hidden_activation[i] += weights_ih[j][i] * input_output[j];
        }
        //compute hidden layer output
        hidden_output[i] = sigmoid(hidden_activation[i]);
    }
    
    //compute output layer activations
    for(int i=0; i<out; i++){
        output_activation[i] = weights_ho[0][i];
        for(int j=1; j<hid; j++){
            output_activation[i] += weights_ho[j][i];
        }
        //compute output layer output
        output_output[i] = sigmoid(output_activation[0]);
    }
    
    //compute output layer little d
    Error = 0;
    for(int i=0; i<hid; i++){
        output_ld[i] = sig_prime(output_output[i]) * (output_output[i]-target[i]);
        Error += .5*(hidden_output[i]-target[i])*(hidden_output[i]-target[i]);

    }
    
    //compute hidden layer little d
    for(int i=0; i<hid; i++){
        double dotprod_weights_errors = 0;
        for(int j=0; j<out; j++){
            dotprod_weights_errors += output_ld[j] * weights_ho[i][j];
        }
        hidden_ld[i] = sig_prime(hidden_output[i]) * dotprod_weights_errors;
    }
    
    //compute h_i big d and change weights
    for(int i=1; i<hid; i++){
        for(int j=0; j<in; j++){
            //TODO: inputs should be moved into an array title input_output --> should the output be the input passed through the sigmoid function
            double ih_bd = learning_rate * hidden_ld[i] * input_output[j];
            weights_ih[j][i] = weights_ih[j][i] - ih_bd;
        }
    }
    
    //compute o_h big d and change weights
    for(int i=0; i<out; i++){
        for(int j=0; j<hid; j++){
            double ho_bd = learning_rate * output_ld[i] * hidden_output[j];
            weights_ho[j][i] = weights_ho[j][i] - ho_bd;
        }
    }
    
    
    if(Error<.0001){
        
        //PRINT NET
        for(int i=0; i<out; i++){
            
            printf("output_out[%d] = %f\n",i,output_output[i]);
        }

        
    }
    }
    
        
}
    
    
    
    
    
    

    
    /*************
       UTILITIES
     *************/
    
    double sigmoid(double activation){
        return 1/(1+exp(-1*activation));
    }
    
    double sig_prime(double activation){
        return activation*(1-activation);
    }
    
    


    
    
    
    
    
 
    
    
    
    
    
    
