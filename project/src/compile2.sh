gcc train_nn.c -lm -g -o train
gcc test_nn.c -lm -g -o test
gcc train_nn_cilk.c -lm -g -fcilkplus -o cilk
