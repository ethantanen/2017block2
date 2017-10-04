//
//  neuralnet.c
//  
//
//  Created by Ethan Tanen on 10/2/17.
//
//

#include "neuralnet.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(int args, char **argv){
    
    struct NeuralNet net;
    
    //number of nodes per layer
    int in = 10;
    int hid = 5;
    int out = 10;

    
    net_init(in,hid,out,&net);
    
    
    double input[] = {1,1,1,1,1,1,1,1,1,1};
    
    
    fastforward(&net,input);
    
    print_net(net);
    
    
    for(int i=0; i<net.totWIH; i++){
        printf("[%d] = %f\n",i,net.in_hid[i]);
    }
    
    return 1;
    
}

/*
 calculate error for output layer
 */
double *errorSignalOutput(double *output, double *target, double *deltaE, int output_size){
    //calculate delta e for output and target
    for(int i=0; i<output_size; i++){
        
        printf("stuff: \n i= %d, output[i] = %f, target[i] = %f", i,output[i],target[i]);
        
        deltaE[i] = (target[i]-output[i])*(1-output[i])*(output[i]);
    }
    return deltaE;
}

/*
 calculate error for hidden layer
 */
double *errorSignalHidden(double *output, double *error_layer_plus_one, double *weighted_error, int layer_size, double *error_signal){
    for(int i=0; i<layer_size; i++){
        error_signal[i] = output[i];
        
        //tk is the updated weights?
        
    }
    return 0;
}



/*
 calculate amount weights should be modified
*/
double *deltaWeights(double learning_rate, double *prev_layer_activatons, double *error_signals, int prev_layer_size, double *delta_errors){
    for(int i=0; i<prev_layer_size; i++){
        delta_errors[i] = learning_rate * prev_layer_activatons[i] * error_signals[i];
        
    }
    
    return delta_errors;
    
}



/*
 calculates sigmoid from activation
 */
double sigmoid(double activation){
    return 1/(1+exp(activation));
}


/*
 computes the dot product of two vectors
*/
double dotProduct(double *vector1, double *vector2,int vector_size){
    double sum = 0;
    for(int i=0; i<vector_size;i++){
        sum+= vector1[i] * vector2[i];
    }
    return sum;
}



/*
initiate net by instantiatd varios arrays and populating weights w/ random values
*/
void net_init(int in, int hid, int out, struct NeuralNet *net){
    
    net->numIn = in;
    net->numHid = hid;
    net->numOut = out;
    
    
    net->inputLayer = malloc(sizeof(Node *)*in);
    net->hiddenLayer = malloc(sizeof(Node *)*hid);
    net->outputLayer = malloc(sizeof(Node *)*out);
    
    net->in_hid = malloc(sizeof(double)*in*hid);
    net->hid_out = malloc(sizeof(double)*hid*out);
    
    net->totalNumNeurons = in+hid+out;
    net->totWIH = in*hid;
    net->totWHO = hid*out;
    
    /*
     instantiate weights w/ #'s between 0 and .5
     */
    
    //rand will need to be seeded for true randomness
    //srand(time);
    
    for(int i=0; i<in*hid; i++){
        double val = (double)rand()/(double)RAND_MAX;
        if(val > .5){
            val += -.5;
        }
        net->in_hid[i] = val;
    }
    
    for(int i=0; i<hid*out;i++){
        double val = (double)rand()/(double)RAND_MAX;
        if(val>.5){
            val += -.5;
        }
        net->hid_out[i] = val;
    }
    
    return;
}

void fastforward(NeuralNet *net, double *in){
    
    
    
    
    
    //calculate outputs for hidden layer
    
    
    
    
    //cycle through nodes
    for(int i=0; i<net->numHid; i++){
        
        //get weights for node i
        double weights[net->numIn];
        memcpy(&weights,net->in_hid+(i*net->numIn),sizeof(double)*net->numIn);
      
        //calculate dot product of weights and inputs
        double activation = dotProduct(weights,in,net->numIn);
  
        //pass through sigmoid
        double output = sigmoid(activation);
    
        //update output field
        net->inputLayer[i]->output = output;
    
    }
    
    //
    
    return;
}



void print_net(NeuralNet net){
    
    for(int i=0; i<net.numHid; i++){
        printf("node[%d] output = %f",i,net.hiddenLayer[i]->output);
    }
    
    
}


