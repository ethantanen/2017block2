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



/*
Instantiate network
 */
int main(int args, char **argv){
}





/*
initiate net by instantiatd varoius arrays and populating weights w/ random values
*/
void net_init(int in, int hid, int out, struct NeuralNet *net){
    
    net->numIn = in;
    net->numHid = hid;
    net->numOut = out;
    
    //TODO: input layer and hidden layer will probs need extra node for bias
    net->inputLayer = malloc(sizeof(Node)*in);
    net->hiddenLayer = malloc(sizeof(Node)*hid);
    net->outputLayer = malloc(sizeof(Node)*out);
    
    //TODO: may need to add element to weights to account for bias
    net->in_hid = malloc(sizeof(double)*in*hid);
    net->hid_out = malloc(sizeof(double)*hid*out);
    
    net->totalNumNeurons = in+hid+out;
    net->totWIH = in*hid;
    net->totWHO = hid*out;
    
    
    /*
     instantiate weights w/ #'s between 0 and .5
     */
    
    //TODO: srand() to seed rand()
    
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


/*
 Forward portion of net
 */

//TODO: two section are very similar may be able combine, error maybe thrown for var naming issues...probs not
void fastforward(NeuralNet *net, double *in){
    

    double hidden_layer_outputs[net->numHid];
    
    //cycle through nodes in hidden layer to calculate their outputs
    for(int i=0; i<net->numHid; i++){
        
        //get weights for node i
        double weights[net->numIn];  //TODO: var bias = weights + 1
        memcpy(&weights,net->in_hid+(i*net->numIn),sizeof(double)*net->numIn);
      
        double activation = dot_product(weights,in,net->numIn); //TODO: dot prod + bias
        double output = sigmoid(activation);
        double sigprime = sigPrime(activation);
        
        net->hiddenLayer[i].activation = activation;
        net->hiddenLayer[i].output = output;
        net->hiddenLayer[i].sigPrime = sigprime;
        
        hidden_layer_outputs[i] = output;
    }
    
    //do the same thing for the output layer
    for(int i=0; i<net->numOut; i++){
        
        //get weights for node i
        double weights[net->numHid];
        memcpy(&weights,net->hid_out+(i*net->numHid),sizeof(double)*net->numHid);
        
        double activation = dot_product(weights,hidden_layer_outputs,net->numHid); //TODO: same todo as above
        double output = sigmoid(activation);
        double sigprime = sigPrime(activation);
        
        net->hiddenLayer[i].activation = activation;
        net->hiddenLayer[i].output = output;
        net->hiddenLayer[i].sigPrime = sigprime;
    }

    
    return;
}

/**********************************
 BACKPROPAGATION RELATED SHTUFF
 *********************************/



void calculateLittleDelta(NeuralNet *net){
    
    //TODO: little d for output layer is sigPrime(upstream outputs) + (output-target)
    
    //TODO: little d for hidden layer is sigPrime(?@output of node) * dot_prod(weights*little deltas downstream)
    
}

void calculateBigDelta(NeuralNet *net){
    //learning rate * O * little delta 
    
    
}








/***************************************
 UTILITIES DAWG
 **************************************/



void print_net(NeuralNet net){
    for(int i=0; i<net.numHid; i++){
        printf("node[%d] hidden: = %f\n",i,net.hiddenLayer[i].output);
    }
    for(int i=0; i<net.numOut; i++){
        printf("node[%d] output: = %f\n",i,net.outputLayer[i].output);
    }
}

/*
 calculates sigmoid from activation
 */
double sigmoid(double activation){
    return 1/(1+exp(activation));
}

/*
 calculate the derivative of the sigmoid function at a point
 */
double sigPrime(double activation){
    return activation*(1-activation);
}



/*
 vector utilities
 */

/*
 computes the dot product of two vectors
 */
double dot_product(double *vector1, double *vector2,int vector_size){
    double sum = 0;
    for(int i=0; i<vector_size;i++){
        sum+= vector1[i] * vector2[i];
    }
    return sum;
}

/*
    multiply vector by a scalar
 */
double *scalar_times_vector(double scalar, double *vector,int vector_size){
    double *newVector = malloc(sizeof(double)*vector_size);
    for(int i=0; i<vector_size; i++){
        newVector[i] = vector[i]*scalar;
    }
    return newVector;
}

/*
    subtract vector2 from vector1 entrywise
    note- could make this an add vector function and pass it negative values
 */
double *vector_sub_vector(double *vector1, double *vector2, int vector_size){
    double *newVector = malloc(sizeof(double)*vector_size);
    for(int i=0; i<vector_size; i++){
        newVector[i] = vector1[i]-vector2[i];
    }
    return newVector;
}

/*
    multply two vectors entry by entry
 */
double *vector_entrywise_mult_vector(double *vector1, double *vector2, int vector_size){
    double *newVector = malloc(sizeof(double)*vector_size);
    for(int i=0; i<vector_size; i++){
        newVector[i] = vector1[i] * vector2[i];
        
    }
    return newVector;
}


