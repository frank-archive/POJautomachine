#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE (125)
#define ITEM_SIZE (10)

static char item[ITEM_SIZE][SIZE];

static char * poj_1001(char dst[], char src[], int src_width, int n);
static char * move_leftward (char dst[], char src[], int n);
static char * add_to(char dst[], char src[]);

int main(int argc, char* argv[]){
	int i,j,m,n,b;
	int point;
	char number[5];
	char buf[SIZE];
	char str_temp[7];
	int n_temp;
	while(2 == scanf("%s%d", str_temp, &n_temp)){
            point = 0;
	    for(i=0,j=0; i<6; i++){
	        if(str_temp[i] != '.'){
                    number[j++] = str_temp[i];
	        }
		else{
                    point = i;
		}
            }
	    point = 5 - point;
	    point = n_temp * point;
	    point = SIZE - point -1;

	    poj_1001(buf,number,5,n_temp);
            
	    m=0;
	    n=SIZE-1;
	    for (i=0;i<SIZE;i++){
		    if ( '0' != buf[i] ){
                         m = i;
			 break;
		    }
	    }
	    
	    for (i=SIZE-1; i>=0; i--){
                  if ( '0' != buf[i] ){
                        n = i;
			break;
		  }
	    }
	    b=1;
	    for (i=0;i<SIZE;i++){
                if('0' != buf[i]){
                    b=0;
		}
	    }

	    if (b){
                printf("0");
	    }
	    else {
	        if (m>point){
                    printf(".");
                    for (i=point+1; i<=n; i++){
                        printf ("%c", buf[i]);
		    }
	        }
	        else if (m<=point && point<n){
                    for (i=m;i<=point;i++){
                        printf ("%c", buf[i]);
	  	    }
                    printf (".");
                    for (i=point+1;i<=n;i++){
                        printf ("%c", buf[i]);
		    }
	        }
	        else{
                    for (i=m;i<=point;i++){
                        printf ("%c", buf[i]);
		    }
	        }
	    }
            printf ("\n");
	}
	return 0;
}

static char * poj_1001 (char dst[], char src[], int src_width, int n){
	int i,j,k;
	int carry, bitsum;
	char buf[SIZE];
	char aux[SIZE];
	memset(item, '0', ITEM_SIZE*SIZE);
	memcpy(item[1]+SIZE-src_width, src, src_width);
	bitsum = 0;
	for (i=2;i<=9;i++){
	    carry = 0;
            for (j=SIZE-1; j>=0; j--){
		k = j - (SIZE - src_width);
		if (0<=k){
		    bitsum = i * (src[k] - '0') + carry;
                    item[i][j] = '0' + (bitsum % 10);
		    carry = bitsum / 10;
		}
		else{
			item[i][j] = '0' + carry;
			break;
		}
	    }
	}
	
	if (0 == n){
	    memset (dst, '0', SIZE);
            memset (dst + SIZE - 1, '1', 1);
	}
	else if (1 == n){
            memcpy (dst, item[1], SIZE);
	}
	else{
            memcpy (dst, item[1], SIZE);
	    for (i=0; i<n-1; i++){
                memset (aux, '0', SIZE);
                for (j=0; j<SIZE; j++){
                    move_leftward (buf, item[dst[j]-'0'], SIZE-1-j);
		    add_to (aux, buf);
		}
		memcpy (dst, aux, SIZE);
	    }
	}
	return dst;
}

static char * add_to (char dst[], char src[]){
    int carry, bitsum;
    int i;
    carry = 0;
    bitsum = 0;
    for (i=SIZE-1; i>=0; i--){
        bitsum = carry + (dst[i] - '0') + (src[i] - '0');
	dst[i] = ('0' + bitsum % 10);
	carry = bitsum / 10;
    }
    return dst;
}

static char * move_leftward (char dst[], char src[], int n){
    int i;
    int tail;
    tail = SIZE-1-n;
    memset (dst, '0', SIZE); 
    for (i=0; i<=tail; i++){
        dst[i] = src[i+n];
    }
    return dst;
}