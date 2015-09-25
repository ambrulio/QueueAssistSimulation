#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;   
char buffer[128];
int SPEED, GO_PEDAL, BREAK_PEDAL, SWITCH;
int PREVIOUS_LED ;
int LED ; 
void initializeClient(char *argv[]);
void sendMessage();
void charGetter();
void printScenario();
void closeSafely();
void setSocketOptions();

pthread_t ui_thread;

int main(int argc, char *argv[])
{  
   
   if (argc <3) {
      fprintf(stderr,"usage %s <hostname> <port>\n", argv[0]);
      exit(0);
   }
   initializeClient(argv); 
   
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
   {
      perror("ERROR connecting");
      exit(1);
   }
   
   setSocketOptions();
   
   printf("********************************************************************************************\n\n");
   
   if(pthread_create(&ui_thread, NULL, charGetter, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
   
   printScenario();
   
   while(1){
        
       sendMessage();
       //printf("checking differences between prev %d and new %d\r\n", PREVIOUS_LED,LED);
       /*if(LED != PREVIOUS_LED){
           printScenario();
       }*/
       printScenario();
       //PREVIOUS_LED = LED ; //switch
       usleep(300000);
       
    }
	
	printf("ByE\n");
	return 0;
       
}

void setSocketOptions(){
    struct timeval timeout;      
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                sizeof(timeout)) < 0)
        printf("setsockopt failed\n");

    if (setsockopt (sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
                sizeof(timeout)) < 0)
        printf("setsockopt failed\n");
}

void charGetter(){
int c;
  /* use system call to make terminal send all keystrokes directly to stdin */
  system ("/bin/stty raw");
  while((c=getchar())!= '.') {
    /* type a period to break out of the loop, since CTRL-D won't work raw */
    //printf("got %c\r\n",c);
    
    if(c=='a'){
        //accelerate
        if(SPEED < 250){
            SPEED = SPEED +5;
        }
    }else if(c=='s'){
        //slow down
        if(SPEED > 0){
            SPEED = SPEED -5;
        }
    }else if(c=='x'){
        //pressed break pedal
        if(BREAK_PEDAL==0){
            BREAK_PEDAL=1;
        }else{
            BREAK_PEDAL = 0;
        }
    }else if(c=='z'){
        //pressed go pedal
        if(GO_PEDAL==0){
            GO_PEDAL=1;
        }else{
            GO_PEDAL = 0;
        }
    }else if(c=='o'){
        //pressed switch
        if(SWITCH==0){
        SWITCH=1;
        }else{
        SWITCH=0;
        }
    }
    //putchar(c);
    usleep(100000);
  }
  /* use system call to set terminal behaviour to more normal behaviour */
  system ("/bin/stty cooked");
}
void printScenario(){
    char bp[8] = "";
    char gp[8] = "";
    char qa[4] = "" ;
    char status[15]  ="";
    
    if(SWITCH!=0){
        strcpy(qa,  "ON ");
    }else{
        strcpy(qa,  "OFF");

    }
    if(GO_PEDAL != 0){
       strcpy(gp,  "PRESSED");

    }else{
        strcpy(gp,  "------");

    }
    if(BREAK_PEDAL != 0){
       strcpy(bp,  "PRESSED");

    }else{
        strcpy(bp, "-------");
    }
   switch (LED) {
        case 0:
           strcpy(status,  "OFF     ");
           
           break;
        case 1:
           strcpy(status,  "ON      ");
           break;
        case 2:
           strcpy(status,  "BREAK   ");
           break;
        case 3:
            strcpy(status, "GO      ");
            break;
        case 4:
            strcpy(status, "DISABLED");
            break;
        case 5:    
            strcpy(status, "ERROR   ");
            break;
    }

    
    printf("********* LED [ %s ] | SPEED %.3d km/h | QA [ %s ] | GP [ %s ] | BP [ %s ] *********\r", status, SPEED, qa,gp,bp);
    fflush(stdout);
    
}


/*void printScenario(){
    char bp[8] = "";
    char gp[8] = "";
    char qa[4] = "" ;
    char status[15]  ="";
    
    if(SWITCH!=0){
        strcpy(qa,  "ON");
    }else{
        strcpy(qa,  "OFF");

    }
    if(GO_PEDAL != 0){
       strcpy(gp,  "PRESSED");

    }else{
        strcpy(gp,  "-");

    }
    if(BREAK_PEDAL != 0){
       strcpy(bp,  "PRESSED");

    }else{
        strcpy(bp,  "-");
    }
    switch (LED) {
        case 0:
           strcpy(status,  "OFF");
           
           break;
        case 1:
           strcpy(status,  "ON");
           break;
        case 2:
           strcpy(status,  "BREAKING");
           break;
        case 3:
            strcpy(status,  "ACCELERATING");
            break;
        case 4:
            strcpy(status,  "DISABLED");
            break;
        case 5:    
            strcpy(status, "ERROR");
            break;
    }

    
    printf("********* LED [%s] *** Speed: %d km/h | QA [%s] | GP [%s] | BP [%s] *********\r", status, SPEED, qa,gp,bp);
    fflush(stdout);
    
}*/

void printLEDStatus(){
char status[15] ="";

   switch (LED) {
        case 0:
           strcpy(status,  "OFF");
           
           break;
        case 1:
           strcpy(status,  "ON");
           break;
        case 2:
           strcpy(status,  "BREAKING");
           break;
        case 3:
            strcpy(status,  "ACCELERATING");
            break;
        case 4:
            strcpy(status,  "DISABLED");
            break;
        case 5:    
            strcpy(status, "ERROR");
            break;
    }
     printf("*** LED [%s] *** \r\n",status);
    

}

void sendMessage(){
        bzero(buffer,128);
//       fgets(buffer,255,stdin);
       sprintf(buffer, "%d,%d,%d,%d", SPEED, GO_PEDAL,BREAK_PEDAL,SWITCH);     
       /* Send message to the server */
       //printf("Sto inviando messaggio %s, il buffer ha lunghezza %lu\n", buffer, strlen(buffer));
       n = write(sockfd, buffer, strlen(buffer));
       
       if (n < 0)
       {
          //printf("ERROR writing to socket\n");
          closeSafely();
          
       }
       
       // Now read server response 
       bzero(buffer,128);
       n = read(sockfd, buffer, 128);
       
       if (n < 0)
       {
          //printf("ERROR reading from socket\n");
          closeSafely();
          
       }
       //printf("Converting %s in number \n", buffer);
       LED = atoi(buffer);
       
       
  }
  
void initializeClient(char *argv[]){
    portno = atoi(argv[2]);
   
   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0)
   {
      perror("ERROR opening socket");
      exit(1);
   }
   server = gethostbyname(argv[1]);
   
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);

    SPEED = 0 ;
    GO_PEDAL = 0;
    BREAK_PEDAL = 0;
    SWITCH = 0;

}

void closeSafely(){
    system ("/bin/stty cooked"); //avoid problem of terminal
    pthread_exit(ui_thread);
    //printf("Closing..");
    LED=5;
    printScenario();
    printf("\r\nPremi un tasto per terminare\r\n");
    getchar();
    exit(-1);


}