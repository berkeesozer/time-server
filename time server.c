#include<stdio.h>
#include<string.h>    // for strlen
#include<sys/socket.h>
#include<arpa/inet.h> // for inet_addr
#include<unistd.h>    // for write
#include <time.h> // time library to get time/date datas
#include <string.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
    #define PORT_NUMBER 60017 // the port number that will be used by program
    
    
    int socket_desc , new_socket , c;
    struct sockaddr_in server , client;// structures for all syscalls and functions that deal with internet addresses. 
    char *message;
     
    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);//create an unbound socket in a communications domain, and return a file descriptor that can be used in later function calls that operate on sockets.
    if (socket_desc == -1)//If an error occurs while creating socket
    {
        puts("Could not create socket");//write a line or string to the output stream
        return 1;
}
     
    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons(PORT_NUMBER); // defining port number
     
    // Bind
    if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("Bind failed");//write a line or string to the output stream
        return 1;
    }
    puts("Socket is binded");//write a line or string to the output stream
     
    // Listen
    listen(socket_desc, 3);
     
    // Accept and incoming connection
    puts("Waiting for incoming connections...");//write a line or string to the output stream
    
    c = sizeof(struct sockaddr_in);
    while( new_socket = 
           accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c) )
    {
    	puts("connection accepted");//write a line or string to the output stream
        message = "Hello client, I received your connection. See you\n\n"; //this is a welcome message for client
        write(new_socket, message, strlen(message)); //write function to display that message
        
        
        
        char client_message[5000];
        while(1)

        {
	    if ((recv(new_socket,client_message,sizeof(client_message),0)) < 0 ) //if the server doesn't get input this function returns less than zero 
	    {
		write(new_socket, "receiving input failed", strlen("receiving input failed"));	//displaying the error
            }
	    else
	    {
	    
	    	
	    	time_t t = time(NULL);//time_t represents the clock time as an integer which is a part of the calendar time. 
	    	struct tm tm = *localtime(&t);//struct tm holds the date and time
	        if(strcmp(client_message,"GET_TIME\r\n")==0)//check client_message equal to GET_TIME
	        {	

  			char time[50];//create char array with length
  			time[0]='\0';//initialize a string to empty string
  			char hour[10];//create char array with length
  			sprintf(hour,"%d",tm.tm_hour);//convert int to string
  			char min[10];//create char array with length
  			sprintf(min,"%d",tm.tm_min);//convert int to string
  			char sec[10];//create char array with length
  			
  			sprintf(sec,"%d",tm.tm_sec);//convert int to string
  			strcat(time,hour);//concatenates the first parameter and second param.result is stored in firstp. 
  			strcat(time,":");//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time,min);//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time,":");//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time,sec);//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time,"\n");//concatenates the first parameter and second param.result is stored in firstp.
  			
  			
			//write nbyte bytes from the buffer pointed to by buf to the file associated with the open file descriptor, fildes.
		    	write(new_socket,time,strlen(time));
	        }else if(strcmp(client_message,"GET_DATE\r\n")==0){//check client_message equal to GET_TIME
	        
	        	char date[50];//create char array with length
  			date[0]='\0';//initialize a string to empty string
  			char day[20];//create char array with length
  			sprintf(day,"%d",tm.tm_mday);//convert int to string
  			char mon[20];//create char array with length
  			sprintf(mon,"%d",tm.tm_mon+1);//convert int to string
  			char year[20];//create char array with length
  			sprintf(year,"%d",tm.tm_year+1900);//convert int to string
  			
  			strcat(date,day);//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(date,".");//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(date,mon);//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(date,".");//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(date,year);//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(date,"\n");//concatenates the first parameter and second param.result is stored in firstp.
  			//write nbyte bytes from the buffer pointed to by buf to the file associated with the open file descriptor, fildes.
  			write(new_socket,date,strlen(date));
	        }else if(strcmp(client_message,"GET_TIME_DATE\r\n")==0){//check client_message equal to GET_TIME_DATE
	        
	        	char time_date[50];//create char array with length
  			time_date[0]='\0';//initialize a string to empty string
  			char hour[10];//create char array with length
  			sprintf(hour,"%d",tm.tm_hour);//convert int to string
  			char min[10];//create char array with length
  			sprintf(min,"%d",tm.tm_min);//convert int to string
  			char sec[10];//create char array with length
  			
  			sprintf(sec,"%d",tm.tm_sec);//convert int to string
  			strcat(time_date,hour);//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time_date,":");//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time_date,min);//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time_date,":");//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time_date,sec);//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time_date,", ");//concatenates the first parameter and second param.result is stored in firstp.
  			
  			
  			char day[20];//create char array with length
  			sprintf(day,"%d",tm.tm_mday);//convert int to string
  			char mon[20];//create char array with length
  			sprintf(mon,"%d",tm.tm_mon+1);//convert int to string
  			char year[20];//create char array with length
  			sprintf(year,"%d",tm.tm_year+1900);//convert int to string
  			
  			strcat(time_date,day);//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time_date,".");//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time_date,mon);//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time_date,".");//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time_date,year);//concatenates the first parameter and second param.result is stored in firstp.
  			strcat(time_date,"\n");//concatenates the first parameter and second param.result is stored in firstp.
  			
  			//write nbyte bytes from the buffer pointed to by buf to the file associated with the open file descriptor, fildes.
  			write(new_socket,time_date,strlen(time_date));
  			
  			
	        }else if(strcmp(client_message,"GET_TIME_ZONE\r\n")==0){//check client_message equal to GET_TIME_ZONE
	        
	        	char result[10];//create char array with length
	        	result[0]='\0';//initialize a string to empty string
	        	char zone[10];//create char array with length
	        	sprintf(result,"%s",tm.tm_zone);//convert int to string
	        	strcat(result,zone);//concatenates the first parameter and second param.result is stored in firstp.
	        	strcat(result,":00");
	        	strcat(result,"\n");//concatenates the first parameter and second param.result is stored in firstp.
	        	
	        	
	        	//write nbyte bytes from the buffer pointed to by buf to the file associated with the open file descriptor, fildes.
	        	write(new_socket,result,strlen(result));
	        
	        
	        }else if(strcmp(client_message,"GET_DAY_OF_WEEK\r\n")==0){//check client_message equal to GET_DAY_OF_WEEK
	        	char result[10];//create char array with length
	        	result[0]='\0';
	        	char wday[10];//create char array with length
	        	
	        	
	        	int day_of_week=tm.tm_wday;// day of the week, range 0 to 6
	        	if(day_of_week==1) strcat(wday,"Monday");//concatenates the first parameter and second param.result is stored in firstp.
	        	else if(day_of_week==1) strcat(wday,"Monday");//concatenates the first parameter and second param.result is stored in firstp.
	        	else if(day_of_week==2) strcat(wday,"Tuesday");//concatenates the first parameter and second param.result is stored in firstp.
	        	else if(day_of_week==3) strcat(wday,"Wednesday");//concatenates the first parameter and second param.result is stored in firstp.
	        	else if(day_of_week==4) strcat(wday,"Thursday");//concatenates the first parameter and second param.result is stored in firstp.
	        	else if(day_of_week==5) strcat(wday,"Friday");//concatenates the first parameter and second param.result is stored in firstp.
	        	else if(day_of_week==6) strcat(wday,"Saturday");//concatenates the first parameter and second param.result is stored in firstp.
	        	else if(day_of_week==7) strcat(wday,"Sunday");//concatenates the first parameter and second param.result is stored in firstp.
	        	strcat(result,wday);//concatenates the first parameter and second param.result is stored in firstp.
	        	strcat(result,"\n");//concatenates the first parameter and second param.result is stored in firstp.
	        	//write nbyte bytes from the buffer pointed to by buf to the file associated with the open file descriptor, fildes.
	        	write(new_socket,result,strlen(result));
	        
	        }else if (strcmp(client_message,"CLOSE_SERVER\r\n")==0){//check client_message equal to CLOSE_SERVER
	        	write(new_socket,"GOOD BYE\n",strlen("GOOD BYE\n"));//if it is equal to CLOSE_SERVER, type GOOD BYE and shutdown the socket
	        	close(new_socket); //closing the server
	        }else{//check if its an invalid command (other than the available commands)
	        	write(new_socket,"INCORRECT REQUEST\n",strlen("INCORRECT REQUEST\n"));//type INCORRECT REQUEST
	        }
	        
	        
	    }
	    //this function is very important for receiving inputs from the client.
	    //because it clears the buffer from the previous command/input.
	    //it prevents them to overlap, so without executing this function at the every loop step,it wouldn't run properly.
	    bzero(client_message,2000); 
        }
        
    }
    	    

    return 0;
}

