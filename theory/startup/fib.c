/*
 * fib.c
 *
 *  Created on: Sep 25, 2017
 *      Author: ethantanen
 */

#include <stdio.h>;

int main(){

	fibMom(5);
}

int fibMom(int count){

		fib(1,1,count);

}

int fib(int cur1, int cur2,int count){


	if(count == 0){
		return 0;
	}

	printf("%i \n",cur1);

	count--;
	fib(cur2,cur1+cur2, count);
}
