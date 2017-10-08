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
#include <limits.h>

#include <string.h>

/*
Instantiate network
 */
int main(int args, char **argv){
    
    
    NeuralNet *net = malloc(sizeof(NeuralNet));
    net_init(1,10,1,net);
    
    
    double in1[1] = {1};
    double target1[1] = {0};
    
    double in2[2] = {0,0};
    double target2[2] = {0,0};
    
    
    for(int i=0; i<1000000; i++){
        
        fastforward(net,in1);
    
        calculateLittleDeltas(net, target1);
        calculateBigDeltas(net);
    }

    
    print_net(net);
    free(net);
    
    
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
        double sigprime = sigPrime(output);
        
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
        double sigprime = sigPrime(output);
        
        net->outputLayer[i].activation = activation;
        net->outputLayer[i].output = output;
        net->outputLayer[i].sigPrime = sigprime;
    }

    
    return;
}

/**********************************
 BACKPROPAGATION RELATED SHTUFF
 *********************************/

//TODO: targets should be in nerual net

void calculateLittleDeltas(NeuralNet *net, double *target){
    
    //little d for output layer is sigprime(nodes output) * (output-target)
    
    double outputLittleD[net->numOut];
    
    //compute little for every node in output layer
    for(int i=0; i<net->numOut; i++){
        Node node = net->outputLayer[i];
        double littled = node.sigPrime * (node.output-target[i]);
        net->outputLayer[i].littleDelta = littled;
        outputLittleD[i] = littled;
    }
    
    //little d for a hidden layer is sigprime(nodes output) * (dotproduct(weights,error) for next layer)
    //the * is entrywise multplication
    for(int i=0; i<net->numHid; i++){
        
        double weights[net->numOut];
        
        //get weights that connect node to nodes in (current layer + 1)
        for(int k=0; k<net->numOut; k++){
            weights[i]= net->hid_out[i*net->numOut];
        }
        
        double e = dot_product(weights,outputLittleD,net->numOut);
        double sigprime = net->hiddenLayer[i].sigPrime;
        
        net->hiddenLayer[i].littleDelta =sigprime * e;
    }
    
    return;
}

void calculateBigDeltas(NeuralNet *net){
    //learning rate * O * little delta
    double learningRate = 1;

    
    
    //cycle through hidden layer
    for(int i=0; i<net->numHid; i++){
        
        //cycle through unot layer
        for(int j=0; j<net->numIn; j++){
            
            
            Node nodeH = net->hiddenLayer[i];
            Node nodeI = net->inputLayer[j];
            
            
            double bigDelta = learningRate * nodeH.littleDelta * nodeI.output;
            
            double currentWeightVal = net->in_hid[i+j];
        
            net->in_hid[i+j] = currentWeightVal - bigDelta;
        
        }
        
    }
    
    for(int i=0; i<net->numOut; i++){
        for(int j=0; j<net->numHid; j++){
            
            Node nodeO = net->outputLayer[i];
            Node nodeH = net->hiddenLayer[j];
            
            double bigDelta = learningRate * nodeO.littleDelta * nodeH.output;
            
            double currentWeightVal = net->hid_out[i+j];
            
            net->hid_out[i+j] = currentWeightVal - bigDelta;
            
            
        }
    }
    
    
    return;
    
    
}








/***************************************
 UTILITIES DAWG
 **************************************/



void print_net(NeuralNet *_net){
    
    NeuralNet net = *_net;
    
    printf("\n HIDDEN LAYER: \n");
    
    for(int i=0; i<net.numHid; i++){
        Node node = net.hiddenLayer[i];
        printf("Activaton: %f, Output: %f, SigPrime: %f, LittleDelta: %f\n",node.activation,node.output,node.sigPrime,node.littleDelta);
    }
    
    printf("\n OUTPUT LAYER: \n");
    
    for(int i=0; i<net.numOut; i++){
        Node node = net.outputLayer[i];
        printf("Activaton: %f, Output: %f, SigPrime: %f, LittleDelta: %f\n",node.activation,node.output,node.sigPrime,node.littleDelta);
    }
    return;
}

void print_weights(NeuralNet *_net){
    
    NeuralNet net = *_net;
    
    double *weightsIH = net.in_hid;
    double *weightsHO = net.hid_out;
    
    printf("\nWEIGHTS I->H\n");
    
    for(int i=0; i<net.totWIH; i++){
        printf("%f\n",weightsIH[i]);
    }
    
    printf("\nWEIGHTS H->O\n");
    
    for(int i=0; i<net.totWHO; i++){
        printf("%f\n",weightsHO[i]);
    }
    
    free(weightsIH);
    free(weightsHO);
    
    return;
    
}


/*
 Normalizing -> (x - Xmin)/(Xmax-Xmin) where x is an element in array X
 */
void normalize(double *input, int size){
    
    double min = INT_MAX;
    double max = 0;
    
    for(int i=0; i<size; i++){
        if(input[i] < min)
            min = input[i];
        if(input[i] > max)
            max = input[i];
    }
    
    printf("min: %f, max: %f\n\n",min,max);
    
    for(int i=0; i<size; i++){
        double temp = input[i];
        input[i] = (temp - min)/(max-min);
    }
    
    return;
}


/*
 calculates sigmoid from activation
 */
double sigmoid(double activation){
    return 1/(1+exp(-1*activation));
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


