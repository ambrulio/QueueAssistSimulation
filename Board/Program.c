#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <stddef.h>
#include <pthread.h>                   /* This ert_main.c example uses printf/fflush */
#include "Controller.h"                /* Model's header file */
#include "rtwtypes.h"
#include "distanceSensor.h"
#include <wiringPi.h>
#include <assert.h>


void mainInit();
void initializeSocket(const char *argv[]);
void bindAndListen();
void acceptClient();
void processValues(char* st);
char** str_split(char* a_str, const char a_delim);

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "Controller.h"                /* Model's header file */
#include "rtwtypes.h"

static RT_MODEL_Controller_T Controller_M_;
static RT_MODEL_Controller_T *const Controller_M = &Controller_M_;/* Real-time model */
static P_Controller_T Controller_P = {
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S7>/Delay1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S7>/Delay2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S7>/Delay3'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S7>/Delay4'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S7>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Constant2'
                                        */
  30.0,                                /* Expression: 30
                                        * Referenced by: '<S5>/Constant3'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Delay1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Delay2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Delay3'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Delay4'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S6>/Constant'
                                        */
  200.0,                               /* Expression: 200
                                        * Referenced by: '<S5>/Constant4'
                                        */
  10.0,                                /* Expression: 10
                                        * Referenced by: '<S5>/Constant'
                                        */
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S5>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Constant'
                                        */
  4000.0,                              /* Expression: 4000
                                        * Referenced by: '<S3>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Constant2'
                                        */
  200.0,                               /* Expression: 200
                                        * Referenced by: '<S3>/Constant3'
                                        */
  1U,                                  /* Computed Parameter: Delay1_DelayLength
                                        * Referenced by: '<S7>/Delay1'
                                        */
  1U,                                  /* Computed Parameter: Delay2_DelayLength
                                        * Referenced by: '<S7>/Delay2'
                                        */
  1U,                                  /* Computed Parameter: Delay3_DelayLength
                                        * Referenced by: '<S7>/Delay3'
                                        */
  1U,                                  /* Computed Parameter: Delay4_DelayLength
                                        * Referenced by: '<S7>/Delay4'
                                        */
  1U,                                  /* Computed Parameter: Delay1_DelayLength_h
                                        * Referenced by: '<S6>/Delay1'
                                        */
  1U,                                  /* Computed Parameter: Delay2_DelayLength_c
                                        * Referenced by: '<S6>/Delay2'
                                        */
  1U,                                  /* Computed Parameter: Delay3_DelayLength_l
                                        * Referenced by: '<S6>/Delay3'
                                        */
  1U                                   /* Computed Parameter: Delay4_DelayLength_b
                                        * Referenced by: '<S6>/Delay4'
                                        */
};                                     /* Modifiable parameters */

static DW_Controller_T Controller_DW;  /* Observable states */

/* '<Root>/distance' */
static real_T Controller_U_distance;

/* '<Root>/speed ' */
static real_T Controller_U_speed;

/* '<Root>/gp_pressed' */
static boolean_T Controller_U_gp_pressed;

/* '<Root>/bp_pressed' */
static boolean_T Controller_U_bp_pressed;

/* '<Root>/switch_on' */
static boolean_T Controller_U_switch_on;

/* '<Root>/output_led' */
static int32_T Controller_Y_output_led;

/* '<Root>/break_cmd' */
static boolean_T Controller_Y_break_cmd;

/* '<Root>/go_cmd' */
static boolean_T Controller_Y_go_cmd;

//VARIABILI DA NON TOCCARE

int sockfd, newsockfd, portno, clilen;
   char buffer[128];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
int ERROR_BIT = 0 ;
char** tokens;
static boolean_T OverrunFlag = false;

