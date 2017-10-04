//
//  neuralnet.h
//  
//
//  Created by Ethan Tanen on 10/2/17.
//
//

#ifndef neuralnet_h
#define neuralnet_h

#include <stdio.h>


typedef struct Node{
    
    double output;
    
}Node;


typedef struct NeuralNet{
    
    int numIn;
    int numHid;
    int numOut;
    
    struct Node **inputLayer;
    struct Node **hiddenLayer;
    struct Node **outputLayer;
    
    double  *in_hid;
    double  *hid_out;
    
    int totalNumNeurons;
    int totWIH;
    int totWHO;
    
    
}NeuralNet;









double dotProduct(double *vector1, double *vector2,int vector_size);
double sigmoid(double activation);

/*calculates error signal for output layer by calling a 
 series of other functions
 
 delta error = error * weights_coming_in * learning rate
 */
double *errorOL(double target[], double output[]);

double *deltaO(double target[], double output[]);
double *sigmoidDeriv(double output);

/*
 error of hidden layer is a function of the weights leaving it, the weighted error of the weights leaving it,
 lpo = layer plus one
 */
double *errorHL(double weightsLPO[], double outputs[], double errorLPO[]);
double *errorSignalOutput(double *output, double *target, double *deltaE, int output_size);
double *deltaWeights(double learning_rate, double *prev_layer_activatons, double *error_signals, int prev_layer_size, double *delta_errors);
void net_init(int in, int hid, int out, struct NeuralNet *net);

void fastforward(NeuralNet *net, double *in);


void print_net(NeuralNet net);
#endif /* neuralnet_h */

//both sig and sig' should be stored in unit
