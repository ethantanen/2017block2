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
    
    double activation;
    double output;
    
    double sigPrime;
    
    double littleDelta;
    
}Node;


typedef struct NeuralNet{
    
    int numIn;
    int numHid;
    int numOut;
    
    struct Node *inputLayer;
    struct Node *hiddenLayer;
    struct Node *outputLayer;
    
    double  *in_hid;
    double  *hid_out;
    
    //totWIH  -> total Weights from Input to Hidden
    int totalNumNeurons;
    int totWIH;
    int totWHO;
    
    
}NeuralNet;


 
/*
 Initiates a neural net with random weights between 0 and .5
 */
void net_init(int in, int hid, int out, struct NeuralNet *net);

/*
 These function are called to implement the forward portion of the net
    -sigmoid is needed to calcualte the output of the node
    -sigPrime is a value needed for back propagation but it too is calculated now
 */
void fastforward(NeuralNet *net, double *in);
double sigmoid(double activation);
double sigPrime(double activation);

/*
 function related to backpropagating
 */


//TODO: need calculate little delta and large delta functons
void calculateLittleDeltas(NeuralNet *net);
void calculateBigDeltas(NeuralNet *net);




/****
 UTILITIES
 *****/

void print_net(NeuralNet net);

//vector operations
double dot_product(double *vector1, double *vector2,int vector_size);
double *scalar_times_vector(double scalar, double *vector, int vector_size);
double *vector_sub_vector(double *vector1, double *vector2, int vector_size);
double *vector_entrywise_mult_vector(double *vector1, double *vector2, int vector_size);


#endif /* neuralnet_h */