int main( int argc, const char* argv[] )
{


    printf("Initializing the socket..\n");
    initializeSocket(argv);
    bindAndListen();
 while(1){  
    printf("Initializing data..\n");
    mainInit();
    acceptClient();
    Controller_initialize(Controller_M, &Controller_U_distance,&Controller_U_speed,&Controller_U_gp_pressed,&Controller_U_bp_pressed, &Controller_U_switch_on, &Controller_Y_output_led, &Controller_Y_break_cmd, &Controller_Y_go_cmd);
    printf("Processing...\n"); 
while(1){
	if(OverrunFlag){
			printf("Setting error status to overrun..");
			rtmSetErrorStatus(Controller_M, "Overrun");
			return;
	}
	OverrunFlag = true;


       bzero(buffer,128);
       n = read( newsockfd,buffer,128 );
       
       if (n < 0)
          {
          printf("ERROR reading from socket\n");
	  OverrunFlag = false;
          ERROR_BIT = -1;
	   break;
          }          
       //printf("Received msg: %s\n",buffer);
	processValues(buffer);
	
	//read distance
	setupRaspberry();
	Controller_U_distance = (real_T) getCM();
	//printf("Passsing > %f %u %u %u \n",Controller_U_speed,Controller_U_go_pedal,Controller_U_break_pedal, *(&Controller_U_switch_g)); 
	    Controller_step(Controller_M, Controller_U_distance,Controller_U_speed,Controller_U_gp_pressed,Controller_U_bp_pressed, Controller_U_switch_on, &Controller_Y_output_led, &Controller_Y_break_cmd, &Controller_Y_go_cmd);
	//Controller_step(Controller_M, Controller_U_distance ,Controller_U_speed,Controller_U_go_pedal,Controller_U_break_pedal, *(&Controller_U_switch_g), &Controller_Y_output_led);
		

//printf("LED integer : %d   ",Controller_Y_output_led);
	char outputval[10];
	sprintf(outputval, "%d", Controller_Y_output_led);
	printf("Distance: %f cm ¤ Led %u\r",Controller_U_distance, Controller_Y_output_led);
        fflush(stdout);
	n = write(newsockfd,outputval,1);
       if (n < 0)
          {
           printf("ERROR reading from socket\n");
	   OverrunFlag = false;
           ERROR_BIT = -1;
	   break;
	   
          }
          OverrunFlag = false;
	usleep(10000);
   }
	printf("Rebooting..\n");
 }
    return 0;
}
/*
void initializeSocket(char *argv[]){
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0)
      {
      perror("ERROR opening socket");
      exit(1);
      }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 5001;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
}*/


void processValues(char *st){
	
char *ch;


ch = strtok(st,",");

      
  // printf("Processando velocità %s\n", ch);
   Controller_U_speed = atof(ch);
   ch = strtok(NULL,",");

//printf("Processando go pedal %s\n", ch);
   int gpint = atoi(ch);
   if(gpint==0)
	Controller_U_gp_pressed = false;
   else
	Controller_U_gp_pressed = true;
   
ch = strtok(NULL,",");

//printf("Processando break pedal %s\n", ch);
   int bpint = atoi(ch);
   if(bpint==0)
	Controller_U_bp_pressed = false;
   else
	Controller_U_bp_pressed = true;
   ch = strtok(NULL,",");

//printf("Processando switch %s\n", ch);

int swint = atoi(ch);
   if(swint==0)
	Controller_U_switch_on = false;
   else
	Controller_U_switch_on = true;
  

	


}
void mainInit(){
	
	Controller_M -> ModelData.defaultParam = &Controller_P;
	Controller_M -> ModelData.dwork = &Controller_DW;
	wiringPiSetup(); 


    
}

void bindAndListen(){
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	      {
	      perror("ERROR on binding");
	      exit(1);
	      }
	   
	   listen(sockfd,2);
	   clilen = sizeof(cli_addr);
	   
	
	   
}

void acceptClient(){
   	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
   	if (newsockfd < 0){
      		perror("ERROR on accept");
	      exit(1);
	      }
	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	    if(setsockopt(newsockfd, SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout))<0) 
		perror("Errore in fase di setting delle impostazioni");
	
	    if(setsockopt(newsockfd, SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout))<0) 
		perror("Errore in fase di setting delle impostazioni");

}

void initializeSocket(const char *argv[]){
/* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0)
      {
      perror("ERROR opening socket");
      exit(1);
      }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = atoi(argv[1]);
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
}



   
   
   
   
   
