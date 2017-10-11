//
//  test_nn.c
//  
//
//  Created by Ethan Tanen on 10/9/17.
//
//

#include "test_nn.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main (int argc, char **argv){
    
    
    int in;
    int hid;
    int out;
    

    
    
    
    
    //check if there is a binary file for aquiring weights
    if(argc < 2){
        printf("Include binary file of weights as argument");
        return 1;
    }
    
    //create a var of type FILE from the 1st argument
    printf("Using weights from file %s\n",argv[1]);
    FILE *f = fopen(argv[1],"rb");
    if(f == NULL){
        printf("Error opening file.\n");
    }
    
    //create an array to hold number of nodes in the in,hid and out layers
    int node_count_info[3];
    fread(node_count_info,sizeof(int),3,f);
    
    
    in = node_count_info[0];
    hid = node_count_info[1];
    out = node_count_info[2];
    
    
    printf("\nIN: %d, HID: %d, OUT: %d\n",in,hid,out);
    
    //create arrays to hold the nn weights
    printf("\nReading weights from %s...\n",argv[1]);
    
    double weights_ih[in][hid-1];
    double weights_ho[hid][out];
    
    size_t c = fread(weights_ih,sizeof(double),in*(hid-1),f);
    size_t d = fread(weights_ho,sizeof(double),hid*out,f);
    
    printf("%zu elements read of %d elements in weights_ih\n",c,(in*(hid-1)));
    printf("%zu elements read of %d elements in weights_ho\n\n",d,(hid*out));

    
    double input_activation[in];
    double hidden_activation[hid];
    double output_activation[out];
    
    double input_output[] = {(double)*argv[2],(double)*argv[3]};
    double hidden_output[hid];
    double output_output[out];
    
    
    for(int i=0; i<hid; i++){
        for(int k=0; k<in; k++){
            
            
            printf("weight[%d][%d] = %f\n",k,i,weights_ih[k][i]);
        }
        printf("\n");
    }
    
    
    
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
            output_activation[i] += weights_ho[j][i] * hidden_output[i];
        }
        //compute output layer output
        output_output[i] = sigmoid(output_activation[i]);
    }
    
    for(int i=0; i<out; i++){
        printf("output[%d] = %f\n",i,output_output[i]);
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


